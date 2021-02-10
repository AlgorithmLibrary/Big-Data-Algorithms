/*
 * AMS Algorithm.cpp
 *
 *  Created on: 10 Feb 2021
 *      Author: Grant
 */

#include <iostream>
#include <random>
#include <math.h>

using namespace std;

int hash_function(int x)
{
	int p = 608308871;
	int independence = 4;
	int buckets = 2;

	int a[independence];

	for (int i = 0; i < independence; i++)
	{
		while(a[i] == 0 or a[i] > p)
		{
			a[i] = rand() % p;

			if (i == 0)
			{
				break;
			}
		}
	}

	/*
	cout << "HERE ";
	for (int w = 0; w < independence; w++)
	{
		cout << a[w] << " ";
	}
	cout << endl;
	*/

	int summation = 0;
	for (int j = 0; j < independence; j++)
	{
		summation = summation + a[j] * pow(x, j);
	}

	int result = summation % p;

	int bucket = result % buckets;

	if (bucket == 1)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

int main()
{
	int seed = 15;
	int n = 15;
	int m = 3;
	float correction = 0.68;

	int x[n] = {1, 3, 5, 6, 8, 11, 15, 2, 3, 5, 21, 18, 19, 3, 5};

	int y[m];

	int pi_matrix[m][n];

	for (int i = 0; i < m; i++)
	{
		//srand(seed + i);
		for (int j = 0; j < n; j++)
		{
			srand(seed + pow(i, j) + pow(j, i));
			pi_matrix[i][j] = hash_function(x[j]);
			cout << pi_matrix[i][j];
		}

		int count1 = 0;
		int countminus1 = 0;
		for (int j1 = 0; j1 < n; j1++)
		{
			if (pi_matrix[i][j1] == 1)
			{
				count1++;
			}
			else
			{
				countminus1++;
			}
		}

		if (count1 > (correction * n) or countminus1 > (correction * n))
		{
			seed++;
			i--;
		}
		cout << endl;
	}

	for (int k = 0; k < m; k++)
	{
		int temp_summation = 0;
		for (int l = 0; l < n; l++)
		{
			temp_summation = temp_summation + pi_matrix[k][l] * x[l];
		}
		y[k] = temp_summation;
	}

	float estimator = 0;
	for (int p = 0; p < m; p++)
	{
		estimator = estimator + pow(y[p], 2);
	}
	estimator = estimator / m;

	cout << "The estimated result is " << estimator << endl;

	return 0;
}


