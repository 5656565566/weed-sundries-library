#include "door.h"

int open_time = 0;

bool is_open = false;

void open_door()
{
    if (!is_open)
    {
        open_time = 3;
        is_open = true;
    }
}

void close_door()
{
    open_time = 0;
    is_open = false;
}

int get_door_time()
{
    return open_time;
}

void init_door()
{
    pinMode(DOOR, OUTPUT);
    pinMode(DOOR_TIP, OUTPUT);
}

void loop_door()
{

    if (open_time == 0)
    {
        is_open = false;
    }

    if (is_open)
    {
        digitalWrite(DOOR, HIGH);
        digitalWrite(DOOR_TIP, HIGH);
    }
    else
    {
        digitalWrite(DOOR, LOW);
        digitalWrite(DOOR_TIP, LOW);
    }
    open_time--;
}