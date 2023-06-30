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

/**
 * @brief Class representing a matrix multiplication by scalar operation.
 * This class inherits from the Command base class and represents an operation to multiply a matrix by a scalar number.
 */
class MultiplyByNumCommand : public Command{
private:
    /**
     * @brief The matrix for multiplication.
     */
    std::shared_ptr<Matrix> A;
    /**
     * @brief The scalar number for multiplication.
     */
    double num;
    /**
     * @brief The resulting matrix.
     */
    std::shared_ptr<Matrix> res;
public:
    /**
     * @brief Constructs a MultiplyByNumCommand object.
     * @param A The matrix for multiplication.
     * @param num The scalar number for multiplication.
     */
    MultiplyByNumCommand(std::shared_ptr<Matrix> A, double num);

    /**
     * @brief Executes the matrix multiplication by scalar operation.
     *  This method multiplies each element of matrix A by the scalar number and stores the result in the res attribute.
     */
    void execute() override;

    /**
     * @brief Retrieves the resulting matrix of the multiplication.
     * @return The resulting matrix of the multiplication.
     */
    std::shared_ptr<Matrix> getResult();
};

