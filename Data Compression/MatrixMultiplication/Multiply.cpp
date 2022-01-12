#include "Multiply.h"
using namespace concurrency;

vector<vector<int>> bruteForceMultiply (vector<vector<int>>& A, vector<vector<int>>& B)
{
	int n = A.size();
	vector<vector<int>> C(n, vector<int>(n, 0));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++)
			{
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
	return C;
}

vector<vector<int>> matSum (vector<vector<int>>& A, vector<vector<int>>& B)
{
	int n = A.size();
	vector<vector<int>> C(n, vector<int>(n, 0));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{	
			C[i][j] = A[i][j] + B[i][j];
		}
	}
	return C;
}

vector<vector<int>> matDif (vector<vector<int>>& A, vector<vector<int>>& B)
{
	int n = A.size();
	vector<vector<int>> C(n, vector<int>(n));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{	
			C[i][j] = A[i][j] - B[i][j];
		}
	}
	return C;
}

int padding(int n)
{
	int c = 1;
	while (c * 140 < n)
	{
		c *= 2;
	}
	if (n % c == 0)
		return n;
	else
		return n + (c - n % c);
}

vector<vector<int>> expand(vector<vector<int>> A)
{
	int n = A.size();
	int m = padding(n);
	for (int i = 0; i < n; i++)
	{
		for (int j = n; j < m; j++)
		{
			A[i].push_back(0);
		}
	}
	for (int i = n; i < m; i++)
	{
		A.push_back(vector<int>(m, 0));
	}
	return A;
}


vector<vector<int>> Strassen (vector<vector<int>>& A, vector<vector<int>>& B)
{
	vector<vector<int>> D = expand(A);
	vector<vector<int>> E = expand(B);
	int n = D.size();
	vector<vector<int>> C(n, vector<int>(n, 0));
	return StrassenStep(D, E);
}

vector<vector<int>> StrassenStep(vector<vector<int>> A, vector<vector<int>> B)
{
	unsigned int n = A.size();
	if (n < 150)
		return bruteForceMultiply(A, B);
	else
	{
		n /= 2;
		vector<vector<int>> A11(n, vector<int>(n)), A12(n, vector<int>(n)), A21(n, vector<int>(n)), A22(n, vector<int>(n));
		vector<vector<int>> B11(n, vector<int>(n)), B12(n, vector<int>(n)), B21(n, vector<int>(n)), B22(n, vector<int>(n));
		for (unsigned int i = 0; i < n; i++)
		{
			for (unsigned int j = 0; j < n; j++)
			{
				A11[i][j] = A[i][j];
				B11[i][j] = B[i][j];
			}
		}
		for (unsigned int i = 0; i < n; i++)
		{
			for (unsigned int j = n; j < B.size(); j++)
			{
				A12[i][j - n] = A[i][j];
				B12[i][j - n] = B[i][j];
			}
		}
		for (unsigned int i = n; i < A.size(); i++)
		{
			for (unsigned int j = 0; j < n; j++)
			{
 				A21[i - n][j] = A[i][j];
				B21[i - n][j] = B[i][j];
			}
		}
		for (unsigned int i = n; i < A.size(); i++)
		{
			for (unsigned int j = n; j < B.size(); j++)
			{
				A22[i - n][j - n] = A[i][j];
				B22[i - n][j - n] = B[i][j];
			}
		}

		vector<vector<int>> D1 = StrassenStep(matSum(A11, A22), matSum(B11, B22));
		vector<vector<int>> D2 = StrassenStep(matDif(A12, A22), matSum(B21, B22));
		vector<vector<int>> D3 = StrassenStep(matDif(A21, A11), matSum(B11, B12));
		vector<vector<int>> H1 = StrassenStep(matSum(A11, A12), B22);
		vector<vector<int>> H2 = StrassenStep(matSum(A21, A22), B11);
		vector<vector<int>> V1 = StrassenStep(A22, matDif(B21, B11));
		vector<vector<int>> V2 = StrassenStep(A11, matDif(B12, B22));

		vector<vector<int>> C(A.size(), vector<int>(A.size()));
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				C[i][j] = D1[i][j] + D2[i][j] + V1[i][j] - H1[i][j];
			}
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = n; j < B.size(); j++)
			{
				C[i][j] = V2[i][j - n] + H1[i][j - n];
			}
		}
		for (int i = n; i < A.size(); i++)
		{
			for (int j = 0; j < n; j++)
			{
				C[i][j] = V1[i - n][j] + H2[i - n][j];
			}
		}
		for (int i = n; i < A.size(); i++)
		{
			for (int j = n; j < B.size(); j++)
			{
				C[i][j] = D1[i - n][j - n] + D3[i - n][j - n] + V2[i - n][j - n] - H2[i - n][j - n];
			}
		}
		return C;

	}
}

vector<vector<int>> openMPMultiply (vector<vector<int>>& A, vector<vector<int>>& B)
{
	int n = A.size();
	vector<vector<int>> C(n, vector<int>(n, 0));
	#pragma omp parallel for (i, j, k)
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++)
			{
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
	return C;
}