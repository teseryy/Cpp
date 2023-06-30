#include "SliceCommand.h"

SliceCommand::SliceCommand(std::shared_ptr<Matrix> A, std::vector<int> offset) {
    this->A = A;
    this->offset = offset;
}

void SliceCommand::execute() {
    int startRow = offset[0] - 1;
    int endRow = offset[1];
    int startColumn = offset[2] - 1;
    int endColumn = offset[3];

    //checking the parameters and dimensions of the matrix
    if (startRow > endRow || startColumn > endColumn || startRow > A->getRows() || endRow > A->getRows() || startColumn > A->getColumns() || endColumn > A->getColumns()){
        throw InvalidOffsetException();
    }

    std::shared_ptr<Matrix> newMatrix(new DenseMatrix(endRow - startRow, endColumn - startColumn));

    for (int i = startRow; i < endRow; i++){
        for (int j = startColumn; j < endColumn; j++){
            newMatrix->setValue(i - startRow, j - startColumn, A->getValue(i, j));
        }
    }

    res = newMatrix;
}

std::shared_ptr<Matrix> SliceCommand::getResult() {
    return res;
}
