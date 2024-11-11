#include "easy_webserver.h"
#include "peripheral.h"

WebServerManager::WebServerManager() : server(80) {}

String html_tip(String msg)
{
    String page = "<html><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'>";
    page += "<title>智能台灯控制面板</title>";
    page += "<style>";
    page += "body { font-family: Arial, sans-serif; background-color: #f0f0f0; text-align: center; }";
    page += "h1 { color: #333; }";
    page += "button { padding: 10px 20px; margin: 10px; background-color: #4CAF50; color: white; border: none; border-radius: 5px; }";
    page += "button:hover { background-color: #45a049; }";
    page += ".container { max-width: 600px; margin: auto; padding: 20px; background-color: #fff; border-radius: 10px; box-shadow: 0px 0px 10px rgba(0, 0, 0, 0.1); }";
    page += "</style></head><body>";
    page += "<div class='container'>";
    page += "<h2>" + msg + "</h2>";
    page += "<button onclick=\"location.href='/'\">返回控制面板</button>";
    page += "</div></body></html>";
    return page;
}

void WebServerManager::begin()
{
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected!");
    Serial.println(WiFi.localIP());

    server.on("/", [this]()
              { handleRoot(); });
    server.on("/on", [this]()
              { handleOn(); });
    server.on("/off", [this]()
              { handleOff(); });
    server.on("/brightness", [this]()
              { handleBrightness(); });
    server.on("/motion", [this]()
              { handleMotionControl(); });
    server.on("/set-timer", [this]()
              { handleSetTimer(); });
    server.on("/stats", [this]()
              { handleStats(); });
    server.on("/temp", [this]()
              { handleTemp(); });

    server.begin();
    Serial.println("Server started");
}

void WebServerManager::handleClient()
{
    server.handleClient();
}

bool WebServerManager::isAuthenticated()
{
    if (!server.authenticate(username.c_str(), password.c_str()))
    {
        server.requestAuthentication();
        return false;
    }
    return true;
}

void WebServerManager::handleRoot()
{
    if (!isAuthenticated())
    {
        return;
    }

    String page = "<html><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>智能台灯控制面板</title>";
    page += "<style>";
    page += "body { font-family: Arial, sans-serif; background-color: #f0f0f0; text-align: center; }";
    page += "h1 { color: #333; }";
    page += "button { padding: 10px 20px; margin: 10px; background-color: #4CAF50; color: white; border: none; border-radius: 5px; }";
    page += "button:hover { background-color: #45a049; }";
    page += ".container { max-width: 600px; margin: auto; padding: 20px; background-color: #fff; border-radius: 10px; box-shadow: 0px 0px 10px rgba(0, 0, 0, 0.1); }";
    page += "</style></head><body><div class='container'>";
    page += "<h1>智能台灯控制面板</h1>";
    page += "<button onclick=\"location.href='/on'\">开灯</button>";
    page += "<button onclick=\"location.href='/off'\">关灯</button>";
    page += "<button onclick=\"location.href='/brightness'\">亮度自适应</button>";
    page += "<button onclick=\"location.href='/motion'\">人离灯关</button>";
    page += "<button onclick=\"showTimerModal()\">设置定时开关</button>";
    page += "<button onclick=\"location.href='/stats'\">查看统计</button>";
    page += "<button onclick=\"location.href='/temp'\">环境温度</button>";

    page += "<div id='timerModal' style='display:none; position:fixed; top:50%; left:50%; transform:translate(-50%, -50%); background-color:white; padding:20px; box-shadow:0px 0px 10px rgba(0,0,0,0.2);'>";
    page += "<h2>设置定时开关</h2>";
    page += "<input type='time' id='onTime' placeholder='开灯时间'><br>开灯时间<br>";
    page += "<input type='time' id='offTime' placeholder='关灯时间'><br>关灯时间<br>";
    page += "<button onclick='setTimer()'>保存</button>";
    page += "<button onclick='closeTimerModal()'>取消</button>";
    page += "</div>";

    page += "<script>";
    page += "function showTimerModal() { document.getElementById('timerModal').style.display = 'block'; }";
    page += "function closeTimerModal() { document.getElementById('timerModal').style.display = 'none'; }";
    page += "function setTimer() {";
    page += "var onTime = document.getElementById('onTime').value;";
    page += "var offTime = document.getElementById('offTime').value;";
    page += "location.href = '/set-timer?on=' + onTime + '&off=' + offTime;";
    page += "closeTimerModal(); }";
    page += "</script>";

    page += "</div></body></html>";
    server.send(200, "text/html", page);
}

void WebServerManager::handleOn()
{
    if (!isAuthenticated())
        return;
    SetLed(true);
    Serial.println("LED On...");
    add_new_record(0);
    server.send(200, "text/html", html_tip("开灯"));
}

void WebServerManager::handleOff()
{
    if (!isAuthenticated())
        return;
    SetLed(false);
    Serial.println("LED Off...");
    add_new_record(1);
    server.send(200, "text/html", html_tip("关灯"));
}

void WebServerManager::handleBrightness()
{
    if (!isAuthenticated())
        return;
    // 调用亮度自适应功能
    Serial.println("Brightness auto-adjust enabled.");

    bool last = SetSwitch("brightness");

    if (last)
    {
        server.send(200, "text/html", html_tip("亮度自适应已关闭"));
    }
    else
    {
        server.send(200, "text/html", html_tip("亮度自适应已开启"));
    }
}

void WebServerManager::handleMotionControl()
{
    if (!isAuthenticated())
        return;
    // 调用人离灯关功能
    Serial.println("Motion-based control enabled.");

    bool last = SetSwitch("human");

    if (last)
    {
        server.send(200, "text/html", html_tip("人离灯关已关闭"));
    }
    else
    {
        server.send(200, "text/html", html_tip("人离灯关已开启"));
    }
}

void WebServerManager::handleSetTimer()
{
    if (!isAuthenticated())
        return;
    if (server.hasArg("on") && server.hasArg("off"))
    {
        String onTime = server.arg("on");
        String offTime = server.arg("off");

        Preferences preferences;
        preferences.begin("switch", false);

        preferences.putString("onTime", onTime);
        preferences.putString("offTime", offTime);

        preferences.end();

        // 设置定时器代码逻辑
        Serial.println("Timer set: ON at " + onTime + ", OFF at " + offTime);
        server.send(200, "text/html", html_tip("定时开关设置成功"));
    }
    else
    {
        server.send(400, "text/html", html_tip("未输入有效时间"));
    }
}

void WebServerManager::handleStats()
{
    if (!isAuthenticated())
        return;
    // 跳转到统计页面或数据获取逻辑
    Serial.println("Viewing stats...");
    server.send(200, "text/html", read_record());
}

void WebServerManager::handleTemp()
{
    if (!isAuthenticated())
        return;
    // 跳转到统计页面或数据获取逻辑
    Serial.println("Temp stats...");

    Preferences preferences;
    preferences.begin("sensor", false);
    float temp = preferences.getFloat("temp");
    preferences.end();

    String tempMsg = "当前环境温度: ";
    tempMsg += String(temp);
    tempMsg += "°C";

    server.send(200, "text/html", html_tip(tempMsg));
}
