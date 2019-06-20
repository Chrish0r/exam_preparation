#include <stdio.h>

char pruefziffer(char* old);
void generiere_iban(char alt[], char iban[]);
int mystrlen(char* old_number);

int main() {
    char iban[14];
    char alte_ktonr[] = "67892";

    printf("Alt: %s\n", alte_ktonr);

    generiere_iban(alte_ktonr, iban);

    printf("IBAN: %s\n", iban);

    return 0;
}


char pruefziffer(char* old) {
    int i, pruefziffer, summe = 0;

    for(i = 0; old[i] != '\0'; i++) { // setzte später in main in brackets Wert 10 als Laenge und checke, ob es immer noch geht, oder ob strlen notwendig
        summe += (old[i] - 48);
    }
    pruefziffer = summe % 11;// ToDo: Sonderfall für Rest = 10 = X einstellen
    if(pruefziffer == 10) {
        return'X';
    }
    //printf("Pruefziffer ist %d\n", pruefziffer); testing
    return (pruefziffer + 48); // integer-Wert zurueck in ein "Zahlen"-char umwandeln
}

int mystrlen(char* old_number) {
    int counter = 0;
    while(old_number[counter] != '\0') {
        counter++;
    }
    // printf("Laenge: %d\n", counter);  testing
    return counter;
}

void generiere_iban(char alt[], char iban[]) {
    int i, j, anzahl_nullen;

    iban[0] = 'D';
    iban[1] = 'E';
    iban[2] = pruefziffer(alt);

    anzahl_nullen = 13 - 3 - mystrlen(alt); // 13 ist die Länge der vorgegebenen IBAN (14 - 1 // 1 am Ende ist das '\0'-Zeichen und 3 die bereits vergebenen Stellen.

    for(i = 3; i < (anzahl_nullen + 3); i++) {
        iban[i] = '0'; // oder 48
    }

    for(i = (3 + anzahl_nullen), j = 0; i < 13; i++, j++) {
        iban[i] = alt[j];
    }
    iban[i] = '\0';
}
