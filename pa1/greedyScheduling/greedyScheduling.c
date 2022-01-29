#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Selection sort based approach to sorting jobs



int main(int argc, char* argv[]) {

    // First peek at how many jobs and maxendtime there are
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        exit(EXIT_FAILURE);
    }

    char buf[256];

    // Read the number of jobs to be scheduled
    if (!fscanf(fp, "%s\n", buf)) {
        perror("reading the number of jobs failed");
        exit(EXIT_FAILURE);
    }
    int jobcount = atoi(buf);

    // Next read the maximum number of maxendtime
    if (!fscanf(fp, "%s\n", buf)) {
        perror("reading the number of maxendtime failed");
        exit(EXIT_FAILURE);
    }
    int maxendtime = atoi(buf);

    // We've read the number of maxendtime so close the file and start over
    fclose(fp);


		int nextAvailableTime = 1;


		for (unsigned int job=0; job<jobcount; job++) {
			FILE* fp = fopen(argv[1], "r");
			if (!fp) {
				perror("fopen failed");
				exit(EXIT_FAILURE);
			}

			char buf[256];

			// Read the first two integers (num lines & max end time)
			if (!fscanf(fp, "%s\n", buf) || !fscanf(fp, "%s\n", buf)) {
				perror("reading the number of jobs or maxendtime failed");
				exit(EXIT_FAILURE);
			}



			bool jobFound = false;
			char optimalJob = 'A';
			int optimalEndTime = maxendtime;
			int optimalStartTime = maxendtime;

			for (int line=0; line<jobcount; line++) {
				char jobChar;
				int jobStart;
				int jobEnd;

				if (!fgets(buf, 256, fp)) {
					perror("reaidng a line for a job failed");
					exit(EXIT_FAILURE);
				}

				if (!sscanf(buf, "%c %d %d", &jobChar, &jobStart, &jobEnd)) {
					perror("reading a job line failed");
					exit(EXIT_FAILURE);
				}

				if (jobStart < nextAvailableTime)
					continue;

				if (jobEnd < optimalEndTime ||
						(jobEnd == optimalEndTime && jobStart <= optimalStartTime)) {
					optimalEndTime = jobEnd;
					optimalStartTime = jobStart;
					optimalJob = jobChar;
					jobFound = true;
				}

			}

			if (!jobFound)
				break;

			nextAvailableTime = optimalEndTime + 1;

			printf("%c\n", optimalJob);
			fclose(fp);
		}
		

    exit(EXIT_SUCCESS);
}



