#include <stdio.h>
using namespace std;
int main(int argc, char* argv[]){

	int aflag = 0, bflag =0, cflag=0;
	int ch;
	while((ch=getopt(argc,argv,"ab:c"))!=-1)
	{
		printf("optind:%d\n",optind);
		switch(ch){
			case 'a':
			cout<<"have option: -a"<<endl;
			aflag = 1;
			break;
			case 'b':
			cout<<"have option: -b"<<endl;
			bflag = 1;
			printf("the argument of -b is %s\n",optarg);
			break;
			case 'c':
			cout<<"have option: -c"<<endl;
			cflag=1;
			break;
			case'?':
			printf("Unknown option:%c\n",(char)optopt);
			break;
			}
	}	
	return 0;
}
