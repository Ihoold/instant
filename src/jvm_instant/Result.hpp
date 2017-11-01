//
// Created by ihoold on 01.11.17.
//

#ifndef INSTANT_RESULT_HPP
#define INSTANT_RESULT_HPP


class Result {
    vector<string> code;
    size_t stack_size = 0;
    size_t locall_vars = 0;
public:
    Result() = default;
    Result(vector<string>, size_t, size_t);
};


#endif //INSTANT_RESULT_HPP
