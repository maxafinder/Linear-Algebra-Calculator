#include <iostream>
#include <vector>



typedef struct matrix_t {
	// fields
	int rows;
	int cols;
	std::vector<std::vector<double>> matrix;

	// contructors
	matrix_t();
	matrix_t(std::vector<std::vector<double>>, int, int);

	// functions
	void printMatrix();
} matrix_t;




// function prototypes
matrix_t getMatrix();
std::vector<int> getPrintDimensions(std::vector<std::vector<double>>, int, int);
int getCharsInNum(double);





int main() {

	// create new matrix and fill it with values from the user
	matrix_t m = getMatrix();
	m.printMatrix();
	

} // main()






// constructor with no arguments
matrix_t::matrix_t() {
	rows = 0;
	cols = 0;
}

// constructor with arguments
matrix_t::matrix_t(std::vector<std::vector<double>> theMatrix, int numRows, int numCols) {
	matrix = theMatrix;
	rows = numRows;
	cols = numCols;
}






/*
 * Gets values from the user to fill the matrix.
 * Gets the # of rows and # of columns from the user and then gets
 * values to fill the matrix.
 * @return -> a matrix structure with a matrix filled with values.
 */
matrix_t getMatrix() {
	matrix_t m;

	// get the # of rows and # of columns
	printf("Enter the number of rows:  ");
	std::cin >> m.rows;
	printf("Enter the number of columns:  ");
	std::cin >> m.cols;

	// get the values for the matrix
	std::vector<double> row;
	double value;

	for (int i = 0; i < m.rows; i++) {
		for (int j = 0; j < m.cols; j++) {
			// prints the matrix out for the user
			m.printMatrix();

			// gets value from the user and adds it to the current row
			printf("Enter value:  ");
			std::cin >> value;
			row.push_back(value);
			printf("\n\n");

			// updates the row in the matrix
			if (m.matrix.size() == i + 1) {
				m.matrix.pop_back();
			}
			m.matrix.push_back(row);
		}

		row.clear();
	}	

	return m;
} // getMatrix()









/*
 * Prints out the values in the matrix, and if there is no value at
 * a location, then it prints an underscore for that spot.
 */
void matrix_t::printMatrix() {
	bool firstUnderscore = true;
	std::vector<int> dimensions = getPrintDimensions(matrix, rows, cols);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {

			// the value is in the matrix
			if (matrix.size() > i && matrix[i].size() > j) {

				// if its an integer
				if ((int) matrix[i][j] == matrix[i][j]) {
					printf("%d", (int) matrix[i][j]);
				}
				// its a decimal
				else {
					printf("%.2f", matrix[i][j]);
				}

			}
			// print an underscore as the value
			else if (firstUnderscore) {
				printf("?");
				firstUnderscore = false;
			}
			else {
				printf("_");
			}

			// print necessary spaces
			if (matrix.size() > i && matrix[i].size() > j) {
				for (int k = 0; k < (dimensions[j] - getCharsInNum(matrix[i][j])); k++) {
					printf(" ");
				}
			}
			else {
				for (int k = 0; k < (dimensions[j] - 1); k++) {
					printf(" ");
				}
			}

			// if we are at the end of a row then print a newline
			if (j == (cols - 1)) {
				printf("\n");
			}

		} // end of for-loop
	} // end of for-loop

} // printMatrix()










/*
 * Returns a vector which has the number of characters that should
 * be printed for each column.
 * 
 */
std::vector<int> getPrintDimensions(std::vector<std::vector<double>> matrix, int rows, int cols) {
	std::vector<int> dimensions;
	int max;

	for (int j = 0; j < cols; j++) {
		max = 1;
		for (int i = 0; i < rows; i++) {
			
			if (matrix.size() > i && matrix[i].size() > j) {
				if (getCharsInNum(matrix[i][j]) > max) {
					max = getCharsInNum(matrix[i][j]);	
				}
			}

		}

		dimensions.push_back(max + 2);
	}

	return dimensions;	
} // getPrintDimensions()







/*
 * Returns that amount of characters in the number if the decimal
 * is rounded to 2 decimal places and then accounts for 2 added spaces
 * after the number.
 * @param num -> the number that we will find the # of characters for.
 * @return -> the number of characters that the number takes up.
 */
int getCharsInNum(double num) {
	int chars = 0;
	
	// if its a decimal then add 3 characters for ".xx"
	if ((int) num != num) {
		chars += 3;
	}

	// find the number of chars before the decimal place
	int rounded = (int) num;
	while (rounded != 0) {
		chars++;
		rounded = rounded/10;
	}

	return chars;
} // getCharsInNum()










