#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
int main(){
	vector<int> number;
	for(int i=0;i<10;i++){
		number.push_back(i);
		cout<<number[i]<<endl;	
	}
	while(!number.empty()){
		int n=number.back();
//		cout<<"n = "<<n<<endl;
		number.pop_back();
//		cout<<"n(pop back) = "<<n<<endl;
	}	
	vector<int> v1={10,20,30,40,50};
	vector<int> v2(v1.begin(),v1.end());
	for(int i=0;i<5;i++)
		cout<<"v2("<<i<<") = "<<v2[i]<<endl;
	cout<<endl;
	vector<int> v3 = v1;
	for(int i=0;i<5;i++)
		cout<<"v3("<<i<<") = "<<v3[i]<<endl;
        cout<<endl;
	vector<int> v4(v1);
        for(int i=0;i<5;i++)
		cout<<"v4("<<i<<") = "<<v4[i]<<endl;
	cout<<endl;
	cout<<"//============6/15 test===========//"<<endl;
	vector<int> cand(20);//array length
	cout<<"cand.size()="<<cand.size()<<endl;
	for(int i=0;i<10;i++){
		cand[i]=i;
	cout<<"cand= "<<cand[i]<<endl;	
	}
	cout<<endl;
	cout<<"****  c_str() copy string into char  ******"<<endl;
	const char *c;
	string s="hello";
	c=s.c_str();
	cout<<c<<endl;
	cout<<"****  find() find something in something  *****"<<endl;
	for(int i=0;i<10;i++){
                number.push_back(i);
//                cout<<number[i]<<endl;
        }
	vector<int>::iterator result = find(number.begin(),number.end(),5);
	if(result==number.end())	cout<<"no"<<endl;
	else 	cout<<"yes"<<endl;
	vector<string> trig;
}

