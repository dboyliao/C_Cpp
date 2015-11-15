#include <iostream>

void swap(int *a, int i, int j)
{
    int temp;
    temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

void SelectSort(int *a, const int n)
{
    for (int i = 0; i < n; i++)
    {
        int j = i;
        for (int k = i+1; k < n; k++)
            if (a[k] < a[j])j = k;
        swap(a, i, j);
    }
}

int main()
{
    int a[6] = {1, 5, 9, 3, 2, 8};
    SelectSort(a, 6);
    std::cout << a[0] << a[1] << a[2] <<
        a[3] << a[4] << a[5] << std::endl;
    return 1;
}
