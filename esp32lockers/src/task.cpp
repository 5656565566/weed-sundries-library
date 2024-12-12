#include <Arduino.h>
#include <Keypad.h>
#include <Preferences.h>

#include "const.h"
#include "display.h"
#include "door.h"
#include "task.h"
#include "card.h"

Display display;

String tip = "";

class PasswordManager
{
private:
    char *buffer;     // 用于存储字符串的缓冲区
    size_t maxLength; // 最大字符串长度

public:
    size_t currentLength; // 当前字符串长度

    // 构造函数：初始化字符串管理器，设置最大长度
    PasswordManager(size_t maxLen)
    {
        maxLength = maxLen;
        buffer = new char[maxLength + 1]; // 分配空间，多1是为了存储结尾的'\0'
        currentLength = 0;
        buffer[0] = '\0'; // 初始化为空字符串
    }

    // 析构函数：释放内存
    ~PasswordManager()
    {
        delete[] buffer;
    }

    // 添加字符，成功返回 true，失败返回 false
    bool addChar(char c)
    {
        if (currentLength < maxLength)
        {
            buffer[currentLength++] = c;
            buffer[currentLength] = '\0'; // 添加 '\0' 作为字符串结尾
            return true;
        }
        else
        {
            return false; // 超过最大长度
        }
    }

    // 返回当前存储的字符串
    const char *getString()
    {
        return buffer;
    }

    // 清空字符串
    void clearString()
    {
        currentLength = 0;
        buffer[0] = '\0';
    }

    // 删除末尾的最后一个字符
    bool removeLastChar()
    {
        if (currentLength > 0)
        {
            currentLength--;
            buffer[currentLength] = '\0'; // 调整字符串结尾
            return true;
        }
        return false; // 字符串为空，无法删除
    }

    // 比较输入的字符串与存储的字符串是否一致
    bool compareString(const char *inputString)
    {
        return strcmp(buffer, inputString) == 0;
    }
};

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

PasswordManager stringManager(6);

int error = 0;

byte rowPins[ROWS] = {KEY_8, KEY_7, KEY_6, KEY_5};
byte colPins[COLS] = {KEY_4, KEY_3, KEY_2, KEY_1};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void keypadEvent(KeypadEvent key)
{
    switch (keypad.getState())
    {
    case PRESSED:

        Serial.println(key);

        if (key == '#')
        {
            stringManager.removeLastChar();
            break;
        }

        if (key == 'D')
        {
            Preferences preferences;
            preferences.begin("state", false);

            int lockers = preferences.getInt("lockers", 0);

            if (lockers == 7)
            {
                preferences.putInt("lockers", 0);
            }
            else
            {
                preferences.putInt("lockers", lockers + 1);
            }

            preferences.end();
        }
        if (key == 'C')
        {
            Preferences preferences;
            preferences.begin("state", false);
            error = 0;
            preferences.putBool("play", false);
            preferences.putInt("lockers", 0);
            preferences.end();
        }
        if (key == 'B')
        {
            save_card();
            break;
        }
        if (key == 'A')
        {
            Preferences preferences;
            preferences.begin("state", false);

            int lockers = preferences.getInt("lockers", 0);

            if (lockers == 0)
            {
                stringManager.clearString();
                open_door();
                preferences.putInt("lockers", 1);
            }

            if (lockers == 2)
            {
                stringManager.clearString();
                preferences.putInt("lockers", 3);
            }

            preferences.end();
            break;
        }

        if (key == '*')
        {
            Preferences password;
            password.begin("password", false);

            Preferences state;
            state.begin("state", false);
            int lockers = state.getInt("lockers", 0);

            if (lockers == 1 && stringManager.currentLength == 6)
            {
                password.putString("password", stringManager.getString());

                state.putInt("time", 3);
                state.putInt("step", 2);
                state.putInt("lockers", 7);

                tip = "Password set successfully";
            }
            else if (lockers == 3)
            {
                if (stringManager.compareString(password.getString("password", "").c_str()))
                {
                    stringManager.clearString(); // 密码正确
                    state.putInt("lockers", 7);
                    tip = "Password is correct";
                    open_door();
                    state.putInt("time", 3);
                    state.putInt("step", 4);
                }
                else
                {
                    if (error > 3)
                    {
                        Preferences preferences;
                        preferences.begin("state", false);
                        preferences.putBool("play", true);
                        preferences.end();
                        state.putInt("lockers", 5);
                    }
                    else
                    {
                        state.putInt("lockers", 7);
                        tip = "Wrong password";
                        error += 1;
                        state.putInt("time", 3);
                        state.putInt("step", 3);
                    }
                    stringManager.clearString(); // 密码错误
                }
            }

            password.end();
            state.end();
            break;
        }
        stringManager.addChar(key);
        break;

    case RELEASED:
        if (key == '*')
        {
            break;
        }
        break;

    case HOLD:
        if (key == '#')
        {
            break;
        }
        stringManager.addChar(key);
        break;
    }
}

void init_keypad()
{
    keypad.addEventListener(keypadEvent);
}

void loop_keypad()
{
    char key = keypad.getKey();
}

void init_display()
{
    display.init();
}

void loop_display()
{

    Preferences state;
    state.begin("state", false);
    Preferences sensor;
    sensor.begin("sensor", false);

    int lockers = state.getInt("lockers", 0);

    // 0 请存物 Please deposit item
    // 1 请设置密码 Please set password
    // 2 已占用 Occupied
    // 3 请解锁 Please unlock
    // 4 请取物 Please retrieve item
    // 5 警报 Alarm
    // 6 储物柜高温 Fire Alarm!

    if (lockers == 0)
    {
        tip = "Please deposit item";
    }
    else if (stringManager.currentLength == 0 && lockers == 1)
    {
        tip = "Please set password";
    }
    else if (lockers == 2)
    {
        tip = "Occupied";
    }
    else if (stringManager.currentLength == 0 && lockers == 3)
    {
        tip = "Please unlock";
    }
    else if (lockers == 4)
    {
        tip = "Please retrieve item";

        if (!sensor.getBool("iRSensor"))
        {
            state.putInt("lockers", 0);
        }
    }
    else if (lockers == 5)
    {
        tip = "Alarm";
    }
    else if (lockers == 6)
    {
        tip = "Fire Alarm";
    }
    else if (lockers == 7)
    {
        stringManager.clearString();
    }
    else if (lockers == 1 || lockers == 3)
    {
        tip = String("Password: ") + stringManager.getString();
    }

    display.clear();
    display.setText(tip.c_str());
    display.show();
    state.end();
    sensor.end();
}

void loop_display_tip()
{
    Preferences preferences;
    preferences.begin("state", false);

    int step = preferences.getInt("step", 0);
    int time = preferences.getInt("time", 0);

    if (time > 1)
    {
        preferences.putInt("time", time - 1);
    }
    else if (time == 1)
    {
        preferences.putInt("lockers", step);
        preferences.putInt("time", 0);
    }

    preferences.end();
}