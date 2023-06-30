#include "ConcatenateCommand.h"

ConcatenateCommand::ConcatenateCommand(std::shared_ptr<Matrix> A, std::shared_ptr<Matrix> B, bool byRows) {
    this->A = A;
    this->B = B;
    this->byRows = byRows;
}

void ConcatenateCommand::execute() {
    //checking the conformity of the dimensions of the matrices
    if (byRows){
        if (A->getColumns() != B->getColumns()){
            throw InvalidSizeException();
        }
    }
    else{
        if (A->getRows() != B->getRows()){
            throw InvalidSizeException();
        }
    }

    std::shared_ptr<Matrix> newMatrix;

    if (byRows){
        int rows = B->getRows() + A->getRows();
        int columns = A->getColumns();
        int BRows = B->getRows();

        std::shared_ptr<Matrix> result(new DenseMatrix(rows, columns));

        int ARows = A->getRows();
        int AColumns = A->getColumns();

        //filling the first half with the first matrix
        for (int i = 0; i < ARows; i++){
            for (int j = 0; j < AColumns; j++){
                result->setValue(i, j, A->getValue(i, j));
            }
        }
        //filling the second half with the second matrix
        for (int i = BRows; i < rows; i++){
            for (int j = 0; j < columns; j++){
                result->setValue(i, j, B->getValue(i-BRows, j));
            }
        }

        newMatrix = result;
    }
    else{
        int columns = B->getColumns() + A->getColumns();
        int rows = A->getRows();
        int BColumns = B->getColumns();

        std::shared_ptr<Matrix> result(new DenseMatrix(rows, columns));

        int ARows = A->getRows();
        int AColumns = A->getColumns();

        //filling the first half with the first matrix
        for (int i = 0; i < ARows; i++){
            for (int j = 0; j < AColumns; j++){
                result->setValue(i, j, A->getValue(i, j));
            }
        }
        //filling the second half with the second matrix
        for (int i = 0; i < rows; i++){
            for (int j = BColumns; j < columns; j++){
                result->setValue(i, j, B->getValue(i, j-BColumns));
            }
        }
        newMatrix = result;
    }

    res = newMatrix;
}

std::shared_ptr<Matrix> ConcatenateCommand::getResult() {
    return res;
}
