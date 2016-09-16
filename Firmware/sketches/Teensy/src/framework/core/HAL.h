//
// Created by Phillip Schuster on 28.07.16.
//

#ifndef TEENSY_HAL_H
#define TEENSY_HAL_H

#define PRINTRHUB_REV_01    //Uncomment if building the code for Printrhub Rev 0.1
//#define PRINTRHUB_REV_02  //Uncomment if building the code for Printrhub Rev 0.2
//#define PRINTRHUB_REV_03  //Uncomment if building the code for Printrhub Rev 0.3

#ifdef PRINTRHUB_REV_01

//General setup
#define LED_PIN 21

//The display also uses hardware SPI, plus #9 & #10
#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST 0
#define TFT_MOSI 11
#define TFT_MISO 12
#define TFT_SCLK 13
#define TFT_TOUCH_SENSE_PIN 17
#define TFT_BACKLIGHT_PWM 22
#define TFT_RESET 29

//Commstack
#define COMMSTACK_DATAFLOW_PIN 33
#define COMMSTACK_DATALOSS_MARKER_PIN 3
#define COMMSTACK_BAUDRATE 1728000

//Debug
#define DebugSerial Serial

#endif

#ifdef PRINTRHUB_REV_02

//General setup
#define LED_PIN 21

//The display also uses hardware SPI, plus #9 & #10
#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST 0
#define TFT_MOSI 11
#define TFT_MISO 12
#define TFT_SCLK 13
#define TFT_TOUCH_SENSE_PIN 17
#define TFT_BACKLIGHT_PWM 22
#define TFT_RESET 29

//Commstack
#define COMMSTACK_DATAFLOW_PIN 31
#define COMMSTACK_DATALOSS_MARKER_PIN 3
#define COMMSTACK_BAUDRATE 1728000

//Debug
#define DEBUG_USE_SOFTWARE_SERIAL
#define DEBUG_SOFTWARE_SERIAL_RX_PIN 14
#define DEBUG_SOFTWARE_SERIAL_TX_PIN 2
#define DebugSerial DebugSerial

#endif

#ifdef PRINTRHUB_REV_03

//General setup
#define LED_PIN 21

//The display also uses hardware SPI, plus #9 & #10
#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST 0
#define TFT_MOSI 11
#define TFT_MISO 12
#define TFT_SCLK 13
#define TFT_TOUCH_SENSE_PIN 17
#define TFT_BACKLIGHT_PWM 22
#define TFT_RESET 23

//Commstack
#define COMMSTACK_DATAFLOW_PIN 24
#define COMMSTACK_DATALOSS_MARKER_PIN 3
#define COMMSTACK_BAUDRATE 1728000

//Debug
#define DEBUG_USE_SOFTWARE_SERIAL
#define DEBUG_SOFTWARE_SERIAL_RX_PIN 14
#define DEBUG_SOFTWARE_SERIAL_TX_PIN 2
#define DebugSerial DebugSerial

#endif



#endif //TEENSY_HAL_H
