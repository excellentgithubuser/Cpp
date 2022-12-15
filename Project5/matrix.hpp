#ifndef _MATRIX_HPP
#define _MATRIX_HPP

#include<iostream>
#include <math.h>
#include <time.h>

#include <immintrin.h>
#include <avx2intrin.h>
#include <omp.h>

using namespace std;


template<typename T>
T det_for_one_channel(T * array,size_t rows);

template<typename T>
double * inverse_for_one_channel(T * array,size_t rows);

template<typename T>  //T could be unsigned char, short, int, float, double
class Matrix
{
  protected:
	size_t rows;
    size_t columns;
    size_t channels;
    size_t * count;  //denote the numbers of matrices whose elements are the same; 
	T *elements;  //store the data; malloc with elements, free with elements at the same time

  public:
    Matrix()  //constructor
    {
        this->rows = 0;
        this->columns = 0;
        this->channels = 0;
        this->count = NULL;
        this->elements = NULL; 
    }

	Matrix(size_t rows, size_t columns)  //When input two arguments, we think the matrix has channel one as default
    {
        if(rows != 0 and columns != 0)
        {
            this->rows = rows;
            this->columns = columns;
            this->channels = 1;
            this->count = new size_t(1);
            this->elements = new T[rows * columns]();  
        }
        else
        {
            this->rows = 0;
            this->columns = 0;
            this->channels = 0;
            this->count = NULL;
            this->elements = NULL; 
        }
    }

    Matrix(size_t rows, size_t columns, size_t channels)  //constructor
    {
        if(rows != 0 and columns != 0 and channels != 0)
        {
            this->rows = rows;
            this->columns = columns;
            this->channels = channels;
            this->count = new size_t(1);
            this->elements = new T[rows * columns * channels]();  
        }
        else
        {
            this->rows = 0;
            this->columns = 0;
            this->channels = 0;
            this->count = NULL;
            this->elements = NULL; 
        }
    }

	Matrix(const Matrix<T> & m)  //When using Matrix b = a, this constructor will be invoked
    {
        if(count == NULL and elements == NULL)
        {
            this->rows = m.rows;
            this->columns = m.columns;
            this->channels = m.channels;
            if(m.count != NULL and m.elements != NULL)
            {
                this->count = m.count;
                (*count) ++;
                this->elements = m.elements;
            }
            else
            {
                this->count = NULL;
                this->elements = NULL;
            }
        }
        else if(count == m.count || elements == m.elements)
        {
            cout << "Error of assignment since you can't assign a matrix to itself!" << endl;
        }
        else if(count != NULL and elements != NULL)
        {
            if(*(this->count)==1)
            {
                delete []this->count;
                delete []this->elements;
                count = NULL;
                elements = NULL;
            }
            else //*(this->count)>1
            {
                (*count) --;
            }
            rows = m.rows;
            columns = m.columns;
            channels = m.channels;
            count = m.count;
            if(count != NULL)
            {
                (*count) ++;
            }
            elements = m.elements;
        }
        else
        {
            cout << "Error of assignment!" <<endl;
        }
    }

	~Matrix()  //destructor
    {
        if(count == NULL or elements == NULL)
        {
            if(count != NULL)
            {
                delete []count;
                count = NULL;
            }
            if(elements != NULL)
            {
                delete []elements;
                elements = NULL;
            }
        }
        else if(*(this->count) == 1)
        {
            delete []count;
            delete []elements;
            count = NULL;
            elements = NULL;
        }
        else  //*(this->count) > 1
        {
            *(this->count) -= 1;
        }
    }

    size_t getCount()
    {
        if(count == NULL)
        {
            return 0;
        }
        else
        {
            return *count;
        }
    }

    size_t getRows()
    {
        return rows;
    }

    size_t getColumns()
    {
        return columns;
    }

    size_t getChannels()
    {
        return channels;
    }

    void setSize(size_t a, size_t b, size_t c)
    {
        if(rows == 0 and columns ==0 and channels ==0 and count == NULL and elements == NULL)
        {
            rows = a;
            columns = b;
            channels = c;
            count = new size_t(1);
            elements = new T[rows * columns * channels]();
        }
        else
        {
            cout<<"The size of the matrix is defined (or the matrix is invalid), so you cannot set its size!"<<endl;
        }
    }

