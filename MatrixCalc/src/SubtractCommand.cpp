#include "SubtractCommand.h"

SubtractCommand::SubtractCommand(std::shared_ptr<Matrix> A, std::shared_ptr<Matrix> B) {
    this->A = A;
    this->B = B;
}

void SubtractCommand::execute() {
    //checking the conformity of the dimensions of the matrices
    if (A->getColumns() != B->getColumns() || A->getRows() != B->getRows()){
        throw InvalidSizeException();
    }

    int rows = A->getRows();
    int columns = A->getColumns();

    std::shared_ptr<DenseMatrix> newMatrix(new DenseMatrix(rows, columns));

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            newMatrix->setValue(i, j, A->getValue(i, j) - B->getValue(i, j));
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

std::shared_ptr<Matrix> SubtractCommand::getResult() {
    return res;
}