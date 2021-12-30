# SimpleLogger4SimpleApp
Sometimes we create simple application and we need to use very simple logger in this case. This repository contains two files tha can be used in this case
Usage:

#include <stdio.h>
#include "log.h"

int main(void)
{
    init_logging("./main-log.log", true, TRACE);
    INFO("%s", "Game Started");
    t_position * pos[64];

    int count = to_do_something_useful();
    for (int i = 0; i < count; i++)
    {
       DEBUG("%s = %s", "Useful Info is : ", "Useful Info", "Data");
    }
    INFO("%s", "Game Ended");
    stop_logging();
}
