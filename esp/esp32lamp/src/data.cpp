#include "data.h"

Preferences record;

const char *records[10] = {"record1", "record2", "record3", "record4", "record5", "record6", "record7", "record8", "record9", "record10"};

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
        Serial.println(&timeinfo, "Time synchronized: %Y-%m-%d %H:%M:%S");
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

bool testTime(String hour, String min)
{
    return timer.testTime(hour, min);
}

void updataTime()
{
    timer.update();
}

int roll_index()
{
    record.begin("record");
    int index = record.getInt("index", 0);

    index = (index + 1) % 10;

    record.putInt("index", index);
    record.end();

    return index;
}

void add_new_record(int type)
{
    char buffer[20];

    // 使用 strftime 函数格式化时间为 "xxxx/xx/xx xx:xx:xx"
    strftime(buffer, sizeof(buffer), "%Y/%m/%d %H:%M:%S", &timeinfo);

    record.begin(records[roll_index()]);
    record.putString("time", buffer);
    record.putInt("type", type);
    record.end();
}

String read_record()
{
    String page = "<html><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'>";
    page += "<title>操作记录</title>";
    page += "<style>";
    page += "body { font-family: Arial, sans-serif; background-color: #f0f0f0; text-align: center; padding: 20px; }";
    page += "h2 { color: #333; }";
    page += "table { width: 80%; margin: auto; border-collapse: collapse; }";
    page += "th, td { padding: 10px; border-bottom: 1px solid #ddd; text-align: center; }";
    page += "th { background-color: #4CAF50; color: white; }";
    page += "tr:hover { background-color: #f5f5f5; }";
    page += "button { padding: 10px 20px; margin-top: 20px; background-color: #4CAF50; color: white; border: none; border-radius: 5px; cursor: pointer; }";
    page += "button:hover { background-color: #45a049; }";
    page += "</style></head><body>";

    page += "<h2>操作记录</h2>";
    page += "<table><tr><th>时间</th><th>操作</th></tr>";

    for (int i = 0; i < 10; i++)
    {
        record.begin(records[i]);

        String time = record.getString("time", "");
        int type = record.getInt("type", 0);
        String type_name;

        if (time == "")
        {
            record.end();
            continue;
        }

        switch (type)
        {
        case 0:
            type_name = "开灯";
            break;
        case 1:
            type_name = "关灯";
            break;
        case 2:
            type_name = "人离开关灯";
            break;
        case 3:
            type_name = "定时开灯";
            break;
        case 4:
            type_name = "定时关闭";
            break;
        default:
            type_name = "未知";
            break;
        }

        String table_row = "<tr><td>" + time + "</td><td>" + type_name + "</td></tr>";
        page += table_row;

        record.end();
    }

    page += "</table>";
    page += "<button onclick=\"location.href='/'\">返回控制面板</button>";
    page += "</body></html>";

    return page;
}
