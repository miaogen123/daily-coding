//给定一个正整数a，找到最小的正整数b，它的每个数字相乘之后等于a。 如果没有答案，或者答案不符合32位整数，则返回0
//https://www.lintcode.com/problem/minimum-factorization/description
#include<iostream>

using namespace std;

class Solution {
public:
    /**
     * @param a: a positive integer
     * @return: the smallest positive integer whose multiplication of each digit equals to a
     */
    int smallestFactorization(int a) {
        // Write your code here
		int num_container[32]={0};
		auto j=0;
		auto flag=false;
		auto count=0;
		while(!flag){
			for(j=9;j>0;j--){
				if(a%j==0){
					num_container[count]=j;
					count++;
					//not find
					if(count>31)
						return 0;
					a/=j;
					if(a==1)
						flag=true;
					break;
				}
			}
		}
		//for(const auto &temp:num_container)
		//	cout<<temp<<"\t";
		//cout<<endl;
		//cout<<"count="<<count<<endl;

		//sort num_container and  output
		for(auto p=0;p<count;p++){
			auto min=num_container[p];
			for(auto q=p;q<count;q++){
				if(num_container[q]<min)
					std::swap(min, num_container[q]);
			}
			num_container[p]=min;
		}
		//for(const auto &temp:num_container)
		//	cout<<temp<<"\t";
		//cout<<endl;
		unsigned long sum=num_container[0];
		for(auto p=0;p<count-1;p++)
			sum=sum*10+num_container[p+1];
		return (sum>2147483648)?0:sum;
    }
};

int main(void){
	Solution solu;
	while(1){
		auto temp=0;
		cin>>temp;
		cout<<solu.smallestFactorization(temp)<<endl;
	}
}

