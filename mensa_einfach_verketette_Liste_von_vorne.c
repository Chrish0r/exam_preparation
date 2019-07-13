#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 4

typedef enum {VEGAN = 1, VEGETARISCH, GLUTENFREI, ALLERGENFREI} Kennzeichnung;

typedef struct Gericht {
    int energiegehalt;
    char* name;
    int preis;
    Kennzeichnung kennzeichnungen[MAX];
    int speisenummer;
    struct Gericht* nachfolger;
} Gericht;

Gericht* erzeuge_gericht(int energie, char* name, int preis, Kennzeichnung kenn[], int kenn_anzahl) {
    int i;
    static int naechste_nummer = 1;

    Gericht* gericht = malloc(sizeof(Gericht));

    if(gericht == NULL) { //Falls nicht genug Speicherplatz vorhanden ist
        return NULL;
    }

    gericht->energiegehalt = energie;
    gericht->name = malloc(strlen(name) + 1);
    if(gericht->name == NULL) {
        free(gericht);
        return NULL;
    }
    strcpy(gericht->name, name);
    gericht->preis = preis;

   for(i = 0; i < MAX; i++) {  // geht nicht einfach strcpy(gericht->kennzeichnungen, kenn);
        if(i < kenn_anzahl) {
            gericht->kennzeichnungen[i] = kenn[i];
        } else {
            gericht->kennzeichnungen[i] = 0; //fertig mit enum Kennzeichnung array
        }
    }
    gericht->speisenummer = naechste_nummer;
    naechste_nummer++;

    return gericht;
}

int vergleiche_gerichte(Gericht* g1, Gericht* g2) {
    if(g1->energiegehalt != g2->energiegehalt) {
        return g1->energiegehalt - g2->energiegehalt;
    } else {
        return strcmp(g1->name, g2->name);
    }
}

void hinzufuegen_gericht(Gericht** anker, Gericht* gericht) {
    while(*anker != NULL && vergleiche_gerichte(*anker, gericht) < 0) {
        anker = &(*anker)->nachfolger;
    }
    gericht->nachfolger = *anker;
    *anker = gericht;
}

void print_speisekarte(Gericht* anker) {
    while(anker != NULL) {
        char trennzeichen = '\0';
        int i;

    printf("\n");
    printf("%d. %s\n", anker->speisenummer, anker->name);
    printf("Kennzeichnungen:");

    for(i = 0; i < MAX; i++) {
        switch(anker->kennzeichnungen[i]) {
            case VEGAN: printf("%c vegan", trennzeichen); trennzeichen = ','; break;
            case VEGETARISCH: printf("%c vegetarisch", trennzeichen); trennzeichen = ','; break;
            case GLUTENFREI: printf("%c glutenfrei", trennzeichen); trennzeichen = ','; break;
            case ALLERGENFREI: printf("%c allergenfrei", trennzeichen); trennzeichen = ','; break;
        }
    }
    printf("\n");
    printf("   %d kcal\n", anker->energiegehalt);
    printf("   %5.2lf EUR\n", anker->preis/100.0);  //wieder zurues auf EUR und auf double mit 2 Nachkommastellen
    printf("\n");

    anker = anker->nachfolger; // geht in der Liste zur nächsten Nutzlast weiter (analog: i = i + 1 aka i++;
    }
}

int enthaelt_kennzeichnung(Gericht* g, Kennzeichnung k) {
    int i;

    for(i = 0; i < MAX; i++) {
        if(g->kennzeichnungen[i] == k) { // INTUITION => Nochmal: ein enum-Element ist quasi wie ein einizges char-Zeichen/Buchstabe.
                return 1;
        }
    }
    return 0;
}

Gericht* finde_gericht(Gericht* anker, Kennzeichnung kennzeichnung) { // 'kennzeichnung' ist hier EIN Zeichen des Datentyps Kennzeichnung (was ein typedefed enum ist)
    while(anker != NULL) {
        if(enthaelt_kennzeichnung(anker, kennzeichnung)) {
            return anker;
        }
        anker = anker->nachfolger;
    }
    return NULL;
}

Gericht* finde_gericht2(Gericht* anker, Kennzeichnung kennzeichnung[], int anzahl_kennzeichnungen) {
    int i, anzahl_counter;

    while(anker != NULL) {
        anzahl_counter = 0;
        for(i = 0; i < anzahl_kennzeichnungen; i++) {
            if(enthaelt_kennzeichnung(anker, kennzeichnung[i])){
                anzahl_counter++;
            }
        }
        if(anzahl_counter == anzahl_kennzeichnungen) {
            return anker;
        }
        anker = anker->nachfolger;
    }
    return NULL;
}

int main() {

    Gericht *liste = NULL;

	Kennzeichnung vg[] = { VEGAN, GLUTENFREI }; // ein array, was aus 2 Zeiches des Datentypes enum Kennzeichnung besteht.
	Kennzeichnung vga[] = { VEGETARISCH, GLUTENFREI, ALLERGENFREI};
	Kennzeichnung ga[] = { GLUTENFREI, ALLERGENFREI};
	Kennzeichnung a[] = {  ALLERGENFREI};

	hinzufuegen_gericht(&liste, erzeuge_gericht(532, "Feuriger Tofueintopf", 240, vga, 3));
	hinzufuegen_gericht(&liste, erzeuge_gericht(377, "Fallobsteintopf mit Pinienkernen", 240, vg, 2));
	hinzufuegen_gericht(&liste, erzeuge_gericht(874, "Wiener Schnitzel in Maispanade", 385, ga+1, 1));
	hinzufuegen_gericht(&liste, erzeuge_gericht(1319, "Gemischter Braten im Speckmantel auf Sahnegemuese mit Kroketten", 680, ga, 2));
	hinzufuegen_gericht(&liste, erzeuge_gericht(532, "Apfelstrudel aus Reismehl", 430, vga, 3));

	print_speisekarte(liste);

	printf("\nSuche nach _einem_ vegetarischen Gericht:\n");
	Gericht *vegetarisch = finde_gericht(liste, VEGETARISCH);
	printf("  %s\n", vegetarisch->name);

	printf("\nSuche nach _einem_ glutenfreien, veganen Gericht:\n");
	Gericht *veg_gfrei = finde_gericht2(liste, vg, 2);
	printf("  %s\n", veg_gfrei->name);

    return 0;
}
