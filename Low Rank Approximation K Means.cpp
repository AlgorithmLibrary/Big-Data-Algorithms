/*
 * Subspace Embedding Linear Least Squares.cpp
 *
 *  Created on: 6 Mar 2021
 *      Author: Grant
 */

#include <iostream>
#include <math.h>
#include <random>
#include <bitset>
#include <SVD.h>

using namespace std;

const int r = 8;
const int c = 3;

float** pointer_product_variable(float** A, float** B, int a1, int a2, int b1, int b2)
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

int main()
{
	srand(18);

	int k_rank = 3;
	float epsilon = 0.8;

	float A[r][c] = {{3, 2, 6},
			         {1, 8, 5},
					 {2, 5, 1},
					 {5, 1, 6},
					 {2, 3, 8},
					 {1, 8, 3},
					 {5, 1, 8},
					 {2, 3, 6}};

	float sum[r];
	float total = 0.0;

	for (int x = 0; x < r; x++)
	{
		float temp_sum = 0.0;
		for (int y = 0; y < c; y++)
		{
			temp_sum = temp_sum + pow(A[x][y], 2);
		}
		sum[x] = sqrt(temp_sum);
		total = total + sum[x];
	}

	float probability[r];
	float cumulative[r];

	for (int x1 = 0; x1 < r; x1++)
	{
		probability[x1] = sum[x1] / total;
		if (x1 == 0)
		{
			cumulative[x1] = probability[x1];
		}
		else
		{
			cumulative[x1] = cumulative[x1 - 1] +  probability[x1];
		}
		//cout << cumulative[x1] << endl;
	}

	int rank_selection[k_rank];

	for (int k1 = 0; k1 < k_rank; k1++)
	{
		rank_selection[k1] = 100;
	}

	for (int x2 = 0; x2 < k_rank; x2++)
	{
		bool assigned = false;

		while (assigned == false)
		{
		int temp = rand() % 100;
		float temp_t = float(temp) / 100.0;

		for (int y1 = 0; y1 < r; y1++)
		{
			if (temp_t < cumulative[y1])
			{
				bool exist = false;

				for (int z1 = 0; z1 < k_rank; z1++)
				{
					if (y1 == rank_selection[z1])
					{
						exist = true;
					}
				}

				if (exist == false)
				{
					rank_selection[x2] = y1;
					assigned = true;
					break;
				}
			}
		}
		}
	}

	for (int x3 = 0; x3 < k_rank; x3++)
	{
		cout << rank_selection[x3] << endl;
	}

	float** A_Matrix = new float*[r];

	for (int i1 = 0; i1 < r; i1++)
	{
		A_Matrix[i1] = new float[c];
	}

	for (int a1 = 0; a1 < r; a1++)
	{
		for (int b1 = 0; b1 < c; b1++)
		{
			A_Matrix[a1][b1] = A[a1][b1];
		}
	}

	int d = int(float(k_rank) / pow(epsilon, 2));

	float** Pi_T = new float*[c];

	for (int i2 = 0; i2 < c; i2++)
	{
		Pi_T[i2] = new float[d];
	}

	for (int a2 = 0; a2 < c; a2++)
	{
		for (int b2 = 0; b2 < d; b2++)
		{
			int sign = rand() % 2;

			if (sign == 0)
			{
				Pi_T[a2][b2] = -1.0 / sqrt(d);
			}
			else
			{
				Pi_T[a2][b2] = 1.0 / sqrt(d);
			}
		}
	}

	float** A_Pi_T_Matrix = pointer_product_variable(A_Matrix, Pi_T, r, c, c, d);

	typedef double Real_t;
	int n1=r, n2=d;

	// Create matrix
	Real_t* M =new Real_t[n1*n2];

	int counter = 0;
	for (int a4 = 0; a4 < n1; a4++)
	{
		for (int b4 = 0; b4 < n2; b4++)
		{
			M[counter] = A_Pi_T_Matrix[a4][b4];
			counter++;
		}
	}

	int m = n2;
	int n = n1;
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

	int counter1 = 0;
	for (int a5 = 0; a5 < m; a5++)
	{
		for (int b5 = 0; b5 < k; b5++)
		{
			cout << tU[counter1] << " ";
			counter1++;
		}
		cout << endl;
	}

	float** U_Matrix = new float*[m];

	for (int i3 = 0; i3 < m; i3++)
	{
		U_Matrix[i3] = new float[k];
	}

	int counter2 = 0;
	for (int a6 = 0; a6 < m; a6++)
	{
		for (int b6 = 0; b6 < k; b6++)
		{
			U_Matrix[a6][b6] = tU[counter2];
			counter2++;
		}
	}

	float** U_K_Matrix = new float*[k_rank];

	for (int i4 = 0; i4 < k_rank; i4++)
	{
		U_K_Matrix[i4] = new float[k];
	}

	float** U_T_K_Matrix = new float*[k];

	for (int i4 = 0; i4 < k; i4++)
	{
		U_T_K_Matrix[i4] = new float[k_rank];
	}

	for (int a8 = 0; a8 < k_rank; a8++)
	{
		for (int b8 = 0; b8 < k; b8++)
		{
			U_K_Matrix[a8][b8] = U_Matrix[a8][b8];
			U_T_K_Matrix[b8][a8] = U_Matrix[a8][b8];
		}
	}

	float** A_K_Matrix = new float*[k_rank];

	for (int i5 = 0; i5 < k_rank; i5++)
	{
		A_K_Matrix[i5] = new float[c];
	}

	for (int a9 = 0; a9 < k_rank; a9++)
	{
		int row = rank_selection[a9];

		for (int b9 = 0; b9 < c; b9++)
		{
			A_K_Matrix[a9][b9] = A_Matrix[row][b9];
		}
	}

	float** U_A_K = pointer_product_variable(U_T_K_Matrix, A_K_Matrix, k, k_rank, k_rank, c);

	float** U_U_A_K = pointer_product_variable(U_K_Matrix, U_A_K, k_rank, k, k, c);

	delete[] tU;
	delete[] tS;
	delete[] tVT;
	delete[] M;

	for (int e1 = 0; e1 < r; e1++)
	{
		delete[] A_Matrix[e1];
	}
	delete[] A_Matrix;

	for (int e2 = 0; e2 < c; e2++)
	{
		delete[] Pi_T[e2];
	}
	delete[] Pi_T;

	for (int e3 = 0; e3 < r; e3++)
	{
		delete[] A_Pi_T_Matrix[e3];
	}
	delete[] A_Pi_T_Matrix;

	for (int e4 = 0; e4 < m; e4++)
	{
		delete[] U_Matrix[e4];
	}
	delete[] U_Matrix;

	for (int e5 = 0; e5 < k; e5++)
	{
		delete[] U_T_K_Matrix[e5];
	}
	delete[] U_T_K_Matrix;

	for (int e6 = 0; e6 < k_rank; e6++)
	{
		delete[] A_K_Matrix[e6];
	}
	delete[] A_K_Matrix;

	for (int e8 = 0; e8 < k_rank; e8++)
	{
		delete[] U_K_Matrix[e8];
	}
	delete[] U_K_Matrix;

	//cout << "HERE" << endl;

	return 0;
}


