#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

int *adder1(int a, int b, int *res)
{
    // ABOUT THIS FUNCTION: base 8 adder 1 bit
    // INPUTS:
    //      a: 1 bit
    //      b: 1 bit
    // OUTPUT:
    //      res[0]: sum
    //      res[1]: carry

    res[0] = 0;
    res[1] = 0;

    if ((a + b) >= 8)
    {
        res[0] = 1;
        res[1] = a + b - 8;
    }
    else
    {
        res[1] = a + b;
    }

    return res;
}

void *adder4(int *a, int *b, int *res)
{
    // ABOUT THIS FUNCTION: base 8 adder 4 bits
    // INPUTS:
    //      a: array of 4 bits
    //      b: array of 4 bits
    // OUTPUT:
    //      res[0:3]: sum
    //      R4: carry (not returned)

    int tmp[2] = {0, 0};
    int R0, R1, R2, R3, R4;

    adder1(a[3], b[3], tmp);
    R0 = tmp[1];
    R1 = tmp[0];

    adder1(a[2], b[2], tmp);
    R1 = tmp[1] + R1;
    R2 = tmp[0];

    adder1(a[1], b[1], tmp);
    R2 = tmp[1] + R2;
    R3 = tmp[0];

    adder1(a[0], b[0], tmp);
    R3 = tmp[1] + R3;
    R4 = tmp[0];

    res[0] = R3;
    res[1] = R2;
    res[2] = R1;
    res[3] = R0;
}

bool exist(int *arr, int n, int value)
{
    // ABOUT THIS FUNCTION: check if "value" existe in "arr"
    // INPUTS:
    //      arr: array
    //      a: length of arr
    //      value: the sought value
    // OUTPUT:
    //      true / false

    for (int i = 0; i < n; i++)
    {
        if (arr[i] == value)
            return true;
    }

    return false;
}

void copy(int *arr1, int *arr2, int length1)
{
    // ABOUT THIS FUNCTION: copy elements of arr1 into arr2
    // INPUTS:
    //      arr1: source array
    //      arr2: destination array
    //      length: length of the source array (arr1)

    for (int i = 0; i < length1; i++)
    {
        arr2[i] = arr1[i];
    }
}

int append(int arr[], int n, int value)
{
    // ABOUT THIS FUNCTION: add "value" to the end of "arr"
    // INPUTS:
    //      arr: array
    //      a: length of arr
    //      value: the value we want to append
    // OUTPUT:
    //      new length of the array

    arr[n] = value;

    return n + 1;
}

void getOne(int *one, int nbr_bits)
{
    // ABOUT THIS FUNCTION: return "1" in a binary format (...0001)

    for (int i = 0; i < nbr_bits - 1; i++)
    {
        append(one, i, 0);
    }
    append(one, nbr_bits - 1, 1);
}
