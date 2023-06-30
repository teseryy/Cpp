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
 * @brief The AddCommand class represents a matrix addition operation.
 * The AddCommand class is a concrete subclass of Command that performs the addition
 * of two matrices. It takes two matrices A and B as inputs and calculates their sum.
 */
class AddCommand : public Command{
private:
   /**
    * @brief The first matrix operand.
    */
    std::shared_ptr<Matrix> A;
    /**
    * @brief The second matrix operand.
    */
    std::shared_ptr<Matrix> B;
    /**
    * @brief The result of the addition operation.
    */
    std::shared_ptr<Matrix> res;
public:
    /**
     * @brief Constructs an AddCommand object with the given matrices A and B.
     * @param A The first matrix operand.
     * @param B The second matrix operand.
     */
    AddCommand(std::shared_ptr<Matrix> A, std::shared_ptr<Matrix> B);

    /**
     * @brief Executes the matrix addition operation.
     * The execute() method performs the addition of matrices A and B and stores the result in the res member variable.
     */
    void execute() override;

    /**
     * @brief Returns the result of the matrix addition operation.
     * @return The result of the matrix addition operation as a shared pointer to a Matrix object.
     */
    std::shared_ptr<Matrix> getResult();
};
