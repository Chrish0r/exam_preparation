#include <stdio.h>
#include <stdlib.h>

struct todo {
    char aufgabe[100];
    int tag;
    int monat;
    int jahr;
    struct todo* next;
};

void leererPuffer() {
    char ch;
    while((ch = getchar()) != '\n' && ch != EOF);
}

// Prototypes

void ausgabe(struct todo* anfang);
struct todo* neues_element(struct todo* anfang);

int main() {
    int wahl;
    struct todo* anfang = NULL; // Anfang der Liste


    do{
        printf("Menue\n");
        printf("1 - Ausgeben der ToDoes\n");
        printf("2 - Eingeben eines neuen Elementes\n");

        printf("0 Beenden\n");
        printf("Bitte geben Sie ihre Wahl ein:\n");

        scanf("%d", &wahl);

        switch(wahl) {
        case 1:
            ausgabe(anfang);
            break;
        case 2:
            anfang = neues_element(anfang);
            break;
        case 0:
            break;
        default:
            printf("Ungueltige Eingabe. Bitte erneut versuchen:\n");
           // break;
        }
    }while(wahl != 0);

    return 0;
}

void ausgabe(struct todo* anfang) {
    struct todo* aktuell = anfang;  //diesen struct_pointer brauchen wir, um durch das struct durchzuiterrieren. Pointer zeigt auf Anfang der Liste bzw. der Struktur,
    int counter = 0;

    printf("Die Liste der ToDoes\n");
    while(aktuell != NULL) {
        counter++;
        printf("%02d: %50s %02d %02d %04d\n",
               counter,
               aktuell -> aufgabe,
               aktuell -> tag,
               aktuell -> monat,
               aktuell -> jahr);
        aktuell = aktuell -> next;
    }
}

struct todo* neues_element(struct todo* anfang) {
    struct todo* neu = NULL;

    neu = (struct todo*)malloc(sizeof(struct todo)); //Speicherplaz fuer diesen Pointer allokieren. Malloc liefert einen void_Pointer, der auf einen beliebigen Datentyp zeigt. Daher vor malloc typ casten (unseren Zieltypen).
    if(neu == NULL) {
        printf("Nicht ausreichend Speicherplatz zur Verfügung.\n");
        return anfang; //einfach alte Liste zurückgeben, da ja kein Speicher für neue Liste zur Verfügung steht.
    } else {
        printf("Geben Sie die Daten ein:\n");

        printf("Aufgabentext: ");
        leererPuffer(); // alternative: fflush(stdin);
        scanf("%99[^\n]", neu->aufgabe);
        //(neu->aufgabe, 100, stdin); // hier problematisch, wiel bei fgets() am Ende immer ein '\n' anhaengt.

        printf("Deadline Tag: ");
        scanf("%d", &(neu->tag));
        printf("Deadline Monat: ");
        scanf("%d", &(neu->monat));
        printf("Deadline Jahr: ");
        scanf("%d", &(neu -> jahr));

        neu->next = anfang;
        return neu; // Neues Element am Anfang der Liste.
    }

}