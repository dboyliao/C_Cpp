#include <stdio.h>
#include <malloc.h>

typedef	struct employee
{
	char name[20];
	int number;
	int age;
	int salary;
	struct	employee * next;
}employee;
employee	*Create(int n);
void	List(employee *list);
void	main()
{
	employee	*list;
	list=Create(5);
	List(list);
}
employee	*Create(int n)
{
	int i;
	employee *list;
	employee *p,*q;
	i=0;
	list=p=(employee *)malloc(sizeof(employee));
	while(i<n)
	{
		q=p;
		p=(employee *)malloc(sizeof(employee));
		
		printf("\nInput name:");
		scanf("%s",p->name);
		printf("Input ID:");
		scanf("%d",&p->number);
		printf("Input age:");
		scanf("%d",&p->age);
		printf("Input salary:");
		scanf("%d",&p->salary);

		p->next=NULL;
		q->next=p;
		i++;
	}
	return list;
}
void	List(employee *list)
{
	employee *p=list->next;
	printf("Name\tID\tAge\tSalary\n");
	while(p!=NULL)
	{
		printf("%s\t%d\t%d\t%d\n",p->name,p->number,p->age,p->salary);
		p=p->next;
	}
}
