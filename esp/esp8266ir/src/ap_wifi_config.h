#ifndef AP_WIFI_CONFIG_H
#define AP_WIFI_CONFIG_H

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <DNSServer.h>

void init_wifi_ap();
void stop_wifi_ap();
bool get_wifi_ap();

#endif