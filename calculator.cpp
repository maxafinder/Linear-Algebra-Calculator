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
	matrix_t getReducedEchelonForm();
	void swap(int, int);
	void replace(int, double, int);
	void scale(int, double);


} matrix_t;




// function prototypes
matrix_t getMatrix();
std::vector<int> getPrintDimensions(std::vector<std::vector<double>>, int, int);
int getCharsInNum(double);
matrix_t moveZerosToBottom(matrix_t, int, int);
matrix_t zeroColumnBottom(matrix_t, int , int);
matrix_t zeroColumnTop(matrix_t, int, int);





int main() {

	// create new matrix and fill it with values from the user
	matrix_t m = getMatrix();
	m.printMatrix();


	// TEST
	matrix_t echelonMatrix = m.getReducedEchelonForm();

	printf("\n\nOriginal: \n");
	m.printMatrix();
	printf("\n\nEchelon Form: \n");
	echelonMatrix.printMatrix();


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
 * Calculates the Echelon form of the matrix and then returns a new matrix
 * containing the values of the Echelon form.
 * @return -> A matrix that contains the Echelon form of the given matrix.
 */
matrix_t matrix_t::getReducedEchelonForm() {
	matrix_t echelonMatrix;
	echelonMatrix.rows = rows;
	echelonMatrix.cols = cols;
	echelonMatrix.matrix = matrix;

	echelonMatrix = moveZerosToBottom(echelonMatrix, 0, 0);

	// find a pivot column in every column
	int row = 0;
	for (int col = 0; col < echelonMatrix.cols; col++) {
		// move the zeros to the bottom for all rows beneath row
		echelonMatrix = moveZerosToBottom(echelonMatrix, row, col);	

		// find the next pivot column
		while (col < echelonMatrix.cols - 1 && echelonMatrix.matrix[row][col] == 0) {
			col++;
			echelonMatrix = moveZerosToBottom(echelonMatrix, row, col);	
		}

		// zero the column out
		echelonMatrix = zeroColumnBottom(echelonMatrix, row, col);
		row++;
		if (row == echelonMatrix.rows) {
			break;
		}
	}


	// zero out the tops of the columns	
	for (int i = 0; i < echelonMatrix.rows; i++) {
		for (int j = 0; j < echelonMatrix.matrix[i].size(); j++) {
			// if we find a pivot column, then zero the columns above it
			if (echelonMatrix.matrix[i][j] != 0) {
				echelonMatrix = zeroColumnTop(echelonMatrix, i, j);
				break;
			}
		}
	}

	return echelonMatrix;
} // getReducedEchelonForm()






/*
 * Moves any rows that are below "row" that have a zero in "col" to the bottom of the matrix.
 * @param m -> the matrix that we are working with.
 * @param row -> the first row that we will consider to swap.
 * @param col -> the column that we are looking for zeros in.
 * @return -> the matrix with the zeros at the bottom for that column.
 */
matrix_t moveZerosToBottom(matrix_t m, int row, int col) {
	for (int i = row; i < m.matrix.size(); i++) {
		// we swap
		if (m.matrix[i][col] == 0) {

			// look for row to swap with
			for (int j = i + 1; j < m.matrix.size(); j++) {
				if (m.matrix[j][col] != 0) {
					m.swap(i, j);	
				}
			}
		}
	} // for-loop

	return m;
} // moveZerosToBottom()






/*
 * Performs row replacement on all of the rows below "row" so that every entry in col is 0.
 * @param m -> the matrix.
 * @param row -> the row that we are going to zero the entries below.
 * @param col -> the column that we are zeroing out.
 * @return -> the matrix after the operation is performed.
 */
matrix_t zeroColumnBottom(matrix_t m, int row, int col) {
	if (m.matrix[row][col] == 0) {
		return m;
	}

	// scale the row so that the entry in col is 1
	double scale = 1.0 / m.matrix[row][col];
	m.scale(row, scale);
	m.matrix[row][col] = 1;

	// row replace every row underneath "row"	so that there are all zeros in that column
	for (int i = row + 1; i < m.matrix.size(); i++) {
		scale = -1 * m.matrix[i][col];
		m.replace(row, scale, i);
	}

	// return the matrix
	return m;
} // zeroColumnBottom()






/*
 * Zero out all of the entries in the column "col" above "row".
 * @param m -> the matrix
 * @param row -> the row that we are going to zero out above.
 * @param col -> the column that we are going to zero out.
 * @return -> the matrix after the operation is performed.
 */
matrix_t zeroColumnTop(matrix_t m, int row, int col) {
	// for each row above row find the scale to make it zero
	double scale;
	for (int i = row - 1; i >= 0; i--) {
		scale = -1 * m.matrix[i][col];
		m.replace(row, scale, i);	
	}
	
	return m;
} // zeroColumnBottom()





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
	
	// if its negative then add a character
	if (num < 0) {
		chars++;
	}

	// if its a decimal then add 3 characters for ".xx"
	if ((int) num != num) {
		chars += 3;
	}

	// find the number of chars before the decimal place
	int rounded = (int) num;
	if (rounded == 0) {
		chars++;
	}
	while (rounded != 0) {
		chars++;
		rounded = rounded/10;
	}

	return chars;
} // getCharsInNum()










