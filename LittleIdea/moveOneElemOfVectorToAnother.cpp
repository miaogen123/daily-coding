//把一个vector的一个move到另外一个，看看会发生什么，在遍历原来的那个，看会不会发生两个拼在一起的情况

#include<vector>
#include<iostream>

using namespace std;

class Temp{
public:
	Temp(int i):k(i){

	}
	Temp(Temp& rhs){

	}
	Temp(Temp && rhs){
		k=move(rhs.k);
	}
	Temp & operator=(Temp&& rhs){
		Temp temp(2);
		return temp;
	}
	int k;
};

int main(void)
{
	vector<int> VI_1{1,2,3,4,5,6,7,8};
	vector<int> VI_2{9,10,11,12,13,14,15,16};

	//copy
	VI_2[0]=std::move(VI_1[3]);

	cout<<"1"<<endl;
	for(const auto & tempval:VI_1){
		cout<<tempval<<"\t";
	}

	cout<<endl<<"2"<<endl;
	for(const auto & tempval:VI_2){
		cout<<tempval<<"\t";
	}

	vector<Temp> VT_1;
	vector<Temp> VT_2;
	//add
	for(auto i=0;i<5;i++){
		Temp temp(i);
		VT_1.push_back(std::move(temp));
	}

	for(auto i=0;i<5;i++){
		Temp temp(i+10);
		VT_2.push_back(std::move(temp));
	}

	cout<<endl<<"VT_1"<<endl;
	//VT_2[2]=std::move(VT_1[3]);

	for(const auto & val:VT_1)
		cout<<val.k<<"\t";
	cout<<endl;
	cout<<"VT_2"<<endl;
	for(const auto & val:VT_2)
		cout<<val.k<<"\t";
	return 0;
// result
// 1
// 1	2	3	4	5	6	7	8	
// 2
// 4	10	11	12	13	14	15	16	
// VT_1
// 0	1	2	3	4	
// VT_2
// 10	11	12	13	14
}
