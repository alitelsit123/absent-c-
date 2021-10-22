#include <iostream>
#include <cctype>
#include <fstream>
#include <windows.h>
using namespace std;
int main(void){
	string l[10];
	l[0] = "tes";
	l[1] = "tes1";
	l[2] = "tes2";
	l[2] = "tes3";
	for(string m: l){
		cout<<m<<endl;
	}
	int j=0,k=0,p=0,x;
	for(x=0;x<3;x++){
		if(x == 0){
			j = x;
		} else if(x == 1){
			k = x;
		}else if(x == 2){
			p = x;
		}
	}
	for(x=0;x<3;x++){
		cout<<j<<k<<p<<endl;
	}
	
}
