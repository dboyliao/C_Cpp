#include<sys/stat.h>
#include<unistd.h>
#include<ftw.h>
int fn(const char *file,const struct stat *st,int flag)
{
if(flag==FTW_D)
printf("%s\n",file);

return 1;
}
int main()
{
	char  buf[80];
	getcwd(buf, sizeof(buf));
ftw(buf,fn,500);
return 1;
}
// #include <sys/stat.h>
// #include <unistd.h>
// #include <ftw.h>
// 
// int  fn(const  char *file, const struct stat *sb, int flag)
// {
// 	if(flag == FTW_D)  
// 		printf("%s --- directory\n", file);
// 	else
// 		printf("%s \n",file);  
// 	return 0;
// }
// 
// int main()
// {
// 	ftw("/etc/X11",fn,500);
// }
