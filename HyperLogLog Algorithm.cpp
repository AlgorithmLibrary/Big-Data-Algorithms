/*
 * HyperLogLog Algorithm.cpp
 *
 *  Created on: 9 Feb 2021
 *      Author: Grant
 */

#include <bitset>
#include <string>
#include <sstream>
#include <climits>
#include <iostream>
#include <math.h>

using namespace std;

const int number_of_inputs = 18;

int size = 10;
int n = 10;
int bucket_position = 3;
int array_size[10];
int stream[number_of_inputs][10];

void integertobinary(int n, int position)
{
	int i;
	for(i=0; n>0; i++)
	{
		stream[position][i]=n%2;
		n= n/2;
	}

	array_size[position] = i;
}

int bucket_index(int position, int bucket_size)
{
	int bucket = 0;

	for (int a = 0; a < bucket_size; a++)
	{
		if (stream[position][a] == 1)
		{
			bucket = bucket + pow(2, a);
		}
	}

	return bucket;
}

int least_significant_bit(int position, int bucket_size)
{
	int least_position = 0;

	int count = 0;
	for (int a = bucket_size; a < n; a++)
	{
		if (stream[position][a] == 1)
		{
			least_position = count;
			break;
		}
		count++;
	}

	return least_position;
}

int main()
{
	int original_stream[number_of_inputs] = {11, 15, 16, 18, 6, 21, 25, 31, 35, 38, 55, 28, 83, 81, 98, 19, 23, 63};
	//int original_stream[number_of_inputs] = {11, 15, 16, 18, 6, 21, 25, 31, 35, 38, 55, 28};
	//int original_stream[number_of_inputs] = {21, 25, 31, 35, 38, 39, 28, 38};
	int number_of_buckets = int(pow(2, bucket_position));
	int buckets[number_of_buckets];

	for (int i = 0; i < number_of_buckets; i++)
	{
		buckets[i] = 0;
	}

	for (int p = 0; p < number_of_inputs; p++)
	{
	integertobinary(original_stream[p], p);

	for (int a = 0; a < n; a++)
	{
		cout << stream[p][a] << endl;
	}

	int lsb = least_significant_bit(p, bucket_position);
	int bucket_number = bucket_index(p, bucket_position);

	cout << "Bucket Number " << bucket_number << endl;
	cout << "Least Significant Bit " << lsb << endl;

	if (lsb > buckets[bucket_number])
	{
		buckets[bucket_number] = lsb;
	}

	cout << endl;
	}

	//Harmonic Mean
	float summation = 0.0;
	for(int a = 0; a < number_of_buckets; a++)
	{
		summation = summation + pow(2, -buckets[a]);
	}

	cout << summation << endl;

	float total_cardinality = 0.794 * number_of_buckets * number_of_buckets / summation;

	//Stochastic Averaging
	/*
	float summation = 0.0;
	for(int a = 0; a < number_of_buckets; a++)
	{
		summation = summation + buckets[a];
	}

	float power = summation / number_of_buckets;
	cout << summation << endl;

	float total_cardinality = 0.794 * number_of_buckets * pow(2, power);
	*/

	cout << "Total Cardinality is " << total_cardinality << endl;

	return 0;
}


