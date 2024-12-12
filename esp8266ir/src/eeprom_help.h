#ifndef EEPROM_HELP_H
#define EEPROM_HELP_H

#include <Arduino.h>
#include <EEPROM.h>

#define WIFI_SSID_LENGTH        32
#define WIFI_PASSWORD_LENGTH    32
#define ADMIN_USERNAME_LENGTH   32
#define ADMIN_PASSWORD_LENGTH   32
#define AC_MODEL_LENGTH         16

#define WIFI_SSID_ADDR          0
#define WIFI_PASSWORD_ADDR      (WIFI_SSID_ADDR + WIFI_SSID_LENGTH + 1)  // 加1是为了\0字符
#define ADMIN_USERNAME_ADDR     (WIFI_PASSWORD_ADDR + WIFI_PASSWORD_LENGTH + 1)
#define ADMIN_PASSWORD_ADDR     (ADMIN_USERNAME_ADDR + ADMIN_USERNAME_LENGTH + 1)
#define AC_MODEL_ADDR           (ADMIN_PASSWORD_ADDR + ADMIN_PASSWORD_LENGTH + 1)

void clearEEPROM();

void write_wifi_ssid(String ssid);
void write_wifi_password(String password);
void write_admin_username(String username);
void write_admin_password(String password);
void write_ac_model(String ac_model);

String read_wifi_ssid();
String read_wifi_password();
String read_admin_username();
String read_admin_password();
String read_ac_model();

#endif