    void setData(T * array, size_t len_of_array)  //setting data from a array
    {
        if(array == NULL)
        {
            return;
        }
        else if(len_of_array < rows * columns * channels)
        {
            cout<<"Setting failed since too little input data!"<<endl;
        }
        else if(len_of_array == rows * columns * channels)
        {
            for(size_t i = 0 ; i < rows ; i++)
            {
                for(size_t j = 0 ; j < columns ; j++)
                {
                    for(size_t k = 0 ; k < channels ; k++)
                    {
                        elements[k * rows * columns + i * columns + j] = array[k * rows * columns + i * columns + j];
                    }
                }
            }
        }
        else
        {
            for(size_t i = 0 ; i < rows ; i++)
            {
                for(size_t j = 0 ; j < columns ; j++)
                {
                    for(size_t k = 0 ; k < channels ; k++)
                    {
                        elements[k * rows * columns + i * columns + j] = array[k * rows * columns + i * columns + j];
                    }
                }
            }
            cout<<"Setting succeeded but there is so much data that some of it wasn't used!"<<endl;
        }
    }

    void change_one_entry(size_t a, size_t b, size_t c, T value)  //change one entry in place (a,b,c) to T
    {   //note that a is from zero to rows-1, and b, c are similar
        if(count == NULL || elements == NULL)
        {
            cout<<"Changing failed since the matrix is not valid!"<<endl;
            return;
        }
        else if(rows < a + 1 || columns < b + 1 || channels < c + 1)
        {
            cout<<"Changing failed since the input position is wrong!"<<endl;
            return;
        }
        else
        {
            if(*count == 1)
            {
                elements[c * rows * columns + a * columns + b] = value;
            }
            else
            {
                size_t * count_temp = new size_t(1);
                T * elements_temp = new T[rows * columns * channels]();
                for(size_t i = 0 ; i < rows ; i++)
                {
                    for(size_t j = 0 ; j < columns ; j++)
                    {
                        for(size_t k = 0 ; k < channels ; k++)
                        {
                            elements_temp[k * rows * columns + i * columns + j] = elements[k * rows * columns + i * columns + j];
                        }
                    }
                }
                elements_temp[c * rows * columns + a * columns + b] = value;
                (*count) -= 1;
                count = count_temp;
                elements = elements_temp;
            }
        }
    }

    void random_generation(T min, T max)  //only for T = int, float, double
    {
        T t;
        int a = 0;
        float b = 0.0f;
        double c = 0.1;
        srand((int)time(0));
        if((typeid(t).name() == typeid(a).name()) and (rows * columns * channels != 0) and (count != NULL) and (elements != NULL))  //T = int
        {
            for(size_t k = 0 ; k < channels ; k++)
            {
                for(size_t i = 0; i < rows ; i++)
                {
                    for(size_t j = 0 ; j < columns ; j++)
                    {
                        elements[k * rows * columns + i * columns + j] = min + 1.0 * (rand() % RAND_MAX) / RAND_MAX * (max - min);
                    }
                }
            }
        }
        else if((typeid(t).name() == typeid(b).name()) and (rows * columns * channels != 0) and (count!= NULL) and (elements != NULL)) //T = float
        {
            for(size_t k = 0 ; k < channels ; k++)
            {
                for(size_t i = 0; i < rows ; i++)
                {
                    for(size_t j = 0 ; j < columns ; j++)
                    {
                        elements[k * rows * columns + i * columns + j] = min + 1.0 * (rand() % RAND_MAX) / RAND_MAX * (max - min);
                    }
                }
            }
        } 
        else if((typeid(t).name() == typeid(c).name()) and (rows * columns * channels != 0) and (count!= NULL) and (elements != NULL))  //T = double
        {
            for(size_t k = 0 ; k < channels ; k++)
            {
                for(size_t i = 0; i < rows ; i++)
                {
                    for(size_t j = 0 ; j < columns ; j++)
                    {
                        elements[k * rows * columns + i * columns + j] = min + 1.0 * (rand() % RAND_MAX) / RAND_MAX * (max - min);
                    }
                }
            }
        }
        else
        {
            cout<<"The type of the elements of the matrix does not support this function!"<<endl;
        }
    }

    friend std::ostream & operator<<(std::ostream & os, const Matrix & m)  //friend function is not a member function
    {
        std::string str = "";
        if(m.rows == 0 || m.columns == 0 || m.channels == 0 || m.count == NULL || m.elements == NULL)
        {
            str = "This is an invalid matrix!\n";
        }
        else
        {
            str = "This is an matrix with rows "+ std::to_string(m.rows) + ", columns "\
            + std::to_string(m.columns) + " and channel " + std::to_string(m.channels)+" .\n";
            for(size_t k = 0 ; k < m.channels ; k++)
            {
                str = str + "The channel " + std::to_string(k) + " is:\n";
                for(size_t i = 0 ; i < m.rows ; i++)
                {
                    for(size_t j = 0 ; j < m.columns ; j++)
                    {
                        str = str + std::to_string(m.elements[k * m.rows * m.columns + i * m.columns + j]) + "  ";
                    }
                    str = str + ";\n";
                }
            }
        }
        os<<str;
        return os;
    }

