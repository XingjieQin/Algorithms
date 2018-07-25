/*
 *原址稳定插入排序算法
 *输入一个以ctrl+x结束的证型数组
 *输出输入数组和已排序数组
 *2018/07/25 10：01
 * */
#include <iostream>
#include <vector>
using namespace std;
void insert_sort(vector<int> &a);
void input(vector<int> &a);
void output(vector<int> &a);
int main(){
	vector<int> v;
	input(v);
	output(v);
	insert_sort(v);
	output(v);
	return 0;
}
void input(vector<int> &a){
	cout << "Please input a array:";
	int tmp;
	while(cin >> tmp){
		a.push_back(tmp);
	}
}
void output(vector<int> &a){
	for(auto i: a){
		cout << i << " ";
	}
	cout << endl;
}
void insert_sort(vector<int> &a){
	for(int j = 1; j < a.size(); ++j){
		int i = j - 1;
		int key = a[j];
		while(i >= 0 && a[i] > key){//算法稳定的原因
			a[i + 1] = a[i];
			--i;
		}
		a[i + 1] = key;
	}
}
