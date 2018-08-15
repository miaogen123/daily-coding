//https://leetcode.com/problems/unique-paths/description/
//62. Unique Paths
//A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).
//The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).
#include<iostream>
#include<array>
#include<vector>
#include<string.h>



using namespace std;

class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        auto size=piles.size();
        auto start=0;
        int end=size-1;
        auto LeeCount=0;
        auto AlexCount=0;
        bool turns=false;
        auto min=0, max=0;
        for(;start<=end;){
           
			cout<<"1"<<endl;
            if(piles[start]>piles[end]){
                max=piles[start];
                start++;
            }else{
				cout<<"2"<<endl;
                max=piles[end];
                end--;
            }
            
            if(turns==false){
                AlexCount+=max;
            }else{
                LeeCount+=max;
            }
            turns=!turns;
        }  
        if(AlexCount>LeeCount)
            return true;
        return false;
    }
};

int main(void){
	Solution solu_t;
	vector<int> temp={7,8,8,10, 11 };
	cout<<solu_t.stoneGame(temp)<<endl;;
	return 0;
}


