#include "easy_webserver.h"

const char *indexPage = R"(
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>空调遥控器</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #e8f4f8;
            margin: 0;
            padding: 0;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 180vh;
        }

        .container {
            background-color: #ffffff;
            padding: 30px;
            border-radius: 15px;
            box-shadow: 0 4px 12px rgba(0, 0, 0, 0.1);
            text-align: center;
            width: 100%;
            max-width: 400px;
        }

        h1 {
            font-size: 24px;
            color: #333;
            margin-bottom: 20px;
        }

        button {
            background-color: #4CAF50;
            color: white;
            border: none;
            padding: 15px 30px;
            margin: 10px;
            border-radius: 5px;
            cursor: pointer;
            font-size: 18px;
            transition: background-color 0.3s;
        }

        button:hover {
            background-color: #45a049;
        }

        select, input[type="number"] {
            padding: 8px;
            font-size: 16px;
            margin: 10px 0;
            width: 100%;
            border-radius: 5px;
            border: 1px solid #ddd;
            box-sizing: border-box;
        }

        input[type="submit"] {
            background-color: #4CAF50;
            color: white;
            border: none;
            padding: 10px 20px;
            border-radius: 5px;
            cursor: pointer;
            font-size: 16px;
            width: 100%;
            margin-top: 10px;
            transition: background-color 0.3s;
        }

        input[type="submit"]:hover {
            background-color: #45a049;
        }

        form {
            margin-bottom: 15px;
        }

        label {
            display: block;
            text-align: left;
            margin-bottom: 5px;
            font-size: 16px;
            color: #555;
        }

        h2 {
            font-size: 20px;
            color: #333;
            margin-top: 30px;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>空调遥控器</h1>
        <button onclick="location.href='/turnOn'">空调开</button>
        <button onclick="location.href='/turnOff'">空调关</button>

        <h2>设置</h2>
        
        <!-- 设置温度 -->
        <form action='/setTemperature' method='get'>
            <label for='temperature'>温度: </label>
            <input type='number' id='temperature' name='temperature' min='16' max='30' value='24'>
            <input type='submit' value='设置温度'>
        </form>

        <!-- 设置风速 -->
        <form action='/setFanSpeed' method='get'>
            <label for='fanSpeed'>风速: </label>
            <select name='fanSpeed'>
                <option value='auto'>自动</option>
                <option value='low'>低</option>
                <option value='medium'>中</option>
                <option value='high'>高</option>
            </select>
            <input type='submit' value='设置风速'>
        </form>

        <!-- 设置模式 -->
        <form action='/setMode' method='get'>
            <label for='mode'>模式(可能不对): </label>
            <select name='mode'>
                <option value='auto'>自动</option>
                <option value='cool'>制冷 / 模式1</option>
                <option value='dry'>除湿 / 模式2</option>
                <option value='fan'>风扇 / 模式3 </option>
                <option value='heat'>制热 / 模式4 </option>
            </select>
            <input type='submit' value='设置模式'>
        </form>

        <!-- 设置其他功能 -->
        <form action='/setLight' method='get'>
            <input type='submit' value='空调LED 开/关'>
        </form>
        <form action='/setSleep' method='get'>
            <input type='submit' value='睡眠模式'>
        </form>
        <form action='/setTurbo' method='get'>
            <input type='submit' value='强劲模式'>
        </form>
        <form action='/setEco' method='get'>
            <input type='submit' value='环保模式'>
        </form>
        <form action='/setTimer' method='get'>
            <input type='submit' value='定时设置'>
        </form>
		<form action='/setPasswordPage' method='get'>
            <input type='submit' value='修改密码'>
        </form>
		<form action='/connectWifiPage' method='get'>
            <input type='submit' value='重连WIFI'>
        </form>
        <form action='/disconnectWifi' method='get'>
            <input type='submit' value='删除WIFI AP 模式'>
        </form>

        <!-- 选择空调型号 -->
        <form action='/setACModel' method='get'>
            <label for='acModel'>选择空调型号: </label>
            <select name='acModel'>
                <option value='Gree'>格力</option>
                <option value='Haier'>海尔</option>
                <option value='Haier160'>海尔160</option>
                <option value='Haier176'>海尔176</option>
                <option value='HaierACYRW02'>海尔ACYRW02</option>
                <option value='Midea'>美的</option>
            </select>
            <input type='submit' value='选择型号'>
        </form>
    </div>
</body>
</html>
)";

