#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Big
{
public:
	Big(){cout<<"a= "<<a_<<",b= "<<b_<<",c= "<<c_<<",d= "<<d_<<",e= "<<e_<<endl;}
	Big(int a,int b,int c,int d, int e):a_(a),b_(b),c_(c),d_(d),e_(e){
		cout<<"a= "<<a<<",b= "<<b<<",c= "<<c<<",d= "<<d<<",e= "<<e<<endl;	
	}
	Big(const Big &ex):a_(ex.a_),b_(ex.b_),c_(ex.c_),d_(ex.d_),e_(ex.e_){}
	~Big(){}
	
  int a_;
  int b_;
  int c_;
  int d_;
  int e_;
  bool operator<(const Big &ex)const{
  if(a_ >ex.a_ ) {
	cout<<"a= "<<a_<<",b= "<<b_<<",c= "<<c_<<",d= "<<d_<<",e= "<<e_<<endl;

	return true;
	}
  else if(a_ == ex.a_){
       if(b_ > ex.b_) return true;
	else return false;
  }
  else{
	cout<<"a= "<<a_<<",b= "<<b_<<",c= "<<c_<<",d= "<<d_<<",e= "<<e_<<endl;
 
	return false;

	}
  }
  void print(){
	cout<<"a= "<<a_<<",b= "<<b_<<",c= "<<c_<<",d= "<<d_<<",e= "<<e_<<endl;
	}
		
};
int main(){
	vector<Big> a;
	a.push_back(Big( 3,4,5,1,2));
	a.push_back(Big( 9,2,1,7,6));
	a.push_back(Big( 8,2,6,3,7));
	a.push_back(Big( 9,3,2,7,1));
	cout<<"No. of candidates: "<<a.size()<<endl;
	sort(a.begin(),a.end());
	cout<<"which is the biggest candidates?"<<endl;
	a[0].print();
	
}
