//给定一个若干整数的排列，给出按正数大小进行字典序从小到大排序后的下一个排列。
//link:https://www.lintcode.com/problem/next-permutation-ii/description


#include<vector>
#include<iostream>

using namespace std;

class Solution {
public:
    /**
     * @param nums: An array of integers
     * @return: nothing
     */
    void nextPermutation(vector<int> &nums) {
        // write your code here
		auto size=nums.size();
		if(size==1){
			std::cout<<"["<<nums[0]<<"]";
			return;
		}
		for(auto i=size-1;i>0;i--){
			if(nums[i]>nums[i-1]){
				auto temp=i;
				for(auto j=i;j<size;j++){
					if(nums[j]>nums[i-1]&&nums[j]<=nums[temp])
						temp=j;
					if(j==size-1){
						swap(nums[i-1], nums[temp]);
						for(auto p=i, q=size-1;p<q;p++, q--)
							swap(nums[p], nums[q]);
					}
				}
				break;
			}
			if(i==1)
				for(auto p=i-1, q=size-1;p<q;p++, q--)
					swap(nums[p], nums[q]);
		}
		std::cout<<"[";
		for(const auto&num: nums)
			cout<<num;
		std::cout<<"]";
    }
};

int main(void){
	Solution solu_t;
	//vector<int> temp{9,8,7,2,3,4,5,6};
	//vector<int> temp{3,2,1};
	vector<int> temp{2,3,1,3,3};
	//vector<int> temp{1,4,3,2};
	solu_t.nextPermutation(temp);
}


