/*
 * Subspace Embedding Sampling.cpp
 *
 *  Created on: 2 Mar 2021
 *      Author: Grant
 */

#include <iostream>
#include <math.h>
#include <random>
#include <bitset>

using namespace std;

const int p = 8;
const int i = 3;
const int m = 3;
const int n = 8;

float** dot_product1(float A[][n], float B[][n], int k)
{
	float** array = new float*[k];

	for (int a = 0; a < k; a++)
	{
	    array[a] = new float[n];
	}

	for (int u = 0; u < k; u++)
	{
		for (int v = 0; v < n; v++)
		{
			array[u][v] = 0.0;
		}
	}

	for(int l = 0; l < k; l++)
	{
		for(int j = 0; j < n; j++)
		{
			for(int k = 0; k < i; k++)
	        {
				array[l][j] += A[l][k] * B[k][j];
	        }
		}
	}

	for (int u1 = 0; u1 < k; u1++)
	{
		for (int v1 = 0; v1 < n; v1++)
		{
			cout << array[u1][v1] << " ";
		}
		cout << endl;
	}
	cout << endl;

	return array;
}

float** dot_product11(float A[][n], float B[][p], int k)
{
	float** array = new float*[k];

	for (int a = 0; a < k; a++)
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

float** dot_product111(float A[][n], float B[][p], int k)
{
	float** array = new float*[k];

	for (int a = 0; a < k; a++)
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

float** dot_product2(float A[][m], float B[][1], int k)
{
	float** array = new float*[k];

	for (int a = 0; a < k; a++)
	{
	    array[a] = new float[1];
	}

	for (int u = 0; u < k; u++)
	{
		for (int v = 0; v < 1; v++)
		{
			array[u][v] = 0.0;
		}
	}

	for(int l = 0; l < k; l++)
	{
		for(int j = 0; j < 1; j++)
		{
			for(int k = 0; k < i; k++)
	        {
				array[l][j] += A[l][k] * B[k][j];
	        }
		}
	}

	for (int u1 = 0; u1 < k; u1++)
	{
		for (int v1 = 0; v1 < 1; v1++)
		{
			cout << array[u1][v1] << " ";
		}
		cout << endl;
	}
	cout << endl;

	return array;
}

float** dot_product3(float A[][p], float B[][1], int k)
{
	float** array = new float*[k];

	for (int a = 0; a < k; a++)
	{
	    array[a] = new float[1];
	}

	for (int u = 0; u < k; u++)
	{
		for (int v = 0; v < 1; v++)
		{
			array[u][v] = 0.0;
		}
	}

	for(int l = 0; l < k; l++)
	{
		for(int j = 0; j < 1; j++)
		{
			for(int k = 0; k < i; k++)
	        {
				array[l][j] += A[l][k] * B[k][j];
	        }
		}
	}

	for (int u1 = 0; u1 < k; u1++)
	{
		for (int v1 = 0; v1 < 1; v1++)
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
	srand(18);

	float epsilon = 0.6;
	float delta = 0.9;
	//int m = 3;

	//int n = 8;

	float A[m][n] = {{8, 2, 5, 1, 6, 2, 8, 9},
					 {3, 8, 9, 3, 1, 5, 6, 1},
					 {9, 1, 8, 4, 5, 8, 11, 5}};

	float B[n][p] = {{3, 2, 6, 1, 9, 1, 5, 9},
			         {1, 8, 5, 3, 1, 9, 1, 6},
					 {2, 5, 1, 9, 3, 8, 1, 3},
					 {5, 1, 6, 8, 3, 5, 6, 1},
					 {2, 3, 8, 1, 5, 1, 1, 3},
					 {1, 8, 3, 2, 1, 8, 2, 9},
					 {5, 1, 8, 1, 2, 3, 5, 1},
					 {2, 3, 6, 1, 5, 8, 5, 9}};

	float G[p][m];
	float G_T[m][p];

	default_random_engine generator;
	normal_distribution<float> distribution(0.0, 1.0 / (log(n) / pow(epsilon, 2)));

	float values[p * m];

	for (int h = 0; h < p * m; h++)
	{
		values[h] = rand() % 2;
	}

	int count = 0;
	for (int l = 0; l < p; l++)
	{
		for (int l1 = 0; l1 < m; l1++)
		{
			if (values[count] == 0)
			{
				G[l][l1] = -1.0 / sqrt(i);
				count++;
			}
			else
			{
				G[l][l1] = 1.0 / sqrt(i);
				count++;
			}
			//G[l][l1] = distribution(generator);
			G_T[l1][l] = G[l][l1];
		}
	}

	for (int l2 = 0; l2 < p; l2++)
	{
		for (int l3 = 0; l3 < m; l3++)
		{
			cout << G[l2][l3] << " ";
		}
		cout << endl;
	}
	cout << endl;

	float summation[n];

	float total = 0.0;
	float d = float(i);

	for (int a = 0; a < n; a++)
	{
		float temp1 = 0.0;

		float array1[m][1];

		for (int b = 0; b < m; b++)
		{
			//temp1 = temp1 + pow(A[b][a], 2);
			array1[b][0] = A[b][a];
		}

		float** r1 = dot_product2(G, array1, p);

		for (int b1 = 0; b1 < p; b1++)
		{
			temp1 = temp1 + pow(r1[b1][0], 2);
		}

		//temp1 = sqrt(temp1);




		float temp2 = 0.0;

		float array2[p][1];

		for (int c = 0; c < p; c++)
		{
			//temp2 = temp2 + pow(B[a][c], 2);
			array2[c][0] = B[a][c];
		}

		float** r2 = dot_product3(G_T, array2, m);

		for (int c1 = 0; c1 < m; c1++)
		{
			temp2 = temp2 + pow(r2[c1][0], 2);
		}

		//temp1 = sqrt(temp1);

		//temp2 = sqrt(temp2);

		summation[a] = temp1 + temp2;

		total = total + summation[a];
	}

	cout << "Summation" << endl;
	for (int a1 = 0; a1 < n; a1++)
	{
		cout << summation[a1] << " ";
	}
	cout << endl;
	cout << "Total " << total << endl;
	cout << endl;


	float probabilities[n];
	float cumulative[n];

	cout << "Probabilities" << endl;
	for (int e1 = 0; e1 < n; e1++)
	{
		float temp1 = 1.0;
		float temp2 = (log(d/delta)) * ((summation[e1] / total) * d) / pow(epsilon, 2);
		//float temp2 = (log(i/delta)) * (summation[e1]);
		cout << temp2 << endl;
		probabilities[e1] = min(temp1, temp2);
	}
	cout << endl;

	for (int e2 = 0; e2 < n; e2++)
	{
		cout << probabilities[e2] << " ";
	}
	cout << endl;
	cout << endl;

	int set_of_i[n];

	for (int u = 0; u < n; u++)
	{
		set_of_i[u] = 0;
	}

	//srand(11);

	//int t = rand() % 100;
	//float tt = float(t) / 100.0;

	for (int r1 = 0; r1 < n; r1++)
	{
		int t = rand() % 100;
		float tt = float(t) / 100.0;

		if (probabilities[r1] > tt)
		{
			set_of_i[r1] = 1;
		}
	}

	cout << "Set of i" << endl;
	for (int s = 0; s < n; s++)
	{
		cout << set_of_i[s] << " ";
	}
	cout << endl;
	cout << endl;

	float Pi[n][n];

	for (int y = 0; y < n; y++)
	{
		for (int y1 = 0; y1 < n; y1++)
		{
			if (y == y1)
			{
				if (set_of_i[y] == 1)
				{
					Pi[y][y] = 1.0;
				}
				else
				{
					Pi[y][y] = 0.0;
				}
			}
			else
			{
				Pi[y][y1] = 0.0;
			}
		}
	}

	for (int x = 0; x < n; x++)
	{
		for (int x1 = 0; x1 < n; x1++)
		{
			cout << Pi[x][x1] << " ";
		}
		cout << endl;
	}
	cout << endl;

	float** result1 = dot_product1(A, Pi, m);
	float r1[m][n];

	for (int k = 0; k < m; k++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << result1[k][j] << " ";
			r1[k][j] = result1[k][j];
		}
		cout << endl;
	}
	cout << endl;

	float** result2 = dot_product1(Pi, B, n);
	float r2[n][p];

	for (int k1 = 0; k1 < n; k1++)
	{
		for (int j1 = 0; j1 < p; j1++)
		{
			cout << result2[k1][j1] << " ";
			r2[k1][j1] = result2[k1][j1];
		}
		cout << endl;
	}

	float** result3 = dot_product111(r1, r2, m);

	for (int k3 = 0; k3 < m; k3++)
	{
		for (int j3 = 0; j3 < p; j3++)
		{
			cout << result3[k3][j3] << " ";
		}
		cout << endl;
	}

	return 0;
}


