#include <stdio.h>

int main(int argc, char* argv[])
{
    int distance = 100;
    float power = 2.345f;
    double super_power = 56789.5432;
    char initial = 'A';
    char first_name[] = "Zed";
    char last_name[] = "Shaw";
    char empty[] = "";
    int hex = 0x11;
    int oct = 011;

	printf("You are %d miles away.\n", distance);
    printf("You have %.3f levels of power.\n", power);
    printf("You have %f awesome super powers.\n", super_power);
    printf("I have an initial %c.\n", initial);
    printf("I have a first name %s.\n", first_name);
    printf("I have a last name %s.\n", last_name);
    printf("My whole name is %s %c. %s.\n",
            first_name, initial, last_name);
    printf("empty string: %s\n", empty);
    printf("hex: %x (decimal %d)\n", hex, hex);
    printf("oct: %o (decimal %d)\n", oct, oct);

    return 0;
}
