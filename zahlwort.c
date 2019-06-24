#include <stdio.h>

int umgekehrt(int num) {
    int i, reversed = 0, stellen;

    for(i = 0; num != 0; i++) {
        stellen = num % 10;

        reversed += stellen;
        reversed *= 10;

        num /= 10;
    }
    reversed /= 10; //letzte Iteration "bereinigen"

    return reversed;
}

int mystrlen(char* text) {
    int i = 0;

    while(text[i] != '\0') {
        i++;
    }
    return i;
}

/*void mystrcpy(char* t1, char* t2) {
    int i;

    for(i = 0; t2[i] != '\0'; i++) {
            t1[i] = t2[i];
    }
    t1[i] = '\0';
} */

void addstring(char* string, char* s2) {
    int i, versatz;
    versatz = mystrlen(string);

    // mystrcpy(string + versatz, s2);
    for(i = 0; string[i] != '\0'; i++) {
        string[i + versatz] = s2[i];
    }
    string[i + versatz] = '\0';
}



void zahlworte(int zahl, char* array) {
    int i, stelle;
    // *array = '\0';

    if(zahl < 0) {
        addstring(array, "minus ");
        zahl *= (-1);
    }

    zahl = umgekehrt(zahl);

    for(i = 0; zahl != 0; i++) {
        stelle = zahl % 10;

        switch(stelle) {
        case 0:
            addstring(array, "null");
            break;
        case 1:
            addstring(array, "eins");
            break;
        case 2:
            addstring(array, "zwei");
            break;
        case 3:
            addstring(array, "drei");
            break;
        case 4:
            addstring(array, "vier");
            break;
        case 5:
            addstring(array, "fuenf");
            break;
        case 6:
            addstring(array, "sechs");
            break;
        case 7:
            addstring(array, "sieben");
            break;
        case 8:
            addstring(array, "acht");
            break;
        default:
            addstring(array, "neun");
        }

        if(zahl > 10) {
            addstring(array, " ");
        }
        zahl /= 10;
    }
}

int main() {

    char feld[100];
    zahlworte(-123, feld);

    printf("|%s|", feld);

    return 0;
}
