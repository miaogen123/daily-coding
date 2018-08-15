//https://code.google.com/codejam/contest/4384486/dashboard
//from the code ham

#include<set>
#include<exception>
#include<iostream>
#include<vector>
#include<cstdio>

using namespace std;

enum class state {white, grep, black};

using VI=vector<int>;
using VVI=vector<vector<int>>;

namespace{
	const int WHITE=0;
	const int GREY=1;
	const int BLACK=2;
}

int dfs(VVI &graph, VI& flag,int& i, set<int>& circle)
{
	flag[i]=GREY;
	circle.insert(i);
	for(auto j=0;j<graph[i].size();j++){
		if(j!=i){
			if(flag[i]==GREY){
				//TODO::record	
				cout<<"here exists a loop"<<endl;
				auto circleEnd=circle.end();
				cout<<endl;
				for(auto i=circle.begin();i!=circleEnd;i++){
					cout<<*i<<"\t";
				}
				cout<<endl;
				return 1;
			}else if(flag[i]==WHITE){
				if(dfs(graph, flag, j, circle)==1)
					return 1;
				circle.erase(i);
				cout<<"erase once"<<endl;
			}
		}
	}
	flag[i]=BLACK;
	return 0;
}

int main(void){
	freopen("test.in", "r", stdin);
	int n=0;
	cin>>n;
	cout<<n;
	set<int> circle;
	for(int j=0;j<n;j++){
		auto planetNum=0;
		cin>>planetNum;
		cout<<planetNum;
		auto c1=0, c2=0;
		vector<vector<int>> graph(planetNum+1, vector<int>{});
		vector<int> flag{0, WHITE};
		for(int k=0;k<planetNum;k++){
			cin>>c1>>c2;
			graph[c1].push_back(c2);
			graph[c2].push_back(c1);
		}
		cout<<endl;
		for(int p=1;p<planetNum+1;p++){
			for(const auto & temp_val:graph[p])
				cout<<temp_val<<"\t";
			cout<<endl;
		}
		for(int i=1;i<n+1;i++){
			if(flag[i]==WHITE){
				auto retVal=dfs(graph,flag,i, circle);
				if(retVal==0)
					throw runtime_error("logic error");
			}
		}
		//system("pause");
	}

	return 0;

}