    friend std::istream & operator>>(std::istream & is, Matrix & m)
    {
        if(m.rows != 0 and m.columns != 0 and m.channels != 0)
        {
            cout<<"For this matrix which has been defined, you cannot input the data! You can change the elements by function change_one_entry."<<endl;
        }

        else if(m.rows == 0 and m.columns == 0 and m.channels == 0 and m.count == NULL and m.elements == NULL)
        {
            cout<<"Please enter the numbers of rows, columns and channels of the matrix, respectively"<<endl;
            size_t a,b,c;
            cin>>a>>b>>c;
            if((a <= 0) || (b <= 0) || (c <= 0))
            {
                cout<<"Illegal input!"<<endl;
                goto flag;
            }
            else
            {
                m.setSize(a, b, c);
                for(size_t k = 0 ; k < m.channels ; k++)
                {
                    cout<<"Pleasr enter the matrix in channel "<<std::to_string(k);
                    cout<<". To enter a "<< std::to_string(m.rows)<<" by "<< std::to_string(m.columns);
                    cout<<" matrix, please follow the order of row major."<<endl;
                    for(size_t i = 0 ; i < m.rows ; i++)
                    {
                        for(size_t j = 0 ; j < m.columns ; j++)
                        {
                            is >> m.elements [k * m.rows * m.columns + i * m.columns + j];
                        }
                    }
                }
            }

        }

        else
        {
            cout<<"There is something wrong about the matrix which has been defined before!"<<endl;
        }

        flag:
        return is;
    }

    Matrix & operator=(const Matrix & m)  //When using b = a, this constructor will be invoked (different from the copy constructor)
    {
        if(count == NULL and elements == NULL)
        {   
            this->rows = m.rows;
            this->columns = m.columns;
            this->channels = m.channels;
            if(m.count != NULL and m.elements != NULL)
            {
                this->count = m.count;
                (*count) ++;
                this->elements = m.elements;
            }
            else
            {
                this->count = NULL;
                this->elements = NULL;
            }
        }
        else if(count == m.count || elements == m.elements)
        {
            cout << "Error of assignment since you can't assign a matrix to yourself!" << endl;
        }
        else if(count != NULL and elements != NULL)
        {   
            if(*(this->count)==1)
            {
                delete []this->count;
                delete []this->elements;
                count = NULL;
                elements = NULL;
            }
            else if(*(this->count)>1)
            {
                (*count) --;
            }
            rows = m.rows;
            columns = m.columns;
            channels = m.channels;
            count = m.count;
            if(count != NULL)
            {
                (*count) ++;
            }
            elements = m.elements;
        }
        else
        {
            cout << "Error of assignment!" << endl;
        }
        return *this;
    }

    Matrix operator+(const Matrix & m) const
    {
        if(count == NULL || elements == NULL || m.count == NULL || m.elements == NULL)
        {
            cout<<"Failure of addition!"<<endl;
            Matrix<T> result;
            return result;
        }
        else if((rows == m.rows) and (columns == m.columns) and (channels == m.channels) and (rows * columns * channels != 0))
        {  
            Matrix<T> result(rows, columns, channels);
            #pragma omp parallel for
            for(size_t k = 0 ; k < channels ; k++)
            {
                for(size_t i = 0 ; i < rows ; i++)
                {
                    for(size_t j = 0 ; j < columns ; j++)
                    {
                        //a[rows=i][columns=j][channels=k]=a.elements[k*a.rows*a.columns+i*a.columns+j]
                        result.elements[k * result.rows * result.columns + i * result.columns + j] = \
                        elements[k * rows * columns + i * columns + j] + \
                        m.elements[k * m.rows * m.columns + i * m.columns + j];
                    }
                }
            }
            return result;
        }
        else
        {
            cout<<"Failure of addition!"<<endl;
            Matrix<T> result;
            return result;
        }
    }

    Matrix operator+(T t) const
    {
        if(count == NULL || elements == NULL)
        {
            cout<<"Failure of addition!"<<endl;
            Matrix<T> result;
            return result;
        }
        else if(rows * columns * channels != 0)
        {  
            Matrix<T> result(rows, columns, channels);
            #pragma omp parallel for
            for(size_t k = 0 ; k < channels ; k++)
            {
                for(size_t i = 0 ; i < rows ; i++)
                {
                    for(size_t j = 0 ; j < columns ; j++)
                    {
                        //a[rows=i][columns=j][channels=k]=a.elements[k*a.rows*a.columns+i*a.columns+j]
                        result.elements[k * result.rows * result.columns + i * result.columns + j] = \
                        elements[k * rows * columns + i * columns + j] + t;
                    }
                }
            }
            return result;
        }
        else
        {
            cout<<"Failure of addition!"<<endl;
            Matrix<T> result;
            return result;
        }
    }

