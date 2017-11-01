//
// Created by ihoold on 01.11.17.
//

#include "Result.hpp"


Result::Result(std::vector<std::string> code, const std::unordered_set<std::string>& vars, size_t stack_size)
        : code(std::move(code)), vars(vars), stack_size(stack_size) {}

Result& Result::concatCode(const std::vector<std::string>& rhs_code) {
    // Concatenate vectors
    code.reserve(code.size() + rhs_code.size());
    code.insert(code.end(), rhs_code.begin(), rhs_code.end());
}

const std::unordered_set<std::string>& Result::getVars() const {
    return vars;
}

void Result::setVars(const std::unordered_set<std::string>& vars) {
    Result::vars = vars;
}

size_t Result::getStackSize() const {
    return stackSize;
}

void Result::setStackSize(size_t stackSize) {
    Result::stackSize = stackSize;
}

