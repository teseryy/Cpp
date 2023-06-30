#pragma once

#include <exception>
#include <string>

/**
 * @brief Base class for MatrixCalculator exceptions.
 * This class inherits from std::exception and serves as the base class for all MatrixCalculator-related exceptions.
 */
class MatrixException : public std::exception {
public:
    /**
     * @brief Constructs a MatrixException object with a custom error message.
     * @param message The error message describing the exception.
     */
    MatrixException(const std::string& message);
    /**
    * @brief Retrieves the error message associated with the exception.
    * @return The error message.
    */
    virtual const char* what() const noexcept;

private:
    /**
    * @brief The error message associated with the exception.
    */
    std::string errorMessage;
};

/**
 * @brief Exception indicating an invalid matrices dimension.
 */
class InvalidSizeException : public MatrixException {
public:
    /**
     * @brief Constructs an InvalidSizeException object.
     */
    InvalidSizeException();
};

/**
 * @brief Exception indicating an invalid argument.
 */
class InvalidArgumentException : public MatrixException {
public:
    /**
     * @brief Constructs an InvalidArgumentException object.
     */
    InvalidArgumentException();
};

/**
 * @brief Exception indicating an invalid operation order for matrices.
 */
class InvalidOperationOrderException : public MatrixException {
public:
    /**
     * @brief Constructs an InvalidOperationOrderException object.
     */
    InvalidOperationOrderException();
};

/**
 * @brief Exception indicating an invalid offset value for matrix slicing.
 */
class InvalidOffsetException : public MatrixException {
public:
    /**
     * @brief Constructs an InvalidOffsetException object.
     */
    InvalidOffsetException();
};

/**
 * @brief Exception indicating an invalid input for matrix operations.
 */
class InvalidInputException : public MatrixException {
public:
    /**
     * @brief Constructs an InvalidInputException object.
     */
    InvalidInputException();
};

/**
 * @brief Exception indicating that the inverse of a matrix does not exist.
 */
class InverseNotExistsException : public MatrixException {
public:
    /**
     * @brief Constructs an InverseNotExistsException object.
     */
    InverseNotExistsException();
};

/**
 * @brief Exception indicating an unknown variable in matrix operations.
 */
class UnknownVariableException : public MatrixException {
public:
    /**
     * @brief Constructs an UnknownVariableException object.
     */
    UnknownVariableException();
};

/**
 * @brief Exception indicating a missing argument for a matrix operation.
 */
class MissingArgumentException : public MatrixException {
public:
    /**
     * @brief Constructs a MissingArgumentException object.
     */
    MissingArgumentException();
};

/**
 * @brief Exception indicating an incorrect file path for matrix data.
 */
class WrongFilePathException : public MatrixException {
public:
   /**
    * @brief Constructs a WrongFilePathException object.
    */
    WrongFilePathException();
};

/**
 * @brief Exception indicating a lack of permission for matrix operations.
 */
class NoPermissionException : public MatrixException {
public:
    /**
     * @brief Constructs a NoPermissionException object.
     */
    NoPermissionException();
};

/**
 * @brief Exception indicating unsaved data for a matrix.
 */
class UnsavedDataException : public MatrixException {
public:
    /**
     * @brief Constructs an UnsavedDataException object.
     */
    UnsavedDataException();
};
