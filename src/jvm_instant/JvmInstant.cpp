#include <stdio.h>
#include <sstream>
#include <iterator>
#include <fstream>
#include <iostream>
#include "Parser.hpp"
#include "Printer.hpp"
#include "JvmVisitor.hpp"

std::string setExtenstionToJ(std::string path) {
    return path.substr(0, path.find_last_of('.'))+".j";
}

int main(int argc, char **argv) {
    FILE *input;
    if (argc > 1) {
        input = fopen(argv[1], "r");
        if (!input) {
            std::cerr << "Error opening input file." << std::endl;
            exit(1);
        }
    } else {
        std::cerr << "Usage: insc_llvm file" << std::endl;
    }
    /* The default entry point is used. For other options see Parser.H */
    Program *parse_tree = pProgram(input);
    if (parse_tree) {
        printf("\nParse Succesful!\n");
        printf("\n[Abstract Syntax]\n");
        ShowAbsyn s;
        printf("%s\n\n", s.show(parse_tree));
        printf("[Linearized Tree]\n");
        PrintAbsyn p;
        printf("%s\n\n", p.print(parse_tree));
        JvmVisitor v;
        auto lines = v.compile(parse_tree);

        const char* const delim = "\n";

        std::ofstream codeStream(setExtenstionToJ(argv[1]), std::ofstream::out);
        std::copy(lines.begin(), lines.end(),
                  std::ostream_iterator<std::string>(codeStream, delim));
        return 0;
    }
    return 1;
}
