#include <stdio.h>

double kurs_durchschnitt(double* kurswerte, int laenge) {
    int i;
    double summe = 0., durchschnitt;

    for(i = 0; i < laenge; i++) {
        summe += kurswerte[i];
    }
    durchschnitt = summe / laenge;

    return durchschnitt; // alternativ direkt, return summe / laenge;
}

int main() {

    double k[] = {120., 150., 80., 14., 110., 65., 99., 180., 140., 55.};

    printf("Der Durchschnittskurs betraegt: %lf\n", kurs_durchschnitt(k, 10));

    return 0;
}