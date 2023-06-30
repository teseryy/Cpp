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
 * @brief Class representing a matrix subtraction operation.
 * This class inherits from the Command base class and represents an operation to subtract one matrix from another.
 */
class SubtractCommand : public Command{
private:
    /**
     * @brief The matrix to be subtracted from.
     */
    std::shared_ptr<Matrix> A;
    /**
     * @brief The matrix to subtract.
     */
    std::shared_ptr<Matrix> B;
    /**detailed
     * @brief The resulting subtracted matrix.
     */
    std::shared_ptr<Matrix> res;
public:
    /**
     * @brief Constructs a SubtractCommand object.
     * @param A The matrix to be subtracted from.
     * @param B The matrix to subtract.
     */
    SubtractCommand(std::shared_ptr<Matrix> A, std::shared_ptr<Matrix> B);

    /**
     * @brief Executes the matrix subtraction operation.
     * This method performs the matrix subtraction operation and stores the result in the res attribute.
     */
    void execute() override;

    /**
     * @brief Retrieves the resulting subtracted matrix.
     * @return The subtracted matrix.
     */
    std::shared_ptr<Matrix> getResult();

};


