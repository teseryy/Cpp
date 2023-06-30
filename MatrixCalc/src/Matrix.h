#pragma once

#include <iostream>
#include <string>
#include <memory>

/**
 *@brief Abstract class for matrix representation.
 *The Matrix class represents an abstract matrix and and represents operations that
 *will be different for matrices of different types, such as setting a value of an element,
 *getting the value of an element, calculating the determinant,
 *obtaining the inverse matrix, transposing, etc.
 */
class Matrix{
    /**
     * @brief Number of rows in the matrix.
     */
    int rows;
    /**
     * @brief Number of columns in the matrix
     */
    int columns;
public:
    /**
     * @brief Constructor for the Matrix class.
     * @param rows Number of rows in the matrix.
     * @param columns Number of columns in the matrix.
     */
    Matrix(int rows, int columns);
    /**
     * @brief Virtual destructor for the Matrix class.
     */
    virtual ~Matrix() = default;

    /**
     * @brief Set the value of an element in the matrix.
     * @param row Row index of the element.
     * @param column Column index of the element.
     * @param value Value to set.
     */
    virtual void setValue(int row, int column, double value) = 0;
    /**
     * @brief Get the value of an element in the matrix.
     * @param row Row index of the element.
     * @param column Column index of the element.
     * @return Value of the element.
     */
    virtual double getValue(int row, int column) const = 0;
    /**
     * @brief Calculate the determinant of the matrix.
     * @return Determinant value of the matrix.
     */
    virtual double getDeterminant() const = 0;
    /**
     * @brief Get the inverse matrix.
     * @return Shared pointer to the Matrix object containing the inverse matrix.
     */
    virtual std::shared_ptr<Matrix> getInvertible () const = 0;
    /**
     * @brief Create a copy of the current matrix.
     * @return Pointer to a new Matrix object, which is a copy of the current matrix.
     */
    virtual Matrix* copy() const = 0;
    /**
     * @brief Transforms the matrix to upper triangular form using the Gaussian elimination method.
     */
    virtual void toTM () = 0;
    /**
     * @brief Transposes the matrix by swapping its rows and columns.
     */
    virtual void transpose() = 0;

    /**
     * @brief Convert the matrix to a string representation.
     * @return String representation of the matrix.
     */
    std::string toString() const;

    /**
     * @brief Set the number of rows in the matrix.
     * @param newRow Number of rows.
     */
    void setRow(int newRow);
    /**
     * @brief Set the number of columns in the matrix.
     * @param newColumn Number of columns.
     */
    void setColumn(int newColumn);
    /**
     * @brief Get the number of columns in the matrix.
     * @return Number of columns.
     */
    int getColumns() const;
    /**
     * @brief Get the number of rows in the matrix.
     * @return Number of rows.
     */
    int getRows() const;

    /**
     * @brief Overloaded stream insertion operator to print the matrix.
     * @param out Reference to the output stream.
     * @param item Reference to the Matrix object to be printed.
     * @return Reference to the output stream.
     */
    friend std::ostream &operator<<(std::ostream &out, const Matrix &item);
};