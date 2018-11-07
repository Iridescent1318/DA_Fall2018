#include <iostream>
#include <vector>
#include <algorithm>
#pragma warning(disable:4996)

struct RFpair{
	int order;
	int rf;
};

int RecmFrnd(bool** FrndMtx, int size, int tar1, int tar2) { 
	int RecmFrndCnt = 0;
	bool tmp1, tmp2;
	for (int i = 0; i < size; i++) {
		if (i == tar1 || i == tar2) continue;
		tmp1 = (tar1 >= i) ? FrndMtx[tar1][i] : FrndMtx[i][tar1];
		tmp2 = (tar2 >= i) ? FrndMtx[tar2][i] : FrndMtx[i][tar2];
		if (tmp1 && tmp2) RecmFrndCnt++;
	}
	return RecmFrndCnt;
}

bool cmp(const RFpair tar1, const RFpair tar2) {
	return tar1.rf > tar2.rf;
}

int main() {
	std::ios::sync_with_stdio(false);
	int n, k, u;
	std::cin >> n >> k >> u;
	bool** FriendMatrix = new bool*[n];
	for (int i = 0; i < n; i++) {
		FriendMatrix[i] = new bool[i+1];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			bool ipt_buff = 0;
			std::cin >> ipt_buff;
			if (i >= j) FriendMatrix[i][j] = ipt_buff;
		}
	}
	std::vector<RFpair> result;
	for (int i = 0; i < n; i++) {
		bool tmp = (u >= i) ? FriendMatrix[u][i] : FriendMatrix[i][u];
		if (i == u || tmp ) continue;
		int rf = RecmFrnd(FriendMatrix, n, u, i);
		if (rf >= k) {
			RFpair tmpPair; tmpPair.order = i; tmpPair.rf = rf;
			result.push_back(tmpPair);
		}
	}
	stable_sort(result.begin(), result.end(), cmp);
	for (int i = 0; i < result.size(); i ++) {
		if (i != 0) std::cout << " ";
		std::cout << result[i].order;
	}
	return 0;
}