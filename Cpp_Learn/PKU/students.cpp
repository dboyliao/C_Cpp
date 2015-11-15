#include <iostream>
#include <cstdio>

class Student
{
  char *name;
  int age;
  char *s_id;
  int grade1;
  int grade2;
  int grade3;
  int grade4;

  public:
    Student(char *name_, int age_, char *s_id_, int grade1_, int grade2_, int grade3_, int grade4_)
    {
      name = name_;
      age = age_;
      s_id = s_id_;
      grade1 = grade1_;
      grade2 = grade2_;
      grade3 = grade3_;
      grade4 = grade4_;
    }
    void printStudent()
    {
      int sum = grade1 + grade2 + grade3 + grade4;
      int avg = sum / 4;
      std::cout << name << "," << age << "," << s_id << "," << avg << std::endl;
    }
};

int main()
{
  char name[10];
  int age;
  char s_id[5];
  int grade1;
  int grade2;
  int grade3;
  int grade4;
  std::cout << "Please enter the student data.(seperated by ',')" << std::endl;
  scanf("%[^,],%d,%[^,],%d,%d,%d,%d", name, &age, s_id, &grade1, &grade2, &grade3, &grade4);
  Student s(name, age, s_id, grade1, grade2, grade3, grade4);
  std::cout << "s initialized!" << std::endl;
  s.printStudent();
  return 0;
}