    friend Matrix operator+(T t, const Matrix & m)
    {
        return m + t;
    }

    Matrix operator-(const Matrix & m) const
    {
        if(count == NULL || elements == NULL || m.count == NULL || m.elements == NULL)
        {
            cout<<"Failure of subtraction!"<<endl;
            Matrix<T> result;
            return result;
        }
        else if((rows == m.rows) and (columns == m.columns) and (channels == m.channels) and (rows * columns * channels != 0))
        {
            Matrix<T> result(rows, columns, channels);
            #pragma omp parallel for
            for(size_t k = 0 ; k < channels ; k++)
            {
                for(size_t i = 0 ; i < rows ; i++)
                {
                    for(size_t j = 0 ; j < columns ; j++)
                    {
                        result.elements[k * result.rows * result.columns + i * result.columns + j] = \
                        elements[k * rows * columns + i * columns + j] - \
                        m.elements[k * m.rows * m.columns + i * m.columns + j];
                    }
                }
            }
            return result;
        }
        else
        {
            cout<<"Failure of subtraction!"<<endl;
            Matrix<T> result;
            return result;
        }
    }

    Matrix operator-(T t) const
    {
        if(count == NULL || elements == NULL)
        {
            cout<<"Failure of subtraction!"<<endl;
            Matrix<T> result;
            return result;
        }
        else if(rows * columns * channels != 0)
        {  
            Matrix<T> result(rows, columns, channels);
            #pragma omp parallel for
            for(size_t k = 0 ; k < channels ; k++)
            {
                for(size_t i = 0 ; i < rows ; i++)
                {
                    for(size_t j = 0 ; j < columns ; j++)
                    {
                        //a[rows=i][columns=j][channels=k]=a.elements[k*a.rows*a.columns+i*a.columns+j]
                        result.elements[k * result.rows * result.columns + i * result.columns + j] = \
                        elements[k * rows * columns + i * columns + j] - t;
                    }
                }
            }
            return result;
        }
        else
        {
            cout<<"Failure of subtraction!"<<endl;
            Matrix<T> result;
            return result;
        }
    }

    friend Matrix operator-(T t, const Matrix & m)
    {
        if(m.count == NULL || m.elements == NULL)
        {
            cout<<"Failure of subtraction!"<<endl;
            Matrix<T> result;
            return result;
        }
        else if(m.rows * m.columns * m.channels != 0)
        {  
            Matrix<T> result(m.rows, m.columns, m.channels);
            #pragma omp parallel for
            for(size_t k = 0 ; k < m.channels ; k++)
            {
                for(size_t i = 0 ; i < m.rows ; i++)
                {
                    for(size_t j = 0 ; j < m.columns ; j++)
                    {
                        //a[rows=i][columns=j][channels=k]=a.elements[k*a.rows*a.columns+i*a.columns+j]
                        result.elements[k * result.rows * result.columns + i * result.columns + j] = \
                        t - m.elements[k * m.rows * m.columns + i * m.columns + j];
                    }
                }
            }
            return result;
        }
        else
        {
            cout<<"Failure of subtraction!"<<endl;
            Matrix<T> result;
            return result;
        }
    }

    Matrix operator*(const Matrix & m) const
    {
        if(count == NULL || elements == NULL || m.count == NULL || m.elements == NULL)
        {
            cout<<"Failure of multiplication!"<<endl;
            Matrix<T> result;
            return result;
        }
        else if((columns == m.rows) and (channels == m.channels) and (rows * columns * channels != 0))
        {
            Matrix<T> result(rows, m.columns, channels);
            #pragma omp parallel for
            for(size_t k = 0 ; k < channels ; k++)
            {

                for(size_t i = 0 ; i < result.rows ; i++)
                {
                    for(size_t j = 0 ; j < result.columns ; j++)
                    {
                        for(size_t l = 0 ; l < columns ; l++)
                        {
                            result.elements[k * result.rows * result.columns + i * result.columns + j] += \
                            elements[k * rows * columns + i * columns + l] * \
                            m.elements[k * m.rows * m.columns + l * m.columns + j];
                        }   
                    }
                }

            }
            return result;
        }
        else
        {
            cout<<"Failure of multiplication!"<<endl;
            Matrix<T> result;
            return result;
        }
    }
    
    Matrix operator*(T t) const
    {
        if(count == NULL || elements == NULL)
        {
            cout<<"Failure of multiplication!"<<endl;
            Matrix<T> result;
            return result;
        }
        else if(rows * columns * channels != 0)
        {
            Matrix<T> result(rows, columns, channels);
            #pragma omp parallel for
            for(size_t k = 0 ; k < channels ; k++)
            {

                for(size_t i = 0 ; i < result.rows ; i++)
                {
                    for(size_t j = 0 ; j < result.columns ; j++)
                    {
                        result.elements[k * result.rows * result.columns + i * result.columns + j] = \
                        elements[k * rows * columns + i * columns + j] * t;
                
                    }
                }

            }
            return result;
        }
        else
        {
            cout<<"Failure of multiplication!"<<endl;
            Matrix<T> result;
            return result;
        }
    }

