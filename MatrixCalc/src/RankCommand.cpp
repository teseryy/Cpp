#include "RankCommand.h"

RankCommand::RankCommand(std::shared_ptr<Matrix> A) {
    this->A = A;
}

void RankCommand::execute() {
    rank = 0;
    std::shared_ptr<Matrix> newMatrix(A->copy());

    newMatrix->toTM();

    int rows = A->getRows();
    int columns = A->getColumns();

    //counting non-zero rows
    for (int i = 0; i < rows; i++) {
        bool hasNonZeroElement = false;
        for (int j = 0; j < columns; j++) {
            if (newMatrix->getValue(i, j) != 0) {
                hasNonZeroElement = true;
                break;
            }
        }
        if (hasNonZeroElement) {
            rank++;
        }
    }
}

int RankCommand::getResult() {
    return rank;
}
