#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

// Реализуйте здесь
// * класс Matrix
// * оператор ввода для класса Matrix из потока istream
// * оператор вывода класса Matrix в поток ostream
// * оператор проверки на равенство двух объектов класса Matrix
// * оператор сложения двух объектов класса Matrix

class Matrix {
  public:
    Matrix() {
    }

    Matrix(const int numRows, const int numCols) {
        Reset(numRows, numCols);
    }

    int GetNumRows() const {
        return data.size();
    }

    int GetNumColumns() const {
        if (data.size()) {
            return data[0].size();
        }
        return 0;
    }

    void Reset(const int numRows, const int numCols) {
        if (numRows < 0 || numCols < 0) {
            throw out_of_range("Number of rows and columns can't be negative");
        }
        if (numRows == 0 || numCols == 0) {
            data = vector<vector<int>>();
        } else {
            data = vector<vector<int>>(numRows, vector<int>(numCols, 0));
        }
    }

    int At(const int row, const int col) const {
        CheckBoundaries(row, col);
        return data[row][col];
    }

    int& At(const int row, const int col) {
        CheckBoundaries(row, col);
        return data[row][col];
    }

  private:
    vector<vector<int>> data;

    void CheckBoundaries(const int row, const int col) const {
        if (row < 0 || row >= GetNumRows() ||
            col < 0 || col >= GetNumColumns()) {
                throw out_of_range("Index is out of range");
        }
    }
};

istream& operator>>(istream& stream, Matrix& matrix) {
    if (stream) {
        int rows, cols;
        stream >> rows >> cols;
        matrix = Matrix(rows, cols);
        for (int i = 0; i < matrix.GetNumRows(); i++) {
            for (int j = 0; j < matrix.GetNumColumns(); j++) {
                stream >> matrix.At(i, j);
            }
        }
    }
    return stream;
}

ostream& operator<<(ostream& stream, const Matrix matrix) {
    if (stream) {
        stream << matrix.GetNumRows() << " " << matrix.GetNumColumns() << endl;
        for (int i = 0; i < matrix.GetNumRows(); i++) {
            for (int j = 0; j < matrix.GetNumColumns(); j++) {
                stream << matrix.At(i, j) << " ";
            }
            stream << endl;
        }
    }
    return stream;
}

bool operator==(const Matrix lhs, const Matrix rhs) {
    if (lhs.GetNumColumns() != rhs.GetNumColumns() ||
        lhs.GetNumRows() != rhs.GetNumRows()) {
        return false;
    }
    for (int i = 0; i < lhs.GetNumRows(); i++) {
        for (int j = 0; j < lhs.GetNumColumns(); j++) {
            if (lhs.At(i, j) != rhs.At(i, j)) {
                return false;
            }
        }
    }
    return true;
}

Matrix operator+(const Matrix lhs, const Matrix rhs) {
    if (lhs.GetNumColumns() != rhs.GetNumColumns() ||
        lhs.GetNumRows() != rhs.GetNumRows()) {
        throw invalid_argument("Matrix sizes are different");
    }
    Matrix matrix(lhs.GetNumRows(), lhs.GetNumColumns());
    for (int i = 0; i < lhs.GetNumRows(); i++) {
        for (int j = 0; j < lhs.GetNumColumns(); j++) {
            matrix.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
        }
    }
    return matrix;
}

int main() {
  Matrix one;
  Matrix two;

  cin >> one >> two;
  cout << one + two << endl;
  return 0;
}
