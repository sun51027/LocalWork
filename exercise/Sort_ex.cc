#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<int> SORT(vector<int> A,vector<int> B, vector<int> C,int N){
	cout<<"N = "<<N<<endl;
	for(int i=0;i<5;i++){
	  for(int j=i-1;j>=0;j--){
		int tmp_A=0, tmp_B=0,tmp_C=0;
		if(A[j]<A[j+1]){
		tmp_A = A[j];
		A[j] = A[j+1];
		A[j+1]= tmp_A;
		tmp_B = B[j];
		B[j]=B[j+1];
		B[j+1] = tmp_B;
		tmp_C = C[j];
		C[j] = C[j+1];
		C[j+1]=tmp_C;
		}
		else if(A[j]==A[j+1]){
		     if(C[j]<C[j+1]){
			tmp_A = A[j];
	                A[j] = A[j+1];
        	        A[j+1]= tmp_A;
                	tmp_B = B[j];
           	        B[j]=B[j+1];
                	B[j+1] = tmp_B;
			tmp_C = C[j];
             	        C[j] = C[j+1];
	                C[j+1]=tmp_C;
			}
			}
	   }
	}
	cout<<"in function"<<endl;
	vector<int> result_B;
/*	for(int i=0;i<5;i++){
	cout
	}
*/	return B;//shall return an array
}
	
int main(){
	vector<int> a{3,6,2,7,2};
	vector<int> c{5,2,3,4,8};
	vector<int> b{1,2,3,4,5};// big->small: 42153
	vector<int> B_;
	int n=5;
	B_ =  SORT(a,b,c,n);
	cout<<"return from function?"<<endl;
	for(int i=0;i<5;i++){
		cout<<B_[i]<<endl;
	}

}

