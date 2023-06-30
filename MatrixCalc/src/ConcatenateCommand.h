#pragma once

#include "Command.h"

#include <memory>

#include "Matrix.h"
#include "DenseMatrix.h"
#include "SparseMatrix.h"
#include "Exceptions.h"

/**
 * @brief Class representing a matrix concatenation operation.
 * This class inherits from the Command base class and represents an operation to concatenate two matrices.
 */
class ConcatenateCommand : public Command{
private:
    /**
     * @brief The first matrix to concatenate.
     */
    std::shared_ptr<Matrix> A;
    /**
     * @brief The second matrix to concatenate.
     */
    std::shared_ptr<Matrix> B;
    /**
     * @brief The resulting matrix after concatenation.
     */
    std::shared_ptr<Matrix> res;
    /**
     * @brief Flag indicating whether to concatenate by rows or by columns.
     */
    bool byRows = true;
public:
    /**
     * @brief Constructs a ConcatenateCommand object.
     * @param A The first matrix to concatenate.
     * @param B The second matrix to concatenate.
     * @param byRows Flag indicating whether to concatenate by rows (true) or by columns (false).
     */
    ConcatenateCommand(std::shared_ptr<Matrix> A, std::shared_ptr<Matrix> B, bool byRows);

    /**
     * @brief Executes the matrix concatenation operation.
     * This method performs the matrix concatenation operation by concatenating the matrices A and B
     * either by rows or by columns based on the value of the byRows flag. The resulting matrix is stored
     * in the res attribute.
     */
    void execute() override;

    /**
     * @brief Retrieves the resulting matrix after concatenation.
     * @return A shared pointer to the resulting matrix after concatenation.
     */
    std::shared_ptr<Matrix> getResult();
};
