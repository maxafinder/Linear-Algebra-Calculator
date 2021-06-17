#include <iostream>
#include <vector>

// function prototypes
int * getDimensions();
std::vector<std::vector<double>> getMatrix(int, int);
void printMatrix(std::vector<std::vector<double>>, int, int);
std::vector<int> getPrintDimensions(std::vector<std::vector<double>>, int, int);
int getCharsInNum(double);





int main() {

	// get dimensions of the matrix
	int * dimensions = getDimensions();

	printf("rows = %d\ncols = %d\n", dimensions[0], dimensions[1]);

	// get the matrix
	std::vector<std::vector<double>> matrix = getMatrix(dimensions[0], dimensions[1]);
	printMatrix(matrix, dimensions[0], dimensions[1]);

} // main()







/*
 * Gets the dimensions of the matrix from the user.
 * @return -> An int array called "dimensions" where dimensions[0] is the # of rows,
 * 						and dimensions[1] is the # of columns.
 */
int * getDimensions() {
	int * dimensions = new int[2];

	printf("Enter the number of rows:  ");
	std::cin >> dimensions[0];

	printf("Enter the number of columns:  ");
	std::cin >> dimensions[1];

	return dimensions;
} // getDimensions()








/*
 * Gets values from the user to fill the matrix.
 * @param rows -> the number of rows in the matrix.
 * @param cols -> the number of columns in the matrix.
 * @return -> a matrix filled with the values provided by the user
 */
std::vector<std::vector<double>> getMatrix(int rows, int cols) {
	std::vector<std::vector<double>> matrix;
	std::vector<double> row;
	double value;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			// prints the matrix out for the user
			printMatrix(matrix, rows, cols);

			// gets value from the user and adds it to the current row
			printf("Enter value:  ");
			std::cin >> value;
			row.push_back(value);
			printf("\n\n");

			// updates the row in the matrix
			if (matrix.size() == i + 1) {
				matrix.pop_back();
			}
			matrix.push_back(row);
		}

		row.clear();
	}	

	return matrix;
} // getMatrix()









/*
 * Prints out the values in the matrix, and if there is no value at
 * a location, then it prints an underscore for that spot.
 * @param matrix -> the matrix and its values.
 * @param rows -> the number of rows in the matrix.
 * @param cols -> the number of cols in the matrix.
 */
void printMatrix(std::vector<std::vector<double>> matrix, int rows, int cols) {
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


