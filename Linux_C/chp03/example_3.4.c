
#include <stdio.h>

struct	person
{
char	name[20];
char	sex;
int	age;
int	height;
int	weight;
};

void  main()
{
struct	person	person1;
strcpy(person1.name,"Li Ming");
person1.sex = 'M';
person1.age = 26;
person1.height = 178;
person1.weight = 135;
printf("%s:\nsex:%c\nage:%d\nheight:%d\n weight:%d\n", person1.name, person1.sex, person1.age, person1.height, person1.weight);
}


