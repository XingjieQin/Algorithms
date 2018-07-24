#include <iostream>
#include <vector>
using namespace std;
void insert_sort(vector<int> &a);//原址稳定的插入排序
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
		while(i >= 0 && a[i] > key){
			a[i + 1] = a[i];
			--i;
		}
		a[i + 1] = key;
	}
}
