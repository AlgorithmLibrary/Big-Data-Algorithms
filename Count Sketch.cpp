/*
 * Count Sketch.cpp
 *
 *  Created on: 15 Feb 2021
 *      Author: Grant
 */

#include <iostream>
#include <random>
#include <math.h>

using namespace std;

float alpha = 0.19;
float epsilon = alpha / 4.0;

const int t = (2.0 / epsilon);

//const int t = 30;
//const int L = n;
const int k = 2;

int count[15];

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

//int CM_function(int hashing_table[][t], int hashing_factors[][k], int n, int t1, int L, int i)
int CM_function(int **hashing_table, int hashing_factors[][k], int n, int t1, int L, int i)
{
	int minimum = 1000;

	for (int r = i; r < L; r++)
	{
		int result = hash_function(i, hashing_factors[r][0], hashing_factors[r][1], t1);

		if (hashing_table[r][result] < minimum && hashing_table[r][result] > 0)
		{
			minimum = hashing_table[r][result];
		}
	}

	if (minimum == 1000)
	{
		return 0;
	}
	else
	{
		//cout << "Minimum is " << minimum << endl;
		return minimum;
	}
}

bool CountMin(int points[], int n, int seed)
{
	//float epsilon = 2.0 / float(t);
	//float alpha = 4.0 * epsilon;

	float delta = 0.01 * alpha / (4.0 * log(n));

	//cout << "Delta is " << delta << endl;

	int p = 608308871;

	int L = int(log(1 / delta));

	int **hashing_table;

	hashing_table = new int *[L];
	for(int m = 0; m < L; m++)
	{
	    hashing_table[m] = new int[t];
	}

	for (int u1 = 0 ; u1 < L; u1++)
	{
		for (int v1 = 0; v1 < t; v1++)
		{
			hashing_table[u1][v1] = 100;
		}
	}

	//cout << "Hashing length " << t << endl;
	//cout << "Number of Hash functions: " << L << endl;

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

	int hashing_factors2[L][k];

	srand(seed*3);

	for (int i1 = 0; i1 < L; i1++)
	{
		for (int j1 = 0; j1 < k; j1++)
		{
			while(hashing_factors[i1][j1] == 0 or hashing_factors[i1][j1] > p)
			{
				hashing_factors2[i1][j1] = mod(rand(), p);

				if (j1 == 0)
				{
					break;
				}
			}
		}
	}

	int sigma;
	int sign_buckets = 6;

	for (int c = 0; c < n; c++)
	{
		for (int d = 0; d < L; d++)
		{
			int result = hash_function(c, hashing_factors[d][0], hashing_factors[d][1], t);
			int sign = hash_function(c, hashing_factors2[d][0], hashing_factors2[d][1], sign_buckets);

			if (sign < 3)
			{
				sigma = 1;
			}
			else
			{
				sigma = -1;
			}

			//cout << "Sigma is " << sigma << endl;

			if (hashing_table[d][result] == 100)
			{
				hashing_table[d][result] = sigma * points[c];
			}
			else
			{
				hashing_table[d][result] = hashing_table[d][result] + sigma * points[c];
			}
		}
	}

	int x = 0;

	for (int b = 0; b < n; b++)
	{
		x = x + pow(points[b], 2);
	}

	x = int(pow(x, 0.5));

	int low_setting = 3;

	//cout << "The heavy hitters occuring at least " << low_setting << " times:" << endl;

	bool hitters = false;

	float lowest_value = (3 * alpha / 4) * x;

	//cout << lowest_value << endl;

	for (int j = 0; j < n; j++)
	{
		int result = CM_function(hashing_table, hashing_factors, n, t, L, j);

		//cout << result << endl;

		if (result >= lowest_value)
		{
			//cout << "Heavy Hitter is present" << endl;
			//cout << "Heavy Hitter " << points[j] << endl;
			count[points[j]]++;
			hitters = true;
		}
	}
	cout << endl;

	return hitters;
}

void heavy_hitter(int points[], int n, int seed)
{
	if (n == 1)
	{
		//cout << "Selected point " << points[0] << endl;
		count[points[0]]++;
		return;
	}

	bool r;

	if (n == 15)
	{
		r = true;
	}
	else
	{
		r = CountMin(points, n, seed);
	}

	if (r == true)
	{
		int middle = int(n / 2);

		int n1 = middle;
		int n2 = n - middle;

		int first_array[n1];
		int second_array[n2];

		for (int i = 0; i < n1; i++)
		{
			first_array[i] = points[i];
		}

		for (int j = 0; j < n2; j++)
		{
			second_array[j] = points[n1 + j];
		}

		heavy_hitter(first_array, n1, seed);
		heavy_hitter(second_array, n2, seed);
	}
	return;
}

int main()
{
	int seed = 11;

	int p = 608308871;

	int n = 15;

	int points[n] = {1, 3, 5, 6, 8, 11, 15, 2, 3, 5, 21, 18, 19, 3, 5};

	heavy_hitter(points, n, seed);

	for (int j = 0; j < n; j++)
	{
		cout << count[j] << endl;
	}

	return 0;
}


