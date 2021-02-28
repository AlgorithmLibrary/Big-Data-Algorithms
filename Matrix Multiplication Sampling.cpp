/*
 * Matrix Multiplication Sampling.cpp
 *
 *  Created on: 28 Feb 2021
 *      Author: Grant
 */

#include <iostream>
#include <math.h>
#include <random>
#include <bitset>

using namespace std;

const int p = 8;
const int i = 3;

float** dot_product(float A[][i], float B[][p], int k)
{
	float** array = new float*[k];

	for (int a = 0; a < p; a++)
	{
	    array[a] = new float[p];
	}

	for (int u = 0; u < k; u++)
	{
		for (int v = 0; v < p; v++)
		{
			array[u][v] = 0.0;
		}
	}

	for(int l = 0; l < k; l++)
	{
		for(int j = 0; j < p; j++)
		{
			for(int k = 0; k < i; k++)
	        {
				array[l][j] += A[l][k] * B[k][j];
	        }
		}
	}

	for (int u1 = 0; u1 < k; u1++)
	{
		for (int v1 = 0; v1 < p; v1++)
		{
			cout << array[u1][v1] << " ";
		}
		cout << endl;
	}
	cout << endl;

	return array;
}

int main()
{
	int m = 3;

	int n = 8;

	float A[m][n] = {{1, 2, 5, 1, 6, 2, 8, 9},
					 {3, 8, 9, 3, 1, 5, 6, 1},
					 {3, 1, 8, 4, 5, 8, 11, 5}};

	float B[n][p] = {{3, 2, 6, 1, 9, 1, 5, 9},
			         {1, 8, 5, 3, 1, 9, 1, 6},
					 {2, 5, 1, 9, 3, 8, 1, 3},
					 {5, 1, 6, 8, 3, 5, 6, 1},
					 {2, 3, 8, 1, 5, 1, 1, 3},
					 {1, 8, 3, 2, 1, 8, 2, 9},
					 {5, 1, 8, 1, 2, 3, 5, 1},
					 {2, 3, 6, 1, 5, 8, 5, 9}};

	float summation[n];

	for (int a = 0; a < n; a++)
	{
		float temp1 = 0.0;

		for (int b = 0; b < m; b++)
		{
			temp1 = temp1 + pow(A[b][a], 2);
		}

		temp1 = sqrt(temp1);

		float temp2 = 0.0;

		for (int c = 0; c < p; c++)
		{
			temp2 = temp2 + pow(B[a][c], 2);
		}

		temp2 = sqrt(temp2);

		summation[a] = temp1 * temp2;
	}

	float probabilities[n];
	float cumulative[n];
	float total = 0.0;

	for (int e = 0; e < n; e++)
	{
		total = total + summation[e];
	}

	for (int e1 = 0; e1 < n; e1++)
	{
		probabilities[e1] = summation[e1] / total;
	}

	for (int e2 = 0; e2 < n; e2++)
	{
		if (e2 == 0)
		{
			cumulative[e2] = probabilities[e2];
		}
		else
		{
			cumulative[e2] = cumulative[e2 - 1] + probabilities[e2];
		}
	}

	for (int e3 = 0; e3 < n; e3++)
	{
		cout << cumulative[e3] << endl;
	}
	cout << endl;

	int set_of_i[i];

	srand(1);

	for (int r = 0; r < i; r++)
	{
		int t = rand() % 100;
		float tt = float(t) / 100.0;

		for (int r1 = 0; r1 < n; r1++)
		{
			if (cumulative[r1] > tt)
			{
				set_of_i[r] = r1;
				break;
			}
		}
	}

	for (int s = 0; s < i; s++)
	{
		cout << set_of_i[s] << " ";
	}
	cout << endl;
	cout << endl;

	float C[m][i];
	float R[i][p];

	for (int y = 0; y < i; y++)
	{
		for (int y1 = 0; y1 < m; y1++)
		{
			C[y1][y] = A[y1][set_of_i[y]] / sqrt(i * probabilities[set_of_i[y]]);
		}

		for (int y2 = 0; y2 < p; y2++)
		{
			R[y][y2] = B[set_of_i[y]][y2] / sqrt(i * probabilities[set_of_i[y]]);
		}
	}

	float** result = dot_product(C, R, m);

	for (int k = 0; k < m; k++)
	{
		for (int j = 0; j < p; j++)
		{
			cout << result[k][j] << " ";
		}
		cout << endl;
	}

	return 0;
}