const char *timerPage = R"(
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>定时器设置</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #f4f4f9;
            margin: 0;
            padding: 0;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
        }

        .container {
            background-color: #ffffff;
            padding: 30px;
            border-radius: 15px;
            box-shadow: 0 4px 12px rgba(0, 0, 0, 0.1);
            text-align: center;
            width: 100%;
            max-width: 400px;
        }

        h1 {
            font-size: 24px;
            color: #333;
            margin-bottom: 20px;
        }

        label {
            display: block;
            font-size: 16px;
            color: #555;
            margin-bottom: 8px;
        }

        input[type="time"], input[type="number"], select {
            width: 100%;
            padding: 10px;
            margin: 10px 0;
            border-radius: 5px;
            border: 1px solid #ddd;
            box-sizing: border-box;
            font-size: 16px;
        }

        input[type="submit"] {
            background-color: #4CAF50;
            color: white;
            border: none;
            padding: 10px 20px;
            border-radius: 5px;
            cursor: pointer;
            font-size: 16px;
            width: 100%;
            margin-top: 20px;
            transition: background-color 0.3s;
        }

        input[type="submit"]:hover {
            background-color: #45a049;
        }

        .back-link {
            text-decoration: none;
            color: #007BFF;
            font-size: 16px;
            margin-top: 20px;
            display: block;
        }
    </style>
    <script>
        // 计算时间并更新分钟输入框
        function calculateDuration() {
            var timeInput = document.getElementById('timer');
            var timeValue = timeInput.value;
            if (!timeValue) return;

            // 获取时间的小时和分钟
            var [hours, minutes] = timeValue.split(':').map(Number);

            // 将时间转换为总分钟数
            var totalMinutes = hours * 60 + minutes;

            // 限制最大值为 24 * 60
            totalMinutes = Math.min(totalMinutes, 24 * 60);

            // 设置分钟输入框的值
            document.getElementById('duration').value = totalMinutes;
        }

        // 监听时间输入框变化
        document.addEventListener('DOMContentLoaded', function() {
            document.getElementById('timer').addEventListener('change', calculateDuration);
        });
    </script>
</head>
<body>
    <div class="container">
        <h1>定时器设置</h1>
        <form action="/setTimer" method="get">
            <label for="timer">定时开关时间:</label>
            <input type="time" id="timer" name="timer" required>

            <label for="duration">定时运行时长（分钟）:</label>
            <input type="number" id="duration" name="duration" min="1" max="1440" value="60" required>

            <input type="submit" value="设置定时器">
        </form>
        <a href="/" class="back-link">返回首页</a>
    </div>
</body>
</html>
)";

const char *passwordPage = R"(
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>修改密码</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #f4f4f9;
            margin: 0;
            padding: 0;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
        }

        .container {
            background-color: #ffffff;
            padding: 30px;
            border-radius: 15px;
            box-shadow: 0 4px 12px rgba(0, 0, 0, 0.1);
            text-align: center;
            width: 100%;
            max-width: 400px;
        }

        h1 {
            font-size: 24px;
            color: #333;
            margin-bottom: 20px;
        }

        label {
            display: block;
            font-size: 16px;
            color: #555;
            margin-bottom: 8px;
        }

        input[type="password"] {
            width: 100%;
            padding: 10px;
            margin: 10px 0;
            border-radius: 5px;
            border: 1px solid #ddd;
            box-sizing: border-box;
            font-size: 16px;
        }

        input[type="submit"] {
            background-color: #4CAF50;
            color: white;
            border: none;
            padding: 10px 20px;
            border-radius: 5px;
            cursor: pointer;
            font-size: 16px;
            width: 100%;
            margin-top: 20px;
            transition: background-color 0.3s;
        }

        input[type="submit"]:hover {
            background-color: #45a049;
        }

        .back-link {
            text-decoration: none;
            color: #007BFF;
            font-size: 16px;
            margin-top: 20px;
            display: block;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>修改密码</h1>
        <form action="/changePassword" method="post">
            <label for="newPassword">新密码:</label>
            <input type="password" id="newPassword" name="newPassword" required>

            <label for="confirmPassword">确认新密码:</label>
            <input type="password" id="confirmPassword" name="confirmPassword" required>

            <input type="submit" value="提交修改">
        </form>
        <a href="/" class="back-link">返回首页</a>
    </div>
</body>
</html>
)";

