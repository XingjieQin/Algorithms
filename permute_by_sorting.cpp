/*
 *获得输入序列的一个均匀随即序列
 *输入一个以CTRL+X结尾的整型序列。
 *输出输入序列调整后的序列
 *2018/08/01
 **/
#include <iostream>
#include <vector>
#include <random>
#include <cmath>
using namespace std;
void input(vector<int> &v);
void output(vector<int> &v);
void permute_by_sorting(vector<int> &v);
void merge_sort(vector<int> &v, const int low, const int high, vector<int> &att);
void my_merge(vector<int> &v, const int low, const int mid, const int high, vector<int> &att);
int main(){
    vector<int> v;
    input(v);
    output(v);
    permute_by_sorting(v);
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
void permute_by_sorting(vector<int> &v){
    default_random_engine e;
    uniform_int_distribution<int> uid(1, pow(v.size(), 3));
    vector<int> priority(v.size(), 0);
    for(int i = 0; i < priority.size(); ++i){
        priority[i] = uid(e);
    }
    merge_sort(priority, 0, priority.size() - 1, v);
}
void merge_sort(vector<int> &v, const int low, const int high, vector<int> &att){
    if(low < high){
        int mid = (high + low) / 2;
        merge_sort(v, low, mid, att);
        merge_sort(v, mid + 1, high, att);
        my_merge(v, low, mid, high, att);
    }
}
void my_merge(vector<int> &v, const int low, const int mid, const int high, vector<int> &att){
    vector<int> left(v.begin() + low, v.begin() + mid + 1);
    vector<int> left_att(att.begin() + low, att.begin() + mid + 1);
    vector<int> right(v.begin() + mid + 1, v.begin() + high + 1);
    vector<int> right_att(att.begin() + mid + 1, att.begin() + high + 1);
    left.push_back(2147483647);
    right.push_back(2147483647);
    int l = 0;
    int r = 0;
    for(int i = low; i <= high; ++i){
            if(left[l] <= right[r]){
                v[i] = left[l];
                att[i] = left_att[l++];
            }else{
                v[i] = right[r];
                att[i] = right_att[r++];
            }
    }
}
