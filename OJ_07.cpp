#include <stdio.h>
#pragma warning(disable:4996)
#define M 1600
#define N 20
int main() {
	int m, n;
	scanf("%d %d", &m, &n);
	double MainDiag[M];
	double UpperDiag[M - 1];
	double LowerDiag[M - 1];
	double B[M][N];
	for (int i = 0; i < m; i++) {
		scanf("%lf", &MainDiag[i]);
	}
	for (int i = 0; i < m - 1; i++) {
		scanf("%lf", &UpperDiag[i]);
	}
	for (int i = 0; i < m - 1; i++) {
		scanf("%lf", &LowerDiag[i]);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%lf", &B[j][i]);
		}
	}
	for (int i = 0; i < m - 1; i++) {
		MainDiag[i + 1] -= LowerDiag[i] / MainDiag[i] * UpperDiag[i];
		for (int j = 0; j < n; j++) {
			B[i + 1][j] -= LowerDiag[i] / MainDiag[i] * B[i][j];
		}
		LowerDiag[i] = 0.;
	}
	for (int i = m - 2; i >= 0; i--) {
		for (int j = 0; j < n; j++) {
			B[i][j] -= B[i + 1][j] * UpperDiag[i] / MainDiag[i + 1];
		}
		UpperDiag[i] = 0;
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			B[i][j] /= MainDiag[i];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			printf("%lf", B[j][i]);
			if (j < m - 1) printf(" ");
			else if (i < n - 1) printf("\n");
		}
	}
	return 0;
}