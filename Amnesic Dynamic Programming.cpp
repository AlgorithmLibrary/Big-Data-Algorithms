/*
 * Amnesic Dynamic Programming.cpp
 *
 *  Created on: 17 Feb 2021
 *      Author: Grant
 */

#include <iostream>
#include <random>
#include <math.h>

using namespace std;

int main()
{
	srand(5);

	int n = 10;

	int list[n + 2] = {-1000, 1, 3, 2, 5, 2, 3, 9, 11, 3, 12, 1000};

	int w[n + 2];

	for (int i = 0; i < n + 2; i++)
	{
		if (i == 0)
		{
			w[i] = 1000;
			continue;
		}

		if (i == n + 1)
		{
			w[i] = 1000;
			continue;
		}

		w[i] = 1;
	}

	for (int j = 0; j < n + 2; j++)
	{
		cout << w[j] << endl;
	}

	int w_capital[n + 2];
	int r[n + 2];
	int check_values[n + 2];

	w_capital[0] = 0;
	r[0] = 0;

	int R[n + 2];

	for (int k = 0; k < n + 2; k++)
	{
		R[k] = 0;
	}

	R[0] = 1;

	float epsilon = 0.5;
	float delta = 0.5;

	for (int t = 1; t < n + 2; t++)
	{
		w_capital[t] = w_capital[t - 1] + w[t];

		int minimum = 10000;
		int check_value = 1000;
		for (int a = 0; a < n + 2; a++)
		{
			if (R[a] == 1)
			{
				int temp = r[a] + w_capital[t - 1] - w_capital[a];

				//cout << temp << endl;

				if ((temp < minimum) && (list[a] < list[t]))
				{
					minimum = temp;
					check_value = list[a];
					cout << minimum << endl;
				}
			}
		}
		cout << endl;
		cout << endl;

		r[t] = minimum;
		check_values[t] = check_value;

		R[t] = 1;

		for (int i = 0; i < n; i++)
		{
			if (R[i] == 1)
			{
				float q1 = 1.0;

				float w_i_t = 0.0;

				for (int j = i; j < t; j++)
				{
					w_i_t = w_i_t + float(w_capital[j]);
				}

				//float q2 = ((1 + epsilon) / epsilon) * (log(4 * pow(t, 3) / delta)) * (w[i] / w_i_t);

				float q2;

				if (w_i_t != 0)
				{
					q2 = ((1 + epsilon) / epsilon) * (log(4.0 * pow(t, 3) / delta)) * (float(w[i]) / w_i_t);
				}
				else
				{
					q2 = ((1 + epsilon) / epsilon) * (log(4.0 * pow(t, 3) / delta)) * (float(w[i]));
				}

				cout << "w_i_t is " << w_i_t << endl;
				//cout << "q2 is " << q2 << endl;

				float q = min(q1, q2);
				//float q = q2;
				cout << "q is " << q << endl;


				float q1_minus = 1.0;

				float w_i_t_minus = 0;

				for (int j = i; j < t - 1; j++)
				{
					w_i_t_minus = w_i_t_minus + float(w_capital[j]);
				}

				float q2_minus;

				if (w_i_t_minus != 0)
				{
					q2_minus = ((1 + epsilon) / epsilon) * (log(4.0 * pow(t - 1, 3) / delta)) * (float(w[i]) / w_i_t_minus);
				}
				else
				{
					q2_minus = ((1 + epsilon) / epsilon) * (log(4.0 * pow(t - 1, 3) / delta)) * (float(w[i]));
				}

				float q_minus = min(q1_minus, q2_minus);
				//float q_minus = q2_minus;

				//cout << "q is " << q << endl;
				cout << "q minus us " << q_minus << endl;
				//cout << endl;

				float p;
				if (i == t)
				{
					p = 1.0;
				}
				else
				{
					p = q / q_minus;
				}

				float removal = 1.0 - p;

				float probability = float((rand() % 100)) / 100.0;
				cout << "probability is " << probability << endl;
				cout << endl;

				if (probability <= removal)
				{
					R[i] = 0;
				}
			}
		}

	}


	cout << "w capital is: ";
	for (int u = 0; u < n + 2; u++)
	{
		cout << w_capital[u] << " ";
	}
	cout << endl;

	cout << "r is: ";
	for (int u1 = 0; u1 < n + 2; u1++)
	{
		cout << r[u1] << " ";
	}
	cout << endl;

	cout << "check value is: ";
	for (int u2 = 0; u2 < n + 2; u2++)
	{
		cout << check_values[u2] << " ";
	}
	cout << endl;

	int temp = -100;
	cout << "The longest increasing subsequence is ";
	for (int u3 = 2; u3 < n + 2; u3++)
	{
		if (check_values[u3] > temp)
		{
			temp = check_values[u3];
			cout << check_values[u3] << " ";
		}
	}
	cout << endl;

	return 0;
}


