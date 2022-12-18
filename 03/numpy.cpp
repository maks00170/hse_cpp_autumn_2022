#include "numpy.hpp"

 
Matrix::Matrix(size_t row, size_t column){
    this->shape0 = row;
    this->shape1 = column;
    this->rows_ = new ProxyRow[row];
    for (size_t i=0; i<row; i++){
        for (size_t j=0; j<column; j++){
            this->rows_[i].data_ = new int[column];
        
        }

    for (size_t j=0; j<column; j++){
            this->rows_[i].data_[j] = 1;
        
        } 
    }


} // конструктор
Matrix::~Matrix(){                  //деструктор // this == self
    delete[] this->rows_; 
}

Matrix::ProxyRow::~ProxyRow(){                 // деструктор для прокси класса  
    delete[] this->data_; 
}

Matrix& Matrix::operator *= (int m){
    for (size_t i=0; i<this->shape0; i++){
        for (size_t j=0; j<this->shape1; j++){
            this->rows_[i].data_[j] *= m ;
        
        }
    }
    return *this; // разименование указателя на объект     
}

Matrix Matrix::operator + (const Matrix& mat) const{
    Matrix result = Matrix(this->shape0, this->shape1);
    for (size_t i=0; i<this->shape0; i++){
        for (size_t j=0; j<this->shape1; j++){
            result[i][j] = mat[i][j] + (*this)[i][j];
        
        }
    }
    return result; 
} 

bool Matrix::operator == (const Matrix& mat) const{
    for (size_t i=0; i<this->shape0; i++){
        for (size_t j=0; j<this->shape1; j++){
            if (mat[i][j] != (*this)[i][j]){
                return false;
            }
        
        }
    }
    return true;
}

bool Matrix::operator != (const Matrix& mat) const{
    for (size_t i=0; i<this->shape0; i++){
        for (size_t j=0; j<this->shape1; j++){
            if (mat[i][j] != (*this)[i][j]){
                return true;
            }
        
        }
    }
    return false;
}

 size_t Matrix::get_rows () const{
    return this->shape0;
 }

size_t Matrix::get_cols() const{
    return this->shape1;
 }

std::ostream& operator <<(std::ostream& os,const Matrix& mat){
    std::string result = "";
    for (size_t i=0; i<mat.get_rows(); i++){
        for (size_t j=0; j<mat.get_cols(); j++){
            result += std::to_string(mat[i][j]) + " ";
        
        }
    result += "\n";
    }
    os<<result;
    return os;
}

void Matrix::print(){
    for (size_t i=0; i<this->shape0; i++){
        for (size_t j=0; j<this->shape1; j++){
            std::cout<<this->rows_[i].data_[j] <<"\t";
        
        }
    std::cout<<std::endl;
    }


}