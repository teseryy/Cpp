CXXFLAGS = -Wall -pedantic -std=c++14

HEADERS = $(wildcard src/*.h)
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:src/%.cpp=build/%.o)

.PHONY: all
all: compile doc

.PHONY: run
run: compile
	./MatrixCalc

.PHONY: compile
compile: MatrixCalc

MatrixCalc: build/main
	cp $< $@

build/main: $(OBJECTS)
	mkdir -p $(@D)
	g++ $^ -o $@

build/%.o: src/%.cpp
	mkdir -p $(@D)
	g++ $(CXXFLAGS) $< -c -o $@

doc: Doxyfile $(HEADERS)
	doxygen Doxyfile

.PHONY: clean
clean:
	rm -rf MatrixCalc build/ doc/ 2>/dev/null

# Requirements / Dependencies
build/Matrix.o: src/Matrix.cpp src/Matrix.h
build/SparseMatrix.o: src/SparseMatrix.cpp src/SparseMatrix.h src/Matrix.h
build/DenseMatrix.o: src/DenseMatrix.cpp src/DenseMatrix.h src/SparseMatrix.h src/Matrix.h
build/Command.o: src/Command.h
build/AddCommand.o : src/AddCommand.h src/AddCommand.cpp src/Command.h
build/ConcatenateCommand.o : src/ConcatenateCommand.h src/ConcatenateCommand.cpp src/Command.h
build/DeterminantCommand.o : src/DeterminantCommand.h src/DeterminantCommand.cpp src/Command.h
build/GaussCommand.o : src/GaussCommand.h src/GaussCommand.cpp src/Command.h
build/InverseCommand.o : src/InverseCommand.h src/InverseCommand.cpp src/Command.h
build/MultiplyByMatrxCommand.o : src/MultiplyByMatrxCommand.h src/MultiplyByMatrxCommand.cpp src/Command.h
build/MultiplyByNumCommand.o : src/MultiplyByNumCommand.h src/MultiplyByNumCommand.cpp src/Command.h
build/RankCommand.o : src/RankCommand.h src/RankCommand.cpp src/Command.h
build/SliceCommand.o : src/SliceCommand.h src/SliceCommand.cpp src/Command.h
build/SubtractCommand.o : src/SubtractCommand.h src/SubtractCommand.cpp src/Command.h
build/TransposeCommand.o : src/TransposeCommand.h src/TransposeCommand.cpp src/Command.h
build/Exceptions.o : src/Exceptions.h src/Exceptions.cpp
build/Calculator.o : src/Calculator.h src/Calculator.cpp src/Matrix.h src/SparseMatrix.h \
src/DenseMatrix.h src/Command.h src/AddCommand.h src/ConcatenateCommand.h src/DeterminantCommand.h \
src/GaussCommand.h src/InverseCommand.h src/MultiplyByMatrxCommand.h src/MultiplyByNumCommand.h \
src/RankCommand.h src/SliceCommand.h src/SubtractCommand.h src/TransposeCommand.h src/Exceptions.h
build/main.o : src/main.cpp src/Calculator.h src/Matrix.h src/SparseMatrix.h \
src/DenseMatrix.h src/Command.h src/AddCommand.h src/ConcatenateCommand.h src/DeterminantCommand.h \
src/GaussCommand.h src/InverseCommand.h src/MultiplyByMatrxCommand.h src/MultiplyByNumCommand.h \
src/RankCommand.h src/SliceCommand.h src/SubtractCommand.h src/TransposeCommand.h src/Exceptions.h
