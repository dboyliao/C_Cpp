#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <netdb.h>
#include <signal.h>

typedef  int bool;
#define true 1
#define false 0

typedef struct stu
{
	char name[20];
	char phone[20];
	bool flag;
    struct stu* next;	
} student;

struct stu* Read(struct stu *phead);
void Write(struct stu *phead);

struct stu* Add(struct stu *phead);
struct stu* Find(struct stu *phead);
void Show(struct stu *phead);
void Search(struct stu *phead);
void Delete(struct stu *phead);
void Export(struct stu *phead);
void Modify(struct stu *phead);
void Export(struct stu *phead);

void Help()
{
  printf("==================================================================\n");
  printf("版本號：V1.0\n");
  printf("開發者：my2005lb\n\n\n");
  printf("%-12s %-12s\n","命令名","功能");
  printf("%-12s %-12s\n","add","增加一條記錄");
  printf("%-12s %-12s\n","show","顯示所有記錄");
  printf("%-12s %-12s\n","find","查找一條記錄");
  printf("%-12s %-12s\n","help","顯示説明");
  printf("%-12s %-12s\n","delete","刪除一條記錄");
  printf("%-12s %-12s\n","update","更新一條記錄");
  printf("%-12s %-12s\n","export","數據匯出");
  printf("%-12s %-12s\n","exit","應用程式退出");
  printf("==================================================================\n");
}
 void Scheclle()
 {
    
	 struct stu *head=NULL;
	 head = Read(head);
	 while(true)
	 {
	 
		 printf("\n請輸入操作命令:>");
		 char command[20];
	     scanf("%s",&command);
	
		 if(strcmp(command,"add")==0)
		 {
			 head = Add(head);
		 }
		 else if(strcmp(command,"update")==0)
		 {
			 Modify(head);
		 }
		 else if(strcmp(command,"delete")==0)
		 {
			 Delete(head);
		 }         
		 else if(strcmp(command,"find")==0)
		 {
			 Search(head);
		 }
		 else if(strcmp(command,"help")==0)
		 {
			 Help();
		 }
		 else if(strcmp(command,"export")==0)
		 {
			 Export(head);
		 }
		 else if(strcmp(command,"exit")==0)
		 {
			 Write(head);
			 exit(0);
		 }
		 else if(strcmp(command,"show")==0)
		 {
			 Show(head);
		 }
		 else
		 {
			 printf("對不起，您輸入了不能識別的命令\n");
		 }
	 }
 }
 struct stu* Add(struct stu *phead)
 {
	 struct stu *pnod = NULL;
	 pnod=(struct student *)malloc(sizeof(student));

	 printf("請輸入姓名:");
	 scanf("%s",pnod->name);
	 printf("\n請輸入電話號碼:");
	 scanf("%s",pnod->phone);
	 printf("記錄姓名:%s,電話號碼:%s,將要添加到新資料中\n",pnod->name,pnod->phone);
	 pnod->next=NULL;
	 pnod->flag = true;
	 if(phead==NULL)
	 {        
		phead=pnod;
	 }
     else
	 {		 
		 struct stu *p = NULL;
		 p=phead;
		 while(true)
		 {
			 if(p->next==NULL)
			 {
				 break;
			 }
			 else
			 {
				 p=p->next;
			 }		 
		 }
		 p->next=pnod;	
	 }
	 return phead;
 }
