//
// Created by ihoold on 01.11.17.
//

#ifndef INSTANT_RESULT_HPP
#define INSTANT_RESULT_HPP

#include <string>
#include <vector>

class Result {
    std::vector<std::string> code;
    size_t stackSize = 0;
public:
    Result(std::vector<std::string> code, size_t stack_size);

    Result() = default;

    const std::vector<std::string>& getCode() const;

    size_t getStackSize() const;

    void setStackSize(size_t stackSize);

    Result& concatCode(const std::vector<std::string>&);

    void addCommand(const std::string& command);
};


#endif //INSTANT_RESULT_HPP
