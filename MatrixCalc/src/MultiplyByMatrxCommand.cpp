#include "MultiplyByMatrxCommand.h"

MultiplyByMatrxCommand::MultiplyByMatrxCommand(std::shared_ptr<Matrix> A, std::shared_ptr<Matrix> B) {
    this->A = A;
    this->B = B;
}

void MultiplyByMatrxCommand::execute() {
    //checking the conformity of the dimensions of the matrices
    if (A->getColumns() != B->getRows()){
        throw InvalidSizeException();
    }

    int rows = A->getRows();
    int columns = B->getColumns();
    int commonSize = A->getColumns();

    std::shared_ptr<DenseMatrix> newMatrix(new DenseMatrix(rows, columns));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            double value = 0.0;
            for (int k = 0; k < commonSize; k++) {
                value += A->getValue(i, k) * B->getValue(k, j);
            }
            newMatrix->setValue(i, j, value);
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

std::shared_ptr<Matrix> MultiplyByMatrxCommand::getResult() {
    return res;
}