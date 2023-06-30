#pragma once

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <unordered_map>
#include <algorithm>
#include <memory>
#include <functional>
#include <iterator>
#include <exception>

#include "Matrix.h"
#include "SparseMatrix.h"
#include "DenseMatrix.h"
#include "AddCommand.h"
#include "ConcatenateCommand.h"
#include "DeterminantCommand.h"
#include "GaussCommand.h"
#include "InverseCommand.h"
#include "MultiplyByMatrxCommand.h"
#include "MultiplyByNumCommand.h"
#include "RankCommand.h"
#include "SliceCommand.h"
#include "SubtractCommand.h"
#include "TransposeCommand.h"
#include "Exceptions.h"

/**
 * @brief Matrix calculator class.
 * This class represents a matrix calculator that reads user commands, executes them, and manages matrices and variables.
 */
class Calculator{
public:
    /**
     * @brief Starts the matrix calculator.
     * This function enters the command loop to read and execute user commands.
     */
    void start ();
private:
    /**
     * @brief Parse a string.
     * The function reads a string and parses it into variables (matrices or numbers) or commands, which are then processed.
     * @param str The string to parse.
     */
    void perform (const std::string& str);
    /**
     * @brief Reads commands from a file.
     * This function reads a sequence of commands from the specified file and executes them, using stack to keep temporary variables.
     * @param inFile The input file containing the commands.
     */
    void readFromFile (const std::string& inFile);
    /**
     * @brief Writes output to a file.
     * This function writes the calculator's memory to the specified file.
     * @param outFile The output file to write the results to.
     */
    void writeToFIle (const std::string& outFile);
    /**
     * @brief The function checks if the string is a command or a variable name, if the string is a command, then it executes it.
     * @param buffer The string to check.
     * @param variableQueue The stack of temporary variables.
     * @param needToSave A flag indicating whether the result needs to be saved.
     * @param byRows A flag indicating whether matrix concatenation should be performed by rows or by columns.
     * @return True if the string is valid, false otherwise.
     */
    bool commandCheck (const std::string& buffer, std::stack<std::string>& variableQueue, bool& needToSave, bool& byRows);

    /**
     * @brief Checks if a string represents a matrix.
     * @param str The string to check.
     * @return True if the string represents a matrix, false otherwise.
     */
    bool isMatrix (const std::string& str);
    /**
     * @brief Checks if a string represents a number.
     * @param str The string to check.
     * @return True if the string represents a number, false otherwise.
     */
    bool isNum (const std::string& str);
    /**
    * @brief Checks if a string represents a word (variable).
    * @param str The string to check.
    * @return True if the string represents a word, false otherwise.
    */
    bool isWord (const std::string& str);

    /**
     * @brief Creates a matrix from a string representation.
     * @param str The string representation of the matrix.
     * @return A shared pointer to the created matrix object.
     */
    std::shared_ptr<Matrix> createMatrix (const std::string& str);
    /**
     * @brief Extracts offset values from a string.
     * @param str The string containing the offset values.
     * @return A vector of offset values.
     */
    std::vector<int> getOffset(std::string str);

    /**
     * @brief Map of matrix objects, with matrix names as keys.
     */
    std::unordered_map<std::string, std::shared_ptr<Matrix>> matrices;
    /**
     * @brief Map of variables, with variable names as keys.
     */
    std::unordered_map<std::string, double> variables;
};
