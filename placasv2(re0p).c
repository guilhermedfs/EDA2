#include <stdio.h>
#include <stdlib.h>

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
void insertionSort(int *arr, int low, int n)
{
    for (int i = low + 1; i <= n; i++)
    {
        int value = arr[i];
        int j = i;

        while (j > low && arr[j - 1] > value)
        {
            arr[j] = arr[j - 1];
            j--;
        }
 
        arr[j] = value;
    }
}
 
int partition(int *a, int low, int high)
{
    int pivot = a[high];
 
    int pIndex = low;

    for (int i = low; i < high; i++)
    {
        if (a[i] <= pivot)
        {
            swap(&a[i], &a[pIndex]);
            pIndex++;
        }
    }

    swap (&a[pIndex], &a[high]);
 
    return pIndex;
}
 
void quicksort(int *a, int low, int high)
{
    if (low >= high) {
        return;
    }
 
    int pivot = partition(a, low, high);
 
    quicksort(a, low, pivot - 1);
 
    quicksort(a, pivot + 1, high);
}
 
void optimizedQuicksort(int *A, int low, int high)
{
    while (low < high)
    {
        if (high - low < 10)
        {
            insertionSort(A, low, high);
            break;
        }
        else {
            int pivot = partition(A, low, high);
 
            if (pivot - low < high - pivot)
            {
                optimizedQuicksort(A, low, pivot - 1);
                low = pivot + 1;
            }
            else {
                optimizedQuicksort(A, pivot + 1, high);
                high = pivot - 1;
            }
        }
    }
}

int main() {
    int num;
    int n, *v, cont = 0;

    v = malloc(1 * sizeof(int));
    
    while(scanf("%d %d", &n, &num) != EOF){
        if(n == 1){
            v = realloc(v, 1);
            v[cont] = num;
            cont++;
        }
        if(n == 2){
            optimizedQuicksort(v, 0, sizeof(v) - 1);
            for(int i = 0; i < num; i++){
                if(i == n - 1){
                    printf("%d", v[i]);
                }
                else{
                    printf("%d ", v[i]);
                }
                printf("/n");
            }
        }
    }

return 0;
}