#include <stdio.h>
#include <string.h>

typedef struct _student
{
    char *name;
    char suid[8];
    int numUnits;
} student;

int main(int argc, char const *argv[])
{
    student people[4];
    people[0].name = strdup("Adam");
    printf("%s\n", people[0].name);
    strcpy(people[1].suid, "40415xx");
    if (people[1].suid[7] == '\0')
    {
        printf("\\0!\n");
    }
    return 0;
}
