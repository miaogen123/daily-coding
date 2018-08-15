//给出一个不含重复数字的排列，求这些数字的所有排列按字典序排序后该排列的编号。其中，编号从1开始。
//link:https://www.lintcode.com/problem/permutation-index/description

#include<typeinfo>
#include<iostream>
#include<array>
#include<vector>

using namespace std;

class Solution {
public:
    /**
     * @param A: An array of integers
     * @return: A long integer
     */
    long long permutationIndex(vector<int> &A) {
        // write your code here
		auto B(A);
		auto min=B[0];
		//constexpr unsigned long long array_size=A.size();
		array<int,100> num_count;
		for(auto i=0;i<B.size();i++){;
			min=B[i];
			for(auto j=i;j<B.size();j++){
				if(B[j]<min){
					swap(B[i], B[j]);
					min=B[i];
				}
			}
			num_count[i]=min;
		}
		
		//for(const auto& temp:num_count){
		//	cout<<temp<<"\t";
		//}
		//cout<<endl;

		//get the position
		long long sum=0;
		auto nums=A.size();
		for(int count1=0;count1<A.size();count1++){
			for(auto i=0;i<A.size();i++){
				if(num_count[i]==A[count1]){
					//cout<<"index"<<endl;
					//cout<<i<<count1<<endl;
					long long count=1;
					for(int j=nums-1;j>0;j--)
						count*=j;
					//cout<<"count_1="<<count<<endl;
					int min_count=0;
					for(auto temp=0;temp<i;temp++){
						if(num_count[temp]<num_count[i])
							min_count++;
						//cout<<num_count[temp]<<"\t"<<num_count[i]<<endl;
						//cout<<min_count<<endl;
					}
					//cout<<"test"<<endl;
					//for(const auto& temp:num_count){
					//	cout<<temp<<"\t";
					//}
					//cout<<endl;

					count*=min_count;
					sum+=count;
					//cout<<"count="<<count<<endl;
					//cout<<"sum="<<sum<<endl;
					num_count[i]=10000;

				}
			}
			nums--;
			//cout<<"here"<<endl;
		}
		return sum+1;
    }

};

int main(void){
	//vector<int> test{2,3,4,1,8,5};
	//vector<int> test{2,3,4,1,5};
//	vector<int> test{12,11,10,98,99,25,45,33,95,13,96,97,90};
	vector<int> test{22,7,15,10,11,12,14,8,9,1,2,3,6,5,4};

	Solution solu_t;
	cout<<solu_t.permutationIndex(test)<<endl;
}

