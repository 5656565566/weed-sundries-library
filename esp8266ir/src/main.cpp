#include <Arduino.h>
#include <TaskScheduler.h>

#include "easy_webserver.h"
#include "eeprom_help.h"
#include "sync_time.h"

WebServerManager webServer;

void printACModels()
{
    Serial.println("支持的空调型号:");
    Serial.println("1. Airton (艾尔顿)          2. Airwell (艾威尔)        3. Amcor (安科)         4. Argo (阿尔戈)");
    Serial.println("5. Bosch 144 (博世 144)    6. Coolix (酷力士)        7. Corona (科罗娜)      8. Daikin 128 (大金 128)");
    Serial.println("9. Daikin 152 (大金 152)    10. Daikin 160 (大金 160)  11. Daikin 176 (大金 176)  12. Daikin 216 (大金 216)");
    Serial.println("13. Daikin 2 (大金 2)      14. Daikin 64 (大金 64)    15. Delonghi (德龙)      16. Ecoclim (爱克利)");
    Serial.println("17. Electra (艾莱特)       18. Fujitsu (富士通)      19. Goodweather (好天气)   20. Gree (格力)");
    Serial.println("21. Haier (海尔)           22. Haier 160 (海尔 160)  23. Haier 176 (海尔 176)   24. Haier ACYRW02 (海尔 ACYRW02)");
    Serial.println("25. Hitachi (日立)         26. Kelon (科龙)          27. Kelvinator (凯尔文)   28. LG (乐金)");
    Serial.println("29. Midea (美的)           30. Mirage (米瑞吉)       31. Mitsubishi (三菱)     32. Mitsubishi Heavy 88 (三菱重工 88)");
    Serial.println("33. Mitsubishi Heavy 152 (三菱重工 152)  34. Neoclima (尼欧克)    35. Panasonic (松下)    36. Rhoss (瑞士)");
    Serial.println("37. Samsung (三星)         38. Sanyo (三洋)          39. Sharp (夏普)          40. TCL 112 (TCL 112)");
    Serial.println("41. Technibel (泰肯贝尔)   42. Teco (天际)           43. Toshiba (东芝)       44. Transcold (特朗科尔德)");
    Serial.println("45. Trotec 3550 (特罗特克 3550)  46. Truma (图鲁玛)      47. Vestel (维斯特尔)    48. Whirlpool (惠而浦)");
    Serial.println("49. York (约克)");
}

void receiveData()
{
    if (Serial.available() > 0)
    {
        String input = "";
        char incomingChar;

        while (Serial.available() > 0)
        {
            incomingChar = Serial.read();
            input += incomingChar;
        }

        Serial.println("Received: " + input);

        if (input == "TURN_ON")
        {
            Serial.println("Turning on the AC...");
        }
        else if (input == "TURN_OFF")
        {
            Serial.println("Turning off the AC...");
        }
        else if (input.startsWith("SET_TEMP"))
        {
            // "SET_TEMP=25"
            int temp = input.substring(9).toInt(); // 提取温度值
            Serial.println("Setting temperature to: " + String(temp));
        }
        else if (input == "RST")
        {

            clearEEPROM();

            write_admin_username("admin");
            write_admin_password("123456");

            ESP.restart();
        }
        else if (input == "LIST")
        {
            printACModels();
        }
        else if (input == "DEG")
        {
            Serial.println(read_wifi_ssid());
            Serial.println(read_wifi_password());
            Serial.println(read_admin_username());
            Serial.println(read_admin_password());
            Serial.println(read_ac_model());
            printACModels();
        }
        else
        {
            Serial.println("Unknown command.");
        }
    }
}

void wifi_reconnect()
{
    if (WiFi.status() != WL_CONNECTED)  // 如果WiFi未连接
    {
        if (read_wifi_ssid() != "")
        {
            WiFi.begin(read_wifi_ssid().c_str(), read_wifi_password().c_str());
            Serial.println("Attempting to reconnect to WiFi...");
        }
    }
}


Scheduler runner;
Task task1(1000 * 60, TASK_FOREVER, &loopsyncTime);
Task task2(5000, TASK_FOREVER, &wifi_reconnect);

void setup()
{
    Serial.begin(115200);
    webServer.begin();
    loopsyncTime();

    runner.addTask(task1);
    runner.addTask(task2);

    task1.enable();
    task2.enable();

}

void loop()
{
    webServer.handleClient();
    receiveData();
}