bool ap_mode = false;

WebServerManager::WebServerManager() : server(80) {}
AirConditionerController airConditionerController = AirConditionerController(D2);

String html_tip(String msg)
{
    String page = "<html><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'>";
    page += "<title>空调遥控器</title>";
    page += "<style>";
    page += "body { font-family: Arial, sans-serif; background-color: #f0f0f0; text-align: center; }";
    page += "h1 { color: #333; }";
    page += "button { padding: 10px 20px; margin: 10px; background-color: #4CAF50; color: white; border: none; border-radius: 5px; }";
    page += "button:hover { background-color: #45a049; }";
    page += ".container { max-width: 600px; margin: auto; padding: 20px; background-color: #fff; border-radius: 10px; box-shadow: 0px 0px 10px rgba(0, 0, 0, 0.1); }";
    page += "</style>";
    page += "<script>";
    page += "setTimeout(function() { window.location.href = '/'; }, 5000);"; // 58秒后自动返回
    page += "</script></head><body>";
    page += "<div class='container'>";
    page += "<h2>" + msg + "</h2>";
    page += "<button onclick=\"location.href='/'\">返回控制面板</button>";
    page += "</div></body></html>";

    return page;
}

void WebServerManager::begin()
{
    server.on("/", [this]()
              { handleRoot(); });
    server.on("/turnOn", [this]()
              { handleTurnOn(); });
    server.on("/turnOff", [this]()
              { handleTurnOff(); });
    server.on("/setTemperature", [this]()
              { handleSetTemperature(); });
    server.on("/setFanSpeed", [this]()
              { handleSetFanSpeed(); });
    server.on("/setMode", [this]()
              { handleSetMode(); });
    server.on("/setLight", [this]()
              { handleSetLight(); });
    server.on("/setSleep", [this]()
              { handleSetSleep(); });
    server.on("/setTurbo", [this]()
              { handleSetTurbo(); });
    server.on("/setEco", [this]()
              { handleSetEco(); });
    server.on("/setTimer", [this]()
              { handleSetTimer(); });
    server.on("/setTimerPage", [this]()
              { setTimerPage(); });
    server.on("/changePassword", [this]()
              { changePassword(); });
    server.on("/setPasswordPage", [this]()
              { setPasswordPage(); });
    server.on("/connectWifi", [this]()
              { handleConnect(); });
    server.on("/connectWifiPage", [this]()
              { connectWifiPage(); });
    server.on("/setACModel", [this]()
              { setACModel(); });
    server.on("/setAPMode", [this]()
              { setAPMode(); });
    server.on("/disconnectWifi", [this]()
              { disconnectWifi(); });

    server.on("/reset", [this]()
              { resetDevice(); });


    int wifi_connect_times = 0;

    if (read_wifi_ssid() == "")
    {
        init_wifi_ap(); // 启动 AP 使其组网
        Serial.println("AP start");
    }
    else
    {
        WiFi.begin(read_wifi_ssid().c_str(), read_wifi_password().c_str());
        Serial.print("Connecting to WiFi");
        while (WiFi.status() != WL_CONNECTED) // 如果WiFi未连接
        {
            if (wifi_connect_times > 20){
                init_wifi_ap();
                break;
            }
            wifi_connect_times += 1;
            delay(300);
            Serial.print(".");
        }
    }
    server.begin();
    Serial.println("Server started");

    airConditionerController.selectACModel(read_ac_model());
}

void WebServerManager::disconnectWifi()
{
    write_wifi_ssid("");
    write_wifi_password("");

    setAPMode();

    delay(2000);

    WiFi.disconnect();
    init_wifi_ap();
}

