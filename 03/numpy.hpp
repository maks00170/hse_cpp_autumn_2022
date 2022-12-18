#include <iostream>
#include <string>

class Matrix
{
    class ProxyRow
    {
    public:
        int *data_;
    public:
        ~ProxyRow();
        int& operator[](size_t j) const // мы не меняем объект
        {
            return data_[j];
        }
    };

public:
    Matrix(size_t row, size_t column); // конструктор
    ~Matrix(); //деструктор
    Matrix& operator *= (int m);   // оператор *= (умножение на число)
    Matrix operator + (const Matrix& mat) const; // оператор + (сложение матриц)
    bool operator == (const Matrix& mat) const;
    bool operator != (const Matrix& mat) const;
    size_t get_rows () const;
    size_t get_cols () const;
    void print();

    ProxyRow& operator[](size_t i) const // мы не меняем объект
    {
        return rows_[i];
    }

private:
    ProxyRow *rows_;
    size_t shape0;
    size_t shape1;
};

std::ostream& operator <<(std::ostream& os,const Matrix& mat);