void Show(struct stu *phead)
{
	 printf("姓名\t 電話號碼\t\n");
	 struct stu *ps= NULL;
	 ps=phead;
	 if(phead==NULL)
	 {
		printf("當前沒有任何記錄\n");
			 
	 }
	else
	{		
		while(ps != NULL)
		{
			if( ps->flag)
			{
				printf("%s\t %s\n",ps->name,ps->phone);
			}

			ps=ps->next;
		}
	}
		 
}
struct stu* Find(struct stu *phead)
{
	printf("請輸入要查的姓名:\n");
	char name[20];
	scanf("%s",name);
	struct stu* ps = NULL;
	ps = phead;
	if(ps != NULL)
	{				
		while(ps != NULL)
		{
			if(strcmp(ps->name,name) == 0 && ps->flag)
				break;

			ps=ps->next;
		}
	}
	return ps;
}
void Search(struct stu *phead)
{   
	struct stu *ps = NULL;
	ps = Find(phead);
	if(ps != NULL)
	{
		printf("姓名：%s|電話號碼：%s\n",ps->name,ps->phone);
	}
	else
	{
		printf("查無記錄!\n");
	}
}
void Delete(struct stu *phead)
{
	struct stu *ps = NULL;
	ps = Find(phead);
	if(ps != NULL)
	{
		printf("姓名：%s|電話號碼：%s 記錄將要清除，請確認(yes/no):",ps->name,ps->phone);
		char command[20];
		scanf("%s",command);
		if(strcmp(command,"yes") == 0)
		{
			ps->flag = false;
			printf("記錄清除完畢!\n");
		}		
	}
	else
	{
		printf("查無記錄!\n");
	}
}
void Modify(struct stu *phead)
{
	struct stu *ps = NULL;
	ps = Find(phead);
	if(ps != NULL)
	{
		printf("姓名：%s|電話號碼：%s\n",ps->name,ps->phone);
		char name[20];
		char phone[20];
		printf("請輸入要修改後的名字:");
		scanf("%s",name);
		printf("\n請輸入要修改後的電話號碼:");
		scanf("%s",phone);
		strcpy(ps->name,name);
		strcpy(ps->phone,phone);
		printf("記錄修改完畢!\n");

	}
	else
	{
		printf("查無記錄!\n");
	}
}
void Export(struct stu *phead)
{
	char command[200];
	printf("輸入要匯出的檔案名(.xml):");
	scanf("%s",command);
	FILE *fp = fopen(command,"ab+");
	if(fp == NULL)
	{
		printf("生成檔出錯，無法執行保存操作\n");
		return ;
	}
	fputs("<?xml version=\"1.0\" encoding=\"GB2312\"?>",fp);
	fputs("<recordset>",fp);
	struct stu *ps= NULL;
	ps=phead;
	if(phead==NULL)
	{
		printf("當前沒有任何記錄\n");
	}
	else
	{		
		while(ps != NULL)
		{
			if(ps->flag)
			{
				char value[500];
				sprintf(value,"<record><name>%s<\/name><phone>%s<\/phone><\/record>",ps->name,ps->phone);
				printf("fewfwe\n");
				fputs(value,fp);
			}

			ps=ps->next;
		}
	}
	fputs("<\/recordset>",fp);
	fclose(fp);
}

void Write(struct stu *phead)
{
	remove("data.dat");

	FILE *fp = fopen("data.dat","ab");
	if(fp == NULL)
	{
		printf("生成檔出錯，無法執行保存操作\n");
		return ;
	}
	struct stu *ps= NULL;
	ps=phead;
	if(phead==NULL)
	{
		printf("當前沒有任何記錄\n");
	}
	else
	{		
		while(ps != NULL)
		{
			if(ps->flag)
			{
				fwrite(ps,sizeof(student),1,fp);
			}

			ps=ps->next;
		}
	}
	fclose(fp);
}
struct stu * Read(struct stu *phead)
{
	FILE *fp = fopen("data.dat","rb");
	if(fp == NULL)
	{
		printf("生成檔出錯，無法執行保存操作\n");
		return NULL;
	}

	struct stu *pCurrent= NULL;
	while(true)
	{
		struct stu *pnode= NULL;
		pnode=(student *)malloc(sizeof(student));
		if(fread(pnode,sizeof(student),1,fp) > 0)
		{
			pnode->next = NULL;
			if(phead == NULL)
			{
				pCurrent = pnode;
				phead = pCurrent;
			}
			else
			{
				pCurrent->next = pnode;
				pCurrent = pnode;
			}
		}
		else
		{
			break;
		}
	}
	fclose(fp);
	return phead;
}
main()
{
	Help();	
	Scheclle();
}

