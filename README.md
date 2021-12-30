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

These files were checked on Ubuntu 20.04 with GCC compiler

gcc --version
gcc (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
Copyright (C) 2019 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

Compiler's option : -Werror -Wall -Wextra --pedantic --std=gnu17
