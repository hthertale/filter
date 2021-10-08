#include <stdio.h>

int main(void)
{
    int array[6] = {0, 1, 2, 3, 4, 5};
    int tmp;
    int start = 0;
    int end = 5;
    while (start < end)
    {
        tmp = array[start];
        array[start] = array[end];
        array[end] = tmp;
        start++;
        end--;
    }
    for (int i = 0; i < 6; i++)
    {
        printf("%i", array[i]);
    }
    printf("\n");
}