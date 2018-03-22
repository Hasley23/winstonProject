#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct time
{
	int Hours;
	int Minutes;
};

typedef struct time time;

struct train
{
	char destination[16];
	int trainNum;
	time tTime;
} temp;

typedef struct train train;

void sortAZ(train *, int); //tired
int writeBinary(train *, int);
int readBinary(train *);
int showTrain(long);
int findTrains(int, int);
void printArray(train *, int);

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
	return 0;
}

int writeBinary(train *arr, int Num)
{
	int i = 0;
	FILE *tf;
	if ((tf = fopen("structure.dat","wb")) == NULL)
		return -1;

	while(i < Num)
	{
		if (i == 0)
			if (fwrite(&Num, sizeof(int), 1, tf) != 1)
				return -1; 
		if (fwrite(&arr[i], sizeof(train), 1, tf) != 1)
			return -1;
		i++;
	}
	fclose(tf);
	return 0;
}

int readBinary(train *arr)
{
	int i = 0, Num = 0;
	FILE *tf;

	if ((tf = fopen("structure.dat","rb")) == NULL)
		return -1;


	if (fread(&Num, sizeof(int), 1, tf) != 1)
		return -1;

	while(i < Num)
	{
		if (fread(&arr[i], sizeof(train), 1, tf) != 1)
			return -1;
		i++;
	}
	fclose(tf);
	return Num;
}

int showTrain(long Num)
{
	int check;
	train *tmp = &temp;
	FILE *tf;
	
	Num--;
	if ((tf = fopen("structure.dat","rb")) == NULL)
		return 1;

	if (fread(&check, sizeof(int), 1, tf) != 1) 
		return 1;
	
	if (Num < (long)check && Num > -1)
	{
		if (fseek(tf, Num * (long)sizeof(train), SEEK_CUR) != 0)
			return 1;

		if (fread(tmp, sizeof(train), 1, tf) != 1)
			return 1;
		return 0;
	}
	else 
		return 1;
	fclose(tf);
}

int findTrains(int hrs, int mts)
{
	int i = 0, Num;
	char isExist = 'F';
	train *tmp = &temp;
	FILE *tf;
	
	if ((tf = fopen("structure.dat","rb")) == NULL)
		return -1;

	if (fread(&Num, sizeof(int), 1, tf) != 1)
		return -1;

	while(i < Num)
	{
		if (fread(tmp, sizeof(train), 1, tf) != 1)
			return -1;
     	if((hrs < (*(tmp)).tTime.Hours) || (hrs == (*(tmp)).tTime.Hours && mts < (*(tmp)).tTime.Minutes))
		{	
			if (isExist == 'F')
			{
				printf("\nDeparts list after %02d:%02d:\n", hrs, mts);
				printf("NUMBER   TIME    DESTINATION\n");
				isExist = 'T';
			}
			printf("%03d      %02d:%02d   %s\n", (*(tmp)).trainNum, (*(tmp)).tTime.Hours, (*(tmp)).tTime.Minutes, (*(tmp)).destination);
        }
        i++;
	}

	if (isExist == 'F')
		printf("\nTrains aren't scheduled after this time.\n");
	fclose(tf);
}

void sortAZ(train *arr, int Num)
{
	int i = 0, j;
	train chamber;

	while(i < Num) 
	{	
		j = i + 1;
    	while(j < Num) 
     	{
        	if(strcmp((*(arr + i)).destination, (*(arr + j)).destination) > 0)
           	{
				chamber = *(arr + i);
				*(arr + i) = *(arr + j);
				*(arr + j) = chamber;
           	}
           	j++;
    	}
    	i++;
	}
}

void printArray(train *arr, int Num)
{
	int i = 0;

	printf("NUMBER   TIME    DESTINATION\n");
	while(i < Num)
	{
	    printf("%03d      %02d:%02d   %s\n", (*(arr + i)).trainNum, (*(arr + i)).tTime.Hours, (*(arr + i)).tTime.Minutes, (*(arr + i)).destination);
		i++;
	}
}
