#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {

  // Open the filename given as the first command line argument for reading
  FILE* fp = fopen(argv[1], "r");
  if (!fp) {
    perror("fopen failed");
    return EXIT_FAILURE;
  }

  char buf[256];
  char* string = fgets(buf, 256, fp);
	int startNum = atoi(string); 

	while (startNum != 1) {
		printf("%d\n", startNum);
		
		if (startNum % 2 == 0) {
			startNum /= 2;
		} else {
			startNum *= 3;
			++startNum;
		}
	}

	printf("%d\n", startNum);

  return EXIT_SUCCESS;
}
