/*
 * Matrix Multiplication JL.cpp
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
const int n = 8;

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

float** dot_product1(float A[][n], float B[][i], int k)
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

float** dot_product2(float A[][n], float B[][p], int k)
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

	//int n = 8;

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

	srand(18);

	float Pi[i][n];
	float Pi_t[n][i];

	for (int a = 0; a < i; a++)
	{
		for (int b = 0; b < n; b++)
		{
			int temp = rand() % 2;

			if (temp == 0)
			{
				Pi[a][b] = -1.0 / sqrt(i);
			}
			else
			{
				Pi[a][b] = 1.0 / sqrt(i);
			}
		}
	}

	for (int u = 0; u < i; u++)
	{
		for (int v = 0; v < n; v++)
		{
			cout << Pi[u][v] << " ";
		}
		cout << endl;
	}
	cout << endl;

	for (int a1 = 0; a1 < i; a1++)
	{
		for (int b1 = 0; b1 < n; b1++)
		{
			Pi_t[b1][a1] = Pi[a1][b1];
		}
	}

	for (int u1 = 0; u1 < n; u1++)
	{
		for (int v1 = 0; v1 < i; v1++)
		{
			cout << Pi_t[u1][v1] << " ";
		}
		cout << endl;
	}
	cout << endl;

	float** C_point = dot_product1(A, Pi_t, m);
	float** R_point = dot_product2(Pi, B, i);

	float C[m][i];
	float R[i][p];

	for (int x1 = 0; x1 < m; x1++)
	{
		for (int y1 = 0; y1 < i; y1++)
		{
			C[x1][y1] = C_point[x1][y1];
		}
	}

	for (int x2 = 0; x2 < i; x2++)
	{
		for (int y2 = 0; y2 < p; y2++)
		{
			R[x2][y2] = R_point[x2][y2];
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


