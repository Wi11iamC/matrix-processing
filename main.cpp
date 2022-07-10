#include <iostream>
#include <stdint.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"

#define CHANNEL_NUM 3
using namespace std;
template <typename T>
class Vector
{
    friend ostream &operator<<(ostream &os, const Vector &n);
    friend istream &operator>>(istream &is, Vector &n);

private:
    T *arr;

    int capacity;

    int current;

public:
    Vector()
    {
        arr = new T[1];
        capacity = 1;
        current = 0;
    }

    void push(T data)
    {

        if (current == capacity)
        {
            T *temp = new T[2 * capacity];

            // copying old array elements to new array
            for (int i = 0; i < capacity; i++)
            {
                temp[i] = arr[i];
            }

            // deleting previous array
            delete[] arr;
            capacity *= 2;
            arr = temp;
        }

        // Inserting data
        arr[current] = data;
        current++;
    }

    // function to add element at any index
    void push(T data, int index)
    {

        // if index is equal to capacity then this
        // function is same as push defined above
        if (index == capacity)
            push(data);
        else
            arr[index] = data;
    }

    // function to extract element at any index
    T get(int index)
    {

        // if index is within the range
        if (index < current)
            return arr[index];
    }

    // function to delete last element
    void pop() { current--; }

    // function to get size of the vector
    int size() { return current; }

    // function to get capacity of the vector
    int getcapacity() { return capacity; }

    Vector(const Vector &vector)
    {
        current = vector.current;
        capacity = vector.capacity;
        for (int i = 0; i < current; i++)
        {
            push(vector.arr[i]);
        }
    }

    virtual Vector<T> operator=(const Vector &vector)
    {
        Vector<T> temp;
        temp.current = vector.current;
        temp.capacity = vector.capacity;
        for (int i = 0; i < current; i++)
        {
            temp.push(vector.arr[i]);
        }
        return temp;
    };
    virtual Vector<T> operator+(const Vector &vector)
    {
        Vector<T> temp;
        for (int i = 0; i < current; i++)
        {
            temp.push(arr[i] + vector.arr[i]);
        }
        return temp;
    };

    virtual Vector<T> operator-(const Vector &vector)
    {
        Vector<T> temp;
        for (int i = 0; i < current; i++)
        {
            temp.push(arr[i] - vector.arr[i]);
        }
        return temp;
    };

    virtual Vector<T> &operator*(const Vector &vector) { return *this; };

    T operator[](int index)
    {
        // if index is within the range
        if (index < current)
            return arr[index];
        return -1;
    };

    // function to print array elements
    virtual void print()
    {
        for (int i = 0; i < current; i++)
        {
            cout << arr[i] << " ";
        }
    }
};

class Matrix : public Vector<double>
{
private:
    Vector<double> *a;
    int r, c;

public:
    Matrix() // Default Constructor
    {
        int row, col;
        cout << "Enter Number of Rows and Cols " << endl;
        cin >> row >> col;
        r = row;
        c = col;
        a = new Vector<double>[row];
        init();
    };
    Matrix(int row, int col, Vector<double> b[])
    {
        a = b;
        r = row;
        c = col;
    };
    Matrix(const Matrix &matrix) // Copy Constructor
    {
        r = matrix.r;
        c = matrix.c;
        a = matrix.a;
    };
    void init()
    {
        double element;
        for (int i = 0; i < r; i++)
        {
            std::cout << "Enter Elements of row: " << i << endl;
            for (int j = 0; j < c; j++)
            {
                std::cin >> element;
                a[i].push(element);
            }
        }
    };
    int getRows() { return r; };
    int getCols() { return c; };
    void operator=(const Matrix &matrix)
    {
        r = matrix.r;
        c = matrix.c;
        a = matrix.a;
    };
    Matrix operator+(const Matrix &matrix)
    {

        if (r != matrix.r || c != matrix.c)
        {
            cout << "CANNOT ADD" << endl;
            return *this;
        }
        Vector<double> *b = new Vector<double>[r];
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                b[i].push(a[i][j] + matrix.a[i][j]);
            }
        }
        return Matrix(r, c, b);
    };
    Matrix operator-(const Matrix &matrix)
    {
        if (r != matrix.r || c != matrix.c)
        {
            cout << "CANNOT SUBTRACT" << endl;
            return *this;
        }
        Vector<double> *b = new Vector<double>[r];
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                b[i].push(a[i][j] - matrix.a[i][j]);
            }
        }
        return Matrix(r, c, b);
    };
    Matrix operator*(const Matrix &matrix)
    {
        if (c != matrix.r)
        {
            cout << "CANNOT Matrix MULTIPLY" << endl;
            return *this;
        }
        Vector<double> *b = new Vector<double>[r];
        double sum;
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < matrix.c; j++)
            {
                for (int k = 0; k < matrix.r; k++)
                {
                    sum += a[i][k] * matrix.a[k][j];
                }
                b[i].push(sum);
                sum = 0;
            }
        }
        return Matrix(r, c, b);
    };
    Vector<double> &operator[](int index)
    {
        // if index is within the range

        return a[index];
    };
    void print()
    {
        cout << "Matrix is: " << endl;
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                cout << a[i][j] << " ";
            }
            cout << "\n";
        }
    };
    ~Matrix(){};
    // Bonus Problem 4:
    Matrix transpose()
    {
        Vector<double> *b = new Vector<double>[r];
        for (int i = 0; i < c; i++)
            for (int j = 0; j < r; j++)
                b[i].push(a[j][i]);

        return Matrix(c, r, b);
    }
};

int main(int argc, char const *argv[])
{
    /* Test code for Matrix Class */
    Matrix m1;
    cout << "m1: ";
    m1.print();
    Matrix m2 = m1;
    cout << "m2: ";
    m2.print();
    Matrix m3 = m1 + m2;
    cout << "m3: ";
    m3.print();
    Matrix m4 = m1 - m2;
    cout << "m4: ";
    m4.print();
    Matrix m5 = m1 * m2;
    cout << "m5: ";
    m5.print();
    Matrix m6 = m1.transpose();
    cout << "m6: ";
    m6.print();
    cout << "Here is m6[0][1]: " << m6[0][1] << endl;

    return 0;
}