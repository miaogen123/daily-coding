//设计一个算法，计算出n阶乘中尾部零的个数
//link:https://www.lintcode.com/problem/trailing-zeros/description


#include<iostream>

using namespace std;

class Solution {
public:
    /*
     * @param n: A long integer
     * @return: An integer, denote the number of trailing zeros in n!
     */
    long long trailingZeros(long long n) {
        // write your code here, try to do it without arithmetic operators.
		return n/5;
    }
};
int main(void){
	//vector<int> test{2,3,4,1,8,5};
	//vector<int> test{2,3,4,1,5};
//	vector<int> test{12,11,10,98,99,25,45,33,95,13,96,97,90};

	Solution solu_t;
	cout<<solu_t.trailingZeros(11)<<endl;
}