    friend Matrix operator*(T t, const Matrix & m)
    {
        return m * t;
    }

    bool operator==(const Matrix & m) const
    {
        if(rows != m.rows || columns != m.columns || channels != m.channels)
        {
            return false;
        }
        else if(count == NULL || m.count == NULL || elements == NULL || m.elements == NULL)
        {
            cout<<"There is an illegal matrix!"<<endl;
            return false;
        }
        else
        {
            for(size_t i = 0 ; i < rows ; i++)
            {
                for(size_t j = 0 ; j < columns ; j++)
                {
                    for(size_t k = 0 ; k < channels ; k++)
                    {
                        if(elements[k * rows * columns + i * columns + j] != m.elements[k * rows * columns + i * columns + j])
                        {
                            return false;
                        }
                    }
                }
            }
            return true;
        }
    }

    Matrix<double> inverse()  const  //Note: the output is a matrix of double
    {
        if(rows * columns * channels != 0 and rows == columns and count != NULL and elements != NULL)
        {
            Matrix<double> result(rows, columns, channels);
            for(size_t k = 0; k < channels; k++)
            {
                T * temp = new T[rows * columns]();
                for(size_t i = 0; i < rows; i++)
                {
                    for(size_t j = 0; j < columns; j++)
                    {
                        temp[i * columns + j] = elements[k * rows * columns + i * columns + j];
                    }
                }
                double * result_k = new double[rows * columns]();
                result_k = inverse_for_one_channel<T>(temp, rows);
                if(result_k != NULL)
                {
                    for(size_t i = 0; i < rows; i++)
                    {
                        for(size_t j = 0; j < columns; j++)
                        {
                            result.change_one_entry(i, j, k, result_k[i * columns + j]);
                        }
                    }
                }
                else
                {
                    for(size_t i = 0; i < rows; i++)
                    {
                        for(size_t j = 0; j < columns; j++)
                        {
                            result.change_one_entry(i, j, k, 0);
                        }
                    }
                }
                delete []result_k;
                delete []temp;
            }
            return result;
        }
        else
        {
            Matrix<double> result;
            return result;
        }
    }

    size_t * get_pointer_count() const
    {
        return count;
    }

    T * get_pointer_elements() const
    {
        return elements;
    }


};



template<typename T>
class ROI_of_Matrix : public Matrix<T>
{
  private:
    size_t BeginRowIndex; 
    size_t BeginColumnIndex;
    size_t EndRowIndex;
    size_t EndColumnIndex;

  public:
    ROI_of_Matrix(): Matrix<T>()
    {
        BeginRowIndex = 0;
        BeginColumnIndex = 0;
        EndRowIndex = 0;
        EndColumnIndex = 0;
    }

    ROI_of_Matrix(size_t rows, size_t columns): Matrix<T>(rows, columns)
    {
        BeginRowIndex = 0;
        BeginColumnIndex = 0;
        EndRowIndex = 0;
        EndColumnIndex = 0;
    }

    ROI_of_Matrix(size_t rows, size_t columns, size_t channels): Matrix<T>(rows, columns)
    {
        cout<<"The class 'ROI_of_Matrix' is only open for matrices with channel 1!"<<endl;
        BeginRowIndex = 0;
        BeginColumnIndex = 0;
        EndRowIndex = 0;
        EndColumnIndex = 0;
    }

    ROI_of_Matrix(size_t rows, size_t columns, size_t b_r_i, size_t b_c_i, size_t e_r_i, size_t e_c_i): Matrix<T>(rows, columns)
    {
        if(b_r_i <= rows - 1 and b_c_i <= columns - 1 and e_r_i <= rows - 1 and e_c_i <= columns - 1 \
        and b_r_i <= e_r_i and b_c_i <= e_c_i \
        and ((b_r_i - e_r_i) != 0 or (b_c_i - e_c_i) != 0) )
        {
            BeginRowIndex = b_r_i;
            BeginColumnIndex = b_c_i;
            EndRowIndex = e_r_i;
            EndColumnIndex = e_c_i;
        }
        else
        {
            cout<<"Failed to define ROI as you like since the arguments are inconsistent or incorrect!"<<endl;
            BeginRowIndex = 0;
            BeginColumnIndex = 0;
            EndRowIndex = 0;
            EndColumnIndex = 0;
        }
    }

