#pragma once

#include "Command.h"

#include <memory>

#include "Matrix.h"
#include "Exceptions.h"

/**
 * @brief Class representing a determinant calculation operation.
 * This class inherits from the Command base class and represents an operation to calculate the determinant of a matrix.
 */
class DeterminantCommand : public Command{
private:
    /**
     * @brief The matrix for which to calculate the determinant.
     */
    std::shared_ptr<Matrix> A;
    /**
     * @brief The calculated determinant value.
     */
    double det;
public:
    /**
     * @brief Constructs a DeterminantCommand object.
     * @param A The matrix for which to calculate the determinant.
     */
    DeterminantCommand(std::shared_ptr<Matrix> A);

    /**
     * @brief Executes the determinant calculation operation.
     * This method performs the determinant calculation for the matrix A and stores the result in the det attribute.
     */
    void execute() override;

    /**
     * @brief Retrieves the calculated determinant value.
     * @return The calculated determinant value.
     */
    double getResult();
};

