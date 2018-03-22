#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "fun.h"

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

int printColumn (int choice, train *arr)
{
	int i = 0, Num = 0;
	FILE *tf;

	if ((tf = fopen("structure.dat","rb")) == NULL)
		return -1;


	if (fread(&Num, sizeof(int), 1, tf) != 1)
		return -1;
	
	while(i < Num)
	{
		if (choice == 3)
		{
			if (i == 0)
			{
				if (fread(&arr[i].destination, sizeof(char[16]), 1, tf) != 1)
						return -1;
				printf("DESTINATION\n");
			}
			else
			{
				if (fseek(tf, (long)sizeof(int) * 3L, SEEK_CUR) != 0)
					return -1;
				if (fread(&arr[i].destination, sizeof(char[16]), 1, tf) != 1)
					return -1;
			}
			printf("%s\n", arr[i].destination);
		}
		else if (choice == 1)
		{	
			if (i == 0)
			{
				if (fseek(tf, (long)sizeof(char[16]), SEEK_CUR) != 0)
					return -1;
				if (fread(&arr[i].trainNum, sizeof(int), 1, tf) != 1)
					return -1;
				printf("NUMBER\n");
			}
			else
			{
				if (fseek(tf, (long)sizeof(int) * 2L + (long)sizeof(char[16]), SEEK_CUR) != 0)
					return -1;
				if (fread(&arr[i].trainNum, sizeof(int), 1, tf) != 1)
					return -1;
			}
			printf("%03d\n", arr[i].trainNum);
		}
		else if (choice == 2)
		{
			if (i == 0)
			{
				printf("TIME\n");
			}
			if (fseek(tf, (long)sizeof(char[16]) + (long)sizeof(int), SEEK_CUR) != 0)
				return -1;
			if (fread(&arr[i].tTime, sizeof(int) * 2L, 1, tf) != 1)
				return -1;
			printf("%02d:%02d\n", arr[i].tTime.Hours, arr[i].tTime.Minutes);
		}
		i++;
	}
	fclose(tf);
	return Num;
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
