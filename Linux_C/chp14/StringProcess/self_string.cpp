#include "self_string.h"
//#include <unistd.h>
#include <string.h>
#include <stdlib.h>
//----------------------------------------------------
//
//磞瓃盢pSrcStringいīpDestStringい
//          璝īΘ 玥1玥0
//
//
//----------------------------------------------------
int self_stringcopy(char *pSrcString,char *pDestString)
{
	if(NULL == pSrcString 
		|| NULL== pDestString)
		return -1;
	
	int srclength = strlen(pSrcString);	
	int destlength = sizeof(pDestString);
	
	if(srclength >= destlength)
		return -1;

	int i;
	for(i = 0; i < srclength; i++)
	{
		pDestString[i] = pSrcString[i];
	}
	pDestString[i] = '\0';
	
	return 0;	
}

//
//ノ﹚竡﹃ゑ耕耞方籔ヘ﹃琌单
// 1. type=0,玥纐粄糶
// 2. type=1玥ぃだ糶
//
//
int self_stringcompare(char *pSrcString,char *pDestString,int type)
{
	if(pSrcString == NULL || pDestString == NULL)
		return -1;
	
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

// ﹃糶锣传瞶
// 硄筁typeㄓ北
// 璝0玥锣传糶玥锣传糶
int self_stringChange(char *pSrcString,int type)
{
	if(pSrcString == NULL)
		return -1;

	int length = strlen(pSrcString);
	if(type == 0)
	{
		int i ;
		for(i = 0; i < length; i++)
		{
			if(pSrcString[i] > 'A' && pSrcString[i] < 'Z')
				pSrcString[i] -= 32;
			
		}
	}
	else 
	{
		int i ;
		for(i = 0; i < length; i++)
		{
			if(pSrcString[i] > 'a' && pSrcString[i] < 'z')
				pSrcString[i] += 32;
		}
	}
	return 0;
}

//琩тcode材Ω瞷竚,тぃ玥-1.
int self_stringfindcharfirst(char *pSrcString,char cCode)
{
	if(pSrcString == NULL)
		return -1;

	int length = strlen(pSrcString);
	
	int i;
	for(i = 0; i < length; i++)
	{
		if(pSrcString[i] == cCode)
			return i;
	}
	return -1;
}
//琩т材Ω瞷竚,тぃ玥-1.
int self_stringfindstringfirst(char *pSrcString,char *pSubString)
{
/*	if(pSrcString == NULL || pDestString == NULL)
		return -1;
	
	int srclength = strlen(pSrcString);	
	int destlength = strlen(pDestString);
	
	if(srclength < destlength)
		return -1;
	
	int i = 0;
	for(i = 0; i < srclength; i++)
	{
		if(pSrcString[i] == pSubString[0])
		{
			int j;
			bool flag = true;
			for(j = 1; j < destlength; j++)
			{
				if(pSrcString[i+j] != pSubString[j])
				{
					flag = false;
					break;
				}
			}
			if(flag)
				return i;
		}
	}

  */
	return -1;
}

int self_stringcat(char *pSrcString,char *pCatString)
{
/*	if(pSrcString == NULL || pDestString == NULL)
		return -1;
	
	int srclength = sizeof(pSrcString);	
	int destlength = strlen(pDestString);
	int srcstrlen = strlen(pSrcString);

	if(srclength < destlength+srcstrlen)
		pSrcString = realloc(pSrcString,srclength+destlength);
	
	int i
	for( i= 0; i < destlength; i++)
	{
		pSrcString[i+srclength] = pCatString[i];
	}
	pSrcString[i+srclength]='\0';
	*/
	return 0;
}
