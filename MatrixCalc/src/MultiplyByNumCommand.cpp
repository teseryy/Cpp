#include "MultiplyByNumCommand.h"

MultiplyByNumCommand::MultiplyByNumCommand(std::shared_ptr<Matrix> A, double num) {
    this->A = A;
    this->num = num;
}

void MultiplyByNumCommand::execute() {
    int rows = A->getRows();
    int columns = A->getColumns();

    std::shared_ptr<DenseMatrix> newMatrix(new DenseMatrix(rows, columns));

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            newMatrix->setValue(i, j, A->getValue(i, j) * num);
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

std::shared_ptr<Matrix> MultiplyByNumCommand::getResult() {
    return res;
}