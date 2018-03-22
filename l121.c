#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "fun.h"

int main ()
{
	FILE *fp;
	char c = '0';
	int nline = 0, count = 0, Hours = -1, Minutes = -1;
	long seek;

	if ((fp = fopen("structures.txt","r")) == NULL)
	{
		printf("No such file or directory!\n");
		return 1;
	}

	if (fscanf(fp,"%d", &count) != 1)
	{
		printf("Something went wrong!\n");
		return 1;
	}

	train *array = (train*) malloc (count * sizeof(train));
	
	while (c != '#')
	{
		while (nline < count)
		{
			if (fscanf(fp,"%15s %d %d:%d", array[nline].destination, &array[nline].trainNum, &array[nline].tTime.Hours, &array[nline].tTime.Minutes) != 4)
			{
				printf("Something went wrong!\n");
				return 1;
			} 
			nline++;
		}
		if (fscanf(fp,"%c", &c) != 1)
		{
			printf("Something went wrong!\n");
			return 1;
		}
	}
	fclose(fp);

	sortAZ(array, count);
	if (writeBinary(array, count) == -1)
	{
		printf("Something went wrong!\n");
		return 1;
	}

	//check
	free(array);
	array = (train*) malloc (count * sizeof(train));

	count = readBinary(array);
	if (count == -1) 
	{
		printf("Something went wrong!\n");
		return 1;
	}

	printf("Schedule:\n");
	printArray(array, count);

	printf("\nInput departure time to search (HH:MM):\n");
	while (Hours < 0 || Hours > 23 || Minutes < 0 || Minutes > 59)
	{
		scanf("%d:%d", &Hours, &Minutes);
		if (Hours < 0 || Hours > 23 || Minutes < 0 || Minutes > 59)
			printf("Input THE REAL time: ");	
	}

	if (findTrains(Hours, Minutes) == -1)
	{
		printf("Something went wrong!\n");
		return 1;
	}

	printf("\nEnter the entry number:\n");
	scanf("%ld", &seek);

	if (showTrain(seek) == 0)
	{
		printf("The function returned: true\n\n");
		printArray(&temp, 1);
	}
	else
		printf("The function returned: false\n\n");
		
	free(array);
	array = (train*) calloc (count, sizeof(train));
	
	printf("\nEnter the column number:\n");
	scanf("%ld", &seek);
	printf("\n");
	if (printColumn (seek, array) == -1)
	{
		printf("Something went wrong!\n");
		return 1;
	}
	
	free(array);
	return 0;
}