void WebServerManager::setAPMode()
{
    String html = "<html><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'>";
    html += "<style>";
    html += "body { font-family: 'Arial', sans-serif; background-color: #f7f7f7; margin: 0; padding: 0; display: flex; justify-content: center; align-items: center; height: 100vh; }";
    html += ".container { max-width: 600px; width: 100%; padding: 30px; background-color: #fff; border-radius: 12px; box-shadow: 0 4px 10px rgba(0, 0, 0, 0.1); text-align: center; }";
    html += "h1 { color: #4CAF50; font-size: 28px; margin-bottom: 20px; }";
    html += "p { font-size: 18px; color: #555; }";
    html += ".footer { font-size: 14px; color: #888; margin-top: 20px; }";
    html += "</style>";
    html += "</style>";
    html += "<script>";
    html += "setTimeout(function() { window.location.href = '/'; }, 5000);"; // 8秒后自动返回
    html += "</script></head><body>";
    html += "<div class='container'>";
    html += "<h1>AP 模式启动成功！</h1>";
    html += "<p>遥控器的内网 IP: 192.168.56.1 请确保设备连接到同一WiFi网络以进行控制。</p>";
    html += "<div class='footer'>若遇到问题，请检查网络设置。</div>";
    html += "</div></body></html>";

    ap_mode = true;

    server.send(200, "text/html", html);
}

void WebServerManager::setACModel()
{
    if (!isAuthenticated())
        return;

    String acModel = server.arg("acModel");

    write_ac_model(acModel);

    airConditionerController.selectACModel(acModel);
    server.send(200, "text/html", html_tip("切换空调型号成功"));
}

void WebServerManager::resetDevice()
{
    write_wifi_ssid("");
    write_wifi_password("");

    ESP.restart();
}

void WebServerManager::handleClient()
{
    server.handleClient();
}

bool WebServerManager::isAuthenticated()
{
    if (read_admin_username() == "")
    {
        write_admin_username(username);
    }

    if (read_admin_password() == "")
    {
        write_admin_password(password);
    }

    if (!server.authenticate(read_admin_username().c_str(), read_admin_password().c_str()))
    {
        server.requestAuthentication();
        return false;
    }
    return true;
}

String wifi_connect_page()
{
    String page = "<html><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'>";
    page += "<style>";
    page += "body { font-family: 'Arial', sans-serif; background-color: #f7f7f7; margin: 0; padding: 0; display: flex; justify-content: center; align-items: center; height: 100vh; }";
    page += ".container { max-width: 600px; width: 100%; padding: 30px; background-color: #fff; border-radius: 12px; box-shadow: 0 4px 10px rgba(0, 0, 0, 0.1); text-align: center; }";
    page += "h1 { color: #333; font-size: 28px; margin-bottom: 30px; }";
    page += "p { font-size: 18px; color: #555; margin-bottom: 20px; }";
    page += "form { display: inline-block; text-align: left; width: 100%; margin-top: 20px; }";
    page += "label { font-size: 16px; margin-bottom: 8px; display: block; }";
    page += "select, input[type='password'] { padding: 10px; margin-top: 10px; margin-bottom: 20px; border-radius: 5px; border: 1px solid #ccc; width: 100%; max-width: 350px; font-size: 16px; }";
    page += "input[type='submit'] { background-color: #4CAF50; color: white; border: none; border-radius: 5px; padding: 12px 24px; cursor: pointer; font-size: 18px; width: 100%; max-width: 350px; margin-top: 10px; }";
    page += "input[type='submit']:hover { background-color: #45a049; }";
    page += ".footer { font-size: 14px; color: #888; margin-top: 30px; }";
    page += "</style>";
    page += "<script>";
    page += "function backToControlPanel() { setTimeout(function() { location.href = '/'; }, 8000); }";
    page += "</script>";
    page += "</head><body><div class='container'>";
    page += "<h1>选择一个 WIFI 进行入网</h1>";

    // 获取WiFi列表
    int n = WiFi.scanNetworks();
    if (n == 0)
    {
        page += "<p>未找到 WIFI</p>";
    }
    else
    {
        page += "<form action='/connectWifi' method='get'>";
        page += "<div class='form-group'>";
        page += "<label for='ssid'>选择WiFi: </label>";
        page += "<select name='ssid'>";
        for (int i = 0; i < n; i++)
        {
            page += "<option value='" + WiFi.SSID(i) + "'>" + WiFi.SSID(i) + "</option>";
        }
        page += "</select>";
        page += "</div>";

        page += "<div class='form-group'>";
        page += "<label for='password'>密码: </label>";
        page += "<input type='password' name='password' placeholder='请输入WiFi密码'>";
        page += "</div>";

        page += "<input type='submit' value='连接'>";
        page += "</form>";

        page += "<form action='/setAPMode' method='get'>";
        page += "<input type='submit' value='AP 模式'>";
        page += "</form>";
    }

    page += "<div class='footer'>请在选择并输入密码后点击“连接”</div>";
    page += "</div></body></html>";

    return page;
}