    ROI_of_Matrix(size_t rows, size_t columns, size_t channels, size_t b_r_i, size_t b_c_i, size_t e_r_i, size_t e_c_i): Matrix<T>(rows, columns, 1)
    {
        cout<<"The class 'ROI_of_Matrix' is only open for matrices with channel 1!"<<endl;
        if(b_r_i <= rows - 1 and b_c_i <= columns - 1 and e_r_i <= rows - 1 and e_c_i <= columns - 1 \
        and b_r_i <= e_r_i and b_c_i <= e_c_i\
        and ((b_r_i - e_r_i) != 0 or (b_c_i - e_c_i) != 0) )
        {
            BeginRowIndex = b_r_i;
            BeginColumnIndex = b_c_i;
            EndRowIndex = e_r_i;
            EndColumnIndex = e_c_i;
        }
        else
        {
            cout<<"Failed to define ROI as you like since the arguments are inconsistent or incorrect!"<<endl;
            BeginRowIndex = 0;
            BeginColumnIndex = 0;
            EndRowIndex = 0;
            EndColumnIndex = 0;
        }
    }
 
    ROI_of_Matrix(const ROI_of_Matrix<T> & m): Matrix<T>(m)
    {
        BeginRowIndex = m.BeginRowIndex;
        BeginColumnIndex = m.BeginColumnIndex;
        EndRowIndex = m.EndRowIndex;
        EndColumnIndex = m.EndColumnIndex;
    } 

    ~ROI_of_Matrix(){}

    void showROI()  //不对子类做<<的重载是考虑到对子类也想保留输出整个矩阵（而不仅仅是ROI）的函数
    {
        if(this->rows == 0 || this->columns == 0 || this->channels == 0 || this->count == NULL || this->elements == NULL)
        {
            cout<<"This is an invalid matrix, and thus invalid ROI!"<<endl;
        }
        else if(BeginRowIndex == 0 and BeginColumnIndex == 0 and EndRowIndex == 0 and EndColumnIndex == 0)
        {
            cout<<"The ROI of the matrix is equal to itself!"<<endl;
            cout<<(*this)<<endl;
        }
        else
        {
            cout<<"This is an matrix with rows "<<std::to_string(this->rows)\
            <<" and columns "<<std::to_string(this->columns)<<"."<<endl;
            //cout<<(*this)<<endl;
            for(size_t i = 0 ; i < this->rows ; i++)
            {
                for(size_t j = 0 ; j < this->columns ; j++)
                {
                    cout<<this->elements[i * this->columns + j]<<"  ";
                }
                cout<<endl;
            }
            cout<<"And the ROI is form row "<<std::to_string(BeginRowIndex)<<", column "\
            <<std::to_string(BeginColumnIndex)<<" to row "<<std::to_string(EndRowIndex)<<", column "\
            <<std::to_string(EndColumnIndex)<<endl;
            for(size_t i = 0 ; i < this->rows ; i++)
            {
                for(size_t j = 0 ; j < this->columns ; j++)
                {
                    if(i >= BeginRowIndex and i <= EndRowIndex and j >= BeginColumnIndex and j <= EndColumnIndex)
                    {
                        cout<<std::to_string(this->elements[i * this->columns + j])<<"  ";
                    }
                }
                if(i >= BeginRowIndex and i <= EndRowIndex)
                {
                    cout<<";"<<endl;
                }
            }
        }
    }

    Matrix<T> turn_to_matrix()  //if you want to do something to the ROI, please turn it to a new matrix
    {
        if(this->rows == 0 || this->columns == 0 || this->channels == 0 \
        || this->count == NULL || this->elements == NULL)  //case1
        {
            cout<<"The matrix in class 'ROI_of_Matirx' is an invalid matrix, so the output matirx is also an invalid matrix!"<<endl;
            Matrix<T> result;
            return result;
        }
        else if(BeginRowIndex == 0 and BeginColumnIndex == 0 and EndRowIndex == 0 and EndColumnIndex == 0)  //case2
        {
            Matrix<T> result(this->rows, this->columns);
            for(size_t i = 0 ; i < this->rows ; i++)
            {
                for(size_t j = 0 ; j < this->columns ; j++)
                {
                    result.change_one_entry(i, j, 0, this->elements[i * this->columns + j]);
                }
            }
            return result;
        }
        else  //case3
        {
            Matrix<T> result(EndRowIndex - BeginRowIndex + 1, EndColumnIndex - BeginColumnIndex + 1);
            T * value = new T[(EndRowIndex - BeginRowIndex + 1) * (EndColumnIndex - BeginColumnIndex + 1)];
            size_t flag = 0;
            for(size_t i = 0 ; i < this->rows ; i++)
            {
                for(size_t j = 0 ; j < this->columns ; j++)
                {
                    if(i >= BeginRowIndex and i <= EndRowIndex and j >= BeginColumnIndex and j <= EndColumnIndex)
                    {
                        value[flag] = this->elements[i * this->columns + j];
                        flag ++;
                    }
                }
            }
            result.setData(value, (EndRowIndex - BeginRowIndex + 1) * (EndColumnIndex - BeginColumnIndex + 1));
            delete []value;
            return result;
        }
    }

