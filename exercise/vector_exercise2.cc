#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
int main(){

	vector<pair<int,int>> a;
	int arr[] = {10,30,20,60};
	int arr2[] = {40, 50, 90,10};
	for(int i=0;i<4;i++){
		a.push_back(make_pair(arr[i],arr2[i]));
	}
	cout<<a.size()<<endl;	
	cout<<"before resize"<<endl;
	for(int i=0;i<4;i++){
	cout<<"< "<<a[i].first<<", "<<a[i].second<<">"<<endl;
	}
/*	sort(a.begin(),a.end());
	cout<<"after sorting"<<endl;
        for(int i=0;i<4;i++){
        cout<<"< "<<a[i].first<<", "<<a[i].second<<">"<<endl;
        }

*/

	a.resize(5);
  	cout<<"after resize"<<endl;
        for(int i=0;i<4;i++){
        cout<<"< "<<a[i].first<<", "<<a[i].second<<">"<<endl;
        }
	cout<<a.size()<<endl;	
	
	a.push_back(make_pair(99,98));
	cout<<"after new push_back"<<endl;
	
	cout<<a.size()<<endl;	

/*        sort(a.begin(),a.end());
        cout<<"after sorting"<<endl;
        for(int i=0;i<4;i++){
        cout<<"< "<<a[i].first<<", "<<a[i].second<<">"<<endl;
        }
*/
	

//	a.clear();	
//	cout<<a.size()<<endl;	


}
