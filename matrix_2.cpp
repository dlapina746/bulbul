#include <algorithm>
#include <cstddef>
#include <iostream>
#include <new>

namespace udalcova {
	void free_matrix(int** matrix, size_t m) {
		if (matrix == nullptr) {
			return;
		}
		for (size_t i = 0; i < m; ++i) {
			delete[] matrix[i];
		}
		delete[] matrix;
	}

	int** allocate_matrix(size_t m, size_t n) {
		int** matrix = new (std::nothrow) int* [m];
		if (matrix == nullptr) {
			return nullptr;
		}
		for (size_t i = 0; i < m; ++i) {
			matrix[i] = new (std::nothrow) int[n];
			if (matrix[i] == nullptr) {
				free_matrix(matrix, i);
				return nullptr;
			}
		}

		return matrix;
	}
	size_t row_len(size_t i, size_t n1, size_t m1, size_t n2, size_t m2) {
		size_t len = 0;
		if (i < n1) {
			len +=m1;
		}
		if (i < n2) {
			len +=m2;
		}
		return len;
	}

	int** concat_rows(const int* const* lhs, size_t n1, size_t m1, const int* const* rhs, size_t n2, size_t m2) {
		size_t rows = std::max(n1, n2);
		int** result = new (std::nothrow) int* [rows];
		if (result == nullptr) {
			return nullptr;
		}

		for (size_t i = 0; i < rows; ++i) {
			result[i] = new (std::nothrow) int[row_len(i, n1, m1, n2, m2)];
			if (result[i] == nullptr) {
				free_matrix(result, i);
				return nullptr;
			}
			size_t k = 0;
			if (i < n1) {
				for (size_t j = 0; j < m1; ++j) {
					result[i][k++] = lhs[i][j];
				}
			}
			if (i < n2) {
				for (size_t j = 0; j < m2; ++j) {
					result[i][k++] = rhs[i][j];
				}
			}
		}
		return result;
	}

	bool read_elements(int** matrix, size_t m, size_t n) {
		for (size_t i = 0; i < m; ++i) {
			for (size_t j = 0; j < n; j++) {
				if (!(std::cin >> matrix[i][j])) {
					return false;
				}
			}
		}
		return true;
	}
}

int main() {
	size_t n1 = 0;
	size_t m1 = 0;
	size_t n2 = 0;
	size_t m2 = 0;

	if(!(std::cin >> n1 >> m1) || n1 == 0 || m1 == 0) {
		return 1;
	}

	int** lhs = udalcova::allocate_matrix(n1, m1);
	if (lhs == nullptr) {
		return 2;
	}
	if (!udalcova::read_elements(lhs, n1, m1)) {
		udalcova::free_matrix(lhs, n1);
		return 1;
	}

	if (!(std::cin >> n2 >> m2) || n2 == 0 || m2 == 0) {
		udalcova::free_matrix(lhs, n1);
		return 1;
	}
	int** rhs = udalcova::allocate_matrix(n2, m2);
	if (rhs == nullptr) {
		udalcova::free_matrix(lhs, n1);
		return 2;
	}

	if (!udalcova::read_elements(rhs, n2, m2)) {
		udalcova::free_matrix(lhs, n1);
		udalcova::free_matrix(rhs, n2);
		return 1;
	}

	int** result = udalcova::concat_rows(lhs, n1, m1, rhs, n2, m2);
	udalcova::free_matrix(lhs, n1);
	udalcova::free_matrix(rhs, n2);
	if (result == nullptr) {
		return 2;
	}

	size_t rows = std::max(n1, n2);
	for (size_t i = 0; i < rows; i++) {
		size_t len = udalcova::row_len(i, n1, m1, n2, m2);
		for (size_t j = 0; j < len; j++) {
			std::cout << result[i][j];
			if (j + 1 < len) {
				std::cout << " ";
			}
		}
		std::cout << "\n";
	}

	udalcova::free_matrix(result, rows);
	return 0;
}
