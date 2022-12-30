#include <iostream>
#include <string>
#include <cmath>


class BigInt
{
public:
    BigInt();
    BigInt(int32_t i_num);
    BigInt(std::string s_num);
    BigInt(int32_t* ptr, size_t size);
    ~BigInt();
    BigInt& operator = (const int32_t& i_num); // конструктор через оператор присваивания

    BigInt(const BigInt& copied);
    BigInt& operator = (const BigInt& copied);
    BigInt(BigInt&& moved);
    BigInt& operator = (BigInt&& moved);
    

    BigInt operator - ();

    bool operator < (const BigInt& rhs) const;
    bool operator == (const BigInt& rhs) const;
    bool operator > (const BigInt& rhs) const;
    bool operator <= (const BigInt& rhs) const;
    bool operator != (const BigInt& rhs) const;
    bool operator >= (const BigInt& rhs) const;

    BigInt operator + (const BigInt& rhs) const;
    BigInt operator + (const int32_t& rhs) const;

    BigInt operator - (const BigInt& rhs) const;
    BigInt operator - (const int32_t& rhs) const;

    BigInt operator * (const BigInt& rhs) const;
    BigInt operator * (const int32_t& rhs) const;

    size_t getSize_digit () const;
    int32_t* const & get_digits() const; 
    bool get_positive() const;
private:
    int32_t* digits; // храним 123, как {3, 2, 1}
    size_t size_digits = 0; // размер массива
    bool positive = true;
};
std::string to_string(BigInt bigint);

std::ostream& operator << (std::ostream& os, const BigInt& bigInt);