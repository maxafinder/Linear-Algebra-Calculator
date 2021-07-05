#include <iostream>
#include <vector>


// struct to hold information about a matrix
typedef struct matrix_t {
	int rows;
	int cols;
	std::vector<std::vector<double>> matrix;

	// contructors
	matrix_t();
	matrix_t(std::vector<std::vector<double>>, int, int);

	// functions
	void printMatrix();
	matrix_t getEchelonForm();
	void swap(int, int);
	void replace(int, double, int);
	void scale(int, double);


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





// TODO
/*
 * Calculates the Echelon form of the matrix and then returns a new matrix
 * containing the values of the Echelon form.
 * @return -> A matrix that contains the Echelon form of the given matrix.
 */
matrix_t matrix_t::getEchelonForm() {
	matrix_t echelon;
	echelon.matrix = matrix;

	return echelon;
} // getEchelonForm()




/*
 * Swaps row1 with row2 in the matrix.
 * @param row1 -> the first row that we are swapping.
 * @param row2 -> the second row that we are swapping.
 */
void matrix_t::swap(int row1, int row2) {
	std::vector<double> temp;
	temp = matrix[row2];

	matrix[row2] = matrix[row1];
	matrix[row1] = temp;
} // swap()






/*
 * Replaces adds row1 multiplied by a scale to row2 and replaces row2.
 * @param row1 -> the row in the matrix that we will scale and add to row2.
 * @param scale -> the scale that we are multiplying row1 by.
 * @param row2 -> the row that we are replacing.
 */
void matrix_t::replace(int row1, double scale, int row2) {
	for (int i = 0; i < matrix[row1].size(); i++) {
		matrix[row2][i] = (matrix[row1][i] * scale) + matrix[row2][i];
	}
} // replace()





/*
 * Scales the specified row by the scale.
 * @param row -> the row that we will be scaling.
 * @param scale -> the scale that we are multiplying the row by.
 */
void matrix_t::scale(int row, double scale) {
	for (int i = 0; i < matrix[row].size(); i++) {
		matrix[row][i] = matrix[row][i] * scale;
	}
} // scale()





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










