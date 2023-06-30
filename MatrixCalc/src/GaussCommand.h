#pragma once

#include "Command.h"

#include <memory>

#include "Matrix.h"

/**
 * @brief Class representing a Gaussian elimination operation.
 * This class inherits from the Command base class and represents an operation to perform Gaussian elimination on a matrix.
 */
class GaussCommand : public Command{
private:
    /**
     * @brief The matrix on which to perform Gaussian elimination.
     */
    std::shared_ptr<Matrix> A;
    /**
     * @brief The resulting matrix after Gaussian elimination.
     */
    std::shared_ptr<Matrix> res;
public:
    /**
     * @brief Constructs a GaussCommand object.
     * @param A The matrix on which to perform Gaussian elimination.
     */
    GaussCommand(std::shared_ptr<Matrix> A);

    /**
     * @brief Executes the Gaussian elimination operation.
     * This method performs Gaussian elimination on the matrix A and stores the result in the res attribute.
     */
    void execute() override;

    /**
     * @brief Retrieves the resulting matrix after Gaussian elimination.
     * @return The resulting matrix after Gaussian elimination.
     */
    std::shared_ptr<Matrix> getResult();
};


