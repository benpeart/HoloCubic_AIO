#ifndef APP_SERVER_H
#define APP_SERVER_H

#include "sys/interface.h"
#define SERVER_APP_NAME "WebServer"

#ifdef ESP8266
#include <ESP8266WiFi.h>      // Built-in
#include <ESP8266WiFiMulti.h> // Built-in
#include <ESP8266WebServer.h> // Built-in
#include <ESP8266mDNS.h>
extern ESP8266WebServer server;
#else
#include <WiFi.h>      // Built-in
#include <WiFiMulti.h> // When we need to store multiple WiFi network connection information on the ESP8266 board, we can use the ESP8266WiFiMulti library to achieve this.
#include <WebServer.h> // https://github.com/Pedroalbuquerque/ESP32WebServer
#include <ESPmDNS.h>
#include <DNSServer.h>
#include <HTTPClient.h>
extern WebServer server;
#endif

extern APP_OBJ server_app;

#endif