#include<stdio.h>
#include<iostream>
using namespace std;
int sq(int N){	return N*N; }

int main()
{
	const int N=123;
	const int SQ_N = sq(N);
	cout<<"N:"<<N<<endl;
	cout<<"SQ_N:"<<SQ_N<<endl;
	return 0;
}
