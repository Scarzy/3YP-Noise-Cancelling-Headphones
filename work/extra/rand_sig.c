#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define RMAX 50
#define SIGLENGTH 200.0

int32_t sum1 = 0, sum2 = 0;

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("ERR... No, you must give a file name to write to...\n");
		return 0;
	}
	FILE *file = fopen(argv[1],"w");
	int rands1[(int)SIGLENGTH], rands2[(int)SIGLENGTH];
	srand((unsigned int) time(NULL));
	printf("Values:\n\tRands 1\tRands 2");
	for(int i = 0; i < SIGLENGTH; i++)
	{
		rands1[i] = (rand() % RMAX) - (RMAX / 2);
		rands2[i] = (rand() % RMAX) - (RMAX / 2);
		sum1 += rands1[i];
		sum2 += rands2[i];
		fprintf(file,"%d,",rands1[i]);
		printf("\n\t%d\t%d\t%d\t%d",rands1[i],rands2[i],sum1,sum2);
	}
	fprintf(file, " %f", (sum1/SIGLENGTH));
	printf("\nMean: %f\t %f", (sum1/SIGLENGTH), (sum2/SIGLENGTH));
	printf("\nEnd\n");
}

