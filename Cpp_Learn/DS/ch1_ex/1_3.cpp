#include <iostream>
#include <fstream>

using namespace std;

int main(){
	ofstream outFile("my.out", ios::out);
	if(!outFile){
		cerr << "Cannot open my.out" << endl;
		return 1;
	}
	int n=50;float f=20.3;
	outFile << "n:" << n << endl;
	outFile << "f:" << f << endl;
	return 0;
}