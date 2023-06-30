#include "InverseCommand.h"

InverseCommand::InverseCommand(std::shared_ptr<Matrix> A) {
    this->A = A;
}

void InverseCommand::execute() {
    //matrix size check
    if (A->getColumns() != A->getRows()){
        throw InvalidSizeException();
    }

    //check for matrix nonsingularity
    double det = A->getDeterminant();
    if (det == 0){
        throw InverseNotExistsException();
    }

    res = A->getInvertible();
}

std::shared_ptr<Matrix> InverseCommand::getResult() {
    return res;
}
