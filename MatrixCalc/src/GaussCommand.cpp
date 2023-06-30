#include "GaussCommand.h"

GaussCommand::GaussCommand(std::shared_ptr<Matrix> A) {
    this->A = A;
}

void GaussCommand::execute() {
    std::shared_ptr<Matrix> newMatrix(A->copy());

    newMatrix->toTM();

    res = newMatrix;
}

std::shared_ptr<Matrix> GaussCommand::getResult() {
    return res;
}
