/*
 * Iterative Hard Thresholding.cpp
 *
 *  Created on: 20 Mar 2021
 *      Author: Grant
 */

#include <iostream>
#include <math.h>
#include <queue>
#include <vector>

using namespace std;

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

int* random_sum(int sum, int n, int number)
{
	//srand(1);

	int subSum = sum;
	int randomNumbers[n];

	for(int i = 0; i < n - 2; i++)
	{
	    randomNumbers[i] = rand() % int(subSum / 3); // get random number between 0 and subSum
	    subSum -= randomNumbers[i];
	}

	randomNumbers[n - 1] = subSum; // leftovers go to the last random number

	int randomNumbers1[n];
	int* random_array;

	if (number == 1)
	{
		int count = n - 1;
		for (int i = 0; i < n; i++)
		{
			randomNumbers1[i] = randomNumbers[count];
			count--;
		}

		random_array = randomNumbers1;
	}
	else
	{
		random_array = randomNumbers;
	}

	return random_array;
}

int main()
{
	srand(1);

	int n = 10;
	float signal[n] = {3, 5, 0, 0, 0, 0, 0, 8, 11, 1};

	float k = 0.5;

	int m = int(3 * k * log(float(n) / k));
	//int m = n - 1;

	cout << m << endl;

	float** A = new float*[m];

	for (int w = 0; w < m; w++)
	{
		A[w] = new float[n];
	}

	float** A_T = new float*[n];

	for (int w = 0; w < n; w++)
	{
		A_T[w] = new float[m];
	}

	for (int w1 = 0; w1 < n; w1++)
	{
		int number = 0;

		if ((w1*9) % 5 > 1)
		{
			number = 1;
		}

		int* temp = random_sum(100, m, number);

		for (int w2 = 0; w2 < m; w2++)
		{
			A[w2][w1] = sqrt(float(temp[w2]) / 100.0);
			A_T[w1][w2] = A[w2][w1];
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
	int entries = 3;
	for (int u = 0; u < T; u++)
	{
		float** result1 = pointer_product(A, x, m, n, n, 1);
		float** result2 = pointer_subtraction(z, result1, m, 1);
		float** result3 = pointer_product(A_T, result2, n, m, m, 1);
		float** result4 = pointer_addition(x, result3, n, 1);
		x = threshold(result4, n, entries);
	}

	cout << "X" << endl;
	for (int v = 0; v < n; v++)
	{
		cout << x[v][0] << endl;
	}

	return 0;
}


