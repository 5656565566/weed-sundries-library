#include "sync_time.h"

tm timeinfo;

class Timer
{
private:
    unsigned long lastUpdateTime;
    unsigned long updateInterval; // 更新间隔时间，单位：毫秒

public:
    Timer(int hour, int min, int sec, unsigned long interval = 1000)
    {
        timeinfo.tm_hour = hour;
        timeinfo.tm_min = min;
        timeinfo.tm_sec = sec;
        lastUpdateTime = millis(); // 获取当前时间
        updateInterval = interval; // 默认每1000ms（1秒）更新一次
    }

    void update()
    {
        unsigned long currentTime = millis();
        if (currentTime - lastUpdateTime >= updateInterval)
        {
            lastUpdateTime = currentTime;
            timeinfo.tm_sec++;

            // 检查是否需要更新分钟和小时
            if (timeinfo.tm_sec >= 60)
            {
                timeinfo.tm_sec = 0;
                timeinfo.tm_min++;
                if (timeinfo.tm_min >= 60)
                {
                    timeinfo.tm_min = 0;
                    timeinfo.tm_hour++;
                    if (timeinfo.tm_hour >= 24)
                    {
                        timeinfo.tm_hour = 0;
                    }
                }
            }
        }
    }

    void syncTime()
    {
        // 配置 NTP 服务器和时区信息
        configTime(8 * 3600, 0, NTP1, NTP2, NTP3);

        if (!getLocalTime(&timeinfo))
        {
            Serial.println("Failed to obtain time");
            return;
        }
    }

    bool testTime(String hour, String min)
    {
        // 将时间信息转换为带前导零的字符串（例如，08:01）
        String currentHour = (timeinfo.tm_hour < 10) ? "0" + String(timeinfo.tm_hour) : String(timeinfo.tm_hour);
        String currentMin = (timeinfo.tm_min < 10) ? "0" + String(timeinfo.tm_min) : String(timeinfo.tm_min);

        // 比较小时和分钟
        return (hour == currentHour && min == currentMin);
    }
};

Timer timer(0, 0, 0);

void loopsyncTime()
{
    timer.syncTime();
}