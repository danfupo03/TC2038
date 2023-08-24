#include <iostream>

using namespace std;

/**
 * @brief Merge two subarrays of arr[].
 * 
 * @param arr[] Array to be sorted.
 * @param left First index of the array.
 * @param middle Middle index of the array.
 * @param right Last index of the array.
 * 
 * @return void
 * 
 * @complexity O(n)
**/
void merge(int arr[], int left, int middle, int right)
{
    int n1 = middle - left + 1;
    int n2 = right - middle;

    int L[n1];
    int R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[middle + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] >= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/**
 * @brief Sorts an array using merge sort.
 * 
 * @param arr[] Array to be sorted.
 * @param left First index of the array.
 * @param right Last index of the array.
 * 
 * @return void
 * 
 * @complexity O(n log n)
**/
void mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int middle = left + (right - left) / 2;

        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);

        merge(arr, left, middle, right);
    }
}

int main()
{
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int size = sizeof(arr) / sizeof(arr[0]);

    cout << "\nOriginal Array: [ ";

    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << "]" << endl;

    mergeSort(arr, 0, size - 1);

    cout << "Sorted Array: [ ";
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << "]\n" << endl;
    return 0;
}