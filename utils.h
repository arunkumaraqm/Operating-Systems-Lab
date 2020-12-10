#include "macros.h"

#include <stdio.h>

#ifndef UTILS_H
#define UTILS_H 

void read_array(int* arr, int size)
{
	for (int i = 0; i < size; ++i)
	{
		scan(arr[i]);
	}	
}

void print_array(int* arr, int size)
{
	for (int i = 0; i < size; ++i)
	{
		ps(arr[i]);
	}	
	printf("\n");
}

void fill(int* arr, int size, int fillval)
{
	for (int i = 0; i < size; ++i)
	{	
		arr[i] = fillval;
	}
}

int find(int* arr, int size, int key)
{
	for (int i = 0; i < size; ++i)
	{
		if (arr[i] == key) return i;
	}
	return -1;
}

int location_of_min(int* arr, int size)
{
	int smallest = arr[0], pos = 0;

	for (int i = 0; i < size; ++i)
	{
		if (arr[i] < smallest)
		{
			smallest = arr[i];
			pos = i;
		}
	}

	return pos;
}
#endif