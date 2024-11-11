#include <ESP32Servo.h>

#include "door.h"

Servo sg90;

int pos = 0;
int angle = 0;
int open_time = 0;

bool is_open = false;

void rotateServo(int target_angle)
{
    if (target_angle != pos)
    {
        sg90.write(pos);
        pos = target_angle;
    }
}

void open_door()
{
    open_time = 5;
    is_open = true;
}

void close_door()
{
    open_time = 0;
    is_open = false;
}

void init_door()
{
    sg90.attach(SG90);
    sg90.write(0);
    pinMode(LED, OUTPUT);
}

void loop_door()
{

    if (open_time == 0)
    {
        is_open = false;
    }

    if (is_open)
    {
        digitalWrite(LED, HIGH);
        rotateServo(0);
    }
    else
    {
        digitalWrite(LED, LOW);
        rotateServo(180);
        
    }
    
    open_time--;
}