/*
 *最大子数组问题的分治解法
 *输入一个以ctrl+x结束的整型数组
 *输出最大子数组的位置及和
 *2018/07/25 17:09
 **/
#include <iostream>
#include <vector>
using namespace std;
struct Result{
    int left, right;
    int sum;
};
void input(vector<int> &v);
void output(const Result &r);
Result find_maximun_subarray(vector<int> &v, int low, int high);
Result find_maximun_cross_subarray(vector<int> &v, int low, int mid, int high);
int main(){
    vector<int> v;
    input(v);
    output(find_maximun_subarray(v, 0, v.size() - 1));
    return 0;
}
void input(vector<int> &v){
    int tmp;
    while(cin >> tmp){
            v.push_back(tmp);
    }
}
void output(const Result &r){
    cout << "sum[" << r.left << "," << r.right << "] = " << r.sum << endl;
}
Result find_maximun_subarray(vector<int> &v, int low, int high){
    if(low == high){
        return {low, high, v[low]};
    }
    int mid = (low + high) / 2;
    Result left = find_maximun_subarray(v, low, mid);
    Result right = find_maximun_subarray(v, mid + 1, high);
    Result cross = find_maximun_cross_subarray(v, low, mid, high);
    if(left.sum > right.sum && left.sum > cross.sum){
        return left;
    }
    else if(right.sum > left.sum && right.sum > cross.sum){
        return right;
    }
    else{
        return cross;
    }

}
Result find_maximun_cross_subarray(vector<int> &v, int low, int mid, int high){
    int left_sum = -2147483648, left_pos, curr_sum = 0;
    for(int i = mid; i >= low; --i){
        curr_sum += v[i];
        if(curr_sum > left_sum){
            left_sum = curr_sum;
            left_pos = i;
        }
    }
    int right_sum = -2147483648, right_pos;
    curr_sum = 0;
    for(int i = mid + 1;i <= high; ++i){
        curr_sum += v[i];
        if(curr_sum > right_sum){
            right_sum = curr_sum;
            right_pos = i;
        }
    }
    return {left_pos, right_pos, left_sum + right_sum};
}
