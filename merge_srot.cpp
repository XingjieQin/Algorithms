/*
 *非原址稳定归并排序算法
 *输入一个以ctrl+x结尾的数组
 *输出原数组和排序后的数组
 *2018/07/25 13:57
 **/
 #include <iostream>
 #include <vector>
 using namespace std;
 void input(vector<int> &v);
 void output(vector<int> &v);
 void merge_sort(vector<int> &v, int p, int r);
 void my_merge(vector<int> &v, int p, int q, int r);
 int main(){
    vector<int> v;
    input(v);
    output(v);
    merge_sort(v, 0, v.size() - 1);
    output(v);
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
 void merge_sort(vector<int> &v, int p, int r){
     if(p < r){
        int q = (r + p) / 2;
        merge_sort(v, p, q);
        merge_sort(v, q + 1, r);
        my_merge(v, p, q, r);
     }
 }
 void my_merge(vector<int> &v, int p, int q, int r){
     int len1 = q - p + 1;
     int len2 = r - q;
     vector<int> left(v.begin() + p, v.begin() + q + 1);
     vector<int> right(v.begin() + q + 1, v.begin() + r + 1);
     left.push_back(2147483647);//哨兵
     right.push_back(2147483647);//哨兵
     int i = 0, j = 0;
     for(int k = p; k <= r; ++k){
         if(left[i] <= right[j]){//归并算法稳定的原因
            v[k] = left[i];
            ++i;
         }else{
             v[k] = right[j];
             ++j;
         }
     }
 }