    void turned_from_matrix(Matrix<T> & m,size_t b_r_i, size_t b_c_i, size_t e_r_i, size_t e_c_i)
    {
        if(m.getRows() != 0 and m.getColumns() != 0 and m.getChannels() == 1 and m.get_pointer_count() != NULL and m.get_pointer_elements() != NULL)
        {
            if(this->count == NULL and this->elements == NULL)
            {
                this->rows = m.getRows();
                this->columns = m.getColumns();
                this->channels = 1;
                this->count = m.get_pointer_count();
                (*(this->count)) ++;
                this->elements = m.get_pointer_elements();
                if(b_r_i <= this->rows - 1 and b_c_i <= this->columns - 1 and e_r_i <= this->rows - 1 \
                and e_c_i <= this->columns - 1 and b_r_i <= e_r_i and b_c_i <= e_c_i \
                and ((b_r_i - e_r_i) != 0 or (b_c_i - e_c_i) != 0) )
                {
                    BeginRowIndex = b_r_i;
                    BeginColumnIndex = b_c_i;
                    EndRowIndex = e_r_i;
                    EndColumnIndex = e_c_i;
                }
                this->BeginRowIndex = b_r_i;
                this->BeginColumnIndex = b_c_i;
                this->EndRowIndex = e_r_i;
                this->EndColumnIndex = e_c_i;
            }
            else
            {
                cout<<"This ROI_matrix is not empty! Turning failed!"<<endl;
            }
        }
        else
        {
            cout<<"This matrix does not qualify for conversion to ROI! Turning failed!"<<endl;
        }
    }

};


template<>
Matrix<float> Matrix<float>::operator*(const Matrix<float> & m) const
{
    if(count == NULL || elements == NULL || m.count == NULL || m.elements == NULL)
    {
        cout<<"Failure of multiplication!"<<endl;
        Matrix<float> result;
        return result;
    }
    else if((columns == m.rows) and (channels == m.channels) and (rows * columns * channels != 0))
    {
        Matrix<float> m_trans(m.columns, m.rows, m.channels);
        for(size_t k = 0; k < channels; k++)
        {
            for (size_t i = 0; i < m.rows; i++)
            {
                for (size_t j = 0; j < m.columns; j++)
                {
                    m_trans.elements[k * m_trans.rows * m_trans.columns + j * m_trans.columns + i] =\
                    m.elements[k * m.rows * m.columns + i * m.columns + j];                    
                }
            }
        }
        Matrix<float> result(rows, m.columns, channels);
        #pragma omp parallel for
        for(size_t k = 0 ; k < channels ; k++)
        {

            for(size_t i = 0 ; i < result.rows ; i++)
            {
                for(size_t j = 0 ; j < result.columns ; j++)
                {
                    size_t l;

                    for (l = 0; l < (columns / 8) * 8; l += 8)
                    {
                        float sum[8] __attribute__((aligned(256))) = {0};
                        __m256 aa = _mm256_loadu_ps(elements + (k * rows * columns + i * (columns) + l));
                        __m256 bb = _mm256_loadu_ps(m_trans.elements + (k * m_trans.rows * m_trans.columns + j * (m_trans.columns) + l));
                        __m256 cc = _mm256_mul_ps(aa, bb);

                        _mm256_storeu_ps(sum, cc);
                        result.elements[k * result.rows * result.columns + i * result.columns + j] +=\
                        (sum[0] + sum[1] + sum[2] + sum[3] + sum[4] + sum[5] + sum[6] + sum[7]);
                    }
                        
                    for(l = (columns / 8) * 8; l < columns; l++)
                    {
                        result.elements[k * result.rows * result.columns + i * result.columns + j] +=\
                        elements[k * rows * columns + i * columns + l] * m.elements[k * m.rows * m.columns + l * m.columns + j];
                    }

                }
           }

        }
        return result;
    }
    else
    {
        cout<<"Failure of multiplication!"<<endl;
        Matrix<float> result;
        return result;
    }
}

