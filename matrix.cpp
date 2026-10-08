#include <iostream>
#include <new>

int** createMatrix(size_t rows, size_t cols) {
	int** grid = new (std::nothrow) int*([rows];
	if(grid == nullptr) {
		return nullptr;
	}

	size_t i = 0;
	while (i < rows) {
		grid[i] = new (std::nothrow) int[cols];
		if (grid[i] == nullptr) {
			size_t j =0;
			while (j < i) {
				delete[] grid[j];
				j++;
			}
			delete[] grid;
			return nullptr;
		}
		i++;
	}
	return grid;
}

void destroyMatrix(int** grid, size_t rows) {
	if (grid == nullptr) return;

	for (size_t i = 0; i < rows; i++) {
		delete[] grid[i];
	}
	delete[] grid;
}

int main() {
	size_t rows, cols;

	std::cout << "Введите количество строк (m) и столбцов (n):";
	if (!(std::cin >> rows >> cols)) {
		return 1;
	}

	if (rows <= 0 || cols <= 0) {
		return 1;
	}

	int** matrix = createMatrix(rows, cols);
	if (matrix == nullptr) {
		return 2;
	}

	std::cout << "Введите элементы матрицы (" << rows << "x" << cols << ");" << std::endl;
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < cols; j++) {
			if (!(std::cin >> matrix[i][j])) {
				destroyMatrix(matrix, rows);
				return 1;
			}
		}
	}

	std::cout << "Транспонированная матрица (" << cols << "x" << rows << "):" << std::endl;
	size_t j = 0;
	while (j < cols) {
		size_t i = 0;
		while (i < rows) {
			std::cout << matrix[i][j];
			if (i < rows - 1) {
				std::cout << " ";
			}
			i++
		}
		std::cout << std::endl;
	}

	destroyMatrix(matrix, rows);
	return 0;
}

