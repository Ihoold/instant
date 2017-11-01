//
// Created by ihoold on 01.11.17.
//

#ifndef INSTANT_RESULT_HPP
#define INSTANT_RESULT_HPP

#include <string>
#include <vector>
#include <unordered_set>

class Result {
    std::vector<std::string> code;
    std::unordered_set<std::string> vars;
    size_t stackSize = 0;
public:
    Result(std::vector<std::string> code, const std::unordered_set<std::string>& vars, size_t stack_size);

    Result() = default;

    const std::unordered_set<std::string>& getVars() const;

    void setVars(const std::unordered_set<std::string>& vars);

    size_t getStackSize() const;

    void setStackSize(size_t stackSize);

    Result& concatCode(const std::vector<std::string>&);
};


#endif //INSTANT_RESULT_HPP
