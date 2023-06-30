#pragma once

#include "Command.h"

#include <memory>

#include "Matrix.h"

/**
 * @brief Class representing a matrix transpose operation.
 * This class inherits from the Command base class and represents an operation to transpose a matrix.
 */
class TransposeCommand : public Command{
private:
    /**
     * @brief The matrix to be transposed.
     */
    std::shared_ptr<Matrix> A;
    /**
     * @brief The resulting transposed matrix.
     */
    std::shared_ptr<Matrix> res;
public:
    /**
     * @brief Constructs a TransposeCommand object.
     * @param A The matrix to be transposed.
     */
    TransposeCommand(std::shared_ptr<Matrix> A);

    /**
     * @brief Executes the matrix transpose operation.
     * This method performs the matrix transpose operation and stores the result in the res attribute.
     */
    void execute() override;

    /**
     * @brief Retrieves the resulting transposed matrix.
     * @return The transposed matrix.
     */
    std::shared_ptr<Matrix> getResult();
};

