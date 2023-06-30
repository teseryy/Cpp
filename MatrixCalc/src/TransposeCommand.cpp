#include "TransposeCommand.h"

TransposeCommand::TransposeCommand(std::shared_ptr<Matrix> A) {
    this->A = A;
}

void TransposeCommand::execute() {
    std::shared_ptr<Matrix> newMatrix(A->copy());

    newMatrix->transpose();

    res = newMatrix;
}

std::shared_ptr<Matrix> TransposeCommand::getResult() {
    return res;
}
