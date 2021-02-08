/*
 * Morris Algorithm.cpp
 *
 *  Created on: 8 Feb 2021
 *      Author: Grant
 */

#include <iostream>
#include <random>
#include <time.h>
#include <math.h>

using namespace std;

void swap(float* a, float* b)
{
    float t = *a;
    *a = *b;
    *b = t;
}

int partition (float arr[], int low, int high)
{
    float pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high- 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(float arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int morris(int x)
{
	float r = ((rand() % 100) / 100.0);

	if (r < (1.0 / (pow(2, x))))
	{
		x++;
	}

	return x;
}

float morris_plus(int s, int e)
{
	int x[s];

	for (int i = 0; i < s; i++)
	{
		int x_temp = 0;
		for (int j = 0; j < e; j++)
		{
			x_temp = morris(x_temp);
		}
		x[i] = x_temp;
	}

	float average;

	float sum = 0.0;
	for (int k = 0; k < s; k++)
	{
		sum = sum + float(x[k]);
	}

	average = sum / s;

	return average;
}

float morris_plus_plus(int s, int e, int t)
{
	float x[t];

	for (int i = 0; i < t; i++)
	{
		x[i] = morris_plus(s, e);
	}

	quickSort(x, 0, t - 1);

	for (int j = 0; j < t; j++)
	{
		cout << x[j] << endl;
	}

	int indicator = t % 2;

	cout << "Indicator is " << indicator << endl;

	float median_estimate;

	if (indicator == 1)
	{
		median_estimate = x[((t - 1) / 2)];
	}
	else
	{
		median_estimate = (x[t / 2 - 1] + x[t / 2]) / 2.0;
	}

	return median_estimate;
}

int main()
{
	srand(11);

	int e = 100;
	int s = 15;
	int t = 8;

	float x = morris_plus_plus(s, e, t);

	cout << "x is " << x << endl;

	int n = pow(2, x) - 1;

	cout << "The initial n is " << n << endl;

	return 0;
}


