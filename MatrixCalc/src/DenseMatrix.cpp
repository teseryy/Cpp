#include "DenseMatrix.h"

DenseMatrix::DenseMatrix(int row, int column) : Matrix(row, column) {
    values.resize(row);

    for (int i = 0; i < row; i++){
        values[i].resize(column, 0);
    }
}

DenseMatrix::DenseMatrix(const DenseMatrix &other) : Matrix(other.getRows(), other.getColumns()){
    this->determinantSign = other.determinantSign;
    this->values = other.values;
}

void DenseMatrix::setValue(int row, int column, double value) {
    values[row][column] = value;
}

double DenseMatrix::getValue(int row, int column) const {
    return values[row][column];
}

Matrix *DenseMatrix::copy() const {
    DenseMatrix* newMatrix = new DenseMatrix(getRows(), getColumns());
    newMatrix->determinantSign = this->determinantSign;
    newMatrix->values = this->values;

    return newMatrix;
}

bool DenseMatrix::canBeSparse(void) {
    //lower bound on the number of zeros
    double border = 0.65;
    int countZero = 0;

    int numRows = getRows();
    int numCols = getColumns();

    for (int i = 0; i < numRows; i++){
        for (int j = 0; j < numCols; j++){
            if (getValue(i, j) == 0.0){
                countZero++;
            }
        }
    }

    if (countZero / (numRows*numCols) >= border){
        return true;
    }

    return false;
}

SparseMatrix* DenseMatrix::toSparse(void) {
    int numRows = getRows();
    int numCols = getColumns();

    SparseMatrix* newMatrix = new SparseMatrix(numRows, numCols);

    for (int i = 0; i < numRows; i++){
        for (int j = 0; j < numCols; j++){
            newMatrix->setValue(i, j, getValue(i, j));
        }
    }

    return newMatrix;
}

void DenseMatrix::toTM() {
    int pivotRow = 0;
    int pivotCol = 0;
    int numRows = getRows();
    int numCols = getColumns();

    while (pivotRow < numRows && pivotCol < numCols) {
        int maxRow = pivotRow;
        double maxValue = std::abs(getValue(pivotRow, pivotCol));

        for (int i = pivotRow + 1; i < numRows; i++) {
            //Finding the largest leading element of the rows
            double value = std::abs(getValue(i, pivotCol));
            if (value > maxValue) {
                maxRow = i;
                maxValue = value;
            }
        }

        if (maxValue == 0) {
            pivotCol++;
            continue;
        }

        //The row with the largest leading element is moved to the pivotRow
        if (pivotRow!= maxRow){
            //Rows are swapped
            std::swap(values[pivotRow], values[maxRow]);

            determinantSign *= -1;
        }

        for (int i = pivotRow + 1; i < numRows; i++) {
            double factor = -getValue(i, pivotCol) / getValue(pivotRow, pivotCol);
            for (int col = pivotCol; col < numCols; col++) {
                values[i][col] += factor * values[pivotRow][col];
                if (is_equal(values[i][col], 0)){
                    values[i][col] = 0;
                }
            }
        }

        pivotRow++;
        pivotCol++;
    }
}

double DenseMatrix::getDeterminant() const {

    DenseMatrix newMatrix(*this);
    newMatrix.toTM();

    int numRows = newMatrix.getRows();
    double det = 1;

    for (int i = 0; i < numRows; i++){
        det *= newMatrix.getValue(i, i);
    }
    det *= newMatrix.determinantSign;

    return det;
}

std::shared_ptr<Matrix> DenseMatrix::getInvertible() const {

    int numRows = getRows();
    int numCols = getColumns();
    std::shared_ptr<Matrix> inverseMatrix(new DenseMatrix(numRows, numCols));

    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            double cofactor = getCofactor(row, col);

            inverseMatrix->setValue(row, col, cofactor);
        }
    }

    inverseMatrix->transpose();

    double determinant = getDeterminant();

    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            double value = inverseMatrix->getValue(row, col);
            inverseMatrix->setValue(row, col, value / determinant);
        }
    }

    return inverseMatrix;
}

double DenseMatrix::getCofactor(int row, int col) const {
    int numRows = getRows();
    int numCols = getColumns();

    DenseMatrix minorMatrix(numRows - 1, numCols - 1);
    int minorRow = 0;

    //Filling in the matrix of minors
    for (int i = 0; i < numRows; i++) {
        if (i == row) {
            continue;
        }

        int minorCol = 0;
        for (int j = 0; j < numCols; j++) {
            if (j == col) {
                continue;
            }

            double value = getValue(i, j);
            minorMatrix.setValue(minorRow, minorCol, value);
            minorCol++;
        }

        minorRow++;
    }

    //Finding the determinant of a matrix of minors
    double minorDeterminant = minorMatrix.getDeterminant();
    int sign = (row + col) % 2 == 0 ? 1 : -1;
    double cofactor = minorDeterminant * sign;

    if (cofactor == 0.0){
        return 0;
    }
    return cofactor;
}

void DenseMatrix::transpose() {
    int numRows = getRows();
    int numCols = getColumns();

    std::vector<std::vector<double>> transposedValues(numCols, std::vector<double>(numRows, 0));

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            transposedValues[j][i] = values[i][j];
        }
    }

    values = transposedValues;
    setColumn(numRows);
    setRow(numCols);
}

bool DenseMatrix::is_equal(double x, double y) const{
    double eps = 0.00000005;
    return std::fabs(x - y) < eps;
}
