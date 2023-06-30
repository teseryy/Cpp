#pragma once

#include "Command.h"

#include <memory>
#include <vector>

#include "Matrix.h"
#include "DenseMatrix.h"
#include "SparseMatrix.h"
#include "Exceptions.h"

/**
 * @brief Class representing a matrix slicing operation.
 * This class inherits from the Command base class and represents an operation to slice a matrix into a smaller matrix based on specified offsets.
 */
class SliceCommand : public Command{
private:
    /**
     * @brief The matrix to be sliced.
     */
    std::shared_ptr<Matrix> A;
    /**
     * @brief The resulting sliced matrix.
     */
    std::shared_ptr<Matrix> res;
    /**
     * @brief The offsets for slicing.
     */
    std::vector<int> offset;
public:
    /**
     * @brief Constructs a SliceCommand object.
     * @param A The matrix to be sliced.
     * @param offset The offsets for slicing.
     */
    SliceCommand(std::shared_ptr<Matrix> A, std::vector<int> offset);

    /**
     * @brief Executes the matrix slicing operation.
     * This method performs the matrix slicing operation based on the specified offsets and stores the result in the res attribute.
     */
    void execute() override;

    /**
     * @brief Retrieves the resulting sliced matrix.
     * @return The sliced matrix.
     */
    std::shared_ptr<Matrix> getResult();
};

