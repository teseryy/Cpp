#include "Matrix.h"

Matrix::Matrix(int rows, int columns) : rows(rows), columns(columns) {}

int Matrix::getRows() const{
    return rows;
}

int Matrix::getColumns() const{
    return columns;
}

std::ostream &operator<<(std::ostream &out, const Matrix &item) {
    out << item.toString();
    return out;
}

void Matrix::setRow(int newRow) {
    rows = newRow;
}

void Matrix::setColumn(int newColumn) {
    columns = newColumn;
}

std::string Matrix::toString() const{
    std::string newStr;
    int numRows = getRows();
    int numCols = getColumns();
    newStr.push_back('[');

    bool isFirstNum = true;
    bool isFirstRow = true;

    for (int i = 0; i < numRows; i++){
        if (isFirstRow) {
            newStr += "[";
            isFirstRow = false;
        }
        else{
            newStr += ", ";
            newStr += "[";
        }
        for (int j = 0; j < numCols; j++){
            if (isFirstNum){
                newStr += std::to_string(getValue(i, j));
                isFirstNum = false;
            }
            else{
                newStr += ", ";
                newStr += std::to_string(getValue(i, j));
            }
        }
        newStr += "]";
        isFirstNum = true;
    }

    newStr += "]";

    return newStr;
}
