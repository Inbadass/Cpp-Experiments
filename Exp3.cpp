#include <iostream>
#include <cassert>
using namespace std;

class Matrix
{
private:
    int data[2][2];
public:
    Matrix(int a = 0, int b = 0, int c = 0, int d = 0)
    {
        data[0][0] = a;
        data[0][1] = b;
        data[1][0] = c;
        data[1][1] = d;
    }

    // Operator +
    Matrix operator+(const Matrix &m) const
    {
        Matrix result;
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                result.data[i][j] = data[i][j] + m.data[i][j];
        return result;
    }

    // Operator -
    Matrix operator-(const Matrix &m) const
    {
        Matrix result;
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                result.data[i][j] = data[i][j] - m.data[i][j];
        return result;
    }

    // Operator *
    Matrix operator*(const Matrix &m) const
    {
        Matrix result;
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                result.data[i][j] = 0;
                for (int k = 0; k < 2; k++)
                    result.data[i][j] += data[i][k] * m.data[k][j];
            }
        }
        return result;
    }

    // Operator ==
    bool operator==(const Matrix &m) const
    {
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                if (data[i][j] != m.data[i][j])
                    return false;
        return true;
    }

    // Transpose
    Matrix transpose() const
    {
        return Matrix(data[0][0], data[1][0], data[0][1], data[1][1]);
    }

    // Operator []
    int* operator[](int index)
    {
        return data[index];
    }

    // Operator <<
    friend ostream& operator<<(ostream &out, const Matrix &m)
    {
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
                out << m.data[i][j] << " ";
            out << endl;
        }
        return out;
    }
};

int main()
{
    Matrix A(1, 2, 3, 4);
    Matrix B(5, 6, 7, 8);

    Matrix sum = A + B;
    Matrix diff = A - B;
    Matrix product = A * B;
    Matrix trans = A.transpose();

    // Unit Tests
    assert(sum[0][0] == 6);
    assert(sum[1][1] == 12);
    assert(diff[0][0] == -4);
    assert(diff[1][1] == -4);
    assert(product[0][0] == 19);
    assert(product[0][1] == 22);
    assert(product[1][0] == 43);
    assert(product[1][1] == 50);
    assert(trans[0][1] == 3);
    assert(trans[1][0] == 2);
    assert(A == Matrix(1, 2, 3, 4));
    assert(!(A == B));

    cout << "Matrix A:" << endl << A;
    cout << "Matrix B:" << endl << B;
    cout << "Addition of Matrices:" << endl << sum;
    cout << "Subtraction of Matrices:" << endl << diff;
    cout << "Multiplication of Matrices:" << endl << product;
    cout << "Transpose of A:" << endl << trans;
    cout << "All unit tests passed successfully." << endl;
    return 0;
}
