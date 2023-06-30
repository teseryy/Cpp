#include "Calculator.h"

void Calculator::start() {
    std::string line;

    std::cout << "The calculator is running, you can start entering data." << std::endl;

    while (getline(std::cin, line)) {
        if (line == "EXIT"){
            break;
        }
        else{
            try {
                perform(line);
            }
            catch (const MatrixException& ex) {
                std::cout << ex.what() << std::endl;
            }
        }
    }

    if (!std::cin.eof()) {
        std::cout << "Calculator turned off successfully" << std::endl;
    }
    else {
        std::cout << "Calculator turned off due to invalid input" << std::endl;
    }
}

void Calculator::perform(const std::string &str) {
    std::string offset;
    std::stack<std::string> variableQueue;
    std::string buffer;
    bool isReading = false;
    bool isReadingMtrx = false;
    bool isReadingNum = false;
    bool byRows = false;
    bool isMtrxClosed = false;
    bool needToSave = false;

    size_t len = str.size();

    for (int i = 0; i < int(len); i++){
        if ((str[i] == ' ' && buffer.empty()) || (str[i] == ' ' && isReading) || (str[i] == '\t' && isReading)){
            continue;
        }
        else if ((str[i] == ' ' || str[i] == '\t') && !isReading && !buffer.empty()){
            //command processing
            try {
                bool res = commandCheck(buffer, variableQueue, needToSave, byRows);

                if (!res){
                    return;
                }
            }
            catch (const MatrixException& ex) {
                std::cout << ex.what() << std::endl;
                return;
            }

            buffer.clear();
        }
        else if (str[i] != ' ' && str[i] != '\t'){
            //string processing, character reading
            if (str[i] == '['){
                isMtrxClosed = false;
                isReading = true;
                isReadingMtrx = true;
                buffer += str[i];
                continue;
            }
            else if (str[i] == ']' && isMtrxClosed){
                buffer += str[i];
                isReading = false;
                isMtrxClosed = false;
                isReadingMtrx = false;

                variableQueue.push(buffer);
                buffer.clear();
            }
            else if (str[i] == ']'){
                buffer += str[i];
                isMtrxClosed = true;
            }
            else if (str[i] == '(' && !isReading){
                isReading = true;
                isReadingNum = true;
                continue;
            }
            else if (isdigit(str[i])){
                buffer += str[i];
            }
            else if (str[i] == ',' && isReadingNum){
                offset += buffer + ",";
                buffer.clear();
            }
            else if (str[i] == '.' || str[i] == ','){
                buffer += str[i];
            }
            else if (isalpha(str[i]) && (isReadingNum || isReadingMtrx)){
                throw InvalidInputException();
            }
            else if (isalpha(str[i])){
                buffer += str[i];
            }
            else if (str[i] == '='){
                buffer += str[i];
            }
            else if (str[i] == '/' || str[i] == '_' || str[i] == '@'){
                buffer += str[i];
            }
            else if (str[i] == ')' && isReadingNum){
                isReadingNum = false;
                isReading = false;
                if (!buffer.empty()){
                    offset += buffer + ",";
                    buffer.clear();
                }
                variableQueue.push(offset);
                offset.clear();
            }
            else{
                buffer += str[i];
            }
        }
    }
    //command processing
    if (!buffer.empty()) {
        try {
            bool res = commandCheck(buffer, variableQueue, needToSave, byRows);

            if (!res){
                return;
            }
        }
        catch (const MatrixException& ex) {
            std::cout << ex.what() << std::endl;
            return;
        }
    }

    //writing variables to memory
    if (needToSave){
        if (variableQueue.empty()){
            throw MissingArgumentException();
        }
        std::string value = variableQueue.top();
        variableQueue.pop();
        if (variableQueue.empty()){
            throw MissingArgumentException();
        }
        std::string name = variableQueue.top();
        variableQueue.pop();

        if (!isWord(name)){
            throw InvalidInputException();
        }

        if (isMatrix(value)){
            if (variables.find(name) != variables.end()){
                variables.erase(variables.find(name));
            }
            if (matrices.find(name) != matrices.end()){
                try {
                    matrices.find(name)->second = createMatrix(value);
                }
                catch (const MatrixException& ex) {
                    std::cout << ex.what() << std::endl;
                    return;
                }
                catch (std::exception &e){
                    throw InvalidInputException();
                }
            }
            else {
                try {
                    matrices.insert(std::make_pair(name, createMatrix(value)));
                }
                catch (const MatrixException& ex) {
                    std::cout << ex.what() << std::endl;
                    return;
                }
                catch (std::exception &e){
                    throw InvalidInputException();
                }
            }
        }
        else if (isNum(value)){
            if (matrices.find(name) != matrices.end()){
                matrices.erase(matrices.find(name));
            }
            if (variables.find(name) != variables.end()){
                try {
                    variables.find(name)->second = std::stod(value);
                }
                catch (std::exception &e){
                    throw InvalidInputException();
                }
            }
            else{
                try {
                    variables.insert(std::make_pair(name, std::stod(value)));
                }
                catch (std::exception &e){
                    throw InvalidInputException();
                }
            }
        }
        else{
            throw InvalidInputException();
        }
    }

    //checking for empty stack of temporary variables
    if (!variableQueue.empty()){
        throw UnsavedDataException();
    }
}