void WebServerManager::handleRoot()
{
    if (read_wifi_ssid() == "" && !ap_mode)
    {
        server.send(200, "text/html", wifi_connect_page());
    }
    else if (!isAuthenticated())
    {
        return;
    }
    else
    {
        server.send(200, "text/html", indexPage);
    }
}

void WebServerManager::handleTurnOn()
{
    if (!isAuthenticated())
        return;
    airConditionerController.turnOn();
    server.send(200, "text/html", html_tip("空调开"));
}

void WebServerManager::handleTurnOff()
{
    if (!isAuthenticated())
        return;
    airConditionerController.turnOff();
    server.send(200, "text/html", html_tip("空调关"));
}

// 用户设置温度
void WebServerManager::handleSetTemperature()
{
    if (!isAuthenticated())
        return;

    int temperature = server.arg("temperature").toInt();
    airConditionerController.setTemperature(temperature);

    server.send(200, "text/html", html_tip("温度设置到" + String(temperature) + "摄氏度"));
}

// 用户设置风速
void WebServerManager::handleSetFanSpeed()
{
    if (!isAuthenticated())
        return;

    String fanSpeed = server.arg("fanSpeed");
    int fanSpeedLevel = 0;
    String fanSpeedName = "自动";

    if (fanSpeed == "low")
    {
        fanSpeedLevel = 1;
        String fanSpeedName = "低";
    }
    else if (fanSpeed == "medium")
    {
        fanSpeedLevel = 2;
        String fanSpeedName = "中";
    }
    else if (fanSpeed == "high")
    {
        fanSpeedLevel = 3;
        String fanSpeedName = "高";
    }

    airConditionerController.setFanSpeed(fanSpeedLevel);

    server.send(200, "text/html", html_tip("风速设置到" + fanSpeedName));
}

// 用户设置模式
void WebServerManager::handleSetMode()
{
    if (!isAuthenticated())
        return;

    String mode = server.arg("mode");
    int modeLevel = 0;

    if (mode == "cool")
    {
        modeLevel = 1;
    }
    else if (mode == "dry")
    {
        modeLevel = 2;
    }
    else if (mode == "fan")
    {
        modeLevel = 3;
    }
    else if (mode == "heat")
    {
        modeLevel = 3;
    }

    airConditionerController.setMode(modeLevel);

    server.send(200, "text/html", html_tip("模式设置到" + String(modeLevel)));
}

// 用户设置背光
void WebServerManager::handleSetLight()
{
    if (!isAuthenticated())
        return;

    bool light = airConditionerController.setLight();
    server.send(200, "text/html", html_tip(String(light ? "开启" : "关闭") + "空调数显"));
}

// 用户设置睡眠模式
void WebServerManager::handleSetSleep()
{
    if (!isAuthenticated())
        return;

    bool sleep = airConditionerController.setSleep();
    server.send(200, "text/html", html_tip(String(sleep ? "开启" : "关闭") + "睡眠模式"));
}

// 用户设置强劲模式
void WebServerManager::handleSetTurbo()
{
    if (!isAuthenticated())
        return;

    bool turbo = airConditionerController.setTurbo();
    server.send(200, "text/html", html_tip(String(turbo ? "开启" : "关闭") + "强劲模式"));
}

