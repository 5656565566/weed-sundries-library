#include <Arduino.h>
#include <Preferences.h>

#include "const.h"
#include "data.h"

void AutomaticLight()
{
    Preferences func_switch;
    Preferences sensor;

    sensor.begin("sensor", false);
    func_switch.begin("switch", false);

    bool brightness_switch = func_switch.getBool("brightness");
    bool human_switch = func_switch.getBool("human");

    bool human = sensor.getBool("human");
    float brightness = sensor.getFloat("light");
    bool led = sensor.getBool("led");

    int ledBrightness;

    if (brightness_switch)
    {
        if (brightness > 100)
        {
            ledBrightness = 0;
        }
        else
        {
            ledBrightness = map(brightness, 0, 100, 255, 0);
        }
        analogWrite(LEDPWM, ledBrightness);
    }

    if (human_switch && human && led)
    {
        add_new_record(2);
        sensor.putBool("led", false);
    }

    String onTime = func_switch.getString("onTime");
    String offTime = func_switch.getString("offTime");

    // 处理 onTime
    int separatorIndex = onTime.indexOf(':');
    String key = onTime.substring(0, separatorIndex);
    String value = onTime.substring(separatorIndex + 1);

    if (testTime(key, value))
    {
        add_new_record(3);
        func_switch.putString("onTime", "");
        sensor.putBool("led", true);
    }

    // 处理 offTime
    separatorIndex = offTime.indexOf(':');
    key = offTime.substring(0, separatorIndex); // 将 onTime 改为 offTime
    value = offTime.substring(separatorIndex + 1);

    if (testTime(key, value))
    {
        add_new_record(4);
        func_switch.putString("offTime", "");
        sensor.putBool("led", false);
    }

    sensor.end();
    func_switch.end();
}

bool SetSwitch(String name)
{
    Preferences preferences;
    preferences.begin("switch", false);

    bool last = preferences.getBool(name.c_str(), false);

    preferences.putBool(name.c_str(), !last);
    preferences.end();

    return last;
}