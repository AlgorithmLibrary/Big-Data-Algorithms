/*
 * Set Disjointness Reduction.cpp
 *
 *  Created on: 21 Feb 2021
 *      Author: Grant
 */

#include <iostream>
#include <math.h>

using namespace std;

int main()
{
	int t = 4;
	int n = 6;

	int P[t][n] = {{0, 0, 0, 1, 0, 0},
				   {1, 0, 0, 1, 1, 0},
				   {0, 1, 0, 1, 0, 0},
				   {0, 0, 0, 1, 0, 0}};

	int total_length = t * n;

	int S[total_length];
	for (int a = 0; a < total_length; a++)
	{
		S[a] = 0;
	}

	int S_count = 0;
	for (int i = 0; i < t; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (P[i][j] == 1)
			{
				S[S_count] = j + 1;
				S_count++;
			}
		}
	}

	int k = 4;

	float f = 0.0;

	for (int u = 0; u < S_count; u++)
	{
		f = f + float(pow(S[u], k));
	}

	//cout << f << endl;

	f = pow(f, 1.0 / k);

	//cout << f << endl;

	if (f <= n)
	{
		cout << "All columns have weight 0 or 1." << endl;
	}
	else
	{
		cout << "Not all columns have weight 0 or 1." << endl;
	}

	int w = 4;

	if (f >= pow(w, k))
	{
		cout << "There is a column of weight " << w << endl;
	}
	else
	{
		cout << "There is not a column of weight " << w << endl;
	}

	return 0;
}


