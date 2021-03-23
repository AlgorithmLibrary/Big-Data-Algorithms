/*
 * Matrix Completion.cpp
 *
 *  Created on: 23 Mar 2021
 *      Author: Grant
 */

#include <iostream>
#include <math.h>
#include <queue>
#include <vector>
#include <SVD.h>

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

float** pointer_scale(float** A, int row, int column, float scale)
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
			array[i][j] = A[i][j] * scale;
		}
	}

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

int main()
{
	int row = 3;
	int column = 5;

	float A_input[row][row] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
	float alpha = 2;

	for (int a = 0; a < row; a++)
	{
		for (int b = 0; b < row; b++)
		{
			A_input[a][b] = A_input[a][b] * alpha;
		}
	}

	float** A = new float*[row];

	for (int c = 0; c < row; c++)
	{
		A[c] = new float[row];
	}

	for (int a1 = 0; a1 < row; a1++)
	{
		for (int b1 = 0; b1 < row; b1++)
		{
			A[a1][b1] = A_input[a1][b1];
		}
	}

	float M_input[row][column] = {{5, 1, 0, 0, 0}, {0, 2, 0, 3, 1}, {0, 0, 1, 0, 5}};

	float** M_Matrix = new float*[row];

	for (int c2 = 0; c2 < row; c2++)
	{
		M_Matrix[c2] = new float[column];
	}

	for (int a2 = 0; a2 < row; a2++)
	{
		for (int b2 = 0; b2 < column; b2++)
		{
			M_Matrix[a2][b2] = M_input[a2][b2];
		}
	}

	float** X = new float*[row];

	for (int c3 = 0; c3 < row; c3++)
	{
		X[c3] = new float[column];
	}

	for (int a3 = 0; a3 < row; a3++)
	{
		for (int b3 = 0; b3 < column; b3++)
		{
			X[a3][b3] = M_Matrix[a3][b3];
		}
	}

	float t = 1.0 / alpha;

	int total_count = 45;

	bool converge = false;

	while (converge == false)
	{
		float** result1 = pointer_product(A, X, row, row, row, column);
		float** result2 = pointer_subtraction(result1, M_Matrix, row, column);
		float** result3 = pointer_product(A, result2, row, row, row, column);
		float** result4 = pointer_scale(result3, row, column, t);
		float** Z = pointer_subtraction(X, result4, row, column);

		cout << "Z" << endl;
		for (int r1 = 0; r1 < row; r1++)
		{
			for (int r2 = 0; r2 < column; r2++)
			{
				cout << Z[r1][r2] << " ";
			}
			cout << endl;
		}

		typedef double Real_t;
		int n1=row, n2=column;

		// Create matrix
		Real_t* M =new Real_t[n1*n2];
		int count = 0;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				M[count] = Z[i][j];
				count++;
			}
		}

		int m = n2;
		int n = n1;
		//int m = n1;
		//int n = n2;
		int k = (m<n?m:n);
		Real_t* tU =new Real_t[m*k];
		Real_t* tS =new Real_t[k];
		Real_t* tVT=new Real_t[k*n];

		{ // Compute SVD
			int INFO=0;
		    char JOBU  = 'S';
		    char JOBVT = 'S';
		    int wssize = 3*(m<n?m:n)+(m>n?m:n);
		    int wssize1 = 5*(m<n?m:n);
		    wssize = (wssize>wssize1?wssize:wssize1);
		    Real_t* wsbuf = new Real_t[wssize];
		    svd(&JOBU, &JOBVT, &m, &n, &M[0], &m, &tS[0], &tU[0], &m, &tVT[0], &k, wsbuf, &wssize, &INFO);
		    delete[] wsbuf;
		}

		{ // Check Error
		    Real_t max_err=0;
		    for(size_t i0=0;i0<m;i0++)
		    for(size_t i1=0;i1<n;i1++){
		      Real_t E=M[i1*m+i0];
		      for(size_t i2=0;i2<k;i2++) E-=tU[i2*m+i0]*tS[i2]*tVT[i1*k+i2];
		      if(max_err<fabs(E)) max_err=fabs(E);
		    }
		    std::cout<<max_err<<'\n';
		}

		float** U = new float*[m];

		for (int w = 0; w < m; w++)
		{
			U[w] = new float[k];
		}

		cout << "U" << endl;
		int countr = 0;
		for (int w1 = 0; w1 < m; w1++)
		{
			for (int w2 = 0; w2 < k; w2++)
			{
				U[w1][w2] = tU[countr];
				cout << U[w1][w2] << " ";
				countr++;
			}
			cout << endl;
		}

		float** VT = new float*[k];

		for (int v = 0; v < k; v++)
		{
			VT[v] = new float[n];
		}

		cout << "VT" << endl;
		int counts = 0;
		for (int v1 = 0; v1 < k; v1++)
		{
			for (int v2 = 0; v2 < n; v2++)
			{
				VT[v1][v2] = tVT[counts];
				cout << VT[v1][v2] << " ";
				counts++;
			}
			cout << endl;
		}

		float** UV = pointer_product(U, VT, m, k, k, n);
		float largest = 0.0;

		for (int x = 0; x < m; x++)
		{
			for (int x1 = 0; x1 < n; x1++)
			{
				if (abs(UV[x][x1]) > largest)
				{
					largest = abs(UV[x][x1]);
				}
			}
		}

		float sigma[k];
		float mu = largest * sqrt(m*n/k);

		cout << "Mu is " << mu << endl;
		cout << "Sigma" << endl;

		for (int y = 0; y < k; y++)
		{
			sigma[y] = max(tS[y]-t*mu, 0.0);
			cout << sigma[y] << endl;
		}

		float** S = new float*[k];

		for (int y1 = 0; y1 < k; y1++)
		{
			S[y1] = new float[k];
		}

		for (int y2 = 0; y2 < k; y2++)
		{
			for (int y3 = 0; y3 < k; y3++)
			{
				if (y2 == y3)
				{
					S[y2][y3] = sigma[y2];
				}
				else
				{
					S[y2][y3] = 0.0;
				}
			}
		}


		float** result5 = pointer_product(S, VT, k, k, k, n);
		float** result6 = pointer_product(U, result5, m, k, k, n);

		for (int e1 = 0; e1 < row; e1++)
		{
			for (int e2 = 0; e2 < column; e2++)
			{
				X[e1][e2] = abs(result6[e2][e1]);
			}
		}

		converge = true;

		for (int g1 = 0; g1 < row; g1++)
		{
			for (int g2 = 0; g2 < column; g2++)
			{
				if (M_input[g1][g2] != 0)
				{
					if (abs(X[g1][g2] - M_input[g1][g2]) > 1.5)
					{
						converge = false;
					}
				}
			}
		}
	}

	for (int h1 = 0; h1 < row; h1++)
	{
		for (int h2 = 0; h2 < column; h2++)
		{
			cout << X[h1][h2] << " ";
		}
		cout << endl;
	}

	return 0;
}


