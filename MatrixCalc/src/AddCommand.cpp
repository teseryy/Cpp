#include "AddCommand.h"

AddCommand::AddCommand(std::shared_ptr<Matrix> A, std::shared_ptr<Matrix> B) {
    this->A = A;
    this->B = B;
}

void AddCommand::execute() {
    //checking the conformity of the dimensions of the matrices
    if (A->getRows() != B->getRows() || A->getColumns() != B->getColumns()){
        throw InvalidSizeException();
    }

    int rows = A->getRows();
    int columns = A->getColumns();

    std::shared_ptr<DenseMatrix> newMatrix(new DenseMatrix(rows, columns));

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            newMatrix->setValue(i, j, A->getValue(i, j) + B->getValue(i, j));
        }
    }

    if (newMatrix->canBeSparse()){
        std::shared_ptr<SparseMatrix> newSparse(newMatrix->toSparse());
        res = newSparse;
        return;
    }

    res = newMatrix;
    return;
}

std::shared_ptr<Matrix> AddCommand::getResult() {
    return res;
}