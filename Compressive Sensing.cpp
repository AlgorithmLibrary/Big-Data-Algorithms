/*
 * Compressive Sensing.cpp
 *
 *  Created on: 18 Mar 2021
 *      Author: Grant
 */

#include <iostream>
#include <math.h>

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

float** calculate_simplex(float** simplex_tableau, int rows, int columns)
{
	float** tableau = 0;
	tableau = new float*[rows];

	for (int h = 0; h < rows; h++)
	{
		tableau[h] = new float[columns];

		for (int w = 0; w < columns; w++)
	    {
			tableau[h][w] = simplex_tableau[h][w];
	    }
	}

	bool optimal = false;

	while (optimal == false)
	{
		int bottom_row = rows - 1;

		int pivot_column = 0;
		float value = tableau[bottom_row][0];
		for (int i=0; i < columns; i++)
		{
			if (tableau[bottom_row][i] < value)
			{
				pivot_column = i;
				value = tableau[bottom_row][i];
			}
		}

		cout << "Value " << value << endl;

		if (value >= 0.0)
		{
			optimal = true;
			continue;
		}

		int indicator = 0;
		float indicator_value;
		if (tableau[0][columns - 1] / tableau[0][pivot_column] > 0)
		{
			indicator_value = tableau[0][columns - 1] / tableau[0][pivot_column];
		}
		else
		{
			indicator_value = 100;
		}

		for (int j = 0; j < rows - 1; j++)
		{
			if (tableau[j][columns - 1] / tableau[j][pivot_column] < indicator_value)
			{
				if (tableau[j][columns - 1] / tableau[j][pivot_column] > 0)
				{
					indicator = j;
					indicator_value = tableau[j][columns - 1] / tableau[j][pivot_column];
				}
			}
		}

		float pivot_variable = tableau[indicator][pivot_column];

		for (int a = 0; a < columns; a++)
		{
			tableau[indicator][a] = tableau[indicator][a] / pivot_variable;
		}

		for (int e = 0; e < rows; e++)
		{
			if (e == indicator)
			{
				continue;
			}
			else
			{
				for (int g = 0; g < columns; g++)
				{
					if (g == pivot_column)
					{
						continue;
					}
					else
					{
						float negative_pivot_column_value = -tableau[e][pivot_column];
						float pivot_row_value = tableau[indicator][g];
						float old_value = tableau[e][g];

						float new_value = negative_pivot_column_value * pivot_row_value + old_value;
						tableau[e][g] = new_value;
					}
				}
			}
		}

		for (int b = 0; b < rows; b++)
		{
			if (b == indicator)
			{
				continue;
			}
			else
			{
				tableau[b][pivot_column] = 0;
			}
		}
	}

	return tableau;
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

	for (int w1 = 0; w1 < n; w1++)
	{
		//srand(rand() % 100);
		//int number = rand() % 100;

		int number = 0;
		//if (w1 % 2 == 1)
		if ((w1*9) % 5 > 1)
		{
			number = 1;
		}

		int* temp = random_sum(100, m, number);

		for (int w2 = 0; w2 < m; w2++)
		{
			A[w2][w1] = sqrt(float(temp[w2]) / 100.0);
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

	int r = m + 1;
	int c = n + m + 2;

	float s_tableau[r][c];

	for (int w8 = 0; w8 < r; w8++)
	{
		for (int w9 = 0; w9 < c; w9++)
		{
			if (w9 < n)
			{
				if (w8 < m)
				{
					s_tableau[w8][w9] = A[w8][w9];
				}
				else
				{
					s_tableau[w8][w9] = -1.0;
				}
			}

			if (w9 >= n && w9 < c - 1)
			{
				if (w8 == w9 - n)
				{
					s_tableau[w8][w9] = 1.0;
				}
				else
				{
					s_tableau[w8][w9] = 0.0;
				}
			}

			if (w9 == c - 1)
			{
				if (w8 < r - 1)
				{
					s_tableau[w8][w9] = z[w8][0];
				}
				else
				{
					s_tableau[w8][w9] = 0.0;
				}
			}
		}
	}

	for (int w11 = 0; w11 < r; w11++)
	{
		for (int w12 = 0; w12 < c; w12++)
		{
			cout << s_tableau[w11][w12] << " ";
		}
		cout << endl;
	}


	/*
	float simplex_tableau[3][7] = {{1, 3, 2, 1, 0, 0, 10}, {1, 5, 1, 0, 1, 0, 8},
				                   {-8, -10, -7, 0, 0, 1, 0}};

	int rows = 3;
	int columns = 7;
	*/

	int rows = r;
	int columns = c;

	float** tableau = new float*[rows];

	for (int h = 0; h < rows; h++)
	{
		tableau[h] = new float[columns];
	}

	for (int a = 0; a < rows; a++)
	{
		for (int b = 0; b < columns; b++)
		{
			//tableau[a][b] = simplex_tableau[a][b];
			tableau[a][b] = s_tableau[a][b];
		}
	}

	float** result = calculate_simplex(tableau, rows, columns);

	cout << endl;
	cout << "Result" << endl;
	for (int u = 0; u < rows; u++)
	{
		for (int v = 0; v < columns; v++)
		{
			cout << result[u][v] << " ";
		}
		cout << endl;
	}

	for (int a = 0; a < rows; a++)
	{
		for (int b = 0; b < columns; b++)
		{
			if (result[a][b] == 1)
			{
				bool basic = true;
				int basic_column = b;
				for (int c = 0; c < rows; c++)
				{
					if (c == a)
					{
						continue;
					}
					else
					{
						if (result[c][b] != 0)
						{
							basic = false;
						}
					}
				}

				if (basic == true)
				{
					cout << "Basic Column for row " << a + 1 << " is column " << basic_column + 1 << endl;
				}
			}
		}
	}

	for (int v = 0; v < rows; v++)
	{
		delete[] tableau[v];
	}
	delete tableau;

	cout << "HERE";

	return 0;
}


