//--------------------------------------------------------------------
//
//文件：self_string.h
//描述：用於實現自訂的字串處理庫
//
//--------------------------------------------------------------------
#ifndef SELF_STRING_
#define SELF_STRING_

//用於定義字串拷貝，將源字串中的值拷貝到目的串中
int self_stringcopy(char *pSrcString,char *pDestString);

//用於定義字串比較，判斷源與目的字串是否相等
// 1. type=0,則默認大小寫
// 2. type=1，則不分大小寫
int self_stringcompare(char *pSrcString,char *pDestString,int type);

//用於定義字元串連接，通過type類型來判斷，連接的方式
// 1. type=0,則連接到開頭
// 2. type=-1,則連接到結尾
// 3.type=X,X<strlen(pStrString)的值，則連接到源串的指定字元位置
int self_stringcat(char *pSrcString,char *pCatString,int type);

// 字串大小寫轉換原理，通過type來控制，若為0，則全轉換為小寫，否則全轉換為大寫
int self_stringChange(char *pSrcString,int type);

//查找code第一次出現的位置,找不到，則返回-1.
int self_stringfindcharfirst(char *pSrcString,char cCode);

//查找第一次出現的位置,找不到，則返回-1.
int self_stringfindstringfirst(char *pSrcString,char *pSubString);


#endif
