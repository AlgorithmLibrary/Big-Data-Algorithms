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

const int p = 8;
const int i = 5;
const int m = 3;
const int n = 8;

float** pointer_product(float** A, float** B, int row, int a2, int b1, int b2)
{
	float** array = new float*[1];

	for (int a = 0; a < 1; a++)
	{
	    array[a] = new float[b2];
	}

	for (int u = 0; u < 1; u++)
	{
		for (int v = 0; v < b2; v++)
		{
			array[u][v] = 0.0;
		}
	}

	//for(int l = 0; l < a1; l++)
	//{
		for(int j = 0; j < b2; j++)
		{
			for(int k = 0; k < a2; k++)
	        {
				array[0][j] += A[row][k] * B[k][j];
	        }
		}
	//}

	//for (int u1 = 0; u1 < a1; u1++)
	//{
		for (int v1 = 0; v1 < b2; v1++)
		{
			cout << array[0][v1] << " ";
		}
		cout << endl;
	//}
	cout << endl;

	return array;
}

float** pointer_product2(float** A, float** B, int a1, int a2, int b1, int b2)
{
	float** array = new float*[a1];

	for (int a = 0; a < 1; a++)
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

float** dot_product2(float A[][n], float B[][1], int k)
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
			for(int w = 0; w < n; w++)
	        {
				array[l][j] += A[l][w] * B[w][j];
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

	/*
	float A[m][n] = {{8, 2, 5, 1, 6, 2, 8, 9},
					 {3, 8, 9, 3, 1, 5, 6, 1},
					 {9, 1, 8, 4, 5, 8, 11, 5}};
	*/

	float A[n][p] = {{3, 2, 6, 1, 9, 1, 5, 9},
			         {1, 8, 5, 3, 1, 9, 1, 6},
					 {2, 5, 1, 9, 3, 8, 1, 3},
					 {5, 1, 6, 8, 3, 5, 6, 1},
					 {2, 3, 8, 1, 5, 1, 1, 3},
					 {1, 8, 3, 2, 1, 8, 2, 9},
					 {5, 1, 8, 1, 2, 3, 5, 1},
					 {2, 3, 6, 1, 5, 8, 5, 9}};

	float B[n][1] = {{85},
					 {94},
					 {89},
					 {85},
					 {56},
					 {95},
					 {58},
					 {99}};

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
		/*
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
		*/



		float temp2 = 0.0;

		float array2[p][1];

		for (int c = 0; c < p; c++)
		{
			//temp2 = temp2 + pow(B[a][c], 2);
			array2[c][0] = A[a][c];
		}

		float** r2 = dot_product3(G_T, array2, m);

		for (int c1 = 0; c1 < m; c1++)
		{
			temp2 = temp2 + pow(r2[c1][0], 2);
		}

		//temp1 = sqrt(temp1);

		//temp2 = sqrt(temp2);

		//summation[a] = temp1 + temp2;

		summation[a] = temp2;

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

	/*
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
	*/

	float** result2 = dot_product11(Pi, A, n);
	float r2[n][p];

	int num_values = 0;
	for (int k1 = 0; k1 < n; k1++)
	{
		if (result2[k1][0] != 0)
		{
			num_values++;
		}

		for (int j1 = 0; j1 < p; j1++)
		{
			cout << result2[k1][j1] << " ";
			r2[k1][j1] = result2[k1][j1];
		}
		cout << endl;
	}
	cout << endl;

	float** result3 = dot_product2(Pi, B, n);
	float r3[n][1];

	for (int k2 = 0; k2 < n; k2++)
	{
		for (int j2 = 0; j2 < 1; j2++)
		{
			cout << result3[k2][j2] << " ";
			r3[k2][j2] = result3[k2][j2];
		}
		cout << endl;
	}
	cout << endl;

	/*
	float** result3 = dot_product111(r1, r2, m);

	for (int k3 = 0; k3 < m; k3++)
	{
		for (int j3 = 0; j3 < p; j3++)
		{
			cout << result3[k3][j3] << " ";
		}
		cout << endl;
	}
	*/

	typedef float Real_t;
	int n1=num_values, n2=p;


	float b_m[num_values];


	// Create matrix
	Real_t* M =new Real_t[n1*n2];

	int counter = 0;
	for (int q = 0; q < n1; q++)
	{
		for (int q1 = 0; q1 < n2; q1++)
		{
			if (r2[q][q1] != 0)
			{
				M[counter] = r2[q][q1];
				b_m[q] = B[q][0];
				counter++;
			}
		}
	}

	float** b_matrix = new float*[num_values];

	for (int w5 = 0; w5 < num_values; w5++)
	{
		b_matrix[w5] = new float[1];
	}

	for (int w6 = 0; w6 < num_values; w6++)
	{
		b_matrix[w6][0] = b_m[w6];
	}

	/*
	for(size_t i=0;i<n1*n2;i++)
	{
		M[i]=rand()%15;
	}
	*/

	int m6 = n2;
	int n6 = n1;
	int k6 = (m6<n6?m6:n6);
	//int k6 = max(m6, n6);
	Real_t* tU =new Real_t[m6*k6];
	Real_t* tS =new Real_t[k6];
	Real_t* tVT=new Real_t[k6*n6];

	{ // Compute SVD
	    int INFO=0;
	    char JOBU  = 'S';
	    char JOBVT = 'S';
	    int wssize = 3*(m6<n6?m6:n6)+(m6>n6?m6:n6);
	    int wssize1 = 5*(m6<n6?m6:n6);
	    wssize = (wssize>wssize1?wssize:wssize1);
	    Real_t* wsbuf = new Real_t[wssize];
	    svd(&JOBU, &JOBVT, &m6, &n6, &M[0], &m6, &tS[0], &tU[0], &m6, &tVT[0], &k6, wsbuf, &wssize, &INFO);
	    delete[] wsbuf;
	}

	{ // Check Error
	    Real_t max_err=0;
	    for(size_t i0=0;i0<m6;i0++)
	    for(size_t i1=0;i1<n6;i1++){
	      Real_t E=M[i1*m6+i0];
	      for(size_t i2=0;i2<k6;i2++) E-=tU[i2*m6+i0]*tS[i2]*tVT[i1*k6+i2];
	      if(max_err<fabs(E)) max_err=fabs(E);
	    }
	    std::cout<<max_err<<'\n';
	}
	cout << endl;

	//float u_matrix[m6][k6];

	float** u_matrix = new float*[m6];

	for (int w = 0; w < m6; w++)
	{
		u_matrix[w] = new float[k6];
	}

	int counter1 = 0;
	for (int c1 = 0; c1 < m6; c1++)
	{
		for (int c2 = 0; c2 < k6; c2++)
		{
			cout << tU[counter1] << " ";
			u_matrix[c1][c2] = tU[counter1];
			counter1++;
		}
		cout << endl;
	}
	cout << endl;

	float t_matrix[k6];
	int counter2 = 0;
	for (int c3 = 0; c3 < k6; c3++)
	{
		cout << tS[counter2] << endl;
		if (abs(tS[counter2]) < 0.01)
		{
			b_matrix[c3][0] = 0.0;
		}
		else
		{
			b_matrix[c3][0] = b_matrix[c3][0] / tS[counter2];
		}
		counter2++;
	}
	cout << endl;


	float** v_matrix = new float*[k6];

	for (int w1 = 0; w1 < k6; w1++)
	{
		v_matrix[w1] = new float[n6];
	}

	int counter3 = 0;
	for (int c4 = 0; c4 < k6; c4++)
	{
		for (int c5 = 0; c5 < n6; c5++)
		{
			cout << tVT[counter3] << " ";
			v_matrix[c4][c5] = tVT[counter3];
			counter3++;
		}
		cout << endl;
	}
	cout << endl;

	//int row = 5;

	//float** result8 = pointer_product(u_matrix, v_matrix, row, k6, k6, n6);
	//float** result9 = pointer_product2(result8, b_matrix, 1, n6, num_values, 1);

	float x[n];
	for (int row = 0; row < n; row++)
	{
		float** result8 = pointer_product(u_matrix, v_matrix, row, k6, k6, n6);
		float** result9 = pointer_product2(result8, b_matrix, 1, n6, num_values, 1);
		x[row] = result9[0][0];
	}

	for (int row1 = 0; row1 < n; row1++)
	{
		cout << x[row1] << endl;
	}







	for (int end1 = 0; end1 < n; end1++)
	{
		delete[] result2[end1];
	}
	delete[] result2;

	for (int end2 = 0; end2 < n; end2++)
	{
		delete[] result3[end2];
	}
	delete[] result3;

	for (int end3 = 0; end3 < num_values; end3++)
	{
		delete[] b_matrix[end3];
	}
	delete[] b_matrix;

	for (int end4 = 0; end4 < m6; end4++)
	{
		delete[] u_matrix[end4];
	}
	delete[] u_matrix;

	for (int end5 = 0; end5 < k6; end5++)
	{
		delete[] v_matrix[end5];
	}
	delete[] v_matrix;

	delete[] tU;
	delete[] tS;
	delete[] tVT;
	delete[] M;

	return 0;
}


