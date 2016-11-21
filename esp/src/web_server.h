/*
 * Web server that is initiated and permits users and the cloud to trigger certain
 * actions from the outside by just starting a GET request with a specific URL
 *
 * More Info and documentation:
 * http://www.appfruits.com/2016/11/printrbot-simple-2016-commstack-explained
 *
 * Copyright (c) 2016 Printrbot Inc.
 * Author: Mick Balaban, Phillip Schuster
 * https://github.com/Printrbot/Printrhub
 *
 * Developed in cooperation with Phillip Schuster (@appfruits) from appfruits.com
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

#ifndef WEB_SERVER_H
#define WEB_SERVER_H
#include <ESP8266WiFi.h>
//#include <WebSocketsServer.h>
#include <FS.h>
#include <ESPAsyncWebServer.h>

class WebServer {
 public:
  WebServer();
  void begin();
  void update();

 private:
  bool validateAuthentication(AsyncWebServerRequest *request);
  void addOptionsRequest(String path);
};

#endif
