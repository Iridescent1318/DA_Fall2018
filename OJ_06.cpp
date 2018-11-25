#include <iostream>
#include <vector>
#include <algorithm>
#define P_INT_MAX 4294967295
#define VERSION_2

typedef unsigned int p_int;
struct pair {
	int x;
	int y;
	pair() {
		x = -1; y = -1;
	}
	pair(int X, int Y) {
		x = X; y = Y;
	}
};

void swap(p_int& a, p_int& b) {
	int tmp = a; a = b; b = tmp;
}

#ifdef VERSION_1 // I finished Version 1 first. It takes less space but much more time, causing TLE. Therefore this version is aborted.
pair find(p_int tar, std::vector<std::vector<p_int> >& v);
void insert(p_int tar, std::vector<std::vector<p_int> >& v);
void erase(std::vector<std::vector<p_int> >& v, int row, int cmn);

int main() {
	std::ios::sync_with_stdio(false);
	int n, n1, n2, n3, rowCnt = 0;
	std::cin >> n >> n1 >> n2 >> n3;
	p_int *toFind = new p_int[n1], *toIns = new p_int[n2], *toDel = new p_int[n3];
	std::vector< std::vector<p_int> > vec(1);
	p_int ipt = 0;
	for (int i = 0; i < n; i++) {
		std::cin >> ipt;
		vec[rowCnt].push_back(ipt);
		if (ipt == -1) {
			vec.resize(++rowCnt + 1);
		}
	}
	for (int i = 0; i < n1; i++) std::cin >> toFind[i];
	for (int i = 0; i < n2; i++) std::cin >> toIns[i];
	for (int i = 0; i < n3; i++) std::cin >> toDel[i];
	vec.pop_back();
	pair tmp;
	for (int i = 0; i < n1; i++) {
		tmp = find(toFind[i], vec);
		std::cout << tmp.x << " " << tmp.y;
		if (i < n1 - 1)std::cout << " ";
	}
	std::cout << std::endl;
	for (int i = 0; i < n2; i++) {
		insert(toIns[i], vec);
	}
	for (int i = 0; i < rowCnt; i++) {
		for (std::vector<p_int>::iterator itr = vec[i].begin(); itr != vec[i].end(); itr++) {
			if (*itr == P_INT_MAX) std::cout << -1;
			else std::cout << *itr;
			if (!(i == rowCnt - 1 && itr == vec[i].end()-1)) std::cout << " ";
		}
	}
	std::cout << std::endl;
	for (int i = 0; i < n3; i++) {
		tmp = find(toDel[i], vec);
		erase(vec, tmp.x, tmp.y);
	}
	while (vec.back()[0] == P_INT_MAX && vec.size()>1) {
		vec.pop_back();
		rowCnt--;
	}
	for (int i = 0; i < rowCnt; i++) {
		for (std::vector<p_int>::iterator itr = vec[i].begin(); itr != vec[i].end(); itr++) {
			if (i || itr != vec[0].begin()) std::cout << " ";
			if (*itr == P_INT_MAX && itr != vec[i].begin()) {
				std::cout << -1;
			}
			else if(*itr != P_INT_MAX) std::cout << *itr;
		}
	}
	return 0;
}

pair find(p_int tar, std::vector<std::vector<p_int> >& v) {
	int v_size = v.size();
	int row = 0, cmn = v[0].size() - 1;
	while (cmn) {
		if (v[row][cmn] == tar) return pair(row, cmn); //Return if found
		else if (row < v_size - 1) { //DOWN not exceeded
			if (v[row][cmn] > tar || cmn >= v[row + 1].size()) { //v[][] is greater or DOWN is empty
				cmn--; continue;
			}
			else { //v[][] is smaller and DOWN is not empty
				row++; cmn = v[row].size()-1;
			}
		} 
		else  cmn--; //DOWN exceeded
	}
	while (row < v_size - 1) {
		if (v[row][0] == tar) return pair(row, 0);
		else row++;
	}
	if (v[v_size - 1][0] == tar) return pair(v_size - 1, 0);
	else return pair(-1, -1);
}

