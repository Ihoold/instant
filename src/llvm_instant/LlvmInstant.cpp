#include <sstream>
#include <iterator>
#include <fstream>
#include <iostream>
#include "Parser.hpp"
#include "Printer.hpp"
#include "LlvmVisitor.hpp"

std::string getFilename(const std::string& path) {
    auto filenameEnd = path.find_last_of('.');
    auto filenameBegin = path.find_last_of('/');
    if (filenameBegin == std::string::npos) {
        return path.substr(0, filenameEnd);
    }
    return path.substr(filenameBegin + 1, filenameEnd - filenameBegin - 1);
}

std::string getDirName(const std::string& path) {
    auto filenameBegin = path.find_last_of('/');
    if (filenameBegin == std::string::npos) {
        return "./";
    }
    return path.substr(0, filenameBegin+1);
}

const std::string RUNTIME_PATH = "./lib/runtime.bc";

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
        exit(2);
    }
    /* The default entry point is used. For other options see Parser.H */
    Program *parse_tree = pProgram(input);
    if (parse_tree) {
        LlvmVisitor v;
        const std::string& path = argv[1];

        auto body = v.compile(parse_tree);

        const char* const delim = "\n";
        auto llFilePath = getDirName(path) + getFilename(path) + ".ll";

        {
            std::ofstream codeStream(llFilePath, std::ofstream::out);
            std::copy(body.begin(), body.end(),
                      std::ostream_iterator<std::string>(codeStream, delim));
        }

        std::string lliCommand = "llvm-link -o " + getDirName(path) + getFilename(path) +
                ".bc" + " " + llFilePath + " " + RUNTIME_PATH;
        system(lliCommand.data());
        return 0;
    }
    return 1;
}
