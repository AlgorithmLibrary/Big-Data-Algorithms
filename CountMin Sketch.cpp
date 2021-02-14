/*
 * CountMin Sketch.cpp
 *
 *  Created on: 14 Feb 2021
 *      Author: Grant
 */

#include <iostream>
#include <random>
#include <math.h>

using namespace std;

int n = 15;

const int t = 20;
const int L = n;
const int k = 2;

int remainder(int a, int b)
{
    return a - (a / b) * b;
}

int mod(int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}

int hash_function(int x, int f1, int f2, int t2)
{
	int p = 608308871;

	int summation = f1 * pow(x, 0) + f2 * pow(x, 1);

	int result = mod(summation, p);

	int bucket = mod(result, t2);

	return bucket;
}

int CM_function(int hashing_table[][20], int hashing_factors[][2], int n, int t1, int i)
{
	int minimum = 1000;

	for (int r = i; r < L; r++)
	{
		int result = hash_function(i, hashing_factors[r][0], hashing_factors[r][1], t1);

		if (hashing_table[r][result] < minimum)
		{
			minimum = hashing_table[r][result];
		}
	}
	return minimum;
}

int main()
{
	int seed = 8;

	int p = 608308871;

	int points[n] = {1, 3, 5, 6, 8, 11, 15, 2, 3, 5, 21, 18, 19, 3, 5};

	int hashing_table[L][t];

	for (int u1 = 0 ; u1 < L; u1++)
	{
		for (int v1 = 0; v1 < t; v1++)
		{
			hashing_table[u1][v1] = 100;
		}
	}

	cout << "Hashing length " << t << endl;
	cout << "Number of Hash functions: " << L << endl;

	int hashing_factors[L][k];

	srand(seed*2);

	for (int i = 0; i < L; i++)
	{
		for (int j = 0; j < k; j++)
		{
			while(hashing_factors[i][j] == 0 or hashing_factors[i][j] > p)
			{
				hashing_factors[i][j] = mod(rand(), p);

				if (j == 0)
				{
					break;
				}
			}
		}
	}

	for (int c = 0; c < n; c++)
	{
		for (int d = 0; d < L; d++)
		{
			int result = hash_function(c, hashing_factors[d][0], hashing_factors[d][1], t);
			if (hashing_table[d][result] == 100)
			{
				hashing_table[d][result] = 1;
			}
			else
			{
				hashing_table[d][result] = hashing_table[d][result] + 1;
			}
		}
	}

	int q = 11;

	int x = 0;

	for (int b = 0; b < n; b++)
	{
		x = x + points[b];
	}

	int low_setting = 3;

	cout << "The heavy hitters occuring at least " << low_setting << " times:" << endl;

	for (int j = 0; j < n; j++)
	{
		int result = CM_function(hashing_table, hashing_factors, n, t, j);

		if (result >= 3)
		{
			cout << "Heavy Hitter " << j << endl;
		}
	}

	return 0;
}


