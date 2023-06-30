#pragma once

#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <functional>
#include <iterator>
#include <cmath>

#include "Matrix.h"
#include "SparseMatrix.h"

/**
 * @brief DenseMatrix class represents a dense matrix.
 * This class inherits from the Matrix base class and provides implementations for its virtual methods.
 * A dense matrix stores all its values, including zeros, in a 2D vector.
 */
class DenseMatrix : public Matrix{
public:
    /**
     * @brief Constructor for DenseMatrix.
     * @param row The number of rows in the matrix.
     * @param column The number of columns in the matrix.
     */
    DenseMatrix(int row, int column);
    /**
     * @brief Copy constructor for DenseMatrix.
     * @param other The DenseMatrix to be copied.
     */
    DenseMatrix(const DenseMatrix& other);

    /**
     * @brief Set the value at the specified row and column.
     * @param row The row index.
     * @param column The column index.
     * @param value The value to be set.
     */
    void setValue(int row, int column, double value) override;
    /**
     * @brief Get the value at the specified row and column.
     * @param row The row index.
     * @param column The column index.
     * @return The value at the specified position.
     */
    double getValue(int row, int column) const override;
    /**
     * @brief Calculate the determinant of the matrix.
     * @return The determinant of the matrix.
     */
    double getDeterminant() const override;
    /**
     * @brief Get the invertible version of the matrix.
     * @return A shared pointer to the invertible matrix.
     */
    std::shared_ptr<Matrix> getInvertible () const override;
    /**
     * @brief Transform the matrix to the triangular form.
     * The matrix will be transformed to the upper triangular form.
     */
    void toTM () override;
    /**
     * @brief Create a copy of the matrix.
     * @return A pointer to the copy of the matrix.
     */
    Matrix* copy() const override;
    /**
     * @brief Transpose the matrix.
     */
    void transpose() override;

   /**
    * @brief Check if the dense matrix can be represented as a sparse matrix.
    * @return True if the matrix can be sparse, false otherwise.
    */
    bool canBeSparse ();
    /**
     * @brief Convert the dense matrix to a sparse matrix.
     * @return A pointer to the sparse matrix.
     */
    SparseMatrix* toSparse ();
private:
    /**
     * @brief Calculate the cofactor of the specified row and column.
     * @param row The row index.
     * @param col The column index.
     * @return The cofactor value.
     */
    double getCofactor(int row, int col) const;
    /**
     * @brief Check if two values are equal.
     * @param x The first value.
     * @param y The second value.
     * @return True if the values are equal, false otherwise.
     */
    bool is_equal(double x, double y) const;

    /**
     * @brief A 2D vector to store the values of the matrix.
     * Each row is represented as a vector of values.
     */
    std::vector<std::vector<double>> values;
    /**
     * @brief The sign of the determinant.
     */
    int determinantSign = 1;
};