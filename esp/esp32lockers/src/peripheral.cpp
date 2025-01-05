#include <DHTesp.h>
#include <Preferences.h>
#include <map>

#include "peripheral.h"

DHTesp dht;

void readDHTSensorData()
{
    TempAndHumidity newValues = dht.getTempAndHumidity();
    float humidity = newValues.humidity;       // 读取湿度
    float temperature = newValues.temperature; // 读取温度

    if (isnan(humidity) || isnan(temperature))
    {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }
    Preferences preferences;
    preferences.begin("sensor", false);

    // 将读取到的值赋给全局变量
    preferences.putFloat("humidity", humidity);
    preferences.putFloat("temp", temperature);
    preferences.end();
}

class IRSensor
{
private:
    int sensor_value; // 用于计数
    int sensor_pin;   // 传感器连接的GPIO引脚
    const int initial_value = 3;

public:
    IRSensor(int pin) : sensor_pin(pin), sensor_value(0)
    {
        pinMode(sensor_pin, INPUT);
    }

    // 检查传感器并更新私有数值
    void updateSensor()
    {

        if (digitalRead(sensor_pin) == LOW)
        {
            sensor_value = initial_value; // 检测到，重置私有数值为3
        }
        else
        {
            if (sensor_value > 0)
            {
                sensor_value--; // 未检测到，私有数值减1
            }
        }
    }

    // 返回私有数值是否为0的状态
    bool isSensorValueZero() const
    {
        return sensor_value == 0;
    }
};

IRSensor iRSensor(IRSENSORPIN);

void readIRSensorData()
{
    iRSensor.updateSensor();
    Preferences preferences;
    preferences.begin("sensor", false);

    // 将读取到的值赋给全局变量
    preferences.putBool("iRSensor", iRSensor.isSensorValueZero());
    preferences.end();
}

void init_peripheral()
{
    dht.setup(DHTPIN, DHTesp::AUTO_DETECT);
}
