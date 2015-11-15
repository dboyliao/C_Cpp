#include <iostream>
using namespace std;

int DivZero(int a, int b, int c){
	if (a<0 && b<0 && c<0){
		throw 1;
	}
	if (a==0 && b==0 && c==0){
		throw 2;
	}
	return a + b * c + c;
}

void test(int a, int b, int c){
	try{
		cout << DivZero(a, b, c) << endl;
	} catch (int e){
		if (e == 1){
			cout << "All parameters are smaller than 0." << endl;
		} else if (e == 2){
			cout << "All parameters are zero." << endl;
		}
	}
}

int main(){
	test(1, 2, 3);
	test(-1, -1, -2);
	test(0, 0, 0);
	return 0;
}