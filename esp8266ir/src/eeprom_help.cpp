#include "eeprom_help.h"

void clearEEPROM() {
    EEPROM.begin(1024);  // 初始化 EEPROM，假设 EEPROM 容量为 1024 字节

    // 将 EEPROM 中的每个字节设置为 0xFF
    for (int i = 0; i < 1024; i++) {
        EEPROM.write(i, 0xFF);
    }

    EEPROM.commit();  // 提交更改
    EEPROM.end();     // 结束 EEPROM 使用
}

// length 写入记录字符串长度的地址，addr 是字符串的地址，str 为要保存的字符串
void writeString(int len, int addr, String str)
{
    EEPROM.begin(1024);

    for (unsigned int i = 0; i < str.length(); i++)
    {
        EEPROM.write(addr + i, str[i]); // 写入字符串
    }

    EEPROM.commit();
    EEPROM.end();
}

// length 位是字符串长度，addr 是起始位（字符串首地址）
String readString(int length, int addr)
{
    EEPROM.begin(1024);
    String data = "";

    bool skipFirstInvisible = true;
    for (int i = 0; i < length; i++)
    {
        char c = char(EEPROM.read(addr + i)); // 读取字符

        if (skipFirstInvisible && (c < 32 || c == 0)) // 跳过不可见字符
        {
            continue; // 跳过不可见字符
        }

        if (c == 0xFF || c == '\0') // 检测到 EEPROM 中的填充值或结束符
        {
            break;
        }

        skipFirstInvisible = false;
        data += c;
    }

    EEPROM.end();
    return data;
}

// wifi 规定 ssid 仅为 32 字节
void write_wifi_ssid(String ssid)
{
    writeString(WIFI_SSID_LENGTH, WIFI_SSID_ADDR, ssid);
}

// wifi 密码此固件编译为最长 32 字节
void write_wifi_password(String password)
{
    writeString(WIFI_PASSWORD_LENGTH, WIFI_PASSWORD_ADDR, password);
}

void write_admin_username(String username)
{
    writeString(ADMIN_USERNAME_LENGTH, ADMIN_USERNAME_ADDR, username);
}

void write_admin_password(String password)
{
    writeString(ADMIN_PASSWORD_LENGTH, ADMIN_PASSWORD_ADDR, password);
}

void write_ac_model(String ac_model)
{
    writeString(AC_MODEL_LENGTH, AC_MODEL_ADDR, ac_model);
}

String read_wifi_ssid()
{
    return readString(WIFI_SSID_LENGTH, WIFI_SSID_ADDR);
}

String read_wifi_password()
{
    return readString(WIFI_PASSWORD_LENGTH, WIFI_PASSWORD_ADDR);
}

String read_admin_username()
{
    return readString(ADMIN_USERNAME_LENGTH, ADMIN_USERNAME_ADDR);
}

String read_admin_password()
{
    return readString(ADMIN_PASSWORD_LENGTH, ADMIN_PASSWORD_ADDR);
}

String read_ac_model()
{
    return readString(AC_MODEL_LENGTH, AC_MODEL_ADDR);
}
