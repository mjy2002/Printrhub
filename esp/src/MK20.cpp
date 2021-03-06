/*
 * Custom CommStack implementation acts as a wrapper to separate some CommStack
 * details from the rest of the application code. Mostly holds convenience functions
 *
 * More Info and documentation:
 * http://www.appfruits.com/2016/11/printrbot-simple-2016-commstack-explained
 *
 * Copyright (c) 2016 Printrbot Inc.
 * Author: Phillip Schuster
 * https://github.com/Printrbot/Printrhub
 *
 * Developed in cooperation by Phillip Schuster (@appfruits) from appfruits.com
 * http://www.appfruits.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "MK20.h"
#include "Application.h"
#include "arm_kinetis_debug.h"
#include <ArduinoJson.h>

MK20::MK20(Stream *port, CommStackDelegate *delegate) :
	CommStack(port, delegate) {
  _numTries = 0;
  _isAlive = false;
  _timeout;
}

MK20::~MK20() {

}

void MK20::reset() {
  pinMode(MK20_RESET_PIN, OUTPUT);
  digitalWrite(MK20_RESET_PIN, LOW);
  delay(200);
  digitalWrite(MK20_RESET_PIN, HIGH);
  pinMode(MK20_RESET_PIN, INPUT);
}

bool MK20::writeFirmware(File &firmware_file) {
  EventLogger::log("Reseting Teensy - the hard way");

  //Reset MK20
  reset();

  EventLogger::log("Resetting Teensy done");
  delay(200);

  EventLogger::log("Flashing");

  // flash here
  ARMKinetisDebug target(MK20_SWD_CLK, MK20_SWD_IO, ARMDebug::LOG_NORMAL);
  uint32_t idcode;
  if (target.begin() && target.getIDCODE(idcode)) {
	char result[128];
	EventLogger::log("Debug Port Detected: %d", idcode);
  }
  delay(200);
  ESP.wdtFeed();

  if (!target.detect()) {
	EventLogger::log("Detect failed");
	return false;
  }
  delay(200);
  ESP.wdtFeed();

  if (!target.reset()) {
	EventLogger::log("Reset failed");
	EventLogger::log("Trying to unlock device");
	digitalWrite(MK20_RESET_PIN, LOW);
	target.flashMassErase();
	digitalWrite(MK20_RESET_PIN, HIGH);
	EventLogger::log("Unlock successful. Powercycle device and try again");
	return false;
  } else {
	EventLogger::log("Device reset complete");
  }
  delay(200);
  ESP.wdtFeed();

  if (!target.debugHalt()) {
	EventLogger::log("Debug Halt failed");
  } else {
	EventLogger::log("Debug halt complete");
  }
  delay(200);
  ESP.wdtFeed();

  if (!target.initK20()) {
	EventLogger::log("MK20 Init failed");
  } else {
	EventLogger::log("MK20 initialized");
  }
  delay(200);
  ESP.wdtFeed();

  ARMKinetisDebug::Flasher programmer(target);
  if (!programmer.installFirmware(&firmware_file)) {
	EventLogger::log("Failed to flash");

	//Sometimes, it's just the soft reset that fails after flashing, so do a hard reset and hope for the best
	reset();
	return false;
  }

  EventLogger::log("Resetting Chip");
  reset();

  // end flash
  EventLogger::log("Flashing MK20 complete");

  Application.sendPulse(5, 1);

  return true;
}

bool MK20::updateFirmware(String localFilePath) {
  File firmware_file = SPIFFS.open(localFilePath.c_str(), "r");
  if (!firmware_file) {
	EventLogger::log("Failed to open firmware file %s", localFilePath.c_str());
  } else {
	//Flash MK20 with latest (default) firmware.
	bool result = writeFirmware(firmware_file);
	if (!result) {
	  Application.sendPulse(5, 2);
	  EventLogger::log("Failed to write firmware to MK20");
	} else {
	  Application.sendPulse(5, 3);
	  EventLogger::log("MK20 firmware flashed successfully");
	}

	firmware_file.close();

	return result;
  }

  return false;
}

void MK20::showUpdateFirmwareNotification() {
  if (Application.getFirmwareUpdateInfo() == NULL) return;

  StaticJsonBuffer<500> jsonBuffer;
  JsonObject &updateInfo = jsonBuffer.createObject();
  updateInfo["version"] = "0.13";
  updateInfo["buildnr"] = Application.getFirmwareUpdateInfo()->buildnr;

  //Ask MK20 to show the notification to the user and we are finished here
  requestTask(TaskID::ShowFirmwareUpdateNotification, updateInfo);

  //Wait a bit until the screen has been updated
  delay(200);
}

bool MK20::openSDFileForWrite(String targetFilePath, size_t bytesToSend, bool showUI, Compression compression) {
  StaticJsonBuffer<500> jsonBuffer;
  JsonObject &fileInfo = jsonBuffer.createObject();
  fileInfo["localFilePath"] = targetFilePath;
  fileInfo["showUI"] = showUI;
  fileInfo["fileSize"] = bytesToSend;
  fileInfo["compression"] = (uint8_t) compression;

  //Ask MK20 to show the notification to the user and we are finished here
  requestTask(TaskID::FileOpenForWrite, fileInfo);

  return true;
}

void MK20::showFirmwareInProgressNotification() {
  //If MK20 is alive it will show that the firmware update is in progress
  requestTask(TaskID::ShowFirmwareUpdateInProgress);
}

bool MK20::sendSDFileData(uint8_t *data, size_t size) {
  Application.getMK20Stack()->requestTask(TaskID::FileSaveData, size, data);

  return true;
}

bool MK20::closeSDFile() {
  Application.getMK20Stack()->requestTask(TaskID::FileClose);

  return true;
}

void MK20::showWiFiInfo() {
  Application.getMK20Stack()->requestTask(TaskID::ShowWiFiInfo);
}
