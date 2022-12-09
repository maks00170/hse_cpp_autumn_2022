#pragma once

#include <iostream>
#include <cstring>
#include <functional>

using func_callback = std::function<void (std::string & str)>;

class TokenSplit
{
public:
    TokenSplit() = default;
    std::string split_text;

    void setStartCallback(func_callback cb);
    void setEndCallback(func_callback cb);
    void setDigitTokenCallback(func_callback cb);
    void setStringTokenCallback(func_callback cb);
    void parse(const std::string & str);
private:
    func_callback startCallback;
    func_callback endCallback;
    func_callback digitCallback;
    func_callback stringCallback;

    static bool isstr(std::string token);
};