#include "driver.hpp"

#include <fstream>

Driver::Driver() {}

void Driver::ParseArgs(int argc, const char* argv[]) {
    const char *file_name = "tests/test_program.gr";
    ParseFile(file_name);
}

int Driver::ParseFile(const std::string_view& file_name) {
    std::ifstream stream;
    stream.open(file_name.data());

    if (!stream.is_open()) {
        assert(0);
        abort();
    }

    auto res = front_end_.ParseFile(&stream);

    // lexer_.yyrestart(&stream);

    // auto res = parser.ParseFile(file);

    stream.close();

    return res;
}