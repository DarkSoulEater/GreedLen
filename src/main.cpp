#include <iostream>

#include "driver.hpp"

int main(int argc, const char* argv[]) {
    Driver driver;
    driver.ParseArgs(argc, argv);
    return 0;
}
