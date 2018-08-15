//https://leetcode.com/problems/unique-paths/description/
//62. Unique Paths
//A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).
//The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).
#include<iostream>
#include<array>
#include<string.h>



using namespace std;


class Solution {
public:
 unsigned long long uniquePaths(int m, int n) {
		unsigned long long arr[m][n];
		for(auto i=0;i<m;i++)
			memset(arr[i],0, n*sizeof(int));
		for(auto i=0;i<m;i++){
			arr[i][0]=1;
			arr[i][n-1]=1;
		}
		for(auto i=0;i<n;i++){
			arr[0][i]=1;
			arr[m-1][i]=1;
		}
		for(auto i=1;i<m;i++){
			for(auto j=1;j<n;j++){
				arr[i][j]=arr[i-1][j]+arr[i][j-1];
			}
		}
		//more brief answer
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp (m, vector<int>(n, 1));
        for (int i = 1;i<m;i++) {
            for (int j = 1; j<n; j++) {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
        return dp[m-1][n-1];
    }
};
		//end more brief answer
		//for(auto i=0;i<m;i++){
		//	for(auto j=0;j<n;j++){
		//		cout<<arr[i][j]<<"\t";
		//	}
		//	cout<<endl;
		//}
		return arr[m-1][n-1];
	}
};

int main(void){
	Solution solu_t;
	cout<<solu_t.uniquePaths(100,99)<<endl;;
	return 0;
}


