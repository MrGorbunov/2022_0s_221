#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int main (int, char*[]);

void readMatriciesFromFile (FILE*, unsigned int, 
		unsigned int*, unsigned int*, unsigned int***);
void print2DArr (unsigned int**, unsigned int, unsigned int);

void matMul (unsigned int**, unsigned int, unsigned int,
		unsigned int**, unsigned int, unsigned int,
		unsigned int**);
void multipleMatMulMatrix (unsigned int, unsigned int***, unsigned int*, unsigned int*,
		int**, unsigned int, unsigned int,
		unsigned int**
		);
void multipleMatMulCost (unsigned int*, unsigned int*, int**,
		unsigned int, unsigned int,
		int*);
void calcCostOfGrouping (unsigned int*, unsigned int*, int**, 
		unsigned int, unsigned int, int, 
		int*);




int main(
		int argc, char* argv[]
		) {
	
	// Read from input
	unsigned int numMats;
	unsigned int* numRows;
	unsigned int* numCols;
	unsigned int*** matricies;

	// Processing Variables
	int** multMinCost;
	unsigned int** finalProduct;


	//
	// Reading User Input
	//

	assert(argc == 2); /* Parameter 2 (argv[1]) should be the file path */

	FILE* fp = fopen(argv[1], "r");
	if (!fp) {
		perror("fopen failed");
		exit(EXIT_FAILURE);
	}

	if (!fscanf(fp, "%d\n", &numMats)) {
		perror("reading the number of matricies failed");
		exit(EXIT_FAILURE);
	}
	
	printf("Number mats: %d\n", numMats);

	numRows = calloc(numMats, sizeof(unsigned int));
	numCols = calloc(numMats, sizeof(unsigned int));
	matricies = calloc(numMats, sizeof(unsigned int**));

	readMatriciesFromFile(fp, numMats, numRows, numCols, matricies);



	
	//
	// Sanity check debugs
	printf("Number mats: %d\n", numMats);
	for (unsigned int i=0; i<numMats; i++) {
		printf(" == Matrix %d ==\n", i);
		print2DArr(matricies[i], numRows[i], numCols[i]);
		printf("\n");
	}


	printf("\n\n");
	printf("Multiplying array 0 & 1\n");

	unsigned int** multResult = calloc(numRows[0], sizeof(unsigned int*));
	for (int r=0; r<(int) numRows[0]; r++)
		multResult[r] = calloc(numCols[1], sizeof(unsigned int));

	matMul(matricies[0], numRows[0], numCols[0],
			matricies[1], numRows[1], numCols[1],
			multResult);

	print2DArr(multResult, numRows[0], numCols[1]);

	for (int i=0; i<(int) numRows[0]; i++)
		free(multResult[i]);
	free(multResult);





	//
	// Processing
	//

	// Initializing
	multMinCost = calloc(numMats, sizeof(int*));
	for (unsigned int i=0; i<numMats; i++) {
		multMinCost[i] = calloc(numMats, sizeof(int));
		for (unsigned int j=0; j<numMats; j++)
			multMinCost[i][j] = -1;
	}

	printf("\n");
	print2DArr(multMinCost, numMats, numMats);

	printf("\n");
	printf("Getting cost of multiplication\n");
	int minCost;
	multipleMatMulCost(numRows, numCols, multMinCost, 0, numMats - 1, &minCost);
	printf("Min Cost: %d\n", minCost);

	printf("\n");
	print2DArr(multMinCost, numMats, numMats);


	unsigned int rowsFinalMat = numRows[0];
	unsigned int colsFinalMat = numCols[numMats - 1];
	unsigned int** finalMat = calloc(rowsFinalMat, sizeof(unsigned int*));
	for (unsigned int rf=0; rf<rowsFinalMat; rf++)
		finalMat[rf] = calloc(colsFinalMat, sizeof(unsigned int));

	printf("\nAttempting multiplication of mats %d through %d\n", 0, numMats-1);
	multipleMatMulMatrix(numMats, matricies, numRows, numCols, 
			multMinCost, 0, numMats-1, finalMat);
	printf("\nNow getting matrix\n");
	print2DArr(finalMat, rowsFinalMat, colsFinalMat);

	for (unsigned int rf=0; rf<rowsFinalMat; rf++)
		free(finalMat[rf]);
	free(finalMat);





	//
	// Clean Up
	//

	for (unsigned int m=0; m<numMats; m++) {
		for (unsigned int r=0; r<numRows[m]; r++)
			free(matricies[m][r]);
		free(matricies[m]);
		free(multMinCost[m]);
	}

	free(matricies);
	free(multMinCost);
	free(numRows);
	free(numCols);

	return EXIT_SUCCESS;
}







//======================================================
//
//    Input / Output
//
//======================================================

void readMatriciesFromFile (
		FILE* fp, unsigned int numMats, 
		unsigned int* numRows, unsigned int* numCols, unsigned int*** matricies
		) {

	for (unsigned int mat=0; mat<numMats; mat++) {
		if (!fscanf(fp, "%d %d\n", &numRows[mat], &numCols[mat])) {
			perror("reading matrix size failed");
			exit(EXIT_FAILURE);
		}

		int rowSz = (int) numRows[mat];
		int colSz = (int) numCols[mat];

		matricies[mat] = calloc(rowSz, sizeof(unsigned int*));

		for (int r=0; r<rowSz; r++) {
			matricies[mat][r] = calloc(colSz, sizeof(unsigned int));

			for (int c=0; c<colSz; c++) {
				if (!fscanf(fp, "%d ", &matricies[mat][r][c])) {
					perror("reading matrix value failed");
					exit(EXIT_FAILURE);
				}
			}
		}
	}
}


