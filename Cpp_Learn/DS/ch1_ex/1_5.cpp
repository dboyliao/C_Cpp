#include <iostream>

using namespace std;

int DivZero(int a, int b, int c){
	if (a<=0 || b<=0 || c<= 0){
		throw "All parameters should be larger than 0.";
	}
	return a + b * c + b / c;
}

int main(){
	try {cout << DivZero(1, 2, 0) << endl;}
	catch (char* e){
		cout << e << endl;
	}
	return 0;
}