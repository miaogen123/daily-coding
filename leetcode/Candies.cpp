//https://codejam.withgoogle.com/codejam/contest/6364486/dashboard
//from the code ham

#include<set>
#include<exception>
#include<iostream>
#include<vector>
#include<cstdio>


using namespace std;


using VI=vector<int>;
using LL=long long;
using VLL=vector<LL>;

namespace{
	const LL MAX_MINUS_64=-922337203685477580;
}

VI getFlag(VLL& candies){
	LL size=candies.size();
	VI flag(size, false);
	for(auto i=0;i<size;i++){
		if(candies[i]%2==1||candies[i]%2==-1)
			flag[i]=true;
	}
	return flag;
}

void MaxSubArray(VLL & candies, LL oddnum, LL sweetMax)
{
#ifdef DEBUG
	cout<<"start"<<endl;
#endif
	LL size=candies.size();
	VI flag(std::move(getFlag(candies)));
#ifdef DEBUG
	for(const auto& tempVal:flag){
		cout<<tempVal<<"\t";
	}
	cout<<endl;
#endif
	LL maxS=MAX_MINUS_64;
	//LL maxS=~0;
	//maxS=(maxS<<63)|1;
	//cout<<"hello"<<maxS<<endl;
	LL tempMax=0;
	auto oddCount=0;
	LL WinSt=0;
	bool contiFlag=false;
	for(auto i=0;i<size;i++){
		if(tempMax<0){
			oddCount=flag[i];
			if(oddCount>oddnum){
				tempMax=0;
				continue;
			}
			maxS=(maxS>candies[i]||candies[i]>sweetMax)?maxS:candies[i];
			tempMax=candies[i];
			WinSt=i;
		}else{
			if(maxS==sweetMax){
				cout<<maxS<<endl;
				return;
			}
			tempMax+=candies[i];
			while(oddCount+flag[i]>oddnum||tempMax>sweetMax){
				if(flag[WinSt]&&oddCount>0)
					oddCount--;
				tempMax-=candies[WinSt];
				if(WinSt==i){
					contiFlag=true;
					break;
				}
				WinSt++;
			}
			if(maxS>sweetMax){
				cout<<"error:"<<maxS<<">"<<sweetMax<<endl;
				cout<<tempMax<<endl;
				return;
			}
			if(contiFlag){
				WinSt++;
				contiFlag=false;
				continue;
			}
			oddCount+=flag[i];
			maxS=(maxS>tempMax||tempMax>sweetMax)?maxS:tempMax;
		}
	}
	if(maxS<=sweetMax){
		if(maxS==MAX_MINUS_64){
			cout<<"IMPOSSIBLE"<<endl;
			//cout<<"IMPOSSIBLE"<<" the val="<<maxS<<endl;
			return;
		}
		cout<<maxS<<endl;
	}
	else
		cout<<"IMPOSSIBLE"<<endl;
}

int main(void){
	
	freopen("A-large-practice.in", "r", stdin);
	//freopen("outputOddCountLessZero.txt", "w", stdout);
	//freopen("A-small-practice.in", "r", stdin);
	//freopen("testCandy.in", "r", stdin);
	int Case=0;
	cin>>Case;
	for(int j=0;j<Case;j++){
		unsigned int N=0;
		LL oddnum=0, sweetMax=0;
		cin>>N>>oddnum>>sweetMax;
		LL x1, x2, A, B, C, M, L;
		cin>>x1>>x2>>A>>B>>C>>M>>L;
		VLL Si;
		Si.push_back(x1+L);
		Si.push_back(x2+L);
		for(unsigned int i=3;i<N+1;i++){
			LL X=A*x2+B*x1+C;
			X=X%M;
			Si.push_back(X+L);
			std::swap(x1, x2);
			std::swap(x2, X);
		}
		//if(32==j)
		//	for(const auto & tempVAL:Si)
		//		cout<<tempVAL<<"\t";
		//cout<<endl;
		cout<<"Case #"<<j+1<<": ";
		MaxSubArray(Si,oddnum, sweetMax);
	}	
	return 0;
}
