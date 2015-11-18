#include<map>
#include<iostream>
using namespace std;
int main()
{
   map<int,const char*> student;
   map<int,const char*>::iterator mi;
   typedef pair <int,const char*> Pair;
   student.insert(Pair(1001,"sun"));
   student.insert(Pair(1002,"li"));
   student.insert(Pair(1003,"zheng"));
   student.insert(Pair(1004,"zhang"));
   mi=student.find(1003);//查找學號為1003的學生
   if(mi==student.end())
       cout<<"未找到學號為1003的學生"<<endl;
   else
     cout<<mi->first<<"  "<<mi->second<<endl;
   return 1;
}
