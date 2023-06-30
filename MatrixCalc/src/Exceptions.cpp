#include "Exceptions.h"

MatrixException::MatrixException(const std::string &message) : errorMessage(message) {}

const char *MatrixException::what() const noexcept {
    return errorMessage.c_str();
}

InvalidSizeException::InvalidSizeException() : MatrixException("ERROR : Bad dimension of matrices.") {}

InvalidArgumentException::InvalidArgumentException() : MatrixException("ERROR : Wrong type of the argument.") {}

InvalidOperationOrderException::InvalidOperationOrderException() : MatrixException("ERROR : Wrong order of operations or missing argument.") {}

InvalidOffsetException::InvalidOffsetException() : MatrixException("ERROR : Wrong offset.") {}

InvalidInputException::InvalidInputException() : MatrixException("ERROR : Input Error.") {}

InverseNotExistsException::InverseNotExistsException() : MatrixException("ERROR : Inverse matrix does not exist.") {}

UnknownVariableException::UnknownVariableException() : MatrixException("ERROR: Using unknown variable.") {}

MissingArgumentException::MissingArgumentException() : MatrixException("ERROR : Missing argument.") {}

WrongFilePathException::WrongFilePathException() : MatrixException("ERROR : Wrong file path.") {}

NoPermissionException::NoPermissionException() : MatrixException("ERROR : Don't have permissions to change file.") {}

UnsavedDataException::UnsavedDataException() : MatrixException("Warning : There are unsaved data after the previous operations that will be deleted.") {}
