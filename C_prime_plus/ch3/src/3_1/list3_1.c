#include <stdio.h>

int main(void)
{
    float weight;
    float value;

    printf("Please enter your weight in kg: ");
    scanf("%f", &weight);
    printf("weight: %f", weight);

    value = 1700 * weight;
    printf("Money: %.2f.\n", value);
    return 0;
}
