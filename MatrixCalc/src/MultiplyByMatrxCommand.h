#pragma once

#include "Command.h"

#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <functional>
#include <iterator>

#include "Matrix.h"
#include "DenseMatrix.h"
#include "SparseMatrix.h"
#include "Exceptions.h"

/**
 * @brief Class representing a matrix multiplication operation.
 * This class inherits from the Command base class and represents an operation to multiply one matrix by another.
 */
class MultiplyByMatrxCommand : public Command{
private:
    /**
     * @brief The first matrix for multiplication.
     */
    std::shared_ptr<Matrix> A;
    /**
     * @brief The second matrix for multiplication.
     */
    std::shared_ptr<Matrix> B;
    /**
     * @brief The resulting matrix.
     */
    std::shared_ptr<Matrix> res;
public:
    /**
     * @brief Constructs a MultiplyByMatrixCommand object.
     * @param A The first matrix for multiplication.
     * @param B The second matrix for multiplication.
     */
    MultiplyByMatrxCommand(std::shared_ptr<Matrix> A, std::shared_ptr<Matrix> B);

    /**
     * @brief Executes the matrix multiplication operation.
     * This method multiplies matrix A by matrix B and stores the result in the res attribute.
     */
    void execute() override;

    /**
     * @brief Retrieves the resulting matrix of the multiplication.
     * @return The resulting matrix of the multiplication.
     */
    std::shared_ptr<Matrix> getResult();
};

