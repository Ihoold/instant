//
// Created by ihoold on 01.11.17.
//

#include <algorithm>
#include "Result.hpp"


Result::Result(std::vector<std::string> code, size_t stackSize)
        : code(std::move(code)), stackSize(stackSize) {}

Result& Result::concatCode(const std::vector<std::string>& rhs_code) {
    // Concatenate vectors
    code.reserve(code.size() + rhs_code.size());
    code.insert(code.end(), rhs_code.begin(), rhs_code.end());
}

void Result::addCommand(const std::string& command) {
    code.push_back(command);
}

size_t Result::getStackSize() const {
    return stackSize;
}

void Result::setStackSize(size_t stackSize) {
    Result::stackSize = stackSize;
}

const std::vector<std::string>& Result::getCode() const {
    return code;
}

