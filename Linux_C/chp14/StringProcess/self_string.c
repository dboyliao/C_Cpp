#include "self_string.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
//----------------------------------------------------
//
//功能描述：將pSrcString中的值拷貝到pDestString中
//          若拷貝成功， ，則返回大於1的值，否則返回0
//
//
//----------------------------------------------------
int self_stringcopy(char *pSrcString,char *pDestString)
{
	if(NULL == pSrcString)
		return 0;
	
	int srclength = strlen(pSrcString);	

	int i;
	for(i = 0; i < srclength; i++)
	{
		pDestString[i] = pSrcString[i];
	}
	
	return 1;	
}

//
//用於定義字串比較，判斷源與目的字串是否相等
// 1. type=0,則默認大小寫
// 2. type=1，則不分大小寫
//
//
int self_stringcompare(char *pSrcString,char *pDestString,int type)
{
	if(pSrcString == NULL || pDestString == NULL)
	{
		return -1;
	}
	int srclength = strlen(pSrcString);	
	int destlength = strlen(pDestString);
	
	if(srclength != destlength)
		return -1;

	if(type == 0)
	{
		int i ;
		for(i = 0; i < srclength; i++)
		{
			if(pSrcString[i] != pDestString[i])
				return -1;
		}
	}
	else
	{
		int i ;
		for(i = 0; i < srclength; i++)
		{
			if(pSrcString[i] != pDestString[i]
				&& pSrcString[i] != pDestString[i]+32
				&& pSrcString[i] != pDestString[i]-32)
				return -1;
		}
	}
	return 0;
}
