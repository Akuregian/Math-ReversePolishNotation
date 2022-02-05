#include <iostream>
#include <memory>
#include <typeinfo>
#include "../Header/Parser.h"

int main(int argc, char *argv[])
{
   // while (true)
   // {
        std::string equation_str;
        //std::getline(std::cin, equation_str);
        equation_str = "(3+4/2)^2 + (4-2*7/4)^3";

        // Init Parser(text_equation)
        std::unique_ptr<Parser> parser(new Parser(equation_str, true)); // Runs the Lexigraphical Analyzer

    //}

    return 0;
}
