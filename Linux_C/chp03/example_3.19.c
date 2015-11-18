
#include <stdio.h>

struct student
{
int num;
char name[20];
char sex;
int age;
float score;
};  /* 共5個成員 */

void	main()
{
struct student stud;
char numstr[20],ch;  
FILE *fp;

if((fp=fopen("stud.dat","wb"))==NULL) 
{
    printf("can't open file stud.dat\n");
    exit(1);
}

do
{
printf("enter number:"); gets(numstr); stud.num=atoi(numstr);
printf("enter name:"); gets(stud.name);
printf("enter sex:"); stud.sex=getchar(); getchar();
printf("enter age:"); gets(numstr); stud.age=atoi(numstr);
printf("enter score:"); gets(numstr); stud.score=atof(numstr);

fwrite(&stud,sizeof(struct student),1,fp);  
printf("have another student record(y/n)?"); 
ch=getchar(); getchar();
}while(toupper(ch)=='Y'); 
fclose(fp);  
}