void print2DArr (
		unsigned int** arr, unsigned int rows, unsigned int cols
		) {

	for (unsigned int r=0; r<rows; r++) {
		for (unsigned int c=0; c<cols; c++) {
			printf("%3d ", arr[r][c]);
		}

		printf("\n");
	}
}






//======================================================
//
//    Processing
//
//======================================================

void matMul (
		unsigned int** matA, unsigned int rowsA, unsigned int colsA,
		unsigned int** matB, unsigned int rowsB, unsigned int colsB,
		unsigned int** returnMatResult
		) {

	assert(colsA == rowsB);  /* This is needed for the matrix multiplication to be valid */

	// matrixResult has dimensions rowsA x colsB
	for (int ra=0; ra<(int)rowsA; ra++) {
		for (int cb=0; cb<(int)colsB; cb++) {
			int dotProduct = 0;

			for (int i=0; i<(int)colsA; i++)
				dotProduct += matA[ra][i] * matB[i][cb];

			returnMatResult[ra][cb] = dotProduct;
		}
	}
}


void multipleMatMulMatrix (
		unsigned int numMats, unsigned int*** matricies, unsigned int* numRows, unsigned int* numCols,
		int** matMulCosts, unsigned int matStart, unsigned int matEnd,
		unsigned int** returnMatMul
		) {
	if (matStart == matEnd) {
		for (unsigned int r=0; r<numRows[matStart]; r++) {
			for (unsigned int c=0; c<numCols[matStart]; c++)
				returnMatMul[r][c] = matricies[matStart][r][c];
		}
		return;
	} else if (matStart+1 == matEnd) {
		matMul(matricies[matStart], numRows[matStart], numCols[matStart],
				matricies[matEnd], numRows[matEnd], numCols[matEnd],
				returnMatMul
				);
		return;
	}

	int targetMinCost;
	multipleMatMulCost(numRows, numCols, matMulCosts, matStart, matEnd, &targetMinCost);
	for (int grouping=(int)matStart; grouping<(int)matEnd; grouping++) {
		int totalCost;
		calcCostOfGrouping(numRows, numCols, matMulCosts, 
				matStart, matEnd, grouping, &totalCost);

		if (totalCost != targetMinCost)
			continue;

		unsigned int rowsA = numRows[matStart];
		unsigned int colsA = numCols[grouping];
		unsigned int rowsB = numRows[grouping + 1];
		unsigned int colsB = numCols[matEnd];

		unsigned int** matA = calloc(rowsA, sizeof(unsigned int*));
		unsigned int** matB = calloc(rowsB, sizeof(unsigned int*));
		for (unsigned int ra=0; ra<rowsA; ra++)
			matA[ra] = calloc(colsA, sizeof(unsigned int));
		for (unsigned int rb=0; rb<rowsB; rb++)
			matB[rb] = calloc(colsB, sizeof(unsigned int));

		multipleMatMulMatrix(numMats, matricies, numRows, numCols, 
				matMulCosts, matStart, grouping, matA);
		multipleMatMulMatrix(numMats, matricies, numRows, numCols, 
				matMulCosts, grouping+1, matEnd, matB);
		matMul(matA, rowsA, colsA, matB, rowsB, colsB, returnMatMul);

		for (unsigned int ra=0; ra<rowsA; ra++)
			free(matA[ra]);
		for (unsigned int rb=0; rb<rowsB; rb++)
			free(matB[rb]);
		free(matA);
		free(matB);

		return;
	}

	// This function should always terminate in the above loop, never here
	assert(1 == 0);
}


void multipleMatMulCost (
		unsigned int* numRows, unsigned int* numCols, int** matMulCosts,
		unsigned int matStart, unsigned int matEnd,
		int* returnMinCost
		) {

	assert(matStart <= matEnd);  /* never do backwards multiplication */

	if (matMulCosts[matStart][matEnd] != -1) {
		*returnMinCost = matMulCosts[matStart][matEnd];
		return;
	} else if (matStart == matEnd) {
		matMulCosts[matStart][matEnd] = 0;
		*returnMinCost = 0;
		return;
	}

	int minCost = -1;
	for (int grouping=(int)matStart; grouping<(int)matEnd; grouping++) {
		int groupingCost;
		calcCostOfGrouping(numRows, numCols, matMulCosts, 
				matStart, matEnd, grouping, &groupingCost);
		
		if (minCost == -1 || groupingCost < minCost)
			minCost = groupingCost;
	}

	assert(minCost != -1);  /* If it equals -1, the above for loop was skipped */

	matMulCosts[matStart][matEnd] = minCost;
	*returnMinCost = (unsigned int) minCost;
}


/*
	Calculates the cost a specific grouping of matricies,
	assuming all further sub-groupings are optimal
		ex groupings: (AB)C, (ABC)D, (AB)(CDEF)
 */
void calcCostOfGrouping (
		unsigned int* numRows, unsigned int* numCols, 
		int** matMulCosts, unsigned int matStart, unsigned int matEnd, int grouping,
		int* returnTotalCost
		) {

	 /* 
			The grouping number corresponds to where the string of mats are split, so it
		  should be between the start & end matricies
		*/
	assert(grouping >= (int) matStart && grouping < (int) matEnd);

	int costMatA; // the left and right groups are referred to as A and B
	int costMatB; // ex: (GDS)(EF),  A = GDS, B = EF
	multipleMatMulCost(numRows, numCols, matMulCosts, matStart, grouping, &costMatA);
	multipleMatMulCost(numRows, numCols, matMulCosts, grouping+1, matEnd, &costMatB);

	// cost to multiply matricies A and B
	int costNextMult = numRows[matStart] * numCols[grouping] * numCols[matEnd];

	*returnTotalCost = costMatA + costMatB + costNextMult;
}









