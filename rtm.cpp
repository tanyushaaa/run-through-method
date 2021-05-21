#include "rtm.h"

float Pi(float ai, float bi, float ci, float P){
	return (-ci / (bi + ai*P));
}

float Qi(float ai, float bi, float di, float P, float Q){
	return ((di - ai * Q) / (bi + ai * P));
}

float* rtm(const Matrix& M){
	int n = M.GetA().second;
	float** x = M.GetA().first;

	float* P = new float [n];
	float* Q = new float [n];

	for (int i = 0; i < n; i++){
		if(i == 0){
			P[i] = Pi(0, x[i][i], x[i][i + 1], 0);
			Q[i] = Qi(0, x[i][i], x[i][n], 0, 0);
		} else if (i == n - 1){
			P[i] = Pi(x[i][i - 1], x[i][i], 0, P[i - 1]);
			Q[i] = Qi(x[i][i - 1], x[i][i], x[i][n], P[i - 1], Q[i - 1]);
		} else {
			P[i] = Pi(x[i][i - 1], x[i][i], x[i][i + 1], P[i - 1]);
			Q[i] = Qi(x[i][i - 1], x[i][i], x[i][n], P[i - 1], Q[i - 1]);
		}
	}

	float* answer = new float [n];

	for (int i = n - 1; i >= 0; i--){
		answer[i] = (i == n - 1) ? Q[i] : Q[i] + P[i] * answer[i + 1];
//		std::cout << answer[i] << " ";
	}
	return answer;
}
