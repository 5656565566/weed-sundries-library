#ifndef sensor_H
#define sensor_H

#include "const.h"

void readDS18B20SensorData();
void readLightSensorData();
void readHumanSensorData();
void initSensor();
void LedSetting();
void SetLed(bool led);
bool GetLed();

#endif