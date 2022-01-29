#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>


int main(int, char*[]);

void optimallyMultiplyMatrix (unsigned int, unsigned int, unsigned int***, unsigned int***, unsigned int****, unsigned int****, unsigned int*);
void multiplyMatricies (unsigned int***, unsigned int***, unsigned int, unsigned int, unsigned int, unsigned int***);

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

 	for (int j=0; j+1<matrixCount; j++) {
 		int i = j+1;
 		matMulCost[i][j] = matMulSize[i-1][j][0] * matMulSize[i-1][j][1] * matMulSize[i][j+1][1];
 	}
 
 
 	int iteration = 2;
 
 	while (matMulCost[matrixCount-1][0] == 0) {
 		for (int i=0; i<matrixCount-iteration; i++) {
 			unsigned int costMin = -1;
 
 			for (int j=0; j<iteration; j++) {
 				int row = j+i;
 				int col = i+1+j;
 
 				int matCost = matMulSize[row][i][0] * matMulSize[row][i][1] * matMulSize[iteration + i][col][1] + matMulCost[row][i] + matMulCost[iteration + i][col];
 
 				if (matCost < costMin || costMin == -1)
 					costMin = matCost;
 			}
 
 			printf("\nWriting cost %d to [%d][%d]\n", costMin, i+1, i);
 			matMulCost[i+iteration][i] = costMin;
 		}
 
 		iteration++;
 	}
 

	// Now using the matMulCost, we recursively produce the matrix
	// in the minimum number of operations.
	//
	// Doing this non-recursively would require building a tree which
	// could actually be done while populating the cost array (matMulCost)
	// but I chose against it because it feels a tad overkill.
	unsigned int** matrixResult;

	optimallyMultiplyMatrix(matrixCount-1, 0, &matrixResult, &matMulCost, &matMulSize, &matricies, &matrixCount);
 
	printf("\n");
	print2DArr(matrixResult, matMulSize[matrixCount-1][0][0], matMulSize[matrixCount-1][0][1]);
	printf("\n");
 
 	print2DArr(matMulCost, matrixCount, matrixCount);
 	print2DSizeArr(matMulSize, matrixCount);





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


void optimallyMultiplyMatrix (unsigned int row, unsigned int col, unsigned int*** finalMatrix, unsigned int*** matMulCost, unsigned int**** matMulSize, unsigned int**** matricies, unsigned int* matrixCount) {
	if (row == col) {
		(*finalMatrix) = (*matricies)[row];
		return;
	}
	if (row == col + 1) {
		multiplyMatricies(&(*matricies)[col], &(*matricies)[row], (*matMulSize)[col][col][0], (*matMulSize)[col][col][1], (*matMulSize)[row][row][1], finalMatrix);
		return;
	}

	unsigned int targetCost = (*matMulCost)[row][col];
	for (int i=0; i<row; i++) {
		unsigned int matR = col+i;
		unsigned int matC = col+i+1;
		unsigned int matCost = (*matMulSize)[matR][col][0] * (*matMulSize)[matR][col][1] * (*matMulSize)[row][matC][1] + (*matMulCost)[matR][col] + (*matMulCost)[row][matC];

		if (matCost == targetCost) {
			unsigned int** matA;
			unsigned int** matB;
			unsigned int** finalMatrix;

			unsigned int rowsA = (*matMulSize)[matR][col][0];
			unsigned int colsA = (*matMulSize)[matR][col][1];
			unsigned int rowsB = (*matMulSize)[row][matC][0];
			unsigned int colsB = (*matMulSize)[row][matC][1];

			finalMatrix = calloc (rowsA, sizeof(unsigned int*));
			for (int r=0; r<rowsA; r++)
				finalMatrix[r] = calloc (colsB, sizeof(unsigned int));
	
			optimallyMultiplyMatrix(matR, col, &matA, matMulCost, matMulSize, matricies, matrixCount);
			optimallyMultiplyMatrix(row, matC, &matB, matMulCost, matMulSize, matricies, matrixCount);
			multiplyMatricies(&matA, &matB, rowsA, rowsB, colsB, &finalMatrix);

// 			for (int ra=0; ra<rowsA; ra++)
// 				free(matA[ra]);
// 			for (int rb=0; rb<rowsB; rb++)
// 				free(matB[rb]);
// 			free(matA);
// 			free(matB);

			return;
		}
	}

	perror("Optimal cost not found");
}


// No need for colsA because if the matrix multiplication is valid, then colsA = rowsB in A x B
void multiplyMatricies (unsigned int*** matA, unsigned int*** matB, unsigned int rowsA, unsigned int rowsB, unsigned int colsB, unsigned int*** resultMat) {
//	(*resultMat) = calloc (rowsA, sizeof(unsigned int*));
//	for (int r=0; r<rowsA; r++)
//		(*resultMat)[r] = calloc (colsB, sizeof(unsigned int*));

	for (int cb=0; cb<colsB; cb++) {
		for (int ra=0; ra<rowsA; ra++) {
			int dotProd = 0;
			
			for (int i=0; i<rowsB; i++)
				dotProd += (*matA)[ra][i] * (*matB)[i][cb];

			printf("\nra:%d\n", ra);
			unsigned int* intermArr = (*resultMat)[ra];
			intermArr[cb] = dotProd;
		}
	}
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





