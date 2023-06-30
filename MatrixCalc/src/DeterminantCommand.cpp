#include "DeterminantCommand.h"

DeterminantCommand::DeterminantCommand(std::shared_ptr<Matrix> A) {
    this->A = A;
}

void DeterminantCommand::execute() {
    if (A->getRows() != A->getColumns()){
        throw InvalidSizeException();
    }

    det = A->getDeterminant();
}

double DeterminantCommand::getResult() {
    return det;
}