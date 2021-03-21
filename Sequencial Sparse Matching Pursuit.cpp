/*
 * Sequencial Sparse Matching Pursuit.cpp
 *
 *  Created on: 21 Mar 2021
 *      Author: Grant
 */

#include <iostream>
#include <math.h>
#include <queue>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

float findMedian(float a[], int n)
{
    // First we sort the array
    sort(a, a + n);

    // check for even case
    if (n % 2 != 0)
        return (float)a[n / 2];

    return (float)(a[(n - 1) / 2] + a[n / 2]) / 2.0;
}

float** pointer_median(float** A, int a1, int a2, int n)
{
	float** array = new float*[n];

	for (int a = 0; a < n; a++)
	{
	    array[a] = new float[a2];
	}

	float input[a1];

	for (int i = 0; i < a1; i++)
	{
		input[i] = A[i][0];
	}

	float median = findMedian(input, a1);

	cout << "Median is " << median << endl;

	for (int j = 0; j < n; j++)
	{
		array[j][0] = median;
	}

	return array;
}

float** refresh_vector(float** A, int a1, int a2)
{
	float** array = new float*[a1];

	for (int a = 0; a < a1; a++)
	{
	    array[a] = new float[a2];
	}

	for (int j = 0; j < a1; j++)
	{
		array[j][0] = A[j][0];
	}

	return array;
}


float** pointer_product(float** A, float** B, int a1, int a2, int b1, int b2)
{
	float** array = new float*[a1];

	for (int a = 0; a < a1; a++)
	{
	    array[a] = new float[b2];
	}

	for (int u = 0; u < a1; u++)
	{
		for (int v = 0; v < b2; v++)
		{
			array[u][v] = 0.0;
		}
	}

	for(int l = 0; l < a1; l++)
	{
		for(int j = 0; j < b2; j++)
		{
			for(int k = 0; k < a2; k++)
	        {
				array[l][j] += A[l][k] * B[k][j];
	        }
		}
	}

	for (int u1 = 0; u1 < a1; u1++)
	{
		for (int v1 = 0; v1 < b2; v1++)
		{
			cout << array[u1][v1] << " ";
		}
		cout << endl;
	}
	cout << endl;

	return array;
}

float** pointer_addition(float** A, float** B, int row, int column)
{
	float** array = new float*[row];

	for (int a = 0; a < row; a++)
	{
	    array[a] = new float[column];
	}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			array[i][j] = A[i][j] + B[i][j];
		}
	}

	return array;
}

float** pointer_subtraction(float** A, float** B, int row, int column)
{
	float** array = new float*[row];

	for (int a = 0; a < row; a++)
	{
	    array[a] = new float[column];
	}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			array[i][j] = A[i][j] - B[i][j];
			//array[i][j] = abs(A[i][j] - B[i][j]);
		}
	}

	return array;
}

int* kLargest(float nums[], int n, int k)
{
	vector<float> test (nums, nums + n );
	priority_queue<std::pair<float, int>> q;

	//for (int x : test)
	//        cout << x << " ";

	for (int i = 0; i < test.size(); ++i) {
	    q.push(std::pair<float, int>(test[i], i));
	}

	int index[k];
	int* index_pointer;

	for (int i = 0; i < k; ++i)
	{
	    int ki = q.top().second;
	    index[i] = ki;
	    std::cout << "index[" << i << "] = " << ki << std::endl;
	    q.pop();
	}

	index_pointer = index;
	return index_pointer;
}

float** threshold(float** A, int row, int k)
{
	float array[row];

	for (int i = 0; i < row; i++)
	{
		array[i] = A[i][0];
	}

	int* array1 = kLargest(array, row, k);

	float** array2 = new float*[row];

	for (int a = 0; a < row; a++)
	{
		array2[a] = new float[1];
	}

	for (int b = 0; b < row; b++)
	{
		bool in = false;
		for (int c = 0; c < k; c++)
		{
			if (b == array1[c])
			{
				in = true;
			}
		}

		if (in == true)
		{
			array2[b][0] = A[b][0];
		}
		else
		{
			array2[b][0] = 0.0;
		}
	}

	return array2;
}

int* random_array(int array[], int m, int d)
{
	//cout << "M is " << m << endl;

	//int array[d];

	for (int i = 0; i < d; i++)
	{
		array[i] = 100;
	}

	int choice = m;

	for (int j = 0; j < d; j++)
	{
		int temp = 100;
		bool exist = true;

		while (exist == true)
		{
			temp = rand() % choice;

			if (temp > m)
			{
				continue;
			}

			exist = false;

			for (int j1 = 0; j1 < d; j1++)
			{
				if (array[j1] == temp)
				{
					exist = true;
				}
			}
		}

		array[j] = temp;
	}

	for (int k = 0; k < d; k++)
	{
		cout << array[k] << " ";
	}
	cout << endl;

	//int* result = array;

	return array;
}

int main()
{
	srand(1);

	int n = 10;
	float signal[n] = {3, 5, 0, 0, 0, 0, 0, 8, 11, 1};

	float k = 0.5;

	int m = int(3 * k * log(float(n) / k));

	cout << m << endl;

	float** A = new float*[m];

	for (int w = 0; w < m; w++)
	{
		A[w] = new float[n];
	}

	int d = 3;

	int temp_array[d];

	for (int w1 = 0; w1 < n; w1++)
	{
		int* temp = random_array(temp_array, m, d);

		for (int t = 0; t < d; t++)
		{
			cout << temp[t] << " ";
		}
		cout << endl;


		for (int w2 = 0; w2 < m; w2++)
		{
			bool in = false;
			for (int w3 = 0; w3 < d; w3++)
			{
				if (temp[w3] == w2)
				{
					in = true;
				}
			}

			if (in == true)
			{
				A[w2][w1] = 1.0 / d;
			}
			else
			{
				A[w2][w1] = 0.0;
			}
		}
	}

	cout << "A" << endl;
	for (int w3 = 0; w3 < m; w3++)
	{
		for (int w4 = 0; w4 < n; w4++)
		{
			cout << A[w3][w4] << " ";
		}
		cout << endl;
	}

	float** b_signal = new float*[n];

	for (int w5 = 0; w5 < n; w5++)
	{
		b_signal[w5] = new float[1];
	}

	for (int w6 = 0; w6 < n; w6++)
	{
		b_signal[w6][0] = signal[w6];
	}

	float** z = pointer_product(A, b_signal, m, n, n, 1);

	float** x = new float*[n];

	for (int w8 = 0; w8 < n; w8++)
	{
		x[w8] = new float[1];
	}

	for (int w9 = 0; w9 < n; w9++)
	{
		x[w9][0] = 0.0;
	}

	int T = 5;
	int entries = d;
	int c = 2;
	int iteration = (c - 1)*entries;

	for (int u = 0; u < T; u++)
	{
		float** x_temp = x;

		for (int a = 0; a < iteration; a++)
		{
			float** result1 = pointer_product(A, x_temp, m, n, n, 1);
			float** result2 = pointer_subtraction(z, result1, m, 1);
			float** result3 = pointer_median(result2, m, 1, n);
			float** result4 = pointer_addition(x_temp, result3, n, 1);
			x_temp = refresh_vector(result4, n, 1);
		}
		x = threshold(x_temp, n, entries);
	}

	cout << "X" << endl;
	for (int v = 0; v < n; v++)
	{
		cout << x[v][0] << endl;
	}

	return 0;
}


