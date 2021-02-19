/*
 * Gap Hamming Distance.cpp
 *
 *  Created on: 19 Feb 2021
 *      Author: Grant
 */

#include <iostream>

using namespace std;

int n = 6;

int hamming_distance_reduction(int s1[], int s2[], int supportx, int supporty)
{
	int distinct_elements[n];
	int distinctcount = 0;

	for (int i = 0; i < n; i++)
	{
		int value = s1[i];

		if (value == 0)
		{
			break;
		}

		bool included = false;
		for (int j = 0; j < n; j++)
		{
			if (distinct_elements[j] == value)
			{
				included = true;
			}
		}

		if (included == true)
		{
			continue;
		}
		else
		{
			distinct_elements[distinctcount] = value;
			distinctcount++;
		}
	}

	for (int i1 = 0; i1 < n; i1++)
	{
		int value = s2[i1];

		if (value == 0)
		{
			break;
		}

		bool included = false;
		for (int j1 = 0; j1 < n; j1++)
		{
			if (distinct_elements[j1] == value)
			{
				included = true;
			}
		}

		if (included == true)
		{
			continue;
		}
		else
		{
			distinct_elements[distinctcount] = value;
			distinctcount++;
		}
	}

	int result = 2 * (distinctcount) - supportx - supporty;

	return result;
}

int main()
{
	int x[n] = {0, 1, 0, 1, 1, 0};
	int y[n] = {1, 1, 0, 0, 1, 1};

	int s1[n];
	int s2[n];

	for (int i = 0; i < n; i++)
	{
		s1[i] = 0;
		s2[i] = 0;
	}

	int s1count = 0;
	int s2count = 0;
	for (int j = 0; j < n; j++)
	{
		if (x[j] == 1)
		{
			s1[s1count] = j + 1;
			s1count++;
		}

		if (y[j] == 1)
		{
			s2[s2count] = j + 1;
			s2count++;
		}
	}

	int supportx = 0;
	int supporty = 0;

	for (int k = 0; k < n; k++)
	{
		if (x[k] == 1)
		{
			supportx++;
		}

		if (y[k] == 1)
		{
			supporty++;
		}
	}

	int h = hamming_distance_reduction(s1, s2, supportx, supporty);

	cout << "The hamming distance is " << h << endl;

	return 0;
}


