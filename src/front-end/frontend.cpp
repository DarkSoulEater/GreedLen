#include "frontend.hpp"
#include <fstream>

FrontEnd::FrontEnd(Argument& args)
    : args_(args)
    , lexer_()
    , parser_(lexer_, *this)
{}

std::optional<std::unique_ptr<TranslUnit>>
FrontEnd::ParseFile(std::ifstream* file) {
    lexer_.yyrestart(file);

    auto res = parser_.parse();
    if (res != 0)
        return std::nullopt;

    return {std::move(unit_)};
}