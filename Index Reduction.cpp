/*
 * Index Reduction.cpp
 *
 *  Created on: 21 Feb 2021
 *      Author: Grant
 */

#include <iostream>

using namespace std;

int n = 6;

int index_reduction(int s[], int supportx, int j)
{
	int distinct_elements[n];
	int distinctcount = 0;

	int s1[n + 1];

	for (int a = 0; a < n; a++)
	{
		s1[a] = s[a];
	}

	s1[supportx] = j;

	for (int i = 0; i < n + 1; i++)
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

	if (distinctcount > supportx)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main()
{
	int x[n] = {0, 1, 0, 1, 1, 0};

	int s1[n];

	for (int i = 0; i < n; i++)
	{
		s1[i] = 0;
	}

	int s1count = 0;

	for (int j = 0; j < n; j++)
	{
		if (x[j] == 1)
		{
			s1[s1count] = j + 1;
			s1count++;
		}
	}

	int supportx = 0;

	for (int k = 0; k < n; k++)
	{
		if (x[k] == 1)
		{
			supportx++;
		}
	}

	int j = 2;

	bool result = index_reduction(s1, supportx, j);

	if (result == true)
	{
		cout << "The output value is 0.";
	}
	else
	{
		cout << "The outputs value is 1.";
	}

	return 0;
}


