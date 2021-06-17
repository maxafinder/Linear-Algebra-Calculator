#include <iostream>
#include <vector>

// function prototypes
int * getDimensions();
std::vector<std::vector<int>> getMatrix(int, int);
void printMatrix(std::vector<std::vector<int>>, int, int);




int main() {

	// get dimensions of the matrix
	int * dimensions = getDimensions();

	printf("rows = %d\ncols = %d\n", dimensions[0], dimensions[1]);

	// get the matrix
	std::vector<std::vector<int>> matrix = getMatrix(dimensions[0], dimensions[1]);
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
std::vector<std::vector<int>> getMatrix(int rows, int cols) {
	std::vector<std::vector<int>> matrix;
	std::vector<int> row;
	int value;

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
void printMatrix(std::vector<std::vector<int>> matrix, int rows, int cols) {
	bool firstUnderscore = true;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {

			// the value is in the matrix
			if (matrix.size() > i && matrix[i].size() > j) {
				printf("%d ", matrix[i][j]);
			}
			// print an underscore as the value
			else if (firstUnderscore) {
				printf("? ");
				firstUnderscore = false;
			}
			else {
				printf("_ ");
			}

			// if we are at the end of a row then print a newline
			if (j == (cols - 1)) {
				printf("\n");
			}

		}
	}
} // printMatrix()