void insert(p_int tar, std::vector<std::vector<p_int> >& v) {
	int row = v.size()-1;
	while (v[row].size() == v[row - 1].size()) row--;
	v[row].insert(v[row].begin() + v[row].size(), tar);
	int cmn = v[row].size() - 1;
	while (cmn > 0 && row > 0 && (v[row][cmn - 1] > v[row][cmn] || v[row - 1][cmn] > v[row][cmn])) {
		if (v[row - 1][cmn] > v[row][cmn - 1]) {
			swap(v[row - 1][cmn], v[row][cmn]); row--;
		}
		else {
			swap(v[row][cmn - 1], v[row][cmn]); cmn--;
		}
	}
	while (!cmn && row) {
		if (v[row - 1][0] > v[row][0]) {
			swap(v[row - 1][0], v[row][0]); row--;
		}
		else break;
	}
	while (!row && cmn) {
		if (v[0][cmn-1] > v[0][cmn]) {
			swap(v[0][cmn - 1], v[0][cmn]); cmn--;
		}
		else break;
	}
	return;
}

void erase(std::vector<std::vector<p_int> >& v, int row, int cmn) {
	int v_size = v.size();
	v[row][cmn] = P_INT_MAX;
	if (cmn == v[row].size() - 1) {
		v[row].erase(v[row].begin() + cmn); return;
	}
	if (row == v_size - 1 || v[row + 1].size() - 1 < cmn) {
		swap(v[row][cmn], v[row][cmn + 1]); erase(v, row, cmn + 1); 
	}
	else if ( v[row + 1][cmn] < v[row][cmn + 1] ) {
		swap(v[row][cmn], v[row + 1][cmn]); erase(v, row + 1, cmn);
	}
	else {
		swap(v[row][cmn], v[row][cmn + 1]); erase(v, row, cmn + 1);
	}
}
#endif

#ifdef VERSION_2

struct young_tableau {
	pair find(p_int tar);
	void insert(p_int tar);
	void erase(int row, int cmn);

	p_int** YT;
	int rowNum;
	int cmnNum;
};


int main() {
	std::ios::sync_with_stdio(false);
	int n, n1, n2, n3, rowCnt = 0;
	std::cin >> n >> n1 >> n2 >> n3;
	p_int *ipt = new p_int[n], *toFind = new p_int[n1], *toIns = new p_int[n2], *toDel = new p_int[n3];
	std::vector<int> count_cmn;
	count_cmn.push_back(-1);
	for (int i = 0; i < n; i++) {
		std::cin >> ipt[i];
		if (ipt[i] == P_INT_MAX) {
			rowCnt++;
			count_cmn.push_back(i);
		}
	}
	std::vector<int> count_cmn_fnl;
	for (int i = 0; i < rowCnt - 1; i++) {
		count_cmn_fnl.push_back(count_cmn[i + 1] - count_cmn[i]);
	}
	sort(count_cmn_fnl.begin(), count_cmn_fnl.end()); // Trying to figure out the largest distance between any two adjacent -1's to make the matrix smaller
	young_tableau yt;
	yt.YT = new p_int*[rowCnt]; yt.rowNum = rowCnt; yt.cmnNum = *(count_cmn_fnl.end()-1);
	for (int i = 0; i < yt.rowNum; i++) {
		yt.YT[i] = new p_int[yt.cmnNum];
		for (int j = 0; j < yt.cmnNum; j++) {
			yt.YT[i][j] = P_INT_MAX;
		}
	}
	p_int row_ini = 0, cmn_ini = 0;
	for (int i = 0; i < n; i++) {
		yt.YT[row_ini][cmn_ini] = ipt[i];
		if (yt.YT[row_ini][cmn_ini] == P_INT_MAX) {
			row_ini++; cmn_ini = 0; continue;
		}
		cmn_ini++;
	}
	for (int i = 0; i < n1; i++) std::cin >> toFind[i];
	for (int i = 0; i < n2; i++) std::cin >> toIns[i];
	for (int i = 0; i < n3; i++) std::cin >> toDel[i];
	pair tmp;
	for (int i = 0; i < n1; i++) {
		tmp = yt.find(toFind[i]);
		std::cout << tmp.x << " " << tmp.y;
		if (i < n1 - 1)std::cout << " ";
	}
	std::cout << std::endl;
	for (int i = 0; i < n2; i++) {
		yt.insert(toIns[i]);
	}
	row_ini = 0; cmn_ini = 0;
	for (int i = 0; i < n + n2; i++) {
		if (yt.YT[row_ini][cmn_ini] != P_INT_MAX) {
			if (i || cmn_ini) std::cout << " ";
			std::cout << yt.YT[row_ini][cmn_ini];
		}
		else {
			std::cout << " " << -1;
			row_ini++; cmn_ini = 0; continue;
		}
		cmn_ini++;
	}
	std::cout << std::endl;
	for (int i = 0; i < n3; i++) {
		tmp = yt.find(toDel[i]);
		yt.erase(tmp.x, tmp.y);
	}
	row_ini = 0; cmn_ini = 0;
	for (int i = 0; i < n + n2 - n3; i++) {
		if (cmn_ini == 0 && yt.YT[row_ini][0] == P_INT_MAX) {
			row_ini++;continue;
		}
		if (yt.YT[row_ini][cmn_ini] != P_INT_MAX) {
			if (i || cmn_ini) std::cout << " ";
			std::cout << yt.YT[row_ini][cmn_ini];
		}
		else {
			std::cout << " " << -1;
			row_ini++; cmn_ini = 0; continue;
		}
		cmn_ini++;
	}
	return 0;
}

