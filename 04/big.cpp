#include "big.hpp"


BigInt::BigInt()
{
    size_digits = 0;
    digits = nullptr;
    positive = true;
}


BigInt::BigInt(int32_t i_num)  
//Нужно поддержать семантику работы с обычным int32_t;

{
    if (i_num >= 0){
        positive = true;
    }
    
    int32_t num = i_num;
    size_t size = 0;
    
    while (num){
        num /=10;
        size++;
    }
    size_digits = size;

    digits = new int32_t[size];
    num = i_num;
    size_t i = 0;
    while (num){
        digits[i] = num%10;
        num /=10;
        i++;
    }

}


BigInt::BigInt(std::string s_num)
//Реализовать конструктор, принимающий std::string;

{   
    size_digits = s_num.length();
    if (s_num[0] == '-') {
        size_digits--;
        positive = false;
    }

    digits = new int32_t[size_digits];
    size_t num = s_num.length();
    size_t i = 0;

    while (num>0){
        digits[i] = s_num[num-1] - '0';
        num--;
        i++;
    }


}


BigInt::~BigInt()
{
    //деструктор
    delete[] digits;
}

BigInt::BigInt(const BigInt& copied){ // конструктор копирования
    this-> size_digits = copied.size_digits;
    this-> digits = new int32_t[this->size_digits];
    this-> positive = copied.positive;
    
    for (size_t i = 0; i<this->size_digits; i++){
        this-> digits[i] = copied.digits[i];
    }
}

BigInt BigInt::operator - (){//унарный минус;
    BigInt result = BigInt(*this); //делаем копию текущего объекта
    result.positive = !result.positive; 
    return result;
}

bool BigInt::operator == (const BigInt& rhs) const{ //сравнения ==
    //this-> positive 
    //rhs.positive
    if (rhs.positive != this-> positive){
        return false;
    }

    if (rhs.size_digits != this-> size_digits){
        return false;
    }
    for (size_t i=0; i<this->size_digits; i++) {
        if (this-> digits[i] != rhs.digits[i]){
            return false;
        }
    }
    return true; 
}

bool BigInt::operator < (const BigInt& rhs) const{ //сравнения <
    //this-> positive 
    //rhs.positive
    if (this-> positive < rhs.positive ){
        return true;
    }
    
    if (this-> positive > rhs.positive ){
        return false;
    }

    if (this-> size_digits < rhs.size_digits){
        return true;
    }
    if (!this-> positive){
        for (size_t i=0; i < this->size_digits; i++) {
        if (this-> digits[this->size_digits - i - 1] > rhs.digits[this->size_digits - i - 1]){
            return true;
        }
        }
    }
    else{
        for (size_t i=0; i < this->size_digits; i++) {
        if (this-> digits[this->size_digits - i - 1] < rhs.digits[this->size_digits - i - 1]){
            return true;
        }
        }
    }
    return false; 
}

bool BigInt::operator > (const BigInt& rhs) const{ //сравнения >
    //this-> positive 
    //rhs.positive
    if (this-> positive > rhs.positive ){
        return true;
    }
    
    if (this-> positive < rhs.positive ){
        return false;
    }

    if (this-> size_digits > rhs.size_digits){
        return true;
    }
    if (!this-> positive){
        for (size_t i=0; i < this->size_digits; i++) {
        if (this-> digits[this->size_digits - i - 1] < rhs.digits[this->size_digits - i - 1]){
            return true;
        }
        }
    }
    else{
        for (size_t i=0; i < this->size_digits; i++) {
        if (this-> digits[this->size_digits - i - 1] > rhs.digits[this->size_digits - i - 1]){
            return true;
        }
        }
    }
    return false; 
}

BigInt BigInt::operator + (const BigInt& rhs) const{ // +

    if (!this->positive && rhs.positive){
        return rhs - *this;
    }
    else if (this->positive && !rhs.positive){
        return *this - rhs;
    }
    else if (!this->positive && !rhs.positive){
        return -(*this + rhs);
    }

    int32_t result = 0;
    int32_t car = 0; 
    size_t size = std::max(this-> size_digits, rhs.size_digits) + 1;

    int32_t* result_digits = new int32_t[size];

    for (size_t i=0; i<size; ++i){ // незначащие нули
        result_digits[i] = 0;
    }

    if (this-> size_digits < rhs.size_digits){
        for (size_t i=0; i<this->size_digits; i++){
            result = this->digits[i] + rhs.digits[i] + car;
            car = result/10;
            result_digits[i] = result%10;
        }

        for (size_t i=this->size_digits; i < size - 1; i++){
            result =  rhs.digits[i] + car;
            car = result/10;
            result_digits[i] = result%10;
        }

    }
    else{
        for (size_t i=0; i<rhs.size_digits; i++){
            result = this->digits[i] + rhs.digits[i] + car;
            car = result/10;
            result_digits[i] = result%10;
        }

        for (size_t i=rhs.size_digits; i <this->size_digits; i++){
            result =  this->digits[i] + car;
            car = result/10;
            result_digits[i] = result%10;
        }
    }

    size_t zero = 0;
    int32_t last = result_digits[size-1];
    while (last==0){ 
        zero++;
        last = result_digits[size-1 - zero];
    }

    int32_t* clear = new int32_t[size-zero];
    for (size_t i=0; i<size-zero; i++){
        clear[i] = result_digits[i];
    }

return BigInt(clear, size-zero);
}