std::vector<int> Calculator::getOffset(std::string str) {
    std::string buffer;
    std::vector<int> offset;
    int len = int(str.size());

    for(int i = 0; i < len; i++){
        if (str[i] != ','){
            buffer += str[i];
        }
        else{
            try {
                offset.push_back(std::stoi(buffer));
            }
            catch (std::exception &e){
                throw InvalidInputException();
            }
            buffer.clear();
        }
    }

    if (!buffer.empty()){
        try {
            offset.push_back(std::stoi(buffer));
        }
        catch (std::exception &e){
            throw InvalidInputException();
        }
    }

    return offset;
}

bool Calculator::isMatrix(const std::string &str) {
    if (str.front() != '[' || str.back() != ']') {
        return false;
    }

    std::string matrixStr = str.substr(1, str.length() - 2);

    if (matrixStr.empty()) {
        return false;
    }

    int rowCount = 0;
    int columnCount = 0;
    bool insideRow = false;

    for (char c : matrixStr) {
        if (c == ' ') {
            continue;
        }
        else if (c == '[') {
            if (insideRow) {
                return false;
            }
            insideRow = true;
            rowCount++;
        }
        else if (c == ',') {
            if (!insideRow) {
                columnCount++;
            }
        }
        else if (c == ']') {
            if (!insideRow) {
                return false;
            }
            insideRow = false;
            columnCount++;
        }
        else if (isdigit(c) && !insideRow){
            return false;
        }
        else if (c != ']' && c != ',' && !isdigit(c) && c != '.' && c != '-') {
            return false;
        }
    }

    return true;
}

std::shared_ptr<Matrix> Calculator::createMatrix(const std::string &str) {
    bool isReading = false;
    std::string buffer;
    bool isMtrxClosed = false;
    int len = int(str.size());
    bool isValid = true;

    std::vector<std::vector<double>> matrix;
    std::vector<double> row;

    //filling a vector with rows of matrix elements
    for (int i = 0; i < len; i++) {
        if (str[i] == '[') {
            isMtrxClosed = false;
            isReading = true;
            continue;
        }

        if (str[i] == ']' && isMtrxClosed) {
            isReading = false;
            isMtrxClosed = false;

            row.clear();
            buffer.clear();
            break;
        }
        else if (str[i] == ']') {
            try {
                row.push_back(std::stod(buffer));
            }
            catch (std::exception &e){
                throw InvalidInputException();
            }
            matrix.push_back(row);

            row.clear();
            buffer.clear();

            isMtrxClosed = true;
            isReading = false;
        }
        else if (isdigit(str[i]) && isReading) {
            buffer += str[i];
        }
        else if (str[i] == '.' && isReading) {
            buffer += str[i];
        }
        else if (str[i] == ',' && isReading){
            try {
                row.push_back(std::stod(buffer));
            }
            catch (std::exception &e){
                throw InvalidInputException();
            }
            buffer.clear();
        }
    }

    if (!matrix.empty()) {
        int rows = int(matrix.size());
        if (!matrix[0].empty()){
            int columns = int(matrix[0].size());

            //matrix dimension check
            for (const auto& mRow : matrix) {
                if (int(mRow.size()) != columns) {
                    isValid = false;
                    break;
                }
            }

            if (!isValid){
                throw InvalidInputException();
            }

            std::shared_ptr<DenseMatrix> newMatrix(new DenseMatrix(rows, columns));

            //creating an element of a matrix class from a vector of rows of elements
            for (int i = 0; i < rows; i++){
                for (int j = 0; j < columns; j++){
                    newMatrix->setValue(i, j, matrix[i][j]);
                }
            }

            if (newMatrix->canBeSparse()){
                std::shared_ptr<SparseMatrix> newSparse(newMatrix->toSparse());
                return newSparse;
            }

            return newMatrix;
        }
    }

    return nullptr;
}

