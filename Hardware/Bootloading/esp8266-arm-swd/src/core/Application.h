/*
 * Printrhub -- your best friend in your lab
 * http://www.appfruits.com/littlehelper
 *
 * This software is part of the firmware running Little Helper. You may use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies of the Software
 * but you must include this copyright notice and this permission in all copies or
 * substantial portions of the Software.
 *
 * Appfruits invests time and resources to make this open source. Please support us
 * and the open-source hardware initiative.
 *
 * Copyright 2014-2015 Phillip Schuster (@appfruits)
 * http://www.appfruits.com
 *
 * MIT-License
 */

#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "Arduino.h"
#include "StackArray.h"
#include <WiFiClient.h>
#include <ESP8266WiFi.h>

// Pin definitions
const int LED_PIN = 0;

#define STRINGIZE_DETAIL(x) #x
#define STRINGIZE(x) STRINGIZE_DETAIL(x)
#define logError(msg) (__FILE__ " line " STRINGIZE(__LINE__) ": " msg ": ")

#define LOG(m) Serial.print(logError(m));Serial.println(m)
#define LOG_VALUE(m,v) Serial.print(logError(m));Serial.println(v);

class Mode;

class ApplicationClass
{
#pragma mark Constructor
public:
	ApplicationClass();
	~ApplicationClass();

#pragma mark Application Flow
	void loop();
	void setup();
	void pushMode(Mode* mode);
	Mode* currentMode() { return _currentMode; };

#pragma mark Time Management
	float getDeltaTime();

#pragma mark Member Variables
private:
	bool _firstModeLoop;
	Mode *_nextMode;
	Mode *_currentMode;
	unsigned long _lastTime;
	float _deltaTime;
};

extern ApplicationClass Application;

#endif //_APPLICATION_H_
