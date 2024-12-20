#ifndef DATA_H
#define DATA_H

#include <Arduino.h>
#include <Preferences.h>
#include "task.h"

void loopsyncTime();
void updataTime();
bool testTime(String hour, String min);
void add_new_record(int type);
String read_record();

#endif // DATA_H