bool Calculator::commandCheck(const std::string& buffer, std::stack<std::string>& variableQueue, bool& needToSave, bool& byRows) {
    if (buffer == "ROWS"){
        byRows = true;
    }
    else if (buffer == "COLS") {
        byRows = false;
    }
    else if (buffer == "ADD"){
        if (variableQueue.empty()){
            throw MissingArgumentException();
        }
        std::string sMtx = variableQueue.top();
        variableQueue.pop();
        if (variableQueue.empty()){
            throw MissingArgumentException();
        }
        std::string fMtx = variableQueue.top();
        variableQueue.pop();

        std::shared_ptr<Matrix> fMatrx;
        std::shared_ptr<Matrix> sMatrx;

        if (!isMatrix(fMtx)){
            if (matrices.find(fMtx) != matrices.end()) {
                fMatrx= matrices.find(fMtx)->second;
            }
            else{
                throw UnknownVariableException();
            }
        }
        else{
            try {
                fMatrx = createMatrix(fMtx);
            }
            catch (const MatrixException& ex) {
                std::cout << ex.what() << std::endl;
                return false;
            }
            catch (std::exception &e){
                throw InvalidInputException();
            }
        }

        if (!isMatrix(sMtx)){
            if (matrices.find(sMtx) != matrices.end()) {
                sMatrx= matrices.find(sMtx)->second;
            }
            else{
                throw UnknownVariableException();
            }
        }
        else{
            try {
                sMatrx = createMatrix(sMtx);
            }
            catch (const MatrixException& ex) {
                std::cout << ex.what() << std::endl;
                return false;
            }
            catch (std::exception &e){
                throw InvalidInputException();
            }
        }

        AddCommand add(fMatrx, sMatrx);

        try {
            add.execute();
        }
        catch (const MatrixException& ex) {
            std::cout << ex.what() << std::endl;
            return false;
        }

        std::shared_ptr<Matrix> result = add.getResult();
        variableQueue.push(result->toString());
    }
    else if (buffer == "SUB"){
        if (variableQueue.empty()){
            throw MissingArgumentException();
        }
        std::string sMtx = variableQueue.top();
        variableQueue.pop();
        if (variableQueue.empty()){
            throw MissingArgumentException();
        }
        std::string fMtx = variableQueue.top();
        variableQueue.pop();

        std::shared_ptr<Matrix> fMatrx;
        std::shared_ptr<Matrix> sMatrx;

        if (!isMatrix(fMtx)){
            if (matrices.find(fMtx) != matrices.end()) {
                fMatrx= matrices.find(fMtx)->second;
            }
            else{
                throw UnknownVariableException();
            }
        }
        else{
            try {
                fMatrx = createMatrix(fMtx);
            }
            catch (const MatrixException& ex) {
                std::cout << ex.what() << std::endl;
                return false;
            }
            catch (std::exception &e){
                throw InvalidInputException();
            }
        }

        if (!isMatrix(sMtx)){
            if (matrices.find(sMtx) != matrices.end()) {
                sMatrx= matrices.find(sMtx)->second;
            }
            else{
                throw UnknownVariableException();
            }
        }
        else{
            try {
                sMatrx = createMatrix(sMtx);
            }
            catch (const MatrixException& ex) {
                std::cout << ex.what() << std::endl;
                return false;
            }
            catch (std::exception &e){
                throw InvalidInputException();
            }
        }

        SubtractCommand sub(fMatrx, sMatrx);
        try {
            sub.execute();
        }
        catch (const MatrixException& ex) {
            std::cout << ex.what() << std::endl;
            return false;
        }

        std::shared_ptr<Matrix> result = sub.getResult();
        variableQueue.push(result->toString());
    }
    else if (buffer == "MULM"){
        if (variableQueue.empty()){
            throw MissingArgumentException();
        }
        std::string sMtx = variableQueue.top();
        variableQueue.pop();
        if (variableQueue.empty()){
            throw MissingArgumentException();
        }
        std::string fMtx = variableQueue.top();
        variableQueue.pop();

        std::shared_ptr<Matrix> fMatrx;
        std::shared_ptr<Matrix> sMatrx;

        if (!isMatrix(fMtx)){
            if (matrices.find(fMtx) != matrices.end()) {
                fMatrx= matrices.find(fMtx)->second;
            }
            else{
                throw UnknownVariableException();
            }
        }
        else{
            try {
                fMatrx = createMatrix(fMtx);
            }
            catch (const MatrixException& ex) {
                std::cout << ex.what() << std::endl;
                return false;
            }
            catch (std::exception &e){
                throw InvalidInputException();
            }
        }

        if (!isMatrix(sMtx)){
            if (matrices.find(sMtx) != matrices.end()) {
                sMatrx= matrices.find(sMtx)->second;
            }
            else{
                throw UnknownVariableException();
            }
        }
        else{
            try {
                sMatrx = createMatrix(sMtx);
            }
            catch (const MatrixException& ex) {
                std::cout << ex.what() << std::endl;
                return false;
            }
            catch (std::exception &e){
                throw InvalidInputException();
            }
        }

        MultiplyByMatrxCommand mulm(fMatrx, sMatrx);

        try {
            mulm.execute();
        }
        catch (const MatrixException& ex) {
            std::cout << ex.what() << std::endl;
            return false;
        }

        std::shared_ptr<Matrix> result = mulm.getResult();
        variableQueue.push(result->toString());
    }
    else if (buffer == "MULN"){
        if (variableQueue.empty()){
            throw MissingArgumentException();
        }
        std::string sVal = variableQueue.top();
        variableQueue.pop();
        if (variableQueue.empty()){
            throw MissingArgumentException();
        }
        std::string fMtx = variableQueue.top();
        variableQueue.pop();

        double sValue;
        std::shared_ptr<Matrix> fMatrx;

        if (!isMatrix(fMtx)){
            if (matrices.find(fMtx) != matrices.end()) {
                fMatrx = matrices.find(fMtx)->second;
            }
            else{
                throw UnknownVariableException();
            }
        }
        else{
            try {
                fMatrx = createMatrix(fMtx);
            }
            catch (const MatrixException& ex) {
                std::cout << ex.what() << std::endl;
                return false;
            }
            catch (std::exception &e){
                throw InvalidInputException();
            }
        }

        if (!isNum(sVal)){
            if (variables.find(sVal) != variables.end()) {
                sValue= variables.find(sVal)->second;
            }
            else{
                throw UnknownVariableException();
            }
        }
        else{
            try {
                sValue = std::stod(sVal);
            }
            catch (std::exception &e){
                throw InvalidInputException();
            }
        }

        MultiplyByNumCommand muln(fMatrx, sValue);
        muln.execute();

        std::shared_ptr<Matrix> result = muln.getResult();
        variableQueue.push(result->toString());
    }
    else if (buffer == "TRANSP"){
        if (variableQueue.empty()){
            throw MissingArgumentException();
        }
        std::string fMtx = variableQueue.top();
        variableQueue.pop();

        std::shared_ptr<Matrix> fMatrx;

        if (!isMatrix(fMtx)){
            if (matrices.find(fMtx) != matrices.end()) {
                fMatrx = matrices.find(fMtx)->second;
            }
            else{
                throw UnknownVariableException();
            }
        }
        else{
            try {
                fMatrx = createMatrix(fMtx);
            }
            catch (const MatrixException& ex) {
                std::cout << ex.what() << std::endl;
                return false;
            }
            catch (std::exception &e){
                throw InvalidInputException();
            }
        }

        TransposeCommand transp(fMatrx);
        transp.execute();

        std::shared_ptr<Matrix> result = transp.getResult();

        variableQueue.push(result->toString());
    }
    else if (buffer == "CONC"){
        if (variableQueue.empty()){
            throw MissingArgumentException();
        }
        std::string sMtx = variableQueue.top();
        variableQueue.pop();
        if (variableQueue.empty()){
            throw MissingArgumentException();
        }
        std::string fMtx = variableQueue.top();
        variableQueue.pop();

        std::shared_ptr<Matrix> fMatrx;
        std::shared_ptr<Matrix> sMatrx;

        if (!isMatrix(fMtx)){
            if (matrices.find(fMtx) != matrices.end()) {
                fMatrx= matrices.find(fMtx)->second;
            }
            else{
                throw UnknownVariableException();
            }
        }
        else{
            try {
                fMatrx = createMatrix(fMtx);
            }
            catch (const MatrixException& ex) {
                std::cout << ex.what() << std::endl;
                return false;
            }
            catch (std::exception &e){
                throw InvalidInputException();
            }
        }

        if (!isMatrix(sMtx)){
            if (matrices.find(sMtx) != matrices.end()) {
                sMatrx= matrices.find(sMtx)->second;
            }
            else{
                throw UnknownVariableException();
            }
        }
        else{
            try {
                sMatrx = createMatrix(sMtx);
            }
            catch (const MatrixException& ex) {
                std::cout << ex.what() << std::endl;
                return false;
            }
            catch (std::exception &e){
                throw InvalidInputException();
            }
        }

        ConcatenateCommand conc(fMatrx, sMatrx, byRows);

        try {
            conc.execute();
        }
        catch (const MatrixException& ex) {
            std::cout << ex.what() << std::endl;
            return false;
        }

        std::shared_ptr<Matrix> result = conc.getResult();

        variableQueue.push(result->toString());
        byRows = false;
    }
    else if (buffer == "SLICE"){
        if (variableQueue.empty()){
            throw MissingArgumentException();
        }
        std::string offS = variableQueue.top();
        variableQueue.pop();
        if (variableQueue.empty()){
            throw MissingArgumentException();
        }
        std::string fMtx = variableQueue.top();
        variableQueue.pop();

        std::shared_ptr<Matrix> fMatrx;

        if (!isMatrix(fMtx)){
            if (matrices.find(fMtx) != matrices.end()) {
                fMatrx = matrices.find(fMtx)->second;
            }
            else{
                throw UnknownVariableException();
            }
        }
        else{
            try {
                fMatrx = createMatrix(fMtx);
            }
            catch (const MatrixException& ex) {
                std::cout << ex.what() << std::endl;
                return false;
            }
            catch (std::exception &e){
                throw InvalidInputException();
            }
        }

        std::vector<int> offSet = getOffset(offS);

        SliceCommand slice(fMatrx, offSet);

        try {
            slice.execute();
        }
        catch (const MatrixException& ex) {
            std::cout << ex.what() << std::endl;
            return false;
        }

        std::shared_ptr<Matrix> result = slice.getResult();

        variableQueue.push(result->toString());
    }
    else if (buffer == "INVERSE"){
        if (variableQueue.empty()){
            throw MissingArgumentException();
        }
        std::string fMtx = variableQueue.top();
        variableQueue.pop();

        std::shared_ptr<Matrix> fMatrx;

        if (!isMatrix(fMtx)){
            if (matrices.find(fMtx) != matrices.end()) {
                fMatrx = matrices.find(fMtx)->second;
            }
            else{
                throw UnknownVariableException();
            }
        }
        else{
            try {
                fMatrx = createMatrix(fMtx);
            }
            catch (const MatrixException& ex) {
                std::cout << ex.what() << std::endl;
                return false;
            }
            catch (std::exception &e){
                throw InvalidInputException();
            }
        }

        InverseCommand inv(fMatrx);

        try {
            inv.execute();
        }
        catch (const MatrixException& ex) {
            std::cout << ex.what() << std::endl;
            return false;
        }

        std::shared_ptr<Matrix> result = inv.getResult();
        variableQueue.push(result->toString());
    }
    else if (buffer == "DET"){
        if (variableQueue.empty()){
            throw MissingArgumentException();
        }
        std::string fMtx = variableQueue.top();
        variableQueue.pop();

        std::shared_ptr<Matrix> fMatrx;

        if (!isMatrix(fMtx)){
            if (matrices.find(fMtx) != matrices.end()) {
                fMatrx = matrices.find(fMtx)->second;
            }
            else{
                throw UnknownVariableException();
            }
        }
        else{
            try {
                fMatrx = createMatrix(fMtx);
            }
            catch (const MatrixException& ex) {
                std::cout << ex.what() << std::endl;
                return false;
            }
            catch (std::exception &e){
                throw InvalidInputException();
            }
        }

        DeterminantCommand det(fMatrx);

        try {
            det.execute();
        }
        catch (const MatrixException& ex) {
            std::cout << ex.what() << std::endl;
            return false;
        }

        double result = det.getResult();
        variableQueue.push(std::to_string(result));
    }
    else if (buffer == "RANK"){
        if (variableQueue.empty()){
            throw MissingArgumentException();
        }
        std::string fMtx = variableQueue.top();
        variableQueue.pop();

        std::shared_ptr<Matrix> fMatrx;

        if (!isMatrix(fMtx)){
            if (matrices.find(fMtx) != matrices.end()) {
                fMatrx = matrices.find(fMtx)->second;
            }
            else{
                throw UnknownVariableException();
            }
        }
        else{
            try {
                fMatrx = createMatrix(fMtx);
            }
            catch (const MatrixException& ex) {
                std::cout << ex.what() << std::endl;
                return false;
            }
            catch (std::exception &e){
                throw InvalidInputException();
            }
        }

        RankCommand rank(fMatrx);
        rank.execute();

        int result = rank.getResult();
        variableQueue.push(std::to_string(result));
    }
    else if (buffer == "GAUSS"){
        if (variableQueue.empty()){
            throw MissingArgumentException();
        }
        std::string fMtx = variableQueue.top();
        variableQueue.pop();

        std::shared_ptr<Matrix> fMatrx;

        if (!isMatrix(fMtx)){
            if (matrices.find(fMtx) != matrices.end()) {
                fMatrx = matrices.find(fMtx)->second;
            }
            else{
                throw UnknownVariableException();
            }
        }
        else{
            try {
                fMatrx = createMatrix(fMtx);
            }
            catch (const MatrixException& ex) {
                std::cout << ex.what() << std::endl;
                return false;
            }
            catch (std::exception &e){
                throw InvalidInputException();
            }
        }

        GaussCommand gaussCommand(fMatrx);
        gaussCommand.execute();

        std::shared_ptr<Matrix> result = gaussCommand.getResult();

        variableQueue.push(result->toString());
    }
    else if (buffer == "PRINT"){
        if (variableQueue.empty()){
            throw MissingArgumentException();
        }
        std::string str = variableQueue.top();
        variableQueue.pop();

        if (matrices.find(str) != matrices.end()){
            std::cout << matrices.find(str)->second->toString() << std::endl;
        }
        else if (variables.find(str) != variables.end()){
            std::cout << std::to_string(variables.find(str)->second) << std::endl;
        }
        else{
            if (isMatrix(str) || isNum(str)) {
                std::cout << str << std::endl;
            }
            else{
                throw UnknownVariableException();
            }
        }
    }
    else if (buffer == "SCAN"){
        if (variableQueue.empty()){
            throw MissingArgumentException();
        }
        std::string name = variableQueue.top();

        if (isMatrix(name) || isNum(name)){
            throw UnknownVariableException();
        }
        variableQueue.pop();

        std::string input;
        getline(std::cin, input);

        if (isMatrix(input)){
            if (variables.find(name) != variables.end()){
                variables.erase(variables.find(name));
            }
            if (matrices.find(name) != matrices.end()){
                try {
                    matrices.find(name)->second = createMatrix((input));
                }
                catch (const MatrixException& ex) {
                    std::cout << ex.what() << std::endl;
                    return false;
                }
                catch (std::exception &e){
                    throw InvalidInputException();
                }
            }
            else {
                try {
                    matrices.insert(std::make_pair(name, createMatrix(input)));
                }
                catch (const MatrixException& ex) {
                    std::cout << ex.what() << std::endl;
                    return false;
                }
                catch (std::exception &e){
                    throw InvalidInputException();
                }
            }
        }
        else if (isNum(input)) {
            if (matrices.find(name) != matrices.end()){
                matrices.erase(matrices.find(name));
            }
            if (variables.find(name) != variables.end()) {
                try {
                    variables.find(name)->second = std::stod(input);
                }
                catch (std::exception &e){
                    throw InvalidInputException();
                }
            }
            else {
                try {
                    variables.insert(std::make_pair(name, std::stod(input)));
                }
                catch (std::exception &e){
                    throw InvalidInputException();
                }
            }
        }
        else{
            throw InvalidInputException();
        }
    }
    else if (buffer == "IMPORT"){
        if (variableQueue.empty()){
            throw MissingArgumentException();
        }
        std::string path = variableQueue.top();
        variableQueue.pop();

        try {
            readFromFile(path);
        }
        catch (const MatrixException& ex) {
            std::cout << ex.what() << std::endl;
            return false;
        }
    }
    else if (buffer == "EXPORT"){
        if (variableQueue.empty()){
            throw MissingArgumentException();
        }
        std::string path = variableQueue.top();
        variableQueue.pop();

        try {
            writeToFIle(path);
        }
        catch (const MatrixException& ex) {
            std::cout << ex.what() << std::endl;
            return false;
        }
    }
    else if (buffer == "="){
        needToSave = true;
    }
    else{
        variableQueue.push(buffer);
    }

    return true;
}

