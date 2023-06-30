#pragma once

#include "Command.h"

#include <memory>

#include "Matrix.h"

/**
 * @brief Class representing a rank computation operation for a matrix.
 * This class inherits from the Command base class and represents an operation to compute the rank of a matrix.
 */
class RankCommand : public Command{
private:
    /**
     * @brief The matrix for which the rank will be computed.
     */
    std::shared_ptr<Matrix> A;
    /**
     * @brief The resulting rank of the matrix.
     */
    int rank;
public:
    /**
     * @brief Constructs a RankCommand object.
     * @param A The matrix for which the rank will be computed.
     */
    RankCommand(std::shared_ptr<Matrix> A);

    /**
     * @brief Executes the rank computation operation.
     * This method computes the rank of the matrix A and stores the result in the rank attribute.
     */
    void execute() override;

    /**
     * @brief Retrieves the rank of the matrix.
     * @return The rank of the matrix.
     */
    int getResult();
};

