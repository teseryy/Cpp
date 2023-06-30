#pragma once

#include <cstdlib>
#include <string>

/**
 * @brief The Command class represents a base class for matrix operations.
 * The Command class is an abstract class that defines the execute() method.
 * Subclasses of Command can implement specific matrix operations by overriding the execute() method.
 * This class follows the Command design pattern, allowing for encapsulation of operations and decoupling of the invoker and the receiver.
 */
class Command {
public :
    /**
     * @brief Executes the matrix operation.
     */
    virtual void execute() = 0;
};


