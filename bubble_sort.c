#include <stdio.h>
void  bubble_sort(int* array, int length) {
    int i, temp;

    while(length--) { //?
        for(i = 0; i < length; i++) {
            if(array[i] > array[i + 1]) {
                temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
            }
        }
    }
}

int main() {
    int a[] = {6, 3, 1, 5, 11, 4, 23, 7, 8, 2};
    int i;

    int laenge = sizeof(a) / sizeof(a[0]);

    bubble_sort(a, laenge);

    for(i = 0; i < laenge; i++) {
        printf("%d  ", a[i]);
    }
    printf("\n");

    return 0;
}