// 用户设置环保模式
void WebServerManager::handleSetEco()
{
    if (!isAuthenticated())
        return;

    bool econo = airConditionerController.setEcono();
    server.send(200, "text/html", html_tip(String(econo ? "开启" : "关闭") + "环保模式"));
}

// 用户设置定时器
void WebServerManager::handleSetTimer()
{
    if (!isAuthenticated())
        return;

    int duration = server.arg("duration").toInt();

    airConditionerController.setTimer(duration);
    server.send(200, "text/html", html_tip("定时设置" + String(duration) + "分钟"));
}

void WebServerManager::setTimerPage()
{
    if (!isAuthenticated())
        return;
    server.send(200, "text/html", timerPage);
}

void WebServerManager::changePassword()
{
    if (!isAuthenticated())
        return;

    String newPassword = server.arg("newPassword");
    String confirmPassword = server.arg("confirmPassword");

    if (newPassword == confirmPassword)
    {
        write_admin_password(newPassword);
    }
    server.send(200, "text/html", html_tip("新密码设置成功"));
}

void WebServerManager::setPasswordPage()
{
    if (!isAuthenticated())
        return;
    server.send(200, "text/html", passwordPage);
}

void WebServerManager::handleConnect()
{
    String ssid = server.arg("ssid");
    String password = server.arg("password");

    WiFi.begin(ssid.c_str(), password.c_str());

    unsigned long startAttemptTime = millis();
    while (WiFi.status() != WL_CONNECTED)
    {
        if (millis() - startAttemptTime >= 10000)
        { // 连接超时10秒
            String page = "<html><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'>";
            page += "<style>";
            page += "body { font-family: 'Arial', sans-serif; background-color: #f7f7f7; margin: 0; padding: 0; display: flex; justify-content: center; align-items: center; height: 100vh; }";
            page += ".container { max-width: 600px; width: 100%; padding: 30px; background-color: #fff; border-radius: 12px; box-shadow: 0 4px 10px rgba(0, 0, 0, 0.1); text-align: center; }";
            page += "h1 { color: #FF6347; font-size: 28px; margin-bottom: 20px; }";
            page += "p { font-size: 18px; color: #555; }";
            page += ".footer { font-size: 14px; color: #888; margin-top: 20px; }";
            page += "</style>";
            page += "<script>";
            page += "setTimeout(function() { window.location.href = '/'; }, 8000);"; // 8秒后自动返回
            page += "</script></head><body>";
            page += "<div class='container'>";
            page += "<h1>连接失败！</h1>";
            page += "<p>无法连接到所选WiFi，请检查SSID和密码。</p>";
            page += "<div class='footer'>请确保WiFi信息正确并重试 8s 后返回。</div>";
            page += "</div></body></html>";

            server.send(200, "text/html", page);
            return;
        }
        delay(500);
    }

    write_wifi_ssid(ssid);
    write_wifi_password(password);

    String html = "<html><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'>";
    html += "<style>";
    html += "body { font-family: 'Arial', sans-serif; background-color: #f7f7f7; margin: 0; padding: 0; display: flex; justify-content: center; align-items: center; height: 100vh; }";
    html += ".container { max-width: 600px; width: 100%; padding: 30px; background-color: #fff; border-radius: 12px; box-shadow: 0 4px 10px rgba(0, 0, 0, 0.1); text-align: center; }";
    html += "h1 { color: #4CAF50; font-size: 28px; margin-bottom: 20px; }";
    html += "p { font-size: 18px; color: #555; }";
    html += ".footer { font-size: 14px; color: #888; margin-top: 20px; }";
    html += "</style></head><body>";
    html += "<div class='container'>";
    html += "<h1>连接成功！</h1>";
    html += "<p>遥控器的内网 IP: " + WiFi.localIP().toString() + "，请确保设备连接到同一WiFi网络以进行控制。</p>";
    html += "<div class='footer'>若遇到问题，请检查网络设置。</div>";
    html += "</div></body></html>";

    server.send(200, "text/html", html);

    loopsyncTime();
    delay(2000);

    stop_wifi_ap();
    return;
}

void WebServerManager::connectWifiPage()
{
    if (!isAuthenticated())
        return;
    server.send(200, "text/html", wifi_connect_page());
}
