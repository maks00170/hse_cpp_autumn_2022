#include "token_split.hpp"

bool TokenSplit::isstr(std::string token)
{
    size_t digit_count = 0;
    for (size_t i=0; i < token.length(); ++i) {
        if (std::isdigit(token[i])){
            digit_count++;
        }
    }
    if (digit_count == token.length()){    
        return false;
    }
    return true;
}

void TokenSplit::setStartCallback(func_callback cb)
{
    this->startCallback = cb;
}

void TokenSplit::setEndCallback(func_callback cb)
{
    this->endCallback = cb;
}

void TokenSplit::setDigitTokenCallback(func_callback cb)
{
    this->digitCallback = cb;
}

void TokenSplit::setStringTokenCallback(func_callback cb)
{
    this->stringCallback = cb;
}

void TokenSplit::parse(const std::string & str)
{
    std::string text = str; 
    this->startCallback(text);
    std::string token = "";
    std::string result = "";

    for (size_t i = 0; i < text.length(); ++i) {
        if (std::isspace(text[i])) {
            if (token != "") {
                if (TokenSplit::isstr(token)) {
                    this->stringCallback(token);
                }
                else{
                    this->digitCallback(token);
                }
                result += token + ", ";
            }
            token = "";
            continue;
        }
        
        token += text[i];
    }
    this->endCallback(result);
    this->split_text = result;
}