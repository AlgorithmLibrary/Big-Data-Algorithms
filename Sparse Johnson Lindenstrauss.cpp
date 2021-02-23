/*
 * Sparse Johnson Lindenstrauss.cpp
 *
 *  Created on: 23 Feb 2021
 *      Author: Grant
 */

#include <iostream>
#include <math.h>
#include <random>

using namespace std;

const int n = 5;
const int d = 9;

float** dot_product(int x[][n], float R[][d], int k)
{
	float** array = new float*[k];

	for (int a = 0; a < n; a++)
	{
	    array[a] = new float[n];
	}

	for(int i = 0; i < k; i++)
	{
		for(int j = 0; j < n; j++)
		{
			for(int k = 0; k < d; k++)
	        {
				array[i][j] += R[i][k] * x[k][j];
	        }
		}
	}

	for (int u = 0; u < k; u++)
	{
		for (int v = 0; v < n; v++)
		{
			cout << array[u][v] << " ";
		}
		cout << endl;
	}
	cout << endl;

	return array;
}

int main()
{
	int x[d][n] = {{1, 2, 5, 1, 3},
			 	   {3, 8, 9, 11, 1},
				   {3, 1, 8, 2, 3},
				   {3, 1, 8, 6, 1},
				   {5, 1, 2, 8, 9},
				   {8, 3, 1, 3, 3},
				   {5, 6, 5, 1, 3},
				   {2, 1, 6, 1, 3},
				   {1, 2, 8, 1, 1}};

	float e = 0.8;

	//int k = int(24.0 * log10(d) / (3 * pow(e, 2) + 2 * pow(e, 3)));

	int k = int(3 * log10(d) / (pow(e, 2)));

	int s = int(3 * log10(d) / (e));

	//cout << k << endl;

	float R[k][d];

	srand(5);

	int block[s][d];

	for (int e1 = 0; e1 < s; e1++)
	{
		for (int e2 = 0; e2 < d; e2++)
		{
			block[e1][e2] = 100;
		}
	}

	if (s != k)
	{
		for (int e3 = 0; e3 < d; e3++)
		{
			//int count = 0;
			for (int e4 = 0; e4 < s; e4++)
			{
				int temp;
				bool in = false;
				bool already_in;

				while (in == false)
				{
					temp = rand() % k;
					already_in = false;

					for (int e5 = 0; e5 < s; e5++)
					{
						if (block[e5][e3] == temp)
						{
							already_in = true;
						}
					}

					if (already_in == false)
					{
						in = true;
					}
				}

				block[e4][e3] = temp;
			}
		}
	}

	//default_random_engine generator;
	//normal_distribution<float> distribution(0.0, 1.0);

	int set[k * d];

	for (int b = 0; b < k * d; b++)
	{
		set[b] = rand() % 2;
	}

	for (int c = 0; c < k * d; c++)
	{
		cout << set[c] << " ";
	}
	cout << endl;

	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < d; j++)
		{
			int element = set[i * k + j];

			if (element == 0)
			{
				R[i][j] = -1;
			}
			else
			{
				R[i][j] = 1;
			}

			bool in_block = false;

			for (int j1 = 0; j1 < s ; j1++)
			{
				if (i == block[j1][j])
				{
					in_block = true;
				}
			}

			if (in_block == false)
			{
				R[i][j] = 0;
			}
		}
	}

	cout << "R" << endl;
	for (int i1 = 0; i1 < k; i1++)
	{
		for (int j1 = 0; j1 < d; j1++)
		{
			cout << R[i1][j1] << " ";
		}
		cout << endl;
	}
	cout << endl;

	float** result = dot_product(x, R, k);

	for (int u = 0; u < k; u++)
	{
		for (int v = 0; v < n; v++)
		{
			result[u][v] = result[u][v] / pow(k, 1.0 / 2.0);
		}
	}

	for (int u1 = 0; u1 < k; u1++)
	{
		for (int v1 = 0; v1 < n; v1++)
		{
			cout << result[u1][v1] << " ";
		}
		cout << endl;
	}

	return 0;
}


