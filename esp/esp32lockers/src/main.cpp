#include <TaskScheduler.h>

#include "const.h"
#include "door.h"
#include "task.h"
#include "card.h"
#include "peripheral.h"

Scheduler runner;

bool stop_play = false;

void debug()
{
    Preferences preferences;
    preferences.begin("sensor", false);

    float temp = preferences.getFloat("temp", 0);
    float humidity = preferences.getFloat("humidity", 0);
    bool iRSensor = preferences.getBool("iRSensor");

    Serial.println("Sensor Data:");
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.println("C");

    Serial.println("Sensor Data:");
    Serial.print("humidity: ");
    Serial.print(humidity);
    Serial.println("B");

    Serial.print("iRSensor Presence: ");
    Serial.println(iRSensor ? "No" : "Yes");

    preferences.end();
}

void play();

Task task1(1000, TASK_FOREVER, &loop_door);
Task task2(1000, TASK_FOREVER, &loop_display_tip);
Task task3(1000, TASK_FOREVER, &loop_mfrc);
Task task4(500, TASK_FOREVER, &readDHTSensorData);
Task task5(500, TASK_FOREVER, &readIRSensorData);
Task task6(2000, TASK_FOREVER, &debug);
Task task7(1, TASK_FOREVER, &play); // 定义播放任务，每 1ms 检查一次播放状态

int melody[] = {
    262, 262, 392, 392, 440, 440, 392, 0,
    349, 349, 330, 330, 294, 294, 262, 0,
    392, 392, 349, 349, 330, 330, 294, 0,
    392, 392, 349, 349, 330, 330, 294, 0,
    262, 262, 392, 392, 440, 440, 392, 0,
    349, 349, 330, 330, 294, 294, 262, 0};
int noteDurations[] = {4, 4, 4, 4, 4, 4, 2, 4,
                       4, 4, 4, 4, 4, 4, 2, 4,
                       4, 4, 4, 4, 4, 4, 2, 4,
                       4, 4, 4, 4, 4, 4, 2, 4,
                       4, 4, 4, 4, 4, 4, 2, 4,
                       4, 4, 4, 4, 4, 4, 2, 4};
int currentNote = 0;

void play()
{

    Preferences preferences;
    preferences.begin("state", false);

    bool play = preferences.getBool("play", false);
    preferences.end();

    if (!play && stop_play){
        return;
    }
    else{
        stop_play = false;
    }

    if (!play)
    {
        noTone(BEEP); // 暂停
        stop_play = true;
        return;
    }

    if (currentNote < sizeof(melody) / sizeof(melody[0]))
    {
        int noteDuration = 1000 / noteDurations[currentNote];
        if (melody[currentNote] > 0)
        {
            tone(BEEP, melody[currentNote], noteDuration); // 播放当前音符
        }
        else
        {
            noTone(BEEP); // 暂停
        }
        task7.delay(noteDuration * 1.3); // 按比例延长音符时长
        currentNote++;                   // 切换到下一个音符
    }
    else
    {
        currentNote = 0; // 重置到第一音符以重复旋律
    }
}

void setup()
{
    Serial.begin(115200); // 调试使用
    init_door();
    init_keypad();
    init_display();
    init_mfrc();

    runner.init();
    init_peripheral();
    pinMode(BEEP, OUTPUT);

    runner.addTask(task1);
    runner.addTask(task2);
    runner.addTask(task3);
    runner.addTask(task4);
    runner.addTask(task5);
    runner.addTask(task6);
    runner.addTask(task7);

    task1.enable();
    task2.enable();
    task3.enable();
    task4.enable();
    task5.enable();
    task6.enable();
    task7.enable();

    runner.startNow();
}

void loop()
{
    loop_keypad();
    loop_display();
    runner.execute();
}
