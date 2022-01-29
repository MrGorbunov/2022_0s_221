#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>


int main(int, char*[]);

int calcMinCost (unsigned int****, unsigned int, unsigned int, unsigned int***, unsigned int****, unsigned int***);

void print2DArr (unsigned int**, unsigned int, unsigned int);
void print2DSizeArr (unsigned int***, unsigned int);



int main(int argc, char* argv[]) {

	unsigned int matrixCount;
	unsigned int* rowSizes;
	unsigned int* colSizes;
	unsigned int*** matricies;
	

	//
	// Reading Input
	//

	FILE* fp = fopen(argv[1], "r");
	if (!fp) {
		perror("fopen failed");
		exit(EXIT_FAILURE);
	}

	if (!fscanf(fp, "%d\n", &matrixCount)) {
		perror("reaidng the number of matrices failed");
		exit(EXIT_FAILURE);
	}

	rowSizes = calloc( matrixCount, sizeof(unsigned int));
	colSizes = calloc( matrixCount, sizeof(unsigned int));
	matricies = calloc( matrixCount, sizeof(unsigned int**));
	
	printf("Num mats: %d\n", matrixCount);
	
	for (int mat=0; mat<matrixCount; mat++) {
		if (!fscanf(fp, "%d %d\n", &rowSizes[mat], &colSizes[mat])) {
			perror("reading matrix size failed");
			exit(EXIT_FAILURE);
		}

		int rowSz = rowSizes[mat];
		int colSz = colSizes[mat];

		matricies[mat] = calloc(rowSz, sizeof(unsigned int*));

		for (int r=0; r<rowSz; r++) {
			matricies[mat][r] = calloc(colSz, sizeof(unsigned int));

			for (int c=0; c<colSz; c++) {
				// indexing is [row][col]
				fscanf(fp, "%d", &matricies[mat][r][c]);
			}

			fscanf(fp, "\n");
		}
	}






	//
	// Processing
	//

	// TODO: Try making contigous array memory block
 	unsigned int**  matMulCost = calloc( matrixCount, sizeof(unsigned int*) );
 	unsigned int*** matMulSize = calloc( matrixCount, sizeof(unsigned int**) );
 
 	for (int i=0; i<matrixCount; i++) {
		matMulCost[i] = calloc( matrixCount, sizeof(unsigned int) );
		matMulSize[i] = calloc( matrixCount, sizeof(unsigned int*) );

 		for (int j=0; j<matrixCount; j++) {
 			matMulSize[i][j] = calloc( 2, sizeof(unsigned int) );

			if (i < j) {
				matMulCost[i][j] = -1;
				matMulSize[i][j][0] = -1;
				matMulSize[i][j][1] = -1;
			}
 		}
 	}


	// Populate matrix size table
	for (int i=0; i<matrixCount; i++) {
		matMulSize[i][i][0] = rowSizes[i];
		matMulSize[i][i][1] = colSizes[i];
	}

	for (int j=0; j<matrixCount; j++) {
		for (int i=j+1; i<matrixCount; i++) {
			matMulSize[i][j][0] = matMulSize[j][j][0];
			matMulSize[i][j][1] = matMulSize[i][i][1];
		}
	}


	/*
		 Now to think:
		A : 2 x 3
		B : 3 x 8

    # of ops = 2 * 3 * 8
	 */

	// Populate cost table
	for (int i=0; i<matrixCount; i++) {
		matMulCost[i][i] = 0;
	}

	int** matrix;

	printf("Min Cost: %d\n", calcMinCost (&matricies, matrixCount-1, 0, &matMulCost, &matMulSize, &matrix));

	print2DArr(matrix, matMulSizes[matrixCount-1][0][0], matMulSizes[matrixCount-1][0][1]);

// 	for (int j=0; j+1<matrixCount; j++) {
// 		int i = j+1;
// 		matMulCost[i][j] = matMulSize[i-1][j][0] * matMulSize[i-1][j][1] * matMulSize[i][j+1][1];
// 	}
// 
// 
// 	int iteration = 2;
// 
// 	while (matMulCost[matrixCount-1][0] == 0) {
// 		for (int i=0; i<matrixCount-iteration; i++) {
// 			unsigned int costMin = -1;
// 
// 			for (int j=0; j<iteration; j++) {
// 				int row = j+i;
// 				int col = i+1+j;
// 
// 				int matCost = matMulSize[row][i][0] * matMulSize[row][i][1] * matMulSize[iteration + i][col][1] + matMulCost[row][i] + matMulCost[iteration + i][col];
// 
// 				if (matCost < costMin || costMin == -1)
// 					costMin = matCost;
// 			}
// 
// 			printf("\nWriting cost %d to [%d][%d]\n", costMin, i+1, i);
// 			matMulCost[i+iteration][i] = costMin;
// 		}
// 
// 		iteration++;
// 	}
// 
// 
// 
// 	print2DArr(matMulCost, matrixCount, matrixCount);
// 	print2DSizeArr(matMulSize, matrixCount);





	//
	// Cleanup
	//

	for (int i=0; i<matrixCount; i++) {
		for (int j=0; j<rowSizes[i]; j++) {
			free(matricies[i][j]);
		}
		free(matricies[i]);
	}
	free(matricies);

	free(rowSizes);
	free(colSizes);

	exit(EXIT_SUCCESS);
}




int calcMinCost (unsigned int**** matricies, unsigned int row, unsigned int col, unsigned int*** costArr, unsigned int**** sizesArr, unsigned int*** matrix) {
	// Base Cases
	if (row == col) {
		*matrix = (*matricies)[row];
		return 0;
	}
	if (row < col) {
		return -1;
	}
	if ((*costArr)[row][col] != 0) {
		return (*costArr)[row][col];	
	}
	if (row == col + 1) {
		unsigned int cost = (*sizesArr)[row-1][col][0] * (*sizesArr)[row-1][col][1] * (*sizesArr)[row][col+1][1];
		(*costArr)[row][col] = cost;
		return cost;
	}

	return -1;
}





void print2DArr (unsigned int** arr, unsigned int rows, unsigned int cols) {
	for (int r=0; r<rows; r++) {
		for (int c=0; c<cols; c++) {
			printf("%3d ", arr[r][c]);
		}

		printf("\n");
	}
}

void print2DSizeArr (unsigned int*** arr, unsigned int numMats) {
	for (int r=0; r<numMats; r++) {
		for (int c=0; c<numMats; c++) {
			printf("%2d x%2d | ", arr[r][c][0], arr[r][c][1]);
		}

		printf("\n");
	}
}





