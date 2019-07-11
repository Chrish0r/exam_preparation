#include <stdio.h>

void  minmax(int* array, int laenge, int* min, int* max) { // laenge entspricht Anzahl der Elemente innerhalb dem Array.
    int i;

    *min = array[0];
    *max = array[0];

    for(i = 0; i < laenge; i++) {
        if(array[i] < *min) {
            *min = array[i];
        }
        if(array[i] > *max) {
            *max = array[i];
        }
    }
}

int main() {

    int daten[] = {1, 32, 33, 23, 11, 98, 11, 255};

    int min, max;

    minmax(daten, sizeof(daten)/sizeof(int), &min, &max);

    printf("Minimum = %d, Maximum = %d\n", min, max);

    return 0;
}