BigInt::BigInt(int32_t* ptr, size_t size){
    this->digits = ptr;
    this->size_digits = size;
    this-> positive = true;
}

BigInt BigInt::operator - (const BigInt& rhs) const{ // -
    
    if (!this->positive && rhs.positive){
        return -(*this + rhs);
    }
    else if (this->positive && !rhs.positive){
        return *this + rhs;
    }
    else if (!this->positive && !rhs.positive){
        return rhs - *this;
    }
    if (*this < rhs){
        return -(rhs - *this);
    } 

    int32_t result = 0;
    size_t size = std::max(this-> size_digits, rhs.size_digits) + 1;

    int32_t* result_digits = new int32_t[size];
    

    for (size_t i=0; i<size; ++i){ // незначащие нули
        result_digits[i] = 0;
    }

    for (size_t i=0; i<rhs.size_digits; i++){
        result = this->digits[i] - rhs.digits[i];
        if (result<0){
            result+=10;
            result_digits[i+1] -= 1;
        }

        result_digits[i] += result;
    }

    for (size_t i=rhs.size_digits; i <size-1; i++){
        result_digits[i] += this->digits[i];
    }


    size_t zero = 0;
    int32_t last = result_digits[size-1];
    while (last==0){ 
        zero++;
        last = result_digits[size-1 - zero];
    }

    int32_t* clear = new int32_t[size-zero];
    for (size_t i=0; i<size-zero; i++){
        clear[i] = result_digits[i];
    }

    return BigInt(clear, size-zero);
}

BigInt BigInt::operator * (const BigInt& rhs) const{ // *
    bool sign = false;

    if (this->positive && !rhs.positive){
        sign = true;
    }
    else if (!this->positive && rhs.positive){
        sign = true;
    }
    
    int32_t car = 0; 
    size_t size = this-> size_digits + rhs.size_digits;

    int32_t* result_digits = new int32_t[size];

    for (size_t i=0; i<size; ++i){ // незначащие нули
        result_digits[i] = 0;
    }

    for (size_t i=0; i<this->size_digits; ++i) {
        for (size_t j=0; j<rhs.size_digits; ++j) {
            result_digits[i+j] += this->digits[i] * rhs.digits[j];
        }
    }

    for (size_t i=0; i<size-1; ++i) {
        car = result_digits[i] / 10;
        result_digits[i+1] += car;
        result_digits[i] %= 10;
    }

    size_t zero = 0;
    int32_t last = result_digits[size-1];
    while (last==0){ 
        zero++;
        last = result_digits[size-1 - zero];
    }

    int32_t* clear = new int32_t[size-zero];
    for (size_t i=0; i<size-zero; i++){
        clear[i] = result_digits[i];
    }
    BigInt bigresult = BigInt(clear, size-zero);
    if (sign){
        bigresult = - bigresult;
    }
    
    return bigresult;

}

bool BigInt::operator <= (const BigInt& rhs) const{ //сравнения <=
    return !(*this > rhs);
}
bool BigInt::operator >= (const BigInt& rhs) const{ //сравнения <=
    return !(*this < rhs);
}
bool BigInt::operator != (const BigInt& rhs) const{ //сравнения <=
    return !(*this == rhs);
}


BigInt& BigInt::operator = (BigInt&& mov) //перемещающий конструктор mov 
{
    this->size_digits = mov.size_digits;
    this->positive = mov.positive;
    this->digits = new int32_t[this->size_digits];

    for (size_t i=0; i<this->size_digits; ++i) {
        this->digits[i] = mov.digits[i];
    }

    mov.size_digits = 0;
    mov.positive = true;
    
    delete[] mov.digits;
    mov.digits = nullptr;

    return *this;
}

size_t BigInt::getSize_digit () const{
    return this->size_digits;
}

int32_t* const & BigInt::get_digits() const{
    return this->digits;
}

bool BigInt::get_positive() const{
    return this->positive;
}

std::ostream& operator << (std::ostream& os, const BigInt& bigInt) //вывод в поток
{
    int32_t* ptr = bigInt.get_digits();
    std::string result = "";

    for (size_t i=0; i < bigInt.getSize_digit(); ++i) { //делаем строку из цифр
        result = std::to_string(ptr[i]) + result;
    }
    if (!bigInt.get_positive())
        result = "-" + result;

    os << result;
    return os;
}

 BigInt BigInt::operator + (const int32_t& rhs) const{
    return *this + rhs;
 }

BigInt BigInt::operator - (const int32_t& rhs) const{
    return *this - rhs;
}

BigInt BigInt::operator * (const int32_t& rhs) const{
    return *this * rhs;

}

std::string to_string(BigInt bigint){
    int32_t* ptr = bigint.get_digits();
    std::string result = "";

    for (size_t i=0; i < bigint.getSize_digit(); ++i) { //делаем строку из цифр
        result = std::to_string(ptr[i]) + result;
    }
    if (!bigint.get_positive())
        result = "-" + result;
    return result;
}