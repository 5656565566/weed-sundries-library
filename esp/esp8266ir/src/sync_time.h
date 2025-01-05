#ifndef SYNC_TIME_H
#define SYNC_TIME_H

#include <Arduino.h>

#define NTP3 "ntp5.ntsc.ac.cn" // 授时服务器
#define NTP2 "ntp5.ict.ac.cn"
#define NTP1 "ntp5.aliyun.com"

void loopsyncTime();

#endif