#include <displaybroker/DisplayBroker.hpp>
#include <iostream>
#include <rpidisplaymanager/version.h>
#include <stdio.h>
#include <string>

auto main(int argc, char **argv) -> int
{
    fprintf(stdout, "Raspberry Pi Display Manager v%s\n", RPIDISPLAYMANAGER_VERSION);

    DisplayBroker displayBroker;

    return 0;
}
