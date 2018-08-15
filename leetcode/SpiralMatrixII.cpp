//https://leetcode.com/problems/spiral-matrix-ii/description/
#include<vector>
#include<iostream>

using namespace std;

//更优化算法
class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> ans(n, vector<int>(n));
        int left = 0, right = n - 1, top = 0, bottom = n - 1;
        int cur = 0;
        while(left <= right && top <= bottom){
            for(int i = left; i <= right; ++i)
                ans[top][i] = ++cur;
            if(++top > bottom) break;
 
            for(int i = top; i <= bottom; ++i)
                ans[i][right] = ++cur;
            if(--right < left) break;
            
            for(int i = right; i >= left; --i)
                ans[bottom][i] = ++cur;
            if(--bottom < top) break;
            
            for(int i = bottom; i >= top; --i)
                ans[i][left] = ++cur;
            ++left;
        }
        return ans;
    }
	//end更优化算法

class Solution {
public:
   vector<vector<int>> generateMatrix(int n) {
	   vector<vector<int>>  temp_flag_to_initialize_the_private(n+2, (vector<int>(n+2, -1)));
	   flag=std::move(temp_flag_to_initialize_the_private);
	   init(n);

	   auto stat=0;
		count=1;
	   auto next_i=1, next_j=1;
	   while(true){
	   switch(stat){
		   case 0:
			   //向右
			   for(;flag[next_i][next_j]==0;next_j++, count++){
					flag[next_i][next_j]=count;
			   }
			   next_j--;
			   if(IsEnd(next_i, next_j)){
				   stat=4;
			   }else{
				   stat=1;
			   }
			   next_i++;
				cout<<"0"<<endl;
				break;
		   case 1:
			   //向下

			   for(;flag[next_i][next_j]==0;next_i++, count++){
					flag[next_i][next_j]=count;
			   }
			   next_i--;
			   if(IsEnd(next_i, next_j)){
				   stat=4;
			   }else{
				   stat=2;
			   }
			   next_j--;
				cout<<"1"<<endl;
				break;
		   case 2:
			   //向左
			   for(;flag[next_i][next_j]==0;next_j--, count++){
					flag[next_i][next_j]=count;
			   }
			   next_j++;
			   if(IsEnd(next_i, next_j)){
				   stat=4;
			   }else{
				   stat=3;
			   }
			   next_i--;
				cout<<"2"<<endl;
				break;
		   case 3:
			   //向上
				cout<<"7"<<endl;
				cout<<next_i<<"\t"<<next_j<<endl;
			   for(;flag[next_i][next_j]==0;next_i--, count++){
					flag[next_i][next_j]=count;
			   }
			   next_i++;
				cout<<"7"<<endl;
				for(const auto & first:flag){
					for(const auto & second:first){
						cout<<second<<"\t";
					}
					cout<<endl;
				}
				cout<<next_i<<"\t"<<next_j<<endl;
				try{
				   if(IsEnd(next_i, next_j)){
					   stat=4;
				   }else{
					   stat=0;
				   }
				}catch (std::exception& e){
					cout<<e.what()<<endl;
				}
			    next_j++;
				cout<<"3"<<endl;
				break;
		   case 4:
				vector<vector<int>> temp;
				auto to_expel_1nd_last=0;
				for(auto & first:flag){
					if(to_expel_1nd_last!=0&&to_expel_1nd_last!=n+1)
						temp.push_back(std::move(vector<int>(std::begin(first)+1, std::end(first)-1)));
					to_expel_1nd_last++;
				}
				return temp;
				break;
	   }

	   }
    }
   inline bool IsEnd(int  next_i, int next_j){
	   if(
			   (flag[next_i+1][next_j]==-1||flag[next_i+1][next_j]>0)&&
			   (flag[next_i-1][next_j]==-1||flag[next_i-1][next_j]>0)&&
			   (flag[next_i][next_j+1]==-1||flag[next_i][next_j+1]>0)&&
			   (flag[next_i][next_j-1]==-1||flag[next_i][next_j-1]>0)
			)
				
		return cout<<next_i<<"\t"<<next_j<<endl,true;
	   else
		   return false;
   }
   void init(int n){
	    for(auto i=1;i<n+1;i++)
			for(auto j=1;j<n+1;j++){
				flag[i][j]=0;
			}
   }
private:
	vector<vector<int>> flag;
	int count;
};
int main(void){
	Solution solu_t;
	auto temp=0;
	while(cin>>temp){
		auto ret_val=solu_t.generateMatrix(temp);
		for(const auto & first:ret_val){
			for(const auto & second:first){
				cout<<second<<"\t";
			}
			cout<<endl;
		}
	}
	return 0;
}

