#include <iostream>
#include <string>
#include <cstring>

enum class Error
{
    NoError,
    CorruptedArchive
};


struct Data
{
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }

    template <class Deserializer>

    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a, b, c);
    }
   
};

class Serializer
{
    static constexpr char Separator = ' ';
public:
    explicit 
    Serializer(std::ostream& out)
    : out_(out) {};

    template <class T>
    Error save(T& object)
    {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&&... args)
    {
        return process(std::forward<ArgsT>(args)...);
    }
    template <class T, class... ArgsT>
    Error process(T&& arg, ArgsT&&... args)
    {
        Error error = process(arg);
        if (error == Error::CorruptedArchive)
            return Error::CorruptedArchive;

        return process(std::forward<ArgsT>(args)...);
    }
    Error process(bool& arg_bool);
    Error process(uint64_t& arg_uint);

private:
    std::ostream& out_;
};



class Deserializer
{
public:
    explicit 
    Deserializer(std::istream& in)
    : in_(in) {};

    template <class T>
    Error load(T& object) {
        return object.deserialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&&... args)
    {
        return process(std::forward<ArgsT>(args)...);
    }
    template <class T, class... ArgsT>
    Error process(T&& arg, ArgsT&&... args)
    {
        Error error = process(arg);
        if (error == Error::CorruptedArchive)
            return Error::CorruptedArchive;

        return process(std::forward<ArgsT>(args)...);
    }
    Error process(bool& value_bool);
    Error process(uint64_t& value_uint);
private:
    std::istream& in_;
};
