/*
 * Faster Johnson Lindenstrauss.cpp
 *
 *  Created on: 25 Feb 2021
 *      Author: Grant
 */

#include <iostream>
#include <math.h>
#include <random>
#include <bitset>

using namespace std;

const int n = 5;
const int d = 5;

float** dot_product_first(float R[][d], float x[][d], int k)
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

float** dot_product_second(float R[][d], int x[][n], int k)
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
	int x[d][n] = {{1, 2, 5, 1, 3}, {3, 8, 9, 11, 1}, {3, 1, 8, 2, 3}, {3, 1, 8, 6, 1}, {5, 1, 2, 8, 9}};

	float e = 0.95;

	int k = int(24.0 * log10(d) / (3 * pow(e, 2) + 2 * pow(e, 3)));

	//cout << k << endl;

	srand(5);

	float D[d][d];
	float H[d][d];
	float P[k][d];

	for (int i = 0; i < d; i++)
	{
		for (int j = 0; j < d ; j++)
		{
			if (i == j)
			{
				int sign = rand() % 2;

				if (sign == 0)
				{
					D[i][j] = -1.0;
				}
				else
				{
					D[i][j] = 1.0;
				}
			}
			else
			{
				D[i][j] = 0.0;
			}
		}
	}

	for (int k = 0; k < d; k++)
	{
		for (int l = 0; l < d; l++)
		{
			cout << D[k][l] << " ";
		}
		cout << endl;
	}
	cout << endl;

	for (int i1 = 0; i1 < d; i1++)
	{
		for (int j1 = 0; j1 < d ; j1++)
		{
			//H[i1][j1] = sqrt(d);

			int first = i1;
			int second = j1;

			int first_array[32];
			bitset<32> first_bit = first;
			for(int a=0, b=31; a < 32; a++,b--)
			{
			     first_array[a] = first_bit[b];
			}

			int second_array[32];
			bitset<32> second_bit = second;
			for(int a1=0, b1=31; a1 < 32; a1++,b1--)
			{
				second_array[a1] = second_bit[b1];
			}

			int sum = 0;
			for (int a3 = 0; a3 < 32; a3++)
			{
				sum = sum + first_array[a3] * second_array[a3];
			}

			float p = pow(-1, sum);

			H[i1][j1] = sqrt(d) * p;
			//H[i1][j1] = p;
		}
	}

	for (int k1 = 0; k1 < d; k1++)
	{
		for (int l1 = 0; l1 < d; l1++)
		{
			cout << H[k1][l1] << " ";
		}
		cout << endl;
	}
	cout << endl;

	float epsilon = e;
	float p_small = 1;

	float q_first = pow(epsilon, p_small - 2) * pow(log(n), p_small) / d;
	float q_second = 1.0;
	float q = min(q_first, q_second);

	default_random_engine generator;
	normal_distribution<float> distribution(0.0, sqrt(1.0/q));

	for (int i2 = 0; i2 < k; i2++)
	{
		for (int j2 = 0; j2 < d ; j2++)
		{
			int random = rand() % 100;
			float ran = float(random) / 100.0;

			if (ran > q)
			{
				P[i2][j2] = 0.0;
			}
			else
			{
				P[i2][j2] = distribution(generator);
			}
		}
	}

	cout << "P" << endl;
	for (int k2 = 0; k2 < k; k2++)
	{
		for (int l2 = 0; l2 < d; l2++)
		{
			cout << P[k2][l2] << " ";
		}
		cout << endl;
	}
	cout << endl;

	float** result1 = dot_product_first(H, D, d);

	float HD[d][d];

	for (int u = 0; u < d; u++)
	{
		for (int v = 0; v < d; v++)
		{
			HD[u][v] = result1[u][v];
		}
	}

	float** result2 = dot_product_first(P, HD, k);

	float Pi[k][d];

	for (int u1 = 0; u1 < k; u1++)
	{
		for (int v1 = 0; v1 < d; v1++)
		{
			Pi[u1][v1] = result2[u1][v1];
		}
	}

	float** result3 = dot_product_second(Pi, x, k);

	for (int k3 = 0; k3 < k; k3++)
	{
		for (int l3 = 0; l3 < d; l3++)
		{
			cout << result3[k3][l3] << " ";
		}
		cout << endl;
	}

	return 0;
}


