#include "ser.hpp"

bool ISNumber(std::string str)
{
    for (size_t i=0; i < str.length(); i++) 
    {
        if ( isdigit(str[i]) ){
            continue;
        }
        else
        {
           return false; 
        }               
    }
    return true;
}



Error Serializer::process(bool& arg_bool)          // запись выходной поток bool
{
    std::string value;
    if (arg_bool) 
    {
        value = "true";
    } 
    else 
    {
        value = "false";
    }

    if (out_.tellp() == std::streampos(0)) 
    {
        out_ << value;
    }
    else 
    {
        out_ << Serializer::Separator << value;
    }

    return Error::NoError;
}


Error Serializer::process(uint64_t& arg_uint)   // запись выходной поток uint
{
    std::string value = std::to_string(arg_uint);
    if (out_.tellp() == std::streampos(0)) 
    {
        out_ << value;
    }
    else
    {
        out_ << Serializer::Separator << value;
    }

    return Error::NoError;
}





Error Deserializer::process(bool& value_bool)    // запись из потока в поле структуры bool
{
    std::string text;
    in_ >> text;

    if (text == "true") 
    {
        value_bool = true;
    } 
    else if (text == "false")
    {
        value_bool = false;
    } 
    else 
    {
        return Error::CorruptedArchive;
    }
    
    return Error::NoError;
}


Error Deserializer::process(uint64_t& value_uint) // запись из потока в поле структуры uint
{
    std::string text;
    in_ >> text;

    if (ISNumber(text)) 
    {
        value_uint = std::stoull(text);
    } 
    else 
    {
        return Error::CorruptedArchive;
    }

    return Error::NoError;
}