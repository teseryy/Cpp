#pragma once

#include "Command.h"

#include <memory>

#include "Matrix.h"
#include "Exceptions.h"

/**
 * @brief Class representing an inverse matrix operation.
 * This class inherits from the Command base class and represents an operation to calculate the inverse of a matrix.
 */
class InverseCommand : public Command{
private:
    /**
     * @brief The matrix for which to calculate the inverse.
     */
    std::shared_ptr<Matrix> A;
    /**
    * @brief The resulting inverse matrix.
    */
    std::shared_ptr<Matrix> res;
public:
    /**
     * @brief Constructs an InverseCommand object.
     * @param A The matrix for which to calculate the inverse.
     */
    InverseCommand(std::shared_ptr<Matrix> A);

    /**
     * @brief Executes the inverse matrix operation.
     * This method calculates the inverse of the matrix A and stores the result in the res attribute.
     */
    void execute() override;

    /**
     * @brief Retrieves the resulting inverse matrix.
     * @return The resulting inverse matrix.
     */
    std::shared_ptr<Matrix> getResult();
};


