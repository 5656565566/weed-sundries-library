#ifndef EASY_WEBSERVER_H
#define EASY_WEBSERVER_H

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>

#include "const.h"
#include "data.h"

class WebServerManager {
private:
    WebServer server; // 内置Web服务器实例
    const String username = "admin"; // 默认用户名
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
    void handleOn();
    void handleOff();
    void handleBrightness();
    void handleMotionControl();
    void handleSetTimer();
    void handleStats();
    void handleTemp();

    // 验证用户的身份
    bool isAuthenticated();
};

#endif // EASY_WEBSERVER_H