#include <Arduino.h>
#include <TaskScheduler.h>

#include "const.h"
#include "easy_webserver.h"
#include "task.h"
#include "data.h"
#include <peripheral.h>

WebServerManager webServer;

Scheduler runner;

void debug()
{
    Preferences preferences;
    preferences.begin("sensor", false);

    float temp = preferences.getFloat("temp");
    float light = preferences.getFloat("light");
    bool human = preferences.getBool("human");

    Serial.println("Sensor Data:");
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.println("C");

    Serial.print("Light Intensity: ");
    Serial.print(light);
    Serial.println(" lux");

    Serial.print("Human Presence: ");
    Serial.println(human ? "No" : "Yes");

    preferences.end();
}

Task task1(500, TASK_FOREVER, &readDS18B20SensorData);
Task task2(500, TASK_FOREVER, &readLightSensorData);
Task task3(1000 * 60, TASK_FOREVER, &loopsyncTime);

Task task4(500, TASK_FOREVER, &readHumanSensorData);
Task task5(100, TASK_FOREVER, &LedSetting);
Task task6(3000, TASK_FOREVER, &debug);

void setup()
{

    initSensor();

    runner.init();

    runner.addTask(task1);
    runner.addTask(task2);
    runner.addTask(task3);
    runner.addTask(task4);
    runner.addTask(task5);
    runner.addTask(task6);

    task1.enable();
    task2.enable();
    task3.enable();
    task4.enable();
    task5.enable();
    task6.enable();

    Serial.begin(115200);
    webServer.begin(); // 启动WiFi和Web服务器
    loopsyncTime();

    runner.startNow();

    pinMode(BTN, INPUT);
}

void loop()
{
    webServer.handleClient(); // 处理客户端请求
    runner.execute();
    LedSetting();
    if (!digitalRead(BTN))
    {
        Serial.println("BTN");
        delay(100);
        if (!digitalRead(BTN))
        {
            Serial.println("BTN");
            delay(100);
            SetLed(!GetLed());
        }
    }
    AutomaticLight();
    updataTime();
}
