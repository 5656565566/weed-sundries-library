#include <DS18B20.h>
#include <Preferences.h>
#include <BH1750FVI.h>

#include "peripheral.h"

OneWire oneWire(TEMP);
DS18B20 ds18B20(&oneWire);
BH1750FVI bh1750(
    BH1750_DEFAULT_I2CADDR, BH1750_CONTINUOUS_HIGH_RES_MODE, BH1750_SENSITIVITY_DEFAULT, BH1750_ACCURACY_DEFAULT);

void initSensor()
{
    ds18B20.begin();
    bh1750.begin(
        BH1750FVISDA,
        BH1750FVISCL);
    bh1750.setCalibration(1.06);
    bh1750.setSensitivity(1.00);
    bh1750.setResolution(BH1750_CONTINUOUS_HIGH_RES_MODE);

    /* get BH1750 settings */
    Serial.print(F("Resolution value....: 0x"));
    Serial.println(bh1750.getResolution(), HEX);

    Serial.print(F("Calibration value...: "));
    Serial.println(bh1750.getCalibration());

    Serial.print(F("Sensitivity value...: "));
    Serial.println(bh1750.getSensitivity());
    pinMode(LED, OUTPUT);
    pinMode(LEDPWM, OUTPUT);
}

void readDS18B20SensorData()
{
    ds18B20.requestTemperatures();

    if (ds18B20.isConversionComplete())
    {

        Preferences preferences;
        preferences.begin("sensor", false);

        // 将读取到的值赋给全局变量
        preferences.putFloat("temp", ds18B20.getTempC());
        preferences.end();
    }
}

void readLightSensorData()
{
    float lightLevel = bh1750.readLightLevel();

    Preferences preferences;
    preferences.begin("sensor", false);
    preferences.putFloat("light", lightLevel);
    preferences.end();
}

class SR602Sensor
{
private:
    int sensor_value; // 用于计数
    int sensor_pin;   // SR602传感器连接的GPIO引脚
    const int initial_value = 5;

public:
    SR602Sensor(int pin) : sensor_pin(pin), sensor_value(0)
    {
        pinMode(sensor_pin, INPUT);
    }

    // 检查传感器并更新私有数值
    void updateSensor()
    {

        if (digitalRead(sensor_pin) == HIGH)
        {
            sensor_value = initial_value; // 检测到人体，重置私有数值为3
        }
        else
        {
            if (sensor_value > 0)
            {
                sensor_value--; // 未检测到人体，私有数值减1
            }
        }
    }

    // 返回私有数值是否为0的状态
    bool isSensorValueZero() const
    {
        return sensor_value == 0;
    }
};

SR602Sensor sr602(SRT602PIN);

void readHumanSensorData()
{
    sr602.updateSensor();
    Preferences preferences;
    preferences.begin("sensor", false);
    preferences.putBool("human", sr602.isSensorValueZero());
    preferences.end();
}

void LedSetting()
{
    Preferences preferences;
    preferences.begin("sensor", false);
    if (!preferences.getBool("led"))
    {
        digitalWrite(LED, LOW);
    }
    else
    {
        digitalWrite(LED, HIGH);
    }
    preferences.end();
}

bool GetLed(){
    Preferences preferences;
    preferences.begin("sensor", false);
    bool led = preferences.getBool("led");
    preferences.end();
    return led;
}

void SetLed(bool led)
{
    Preferences preferences;
    preferences.begin("sensor", false);
    preferences.putBool("led", led);
    preferences.end();
}