#ifndef EASY_WEBSERVER_H
#define EASY_WEBSERVER_H

#include <Arduino.h>
#include <ESP8266WebServer.h>

#include "eeprom_help.h"
#include "ap_wifi_config.h"
#include "aircondition.h"
#include "sync_time.h"

class WebServerManager
{
private:
    ESP8266WebServer server;          // 内置Web服务器实例
    const String username = "admin";  // 默认用户名
    const String password = "123456"; // 默认密码

public:
    WebServerManager();

    // 初始化WiFi和Web服务器
    void begin();

    // 处理Web请求
    void handleClient();

private:
    // 处理网页请求
    void handleRoot();

    // 处理控件请求
    void handleTurnOn();
    void handleTurnOff();
    void handleSetTemperature();
    void handleSetFanSpeed();
    void handleSetMode();
    void handleSetLight();
    void handleSetSleep();
    void handleSetTurbo();
    void handleSetEco();
    void handleSetTimer();
    void setTimerPage();
    void changePassword();
    void setPasswordPage();

    void handleConnect();
    void connectWifiPage();
    void setACModel();
    void resetDevice();
    void setAPMode();
    void disconnectWifi();

    // 验证用户的身份
    bool isAuthenticated();
};

#endif