#include <sstream>
#include <iterator>
#include <fstream>
#include <iostream>
#include "Parser.hpp"
#include "Printer.hpp"
#include "JvmVisitor.hpp"

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

int main(int argc, char **argv) {
    FILE *input;
    if (argc > 1) {
        input = fopen(argv[1], "r");
        if (!input) {
            std::cerr << "Error opening input file." << std::endl;
            exit(1);
        }
    } else {
        std::cerr << "Usage: insc_jvm file" << std::endl;
        exit(2);
    }
    /* The default entry point is used. For other options see Parser.H */
    Program *parse_tree = pProgram(input);
    if (parse_tree) {
        JvmVisitor v;
        const std::string& path = argv[1];
        std::vector<std::string> lines {
                ".class public " + getFilename(path),
                ".super java/lang/Object",
                ".method public <init>()V",
                "aload_0",
                "invokespecial java/lang/Object/<init>()V",
                "return",
                ".end method",
        };
        auto body = v.compile(parse_tree);
        lines.insert(lines.end(), body.begin(), body.end());
        const char* const delim = "\n";
        auto jFilePath = getDirName(path) + getFilename(path) + ".j";

        {
            std::ofstream codeStream(jFilePath, std::ofstream::out);
            std::copy(lines.begin(), lines.end(),
                      std::ostream_iterator<std::string>(codeStream, delim));
        }
        std::string jasminCommand =
                "java -jar ./lib/jasmin.jar -d " + getDirName(path) + " " + jFilePath;

        system(jasminCommand.data());
        return 0;
    }
    return 1;
}
