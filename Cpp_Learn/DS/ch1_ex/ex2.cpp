#include <iostream>

using namespace std;

int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

int SumN(int n){
	if (n < 0){
		throw "n must be larger or equal to 0.";
	}
	int result;
	result = 0;
	for (int i=0; i < n; i++){
		result = result + a[i];
	}
	return result;
}

void test(int n){
	try { cout << SumN(n) << endl; }
	catch (char e){
		cout << e << endl;
	}
}

int main(){
	test(3);
	test(10);
	test(-3);
}