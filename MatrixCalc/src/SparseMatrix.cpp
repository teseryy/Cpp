#include "SparseMatrix.h"


SparseMatrix::SparseMatrix(int row, int column) : Matrix(row, column) {}

SparseMatrix::SparseMatrix(const SparseMatrix &other) : Matrix(other.getRows(), other.getColumns()){
    this->determinantSign = other.determinantSign;
    this->values = other.values;
}

void SparseMatrix::setValue(int row, int column, double value) {
    if (is_equal(value, 0)){
        return;
    }
    int idx = getIndex(row, column);
    values[idx] = value;
}

double SparseMatrix::getValue(int row, int column) const {
    int index = getIndex(row, column);
    auto it = values.find(index);
    if (it != values.end()) {
        return it->second;
    } else {
        return 0.0;
    }
}

double SparseMatrix::getDeterminant() const {

    SparseMatrix newMatrix(*this);

    newMatrix.toTM();

    int numRows = newMatrix.getRows();

    double det = 1;

    for (int i = 0; i < numRows; i++){
        det *= newMatrix.getValue(i, i);
    }

    det *= newMatrix.determinantSign;
    if (is_equal(det, 0)){
        det = 0;
    }

    return det;
}

int SparseMatrix::getIndex(int row, int column) const {
    return row * getColumns() + column;
}

void SparseMatrix::swapRows(int row1, int row2) {
    int numCols = getColumns();
    for (int col = 0; col < numCols; col++) {
        int index1 = getIndex(row1, col);
        int index2 = getIndex(row2, col);
        std::swap(values[index1], values[index2]);
    }
}

void SparseMatrix::addRows(int sourceRow, int targetRow, double factor) {
    int numCols = getColumns();
    for (int col = 0; col < numCols; col++) {
        int sourceIndex = getIndex(sourceRow, col);
        int targetIndex = getIndex(targetRow, col);
        values[targetIndex] += factor * values[sourceIndex];
        if (is_equal(values[targetIndex], 0)){
            values[targetIndex] = 0;
        }
    }
}

void SparseMatrix::toTM() {
    int pivotRow = 0;
    int pivotCol = 0;

    int numRows = this->getRows();
    int numCols = this->getColumns();

    while (pivotRow < numRows && pivotCol < numCols) {

        int maxRow = pivotRow;
        double maxValue = std::abs(this->getValue(pivotRow, pivotCol));

        for (int i = pivotRow + 1; i < numRows; i++) {
            //Finding the largest leading element of the rows
            double value = std::abs(this->getValue(i, pivotCol));
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
        if (pivotRow != maxRow) {
            this->swapRows(pivotRow, maxRow);
            this->determinantSign *= -1;
        }

        for (int i = pivotRow + 1; i < numRows; i++) {
            double factor = -this->getValue(i, pivotCol) / this->getValue(pivotRow, pivotCol);
            this->addRows(pivotRow, i, factor);
        }

        pivotRow++;
        pivotCol++;
    }
}

void SparseMatrix::transpose() {
        std::unordered_map<int, double> transposedValues;

        int numCols = getColumns();
        int numRows = getRows();

        for (const auto& entry : values) {
            int index = entry.first;
            int row = index / numRows;
            int col = index % numCols;
            int transposedIndex = col * numRows + row;
            transposedValues[transposedIndex] = entry.second;
        }

        std::swap(numRows, numCols);
        values = std::move(transposedValues);
    }

Matrix *SparseMatrix::copy() const {
    SparseMatrix* newMatrix = new SparseMatrix(getRows(), getColumns());
    newMatrix->determinantSign = this->determinantSign;
    newMatrix->values = this->values;

    return newMatrix;
}

double SparseMatrix::getCofactor(int row, int col) const {
    int numRows = getRows();
    int numCols = getColumns();

    SparseMatrix minorMatrix(numRows - 1, numCols - 1);
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

    if (is_equal(cofactor, 0)){
        return 0;
    }
    return cofactor;
}

std::shared_ptr<Matrix>SparseMatrix::getInvertible() const {

    int numRows = getRows();
    int numCols = getColumns();
    std::shared_ptr<Matrix> inverseMatrix(new SparseMatrix(numRows, numCols));

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

bool SparseMatrix::is_equal(double x, double y) const{
    double eps = 0.00000005;
    return std::fabs(x - y) < eps;
}