pair young_tableau::find(p_int tar) { //Find if the target is in the young tableau.
	int row = 0, cmn = cmnNum - 1;
	while (cmn) {
		if (this->YT[row][cmn] == tar) return pair(row, cmn); //Return if found
		else if (row < rowNum - 1) { //DOWN not exceeded
			if (this->YT[row][cmn] > tar || row == rowNum - 1) { //v[][] is greater or DOWN is empty
				cmn--; continue;
			}
			else { //v[][] is smaller and DOWN is not empty
				row++;
			}
		}
		else  cmn--; //DOWN exceeded
	}
	while (row < rowNum - 1) {
		if (this->YT[row][0] == tar) return pair(row, 0);
		else row++;
	}
	if (this->YT[rowNum - 1][0] == tar) return pair(rowNum - 1, 0);
	else return pair(-1, -1);
}

void young_tableau::insert(p_int tar) { //Insert a distinct element into the young tableau
	int row = rowNum - 1, cmn = cmnNum - 1;
	this->YT[row][cmn] = tar;
	if (this->YT[row][cmn] != P_INT_MAX) {
		while (cmn > 0 && row > 0 && (this->YT[row][cmn - 1] > this->YT[row][cmn] || this->YT[row - 1][cmn] >= this->YT[row][cmn])) {
			if (this->YT[row - 1][cmn] > this->YT[row][cmn - 1]) {
				swap(this->YT[row - 1][cmn], this->YT[row][cmn]); row--;
			}
			else {
				swap(this->YT[row][cmn - 1], this->YT[row][cmn]); cmn--;
			}
		}
		while (!cmn && row) {
			if (this->YT[row - 1][0] > this->YT[row][0]) {
				swap(this->YT[row - 1][0], this->YT[row][0]); row--;
			}
			else break;
		}
		while (!row && cmn) {
			if (this->YT[0][cmn - 1] > this->YT[0][cmn]) {
				swap(this->YT[0][cmn - 1], this->YT[0][cmn]); cmn--;
			}
			else break;
		}
		return;
	}
	else return;
}

void young_tableau::erase(int row, int cmn) { //Delete an existing element from the young tableau
	this->YT[row][cmn] = P_INT_MAX;
	while (row < rowNum - 1 && cmn < cmnNum - 1) {
		if (this->YT[row + 1][cmn] < this->YT[row][cmn + 1]) {
			swap(this->YT[row][cmn], this->YT[row + 1][cmn]); row++;
		}
		else {
			swap(this->YT[row][cmn], this->YT[row][cmn + 1]); cmn++;
		}
	}
	while (row == rowNum - 1 && cmn < cmnNum - 1) {
		if (this->YT[row][cmn + 1] < this->YT[row][cmn]) {
			swap(this->YT[row][cmn], this->YT[row][cmn + 1]); cmn++;
		}
		else break;
	}
	while (cmn == cmnNum - 1 && row < rowNum - 1) {
		if (this->YT[row + 1][cmn] < this->YT[row][cmn]) {
			swap(this->YT[row][cmn], this->YT[row+1][cmn]); row++;
		}
		else break;
	}
}
#endif