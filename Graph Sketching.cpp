/*
 * Graph Sketching.cpp
 *
 *  Created on: 15 Feb 2021
 *      Author: Grant
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <math.h>
#include <random>

using namespace std;

int combination_matrix[45][2];
int AG[10][45];
int counting = 0;

int S[10];

//int S_Count[10];
//int S[10][10];
//int S_Sum[10];

int edges[7][2] = {{0, 1}, {1, 2}, {2, 3}, {4, 5}, {5, 6}, {7, 8}, {7, 9}};

void comb(int N, int K)
{
    std::string bitmask(K, 1); // K leading 1's
    bitmask.resize(N, 0); // N-K trailing 0's

    // print integers and permute bitmask
    do {
    	int vertex = 0;
        for (int i = 0; i < N; ++i) // [0..N-1] integers
        {
            if (bitmask[i])
            {
            	//cout << " " << i;
            	combination_matrix[counting][vertex] = i;
            	cout << " " << combination_matrix[counting][vertex];
            	vertex++;
            }
        }
        counting++;
        cout << endl;
    } while (prev_permutation(bitmask.begin(), bitmask.end()));
}

int checkl0(int selection, int number_of_combinations)
{
	int count = 0;

	for (int i = 0; i < number_of_combinations; i++)
	{
		if (AG[selection][i] != 0)
		{
			count++;
		}
	}
	return count;
}

bool summation(int group[], int n, int number_of_vertices, int number_of_combinations)
{
	int result[number_of_combinations];

	for (int i = 0; i < number_of_combinations; i++)
	{
		result[i] = 0;
	}

	int max = 0;

	for (int u = 0; u < n; u++)
	{
		if (checkl0(group[u], number_of_combinations) > max)
		{
			max = checkl0(group[u], number_of_combinations);
		}
	}

	//cout << "Max is " << max << endl;

	for (int v = 0; v < n; v++)
	{
		for (int w = 0; w < 45; w++)
		{
			result[w] = result[w] + AG[group[v]][w];
		}
	}

	int count = 0;

	for (int j = 0; j < number_of_combinations; j++)
	{
		if (result[j] != 0)
		{
			count++;
		}
	}

	if (count <= max)
	{
		int set_group = S[group[0]];

		for (int a = 0; a < n; a++)
		{
			S[group[a]] = set_group;
		}

		return true;
	}
	else
	{
		return false;
	}
}

int main()
{
	srand(5);

	int number_of_vertices = 10;
	int number_of_combinations = 45;

    comb(10, 2);

    cout << "Total number of combinations is " << counting << endl;

    for (int e = 0; e < 7; e++)
    {
    	int first = edges[e][0];
    	int second = edges[e][1];

    	for (int j = 0; j < number_of_combinations; j++)
    	{
    		if (combination_matrix[j][0] == first && combination_matrix[j][1] == second)
    		{
    			AG[first][j] = 1;
    			AG[second][j] = -1;
    		}

    		if (combination_matrix[j][0] == second && combination_matrix[j][1] == first)
    		{
    			AG[first][j] = -1;
    			AG[second][j] = 1;
    		}
    	}
    }

    for (int i1 = 0; i1 < number_of_vertices; i1++)
    {
        for (int j1 = 0; j1 < number_of_combinations; j1++)
        {
        	cout << AG[i1][j1] << " ";
        	/*
        	if (AG[i1][j1] == 1 || AG[i1][j1] == -1)
        	{
        		cout << combination_matrix[j1][0] << " " << combination_matrix[j1][1] << endl;
        	}
        	*/
        }
        cout << endl;
    }

    for (int v = 0; v < number_of_vertices; v++)
    {
    	S[v] = v;
    }

    int attempts = 35;

    bool complete = false;

    while (complete == false)
    {
    	complete = true;

    	//int first = rand() % number_of_vertices;

    	for (int i = 0; i < attempts; i++)
    	{
    		int first = rand() % number_of_vertices;

    		int second = rand() % number_of_vertices;

    		while (S[first] == S[second] || first == second)
    		{
    			second = rand() % number_of_vertices;
    			/*
    			while (first == second)
    			{
    				second = rand() % number_of_vertices;
    			}
    			*/
    		}

    		int group[2] = {first, second};

    		bool testing = summation(group, 2, number_of_vertices, number_of_combinations);

    		if (testing == true)
    		{
    			//cout << "HERE " << first << " " << second << endl;
    			complete = false;
    			break;
    		}
    	}
    }

    for (int w = 0; w < number_of_vertices; w++)
    {
        cout << S[w] << endl;
    }
}



