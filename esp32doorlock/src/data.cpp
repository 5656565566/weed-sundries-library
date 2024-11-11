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
};

Timer timer(0, 0, 0);

void loopsyncTime()
{
    timer.syncTime();
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
    // 初始化HTML页面和CSS样式
    String page = "<html><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'>";
    page += "<title>历史开门记录</title>";
    page += "<style>";
    page += "body { font-family: Arial, sans-serif; background-color: #f5f5f5; color: #333; text-align: center; margin: 0; padding: 20px;}";
    page += ".container { max-width: 600px; margin: auto; padding: 20px; background-color: #fff; border-radius: 8px; box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);}";
    page += "h1 { color: #333; }";
    page += "table { width: 100%; border-collapse: collapse; margin-top: 20px; }";
    page += "th, td { padding: 10px; border: 1px solid #ddd; text-align: center; }";
    page += "th { background-color: #4CAF50; color: white; }";
    page += "tr:nth-child(even) { background-color: #f2f2f2; }";
    page += "</style></head><body>";
    page += "<div class='container'>";
    page += "<h1>历史开门记录</h1>";
    page += "<table><tr><th>时间</th><th>开门触发类型</th></tr>";

    // 遍历记录，生成表格行
    for (int i = 0; i < 10; i++) {
        record.begin(records[i]);
        String time = record.getString("time", "");
        int type = record.getInt("type", 0);
        String type_name;

        if (time == "") {
            record.end();
            continue;
        }

        switch (type) {
        case 0:
            type_name = "远程";
            break;
        case 1:
            type_name = "密码";
            break;
        case 2:
            type_name = "刷卡";
            break;
        default:
            type_name = "未知";
            break;
        }

        // 将数据添加为表格行
        String table_row = "<tr><td>" + time + "</td><td>" + type_name + "</td></tr>";
        page += table_row;

        record.end();
    }

    page += "</table></div></body></html>";
    return page;
}