template<>
Matrix<double> Matrix<double>::operator*(const Matrix<double> & m) const
{
    if(count == NULL || elements == NULL || m.count == NULL || m.elements == NULL)
    {
        cout<<"Failure of multiplication!"<<endl;
        Matrix<double> result;
        return result;
    }
    else if((columns == m.rows) and (channels == m.channels) and (rows * columns * channels != 0))
    {
        Matrix<double> m_trans(m.columns, m.rows, m.channels);
        for(size_t k = 0; k < channels; k++)
        {
            for (size_t i = 0; i < m.rows; i++)
            {
                for (size_t j = 0; j < m.columns; j++)
                {
                    m_trans.elements[k * m_trans.rows * m_trans.columns + j * m_trans.columns + i] =\
                    m.elements[k * m.rows * m.columns + i * m.columns + j];                    
                }
            }
        }
        Matrix<double> result(rows, m.columns, channels);
        #pragma omp parallel for
        for(size_t k = 0 ; k < channels ; k++)
        {

            for(size_t i = 0 ; i < result.rows ; i++)
            {
                for(size_t j = 0 ; j < result.columns ; j++)
                {
                    size_t l;

                    for (l = 0; l < (columns / 4) * 4; l += 4)
                    {
                        double sum[4] __attribute__((aligned(256))) = {0};
                        __m256d aa = _mm256_loadu_pd(elements + (k * rows * columns + i * (columns) + l));
                        __m256d bb = _mm256_loadu_pd(m_trans.elements + (k * m_trans.rows * m_trans.columns + j * (m_trans.columns) + l));
                        __m256d cc = _mm256_mul_pd(aa, bb);

                        _mm256_storeu_pd(sum, cc);
                        result.elements[k * result.rows * result.columns + i * result.columns + j] +=\
                        (sum[0] + sum[1] + sum[2] + sum[3]);
                    }
                        
                    for(l = (columns / 4) * 4; l < columns; l++)
                    {
                        result.elements[k * result.rows * result.columns + i * result.columns + j] +=\
                        elements[k * rows * columns + i * columns + l] * m.elements[k * m.rows * m.columns + l * m.columns + j];
                    }

                }
            }

        }
        return result;
    }
    else
    {
        cout<<"Failure of multiplication!"<<endl;
        Matrix<double> result;
        return result;
    }
}

template<typename T>
T det_for_one_channel(T * array,size_t rows)  //使用这个函数时，要检测一下满不满足rows^2=矩阵的大小
{
    size_t columns = rows;
    if(rows!=0)
    {
        T result;
        if(rows==1)
        {
            result = array [0];
        }
        else
        {
            result = 0;
            for(size_t i=0; i < rows; i++)
            {
                T * temp = new T[(rows - 1) * (columns - 1)]();
                for(size_t k=0; k < rows - 1; k++)
                {
                    for(size_t l=0; l < columns - 1; l++)
                    {
                        if(l < i)
                        {
                            temp[k * (columns - 1) + l] = array[(k + 1) * columns + l];
                        }
                        else
                        {
                            temp[k * (columns - 1) + l] = array[(k + 1) * columns + (l + 1)];
                        }
                    }
                } 
                if( (1 + i + 1) % 2 == 0)
                {
                    result = result + array[0 * columns + i] * det_for_one_channel(temp, rows - 1);
                }
                else
                {
                    result = result - array[0 * columns + i] * det_for_one_channel(temp, rows - 1);
                }
                delete []temp;
            }
        }
        return result;
    }
    else
    {
        return 0;
    }
}

template<typename T>
double * inverse_for_one_channel(T * array,size_t rows)
{
    size_t columns = rows;
    T det_array = det_for_one_channel(array, rows);
    if(rows >= 2 && det_array != 0)
    {
        double * result = new double[rows * columns]();
        for(size_t i = 0; i < rows; i++)
        {
            for(size_t j = 0; j < columns; j++)
            {
                T * temp = new T[(rows - 1) * (columns - 1)]();
                for(size_t ii = 0; ii < rows - 1; ii++)
                {
                    for(size_t jj = 0; jj < columns - 1; jj++)
                    {
                        if( ii < i && jj < j)
                        {
                            temp[ii * (columns - 1) + jj] = array[ii * columns + jj];
                        }
                        else if(ii < i && jj >= j)
                        {
                            temp[ii * (columns - 1) + jj] = array[ii * columns + jj + 1];
                        }
                        else if(ii >= i && jj < j)
                        {
                            temp[ii * (columns - 1) + jj] = array[(ii + 1) * columns + jj];
                        }
                        else
                        {
                            temp[ii * (columns - 1) + jj] = array[(ii + 1) * columns + jj + 1];
                        }
                    }
                }
                if((i + 1 + j + 1) % 2 == 0)
                {
                    result[j * columns + i] = det_for_one_channel(temp, rows - 1)/det_array;
                } 
                else
                {
                    result[j * columns + i] = - det_for_one_channel(temp, rows - 1)/det_array;
                }
                delete []temp;
            }
        }
        return result;
    }
    else if(rows == 1 && det_array != 0)
    {
        double * result = new double[1]();
        result[0] = 1/array[0];
        return result;
    }
    else
    {
        double * result = NULL;
        return result;
    }
}


#endif