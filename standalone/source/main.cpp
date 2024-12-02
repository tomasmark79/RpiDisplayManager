#include <cxxopts.hpp>
#include <displaybroker/DisplayBroker.hpp>
#include <fmt/core.h>
#include <iostream>
#include <rpidisplaymanager/version.h>
#include <string>

auto main(int argc, char **argv) -> int
{
    fmt::print("Raspberry Display Manager v{}\n", RPIDISPLAYMANAGER_VERSION);
    DisplayBroker displayBroker;
 

    return 0;
}
