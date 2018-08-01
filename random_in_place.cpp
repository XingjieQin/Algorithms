/*
 *获得输入序列的一个均匀随即序列
 *输入一个以CTRL+X结尾的整型序列。
 *输出输入序列调整后的序列
 *2018/08/01
 **/
#include <iostream>
#include <vector>
#include <random>
using namespace std;
void input(vector<int> &v);
void output(vector<int> &v);
void permute_by_swap(vector<int> &v);
int main(){
    vector<int> v;
    input(v);
    output(v);
    permute_by_swap(v);
    output(v);
    return 0;
}
void input(vector<int> &v){
    int tmp;
    while(cin >> tmp){
        v.push_back(tmp);
    }
}
void output(vector<int> &v){
    for(auto i: v){
        cout << i << " ";
    }
    cout << endl;
}
void permute_by_swap(vector<int> &v){
    default_random_engine e;
    int tmp;
    for(int i = 0; i < v.size(); ++i){
        uniform_int_distribution<int> uid(i, v.size() - 1);
        int pos = uid(e);
        tmp = v[pos];
        v[pos] = v[i];
        v[i] = tmp;
    }
}
