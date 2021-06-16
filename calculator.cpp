#include <iostream>

// function prototypes
int * getDimensions();



int main() {

	// get dimensions of the matrix
	int * dimensions = getDimensions();

} // main()







/*
 * Gets the dimensions of the matrix from the user.
 * @return -> An int array called "dimensions" where dimensions[0] is the # of rows,
 * 						and dimensions[1] is the # of columns
 */
int * getDimensions() {
	int * dimensions = new int[2];

	printf("Enter the number of rows:  ");
	std::cin >> dimensions[0];

	printf("Enter the number of columns:  ");
	std::cin >> dimensions[1];

	return dimensions;
} // getDimensions()