bool Calculator::isNum(const std::string &str) {
    return !str.empty() && (str.find_first_not_of("0123456789.-") == str.npos);
}

bool Calculator::isWord(const std::string &str) {
    if (!str.empty()){
        if(!isalpha(str[0])){
            return false;
        }
    }
    else{
        return false;
    }

    for (char c : str){
        if (!isdigit(c) && !isalpha(c) && c != '_'){
            return false;
        }
    }

    return true;
}

void Calculator::readFromFile(const std::string &inFile) {
    std::ifstream fin(inFile);
    std::string line;

    if (!fin.is_open()){
        throw WrongFilePathException();
    }

    while(getline(fin, line)){
        if (line == "EXIT"){
            break;
        }
        else{
            //creating copies of the calculator's memory in case of an error while processing the contents of the file
            std::unordered_map<std::string, std::shared_ptr<Matrix>> matricesCopy = matrices;
            std::unordered_map<std::string, double> variablesCopy = variables;
            try {
                perform(line);
            }
            catch (const MatrixException& ex) {
                std::cout << ex.what() << std::endl;
                variables = variablesCopy;
                matrices = matricesCopy;
            }
        }
    }

    fin.close();
}

void Calculator::writeToFIle(const std::string &outFile) {
    std::ofstream fout(outFile);

    if (!fout.is_open()){
        throw WrongFilePathException();
    }

    for (auto& item: matrices){
        fout << item.first << " = " << item.second->toString() << std::endl;
    }

    for (auto& item : variables){
        fout << item.first << " = " << std::to_string(item.second) << std::endl;
    }

    fout.close();

    if (!fout.good()){
        throw NoPermissionException();
    }
}