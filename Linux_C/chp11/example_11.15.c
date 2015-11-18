#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
	int array1[4]={11,16,47,52};
	int array2[6]={3,6,9,21,22,77};
	int result[10];
	int i;
	merge(array1,array1+4,array2,array2+6,result);
	cout<<"升序合併後，元素順序為：";
	for(i=0;i<10;i++)
		cout<<result[i]<<"   ";
	cout<<endl;
	reverse(array1,array1+4);//數組array1和array2分別反序
	reverse(array2,array2+6);
	merge(array1,array1+4,array2,array2+6,result,greater<int>());
	cout<<"降序合併後，元素順序為：";
	for(i=0;i<10;i++)
		cout<<result[i]<<"   ";
	cout<<endl;	
	return 1;
}