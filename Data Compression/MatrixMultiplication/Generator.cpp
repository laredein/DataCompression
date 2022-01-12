#include "Generator.h"

void showArr (vector<vector<int>>& arr)
{
	for (unsigned int i = 0; i < arr.size(); i++)
	{
		for  (unsigned int j = 0; j < arr[i].size(); j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
void showArr (vector<vector<vector<int>>>& arr)
{
	for (unsigned int i = 0; i < arr.size(); i++)
	{
		for  (unsigned int j = 0; j < arr[i].size(); j++)
		{
			for (unsigned int k = 0; k < arr[i][j].size(); k++)
			{
				cout << arr[i][j][k] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
}

vector<vector<int>> generate(int n, double p)
{
	vector<double> weights(101, (1 - p) / 100);
	weights[0] = p;
	discrete_distribution<int> distr{weights.begin(), weights.end()};
	random_device r;
	default_random_engine generator(r());
	vector<vector<int>> generatedArr(n, vector<int>(n));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			generatedArr[i][j] = distr(generator);
		}
	}
	return generatedArr;
}

vector<vector<vector<int>>> generateMany(int l, int n, double p)
{
	vector<vector<vector<int>>> generatedArrays(l);
	for (int i = 0; i < l; i++)
	{
		generatedArrays[i] = generate(n, p);
	}
	return generatedArrays;
}

pair<vector<vector<int>>, vector<vector<int>>> generatePair(int n, double p)
{
	vector<vector<int>> A, B;
	A = generate(n, p);
	B = generate(n, p);
	return make_pair(A, B);
}

pair<vector<vector<int>>, vector<vector<int>>> generatePair(int n1, double p1, int n2, double p2)
{
	vector<vector<int>> A, B;
	A = generate(n1, p1);
	B = generate(n2, p2);
	return make_pair(A, B);
}

vector<pair<vector<vector<int>>, vector<vector<int>>>> generateManyPairs(int l, int n, double p)
{
	vector<pair<vector<vector<int>>, vector<vector<int>>>> generatedArrays(l);
	for (int i = 0; i < l; i++)
	{
		generatedArrays[i] = generatePair(n, p);
	}
	return generatedArrays;
}

vector<pair<vector<vector<int>>, vector<vector<int>>>> generateManyPairs(int l, int n1, double p1, int n2, double p2)
{
	vector<pair<vector<vector<int>>, vector<vector<int>>>> generatedArrays(l);
	for (int i = 0; i < l; i++)
	{
		generatedArrays[i] = generatePair(n1, p1, n2, p2);
	}
	return generatedArrays;
}