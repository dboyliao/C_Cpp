#include <iostream>

using namespace std;

int Max(int a, int b){
	if (a>b) return a;
	else return b;
}

int main(){
	cout << Max(3, 6);
	return 0;
}