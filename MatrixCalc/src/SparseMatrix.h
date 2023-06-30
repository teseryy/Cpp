#pragma once

#include <cstdlib>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <memory>
#include <functional>
#include <iterator>
#include <string>
#include <cmath>

#include "Matrix.h"

/**
 * @brief A class representing a sparse matrix, a matrix that mainly consists of zero values.
 * This class inherits from the base Matrix class and provides implementations for
 * the required methods.
 */
class SparseMatrix : public Matrix{
public:
    /**
     * @brief Constructs a sparse matrix with the specified number of rows and columns.
     * @param rows The number of rows in the matrix.
     * @param columns The number of columns in the matrix.
     */
    SparseMatrix(int row, int column);

    /**
     * @brief Constructs a sparse matrix by copying another sparse matrix.
     * @param other The sparse matrix to be copied.
     */
    SparseMatrix(const SparseMatrix& other);

    /**
     * @brief Sets the value at the specified row and column in the sparse matrix.
     * If the value is non-zero, it is stored in the unordered map.
     * @param row The row index.
     * @param column The column index.
     * @param value The value to be set.
     */
    void setValue(int row, int column, double value) override;
    /**
     * @brief Get the value of an element in the matrix at the specified row and column in the sparse matrix.
     * If the value is not stored explicitly in the unordered map, it is assumed to be zero.
     * @param row The row index.
     * @param column The column index.
     * @return The value at the specified position.
     */
    double getValue(int row, int column) const override;
    /**
     * @brief Calculates and returns the determinant of the sparse matrix.
     * @return The determinant of the matrix.
     */
    double getDeterminant() const override;
    /**
     * @brief Returns a shared pointer to a new Matrix object that represents the inverse of the sparse matrix.
     * @return A shared pointer to the inverse matrix.
     */
    std::shared_ptr<Matrix> getInvertible () const override;
    /**
     * @brief Creates a deep copy of the sparse matrix.
     * @return A pointer to the copied matrix.
     */
    Matrix* copy() const override;
    /**
     * @brief Transforms the sparse matrix to upper triangular form using the Gaussian elimination method.
     */
    void toTM () override;
    /**
     * @brief Transposes the sparse matrix by swapping its rows and columns.
     */
    void transpose() override;

private:
    /**
     * @brief A map to store the non-zero values of the matrix.
     * The map uses the index as the key and the corresponding value as the value.
     */
    std::unordered_map<int, double> values;
    /**
     * @brief The sign of the determinant.
     */
    int determinantSign = 1;

    /**
     * @brief Check if two values are equal.
     * @param x The first value.
     * @param y The second value.
     * @return True if the values are equal, false otherwise.
     */
    bool is_equal(double x, double y) const;
    /**
     * @brief Calculate the cofactor of the specified row and column.
     * @param row The row index.
     * @param col The column index.
     * @return The cofactor value.
     */
    double getCofactor(int row, int col) const;
    /**
     * @brief Get the index corresponding to the specified row and column.
     * @param row The row index.
     * @param column The column index.
     * @return The index value.
     */
    int getIndex(int row, int column) const;
    /**
     * @brief Swap two rows of the matrix.
     * @param row1 The index of the first row.
     * @param row2 The index of the second row.
     */
    void swapRows(int row1, int row2);
    /**
     * @brief Add a multiple of one row to another row.
     * @param sourceRow The index of the source row.
     * @param targetRow The index of the target row.
     * @param factor The factor by which the source row is multiplied.
     */
    void addRows(int sourceRow, int targetRow, double factor);
};