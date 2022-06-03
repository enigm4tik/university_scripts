// Author: enigm4tik
// Datum: 21.02.2017 - 28.02.2017
// Description: Design des Tutorials eines Spiels
/* Mit diesem Spiel soll es moeglich sein einen Helden zu erstellen, eine Waffe auszuwaehlen, eine Puppe auszuwaehlen
 * und einen Kampf auszufuehren.
 * Fuer die Moeglichkeiten der Eingabe von falschen Wertebreichen oder Tippfehlern wurde vorgesorgt.
 * Der Kampf ist interaktiv und wird nacheinander ausgefuehrt, man entscheidet sich jeweils nach einem Schlag
 * ob man den naechsten Schlag machen moechte.                                                                      */

#include <iostream>
// Für den Randomizer brauche ich cstdlib
#include <cstdlib>
using namespace std;

// Strukturen
/** Hier kommen die unterschiedlichen Strukturen hinein.**/

// Struktur Hero enthaelt Name, Geschlecht, Alter, Gewicht, Staerke, Waffe und Puppe.
struct hero {
    string name;
    string gender;
    int age;
    int weight;
    int strength;
    string arm;
    string doll;
};

// Struktur Weapon enthaelt Name, Einschraenkung (basierend auf Staerke des Helden) und Schaden.
struct weapon {
    string name;
    int restriction;
    int damage;
};

// Struktur Doll enthaelt Material und Schadenspuffer.
struct doll {
    string material;
    int health;
};


int main() {
    // Held
    // Wenn vom User kein Held ausgesucht wird, ist man Xena.
    // Diese Variablen werden bei der Helderstellung ueberschrieben.
    hero hero1;
    hero1.name = "Xena";
    hero1.gender = "Heldin";
    hero1.age = 10;
    hero1.weight = 60;
    hero1.strength = 3;
    hero1.arm = "Schwert";
    hero1.doll = "Eisen";

    // Waffen
    // Jede Waffe hat spezifische Werte.
    weapon waffe1;
    waffe1.name = "Dolch";
    waffe1.restriction = 1;
    waffe1.damage = 5;

    weapon waffe2;
    waffe2.name = "Knueppel";
    waffe2.restriction = 2;
    waffe2.damage = 7;

    weapon waffe3;
    waffe3.name = "Schwert";
    waffe3.restriction = 3;
    waffe3.damage = 10;

    weapon waffe4;
    waffe4.name = "Bogen";
    waffe4.restriction = 1;
    waffe4.damage = 10;

    // Puppen
    // Jede Puppe hat spezifische Werte.
    doll puppe1;
    puppe1.material = "Stroh";
    puppe1.health = 20;

    doll puppe2;
    puppe2.material = "Holz";
    puppe2.health = 50;

    doll puppe3;
    puppe3.material = "Eisen";
    puppe3.health = 100;

    //Funktionen
    // Hier werden die benutzten Funktionen deklariert.
    int menue();
    int fight(int waffe, int puppe);
    int credits();

    // Variablen für Switch
    int selection;
    cout << "MENUE\n"
            "Um durch das Menue zu navigieren, "
            "gib bitte die entsprechende Zahl ein.\n";
    selection = menue();
    switch(selection) {
        case 1: {// HELDEN ERSTELLUNG
            cout << "Willkommen!\n"
                    "Sag mir, bist du eine [ Heldin ] oder ein [ Held ]?\n";

            cin >> hero1.gender;
            // Abfrage ob Geschlecht richtig ist.
            // Wenn es weder Heldin, heldin, held noch Held ist, dann muss man erneut eingeben.
            while (hero1.gender != "heldin" && hero1.gender != "Heldin" && hero1.gender != "w" && hero1.gender!= "f" && hero1.gender != "held" && hero1.gender != "Held" && hero1.gender !="m") {
                // Nach jeder Eingabe vom User wird der Input nach dem 1. Wort geloescht.
                // Damit entgeht man dem Problem, das weitere Variabeln zu bald aufgefuellt werden.
                // Das wird entweder mit cin.ignore(1000, '\n') oder cin.ignore bewerkstelligt.
                cin.ignore(1000, '\n');
                cout << "Das habe ich jetzt nicht verstanden.\n"
                        "Bitte gib [ Held ] oder [ Heldin ] an, damit ich mehr von dir erfahren kann.\n";
                cin >> hero1.gender;
            }
            cout << "Du bist also ";
            // Wenn man eine Heldin ist, wird man so angesprochen.
            if (hero1.gender == "heldin" || hero1.gender == "Heldin" || hero1.gender == "w" || hero1.gender == "f") {
                cout << "eine Heldin.\n";
                hero1.gender = "Heldin";
                cin.ignore(1000, '\n');
            }
            // Sonst ist man ein Held.
            else {
                cout << "ein Held.\n";
                hero1.gender = "Held";
                cin.ignore(1000, '\n');
            }
            cout << "Was ist dein Name?\n";
            /* Damit Personen auch einen Nachnamen oder einen Namen haben koennen, der aus mehreren Worten besteht
             * wird hier statt cin (kann nur jeweils ein Wort speichern) getline verwendet.                     */
            getline(cin, hero1.name);
            // Abfrage ob Name stimmt.
            cout << "Dein Name ist " << hero1.name
                 << ".\nIst das richtig? \n";
            //Variable für Antwort.
            string answer;
            cin >> answer;
            //Solange cin nicht leer ist wird der Inhalt von cin ueberprueft.
            while (cin){
                // Wenn die Antwort weder ja noch nein ist, kommt man in diese Schleife.
                while (answer != "ja" && answer != "Ja" && answer != "y" && answer != "j" && answer != "nein" && answer != "Nein" && answer != "n") {
                    cin.ignore(1000, '\n');
                    cout << "Antworte bitte einfach mit [ ja ] oder [ nein ].\n"
                            "Dein Name ist " << hero1.name << ".\n"
                            "Ist das richtig?\n";
                    cin >> answer;
                    continue;
                }
                // Ist die Antwort nein, n oder Nein muss man den Namen nochmal eingeben.
                while (answer == "nein" || answer == "Nein" || answer == "n") {
                    cin.ignore(1000, '\n');
                    cout << "Ups. Gib bitte deinen Namen nochmal an.\n";
                    cin.ignore();
                    getline(cin, hero1.name);
                    cout << "Dein Name ist " << hero1.name << ". \n"
                            "Ist das richtig?\n";
                    cin >> answer;
                    continue;
                }
                // Ist die Antwort ja, y, j oder Ja kommt man weiter.
                if (answer == "ja" || answer == "Ja" || answer == "y" || answer == "j") {
                    cin.ignore(1000, '\n');
                    cout << "Hab ich also richtig verstanden.\n";
                    break;
                }
            }
            cout << hero1.name <<", wir befinden uns in der Vergangenheit.\n"
                    "Schon in deiner Kindheit wusstest du, dass dir etwas vorherbestimmt war.\n"
                    "In jungen Jahren hast du dich entschlossen hart zu trainieren um bereit zu sein, "
                    "wenn deine Zeit kommt.\n"
                    "Wie alt bist du in diesem Szenario wohl?\n";
            cin >> hero1.age;
            /* While (cin.fail()) ueberprueft ob ein Integer eingegeben wird.
             * Sollte keiner eingegeben werden, wird der Puffer geloescht und man kann ein neues Alter eingeben.*/
            while (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Bitte gib ein Alter ein. Du weisst schon, mit Zahlen...\n";
                cin >> hero1.age;
            }
            while (hero1.age > 13 || hero1.age < 5) {
                cin.clear();
                cout << "Ich sagte doch, dass wir uns in deiner Kindheit befinden! \n"
                        "Such dir bitte ein anderes Alter in Zahlen aus.\n"
                        "Am besten zwischen [ 5 ] und [ 13 ]. \n";
                /* Dieser Block wurde eingefuegt nachdem bei Testruns Zahlen wie Float zu einer Endlosschleife gefuehrt
                 * haben. Das Problem ist, dass zwar abgefragt wird ob das Alter ein integer ist oder nicht,
                 * jedoch sieht eine Zahl wie Float (z.B. 1.2) aus wie ein Integer vor dem Punkt.
                 * Der Rest verbleibt im Puffer und fuehrt dann eine endlose Schleife durch.
                 * Um diesem Problem entgegenzugehen wird der Puffer geleert, also werden die Dezimalzahlen
                 * abgeschnitten. */
                cin.clear();
                cin.ignore(1000, '\n');
                cin >> hero1.age;
            }
            cout << "Genau. Im zarten Alter von " << hero1.age << " findest du dich im Hofe "
                    "deines besten Freundes wieder. \n"
                    "Du siehst vor dir die alten Trainingspuppen, die dein Vater euch gebastelt hat.\n"
                    "Daneben steht ein Tisch mit angeschnittenem Brot. Du siehst an dir herab und denkst nach, "
                    "ob du dir nicht etwas nimmst.\n"
                    "Wieviel wiegst du wohl?\n";
            cin.ignore(1000, '\n');
            // Variable für Gewicht.
            cin >> hero1.weight;
            // Ueberpruefung ob ein Integer eingegeben wurde.
            while (cin.fail()) {
                cin.clear();
                cin.ignore(1000,'\n');
                cout << "Bitte gib ein Gewicht ein. Du weisst schon, mit Zahlen...\n";
                cin >> hero1.weight;
            }
            while (hero1.weight < 100) {
                cin.clear();
                //cin.ignore(1000, '\n');
                if (hero1.weight < 0) {
                    cin.clear();
                    hero1.weight = rand() % 13 +1;
                    cout << "Ein negativer Wert... beim Gewicht? \n"
                            "Also ich denke, dass du schon etwas gewogen hast, "
                            "lass mich nachdenken...\n"
                            "Du bleibst ein Federgewicht und wiegst " << hero1.weight << " Kilogramm.\n";
                    break;

                }
                if (hero1.weight < 15) {
                    cin.clear();
                    cout << "Du wiegst " << hero1.weight << " Kilogramm?\n"
                            "Bist du sicher? \n"
                            "Das ist schon ein bisschen wenig. Du verschlingst das gesamte Brot "
                            "und holst dir nochmal 2 neue.\n";
                    // Kontrolle damit keine Floats durchkommen.
                    cin.clear();
                    cin.ignore(1000, '\n');
                    hero1.strength = 1;
                    break;
                }
                else if (hero1.weight >= 15 && hero1.weight < 40) {
                    cin.ignore(1000, '\n');
                    cout << "Du wiegst " << hero1.weight << " Kilogramm?\n"
                            "Das kommt in etwa hin. \n"
                            "Du nimmst dir eine Scheibe Brot und bist froh, dass jemand an deinen Hunger gedacht hat.\n";
                    // Kontrolle damit keine Floats durchkommen.
                    cin.clear();
                    cin.ignore(1000, '\n');
                    hero1.strength = 2;
                    break;
                }
                else if (hero1.weight >= 40) {
                    cin.ignore(1000, '\n');
                    cout << "Du wiegst " << hero1.weight << " Kilogramm?\n"
                            "Bist du sicher? \n"
                            "Du denkst dir, das Training wird das Brot schon wieder abtrainieren "
                            "und nimmst dir eine Scheibe.\n";
                    // Kontrolle damit keine Floats durchkommen.
                    cin.clear();
                    cin.ignore(1000, '\n');
                    hero1.strength = 3;
                    break;
                }
            }
            // Wenn jemand >=100 Kilo angibt, wird per Zufall entschieden wieviel er wiegt.
            if (hero1.weight >=100) {
                cin.clear();
                hero1.weight = rand() % 99 +1;
                cout << "Mehr als 100 Kilo? \n"
                        "Das kann ich mir nicht vorstellen. Wir sagen einfach du wiegst... "
                        << hero1.weight << " Kilogramm. Verstanden?\n";
                cin.clear();
                if (hero1.weight <10) {
                    cin.ignore(1000, '\n');
                    hero1.strength = 1;
                }
                else if (hero1.weight >=10 && hero1.weight < 40) {
                    cin.ignore(1000, '\n');
                    hero1.strength = 2;
                }
                else {
                    cin.ignore(1000, '\n');
                    hero1.strength = 3;
                }
            }
            cout << "Nachdem du gegessen hast bist du bereit dein Training zu beginnen.\n\n";
        }
        case 2: {// WAFFENWAHL
            cout << "Du siehst dir die Waffen an.\n"
                    "Da liegt ein kleiner " << waffe1.name << ", der dein Interesse weckt. "
                    "Daneben befindet sich eine kleine [ 1 ].\n"
                    "An einen Holzeimer angelehnt ist ein " << waffe2.name << " der etwas verbeult ist. \n"
                    "Ins Holz eingeritzt findest du eine [ 2 ].\n"
                    "Zuletzt entdeckst du das polierte " << waffe3.name << " aber es sieht sehr schwer aus.\n"
                    "In das Heft ist eine kunstvolle [ 3 ] graviert.\n"
                    "Welche Waffe willst du nehmen?\n";
            int waffe;
            cin >> waffe;
            /* Die Restriction beruht auf dem Gewicht der Person.
             * Sehr schlanke Helden (strength=1) koennen nur den Dolch heben,
             * mittlere Helden (strength=2) koennen zwischen Dolch und Knueppel waehlen
             * und schwere Helden (strength=3) koennen alle drei Waffen tragen.
             * Die Idee ist, dass schwache Helden (<10kg) nicht genug Kraft haben .
             * Sucht man sich keine Zahl aus, verletzt man den Wertebereich und kommt in die 1. Schleife.*/
            while (cin.fail()){
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Bitte gib eine der angegebenen Zahlen an.\n"
                        "[ 1 ] Dolch\n"
                        "[ 2 ] Knueppel\n"
                        "[ 3 ] Schwert\n";
                cin >> waffe;
            }
            if (waffe == 1) {
                cin.ignore(1000, '\n');
                if (waffe1.restriction <= hero1.strength) {
                    cout << "Du hast dir den " << waffe1.name << " ausgesucht. Gute Wahl! \n";
                    hero1.arm = waffe1.name;
                }
            }
            else if (waffe == 2) {
                cin.ignore(1000, '\n');
                if (waffe2.restriction <= hero1.strength) {
                    cout <<"Du hast dir den " << waffe2.name << " ausgesucht. Gute Wahl! \n";
                    hero1.arm = waffe2.name;
                }
                else {
                    cout << "Du bist leider nicht stark genug um diese Waffe zu heben - dir fehlen nur ein paar Kilo.\n"
                            "Du bekommst stattdessen den " << waffe2.name << "!\n";
                    hero1.arm = waffe1.name;
                }
            }
            else if (waffe == 3) {
                cin.ignore(1000, '\n');
                if (waffe3.restriction <= hero1.strength) {
                    cout <<"Du hast dir das " << waffe3.name << " ausgesucht. Gute Wahl! \n";
                    hero1.arm = waffe3.name;
                }

                else if (waffe2.restriction <= hero1.strength) {
                    cout << "Du bist leider nicht stark genug um diese Waffe zu heben - dir fehlen nur ein paar Kilo.\n"
                            "Du bekommst stattdessen den " << waffe2.name << "!\n";
                    hero1.arm = waffe2.name;
                }
                else if (waffe1.restriction <= hero1.strength) {
                    cout << "Du bist leider nicht stark genug um diese Waffe zu heben - dir fehlen nur ein paar Kilo.\n"
                            "Du bekommst stattdessen den " << waffe1.name << "!\n";
                    hero1.arm = waffe1.name;
                }
            }
            else if (waffe == 4){
                cin.ignore(1000, '\n');
                cout << "Du hast ein Easter Egg gefunden. Deine Waffe ist ein " << waffe4.name << "\n"
                        "Diese Waffe wurde extra wegen Feralun integriert.\n";
                hero1.arm = waffe4.name;
            }
                // Sucht man sich keine der Waffen aus, wird einem die Waffe, die der strength entspricht gegeben.
            else {
                cout << "Du hast dir keine der vorgestellten Waffen ausgesucht. \n"
                        "Aber um die Geschichte voranzubringen, "
                        "gebe ich dir einfach eine Waffe die zu dir passt. \n";
                if (waffe3.restriction == hero1.strength) {
                    cout << "Du bekommst ... das " << waffe3.name << ". Viel Erfolg damit!\n";
                    hero1.arm = waffe3.name;
                }
                else if (waffe2.restriction == hero1.strength) {
                    cout << "Du bekommst ... den " << waffe2.name << ". Viel Erfolg damit!\n";
                    hero1.arm = waffe2.name;
                }
                else {
                    cout << "Du bekommst ... den " << waffe1.name << ". Viel Erfolg damit!\n";
                    hero1.arm = waffe1.name;
                }
            }
            cout << "Die Waffenwahl ist damit beendet.\n\n";
        }
        case 3: {// PUPPENWAHL
            cout << "Jetzt musst du dich zwischen den Puppen entscheiden.\n"
                    "Die Puppen aus [ " << puppe1.material << " ] halten nicht so viel aus, "
                    "aber sind gut um das Training zu beginnen.\n"
                    "Die Puppen aus [ " << puppe2.material << " ] sind schon eine kleine Herausforderung.\n"
                    "Aber wenn man sich eine Puppe aus [ " << puppe3.material << " ] aussucht, "
                    "kann man sich wirklich beweisen.\n"
                    "Mit welchem Material willst du trainieren?\n";
            string material;
            cin >> hero1.doll;
            // Weder Holz, Stroh noch Eisen angegeben, man kommt in diese Schleife.
            while (hero1.doll != "Stroh" && hero1.doll != "Holz" && hero1.doll != "Eisen") {
                cin.ignore(1000, '\n');
                cout << "Hmm, ich hab leider kein anderes Material, als die, die ich vorgestellt habe.\n"
                        "Wieso suchst du dir nicht eines von diesen aus: [ Stroh ], [ Holz ], [ Eisen ]\n";
                cin >> hero1.doll;
            }
            // Sonst geht es hier weiter.
            cin.ignore(1000, '\n');
            cout << "Mit deinem " << hero1.arm << " und dieser Puppe aus " << hero1.doll << " steht dir "
                    "ja gar nichts mehr im Weg, " << hero1.name << ".\n\n";
        }
        case 4: {// UEBUNG
            cout << "Wir haben jetzt alles zusammen um die Geschichte voranzutreiben.\n"
                    "Du hast eine Waffe - dein " << hero1.arm << ". \n"
                    "Du hast eine Puppe ausgesucht - sie ist aus " << hero1.doll <<". \n"
                    "Jetzt holst du erstmal ordentlich aus und teilst einen Hieb aus.\n";

            //Variablen deklarieren
            int hits = 0;
            int damage = 0;

            /* Ich wollte ueber die Namen der Instanzen zu iterieren.
             * Meine Idee war es allgemein zu schreiben variable.material und dann dort
             * das einzusetzen, was eben gegeben ist  -> puppe1, puppe2 oder puppe3.
             * Da es mit Arrays zu loesen waere, wir sie aber noch nicht durchgemacht haben,
             * habe ich mich entschieden die aufeinanderfolgenden If-Abfragen zu behalten.
             * Mir ist klar, dass diese Loesung nicht ideal ist.*/

            if (puppe1.material == hero1.doll) {
                if (hero1.arm == waffe1.name) {
                    hits = fight(waffe1.damage, puppe1.health);
                    damage = waffe1.damage * hits;
                }
                else if (hero1.arm == waffe2.name) {
                    hits = fight(waffe2.damage, puppe1.health);
                    damage = waffe2.damage * hits;
                }
                else if (hero1.arm == waffe3.name) {
                    hits = fight(waffe3.damage, puppe1.health);
                    damage = waffe3.damage * hits;
                }
                else if (hero1.arm == waffe4.name) {
                    hits = fight(waffe4.damage, puppe1.health);
                    damage = waffe4.damage * hits;
                    cout << "Du hast die Puppe mit einem Bogen erschlagen.\n"
                            "Bist du jetzt zufrieden?\n";
                }
            }
            else if (puppe2.material == hero1.doll) {
                if (hero1.arm == waffe1.name) {
                    hits = fight(waffe1.damage, puppe2.health);
                    damage = waffe1.damage * hits;
                }
                else if (hero1.arm == waffe2.name) {
                    hits = fight(waffe2.damage, puppe2.health);
                    damage = waffe2.damage * hits;
                }
                else if (hero1.arm == waffe3.name) {
                    hits = fight(waffe3.damage, puppe2.health);
                    damage = waffe3.damage * hits;
                }
                else if (hero1.arm == waffe4.name) {
                    hits = fight(waffe4.damage, puppe2.health);
                    damage = waffe4.damage * hits;
                    cout << "Du hast die Puppe mit einem Bogen erschlagen.\n"
                            "Bist du jetzt zufrieden?\n";
                }
            }
            else if (puppe3.material == hero1.doll) {
                if (hero1.arm == waffe1.name) {
                    hits = fight(waffe1.damage, puppe3.health);
                    damage = waffe1.damage * hits;
                }
                else if (hero1.arm == waffe2.name) {
                    hits = fight(waffe2.damage, puppe3.health);
                    damage = waffe2.damage * hits;

                }
                else if (hero1.arm == waffe3.name) {
                    hits = fight(waffe3.damage, puppe3.health);
                    damage = waffe3.damage * hits;
                }
                else if (hero1.arm == waffe4.name) {
                    hits = fight(waffe4.damage, puppe3.health);
                    damage = waffe4.damage * hits;
                    cout << "Du hast die Puppe mit einem Bogen erschlagen.\n"
                            "Bist du jetzt zufrieden?\n";
                }

            }
            cout << "\n"
                    "STATISTIK\n"
                    << hero1.gender << ": " << hero1.name << " \n"
                    "Waffe: " << hero1.arm << " \n"
                    "Puppe: " << hero1.doll << "puppe \n";
            if (hits == 1) {
                cout << "Schaden: " << damage << " Schaden in " << hits << " Hieb\n\n";
            }
            else
                cout << "Schaden: " << damage << " Schaden in " << hits << " Hieben\n\n";
        }
        case 5: {// EXIT
            cout << "Vielen Dank, dass du unser Spiel ausprobiert hast.\n";
            credits();
            break;
        }
        default: {
            cout << "Hat dir die Auswahl nicht gefallen?\n"
                    "Starte bitte das Spiel neu und such dir einen Punkt aus!\n";
        }
    }
return 0;
}
// FUNKTIONEN

/* Das Menue wurde anfangs immer wieder eingebunden, deshalb habe ich es als Funktion definiert.
 * Spaeter habe ich mich entschieden das Menue nur am Anfang zu verwenden,
 * weil es sonst den Fluss des Spiels unterbricht.
 * Man kann natuerlich einfach ans Ende jeder Switch Case menue() einfuegen.*/
int menue() {
    cout <<
        "[ 1 ] Held erstellen\n"
        "[ 2 ] Waffenwahl\n"
        "[ 3 ] Puppenwahl\n"
        "[ 4 ] Uebung\n"
        "[ 5 ] Spiel beenden\n";
    int selection;
    cin >> selection;
    return selection;
};
/* Zu einem richtigen Spiel gehoeren auch Credits.
 * Ich habe meine Geschwister gebeten das Spiel zu spielen, und immer etwas Falsches einzugeben.
 * Dadurch bin ich auf Fehler gestossen, die ich so loesen konnte. */
void credits() {
    cout << "\nCREDITS\n\n"
            "Projekt Manager: Teacher\n"
            "Original Story: enigm4tik\n"
            "Programmierung: enigm4tik\n"
            "Programmierung Support: Teacher, learncpp.com\n"
            "Alpha Tester: Brother und Brother und Sister\n"
            "Besonderes Dankeschoen: Rainstorm Entertainment und dem Spieler dieses Spiels\n";
};

/* In dieser Funktion ist der Kampf beschrieben.
 * Solange die Puppe mehr Leben hat als die Waffe Schaden macht, wird i erhoeht und waffe von puppe abgezogen.
 * Man kann nach jedem Schlag entscheiden ob man den Kampf weiterfuehren will oder nicht. */
int fight(int waffe, int puppe) {
    int i = 0;
    string fight;
    while (puppe >= waffe) {
        puppe = puppe - waffe;
        i++;

        cout << "Du hast " << i << " mal getroffen.\n";
        //Solange die Puppe nach dem Abzug noch genug Leben fuer einen Schlag hat, wird gefragt ob man weitermachen will.
        if (puppe != 0 && puppe >= waffe) {
            cout << "Die Puppe hat noch " << puppe << " Leben.\n"
                    "Willst du noch einmal zuschlagen?\n";
            cin >> fight;
        }
        // Wenn die Puppe nach dem Abzug 0 Leben hat, wird der Sieg ausgegeben.
        if (puppe == 0) {
            cout << "Du hast die Puppe besiegt und ihr " << i * waffe << " Schaden gemacht.\n";
            break;
        }
        // Wird weder ja noch nein angegeben, kommt man hier hinein.
        while (fight != "ja" && fight != "nein" && fight != "Ja" && fight != "Nein" && fight != "j" && fight != "y" && fight != "n") {
            cin.ignore(1000, '\n');
            cout << "Es tut mir leid, das habe ich jetzt nicht verstanden.\n"
                    "Bitte gib [ ja ] ein, wenn du weitermachen willst oder [ nein ] um abzubrechen.\n";
            cin >> fight;
        }
        // Wenn man weiterkaempfen will, beginnt die naechste Iteration.
        if (fight == "ja" || fight == "Ja" || fight == "j" || fight == "y") {
            cin.ignore(1000, '\n');
            continue;
        }
            /* Wenn der Spieler sich entschliesst aufzuhoeren, wird noch nachgefragt, ob er sich sicher ist.
             * Dadurch werden Spieler abgefangen, die die "nein" Funktion ausprobieren,
             * das Spiel aber nicht beenden wollen.*/

        else if (fight == "nein" || fight == "Nein" || fight == "n") {
            cin.ignore(1000, '\n');
            cout << "Willst du den Kampf wirklich abbrechen?\n"
                    "Dadurch wird das Spiel beendet.\n";
            string abbruch;
            cin >> abbruch;
            // Wenn weder nein noch ja angegeben wird, kommt man in diese Schleife.
            while (abbruch != "nein" && abbruch != "Nein" && abbruch != "n" && abbruch != "ja" && abbruch != "Ja" && abbruch != "y" && abbruch != "j") {
                cin.ignore(1000, '\n');
                cout << "Bitte gib [ ja ] ein um abzubrechen oder [ nein ] um weiterzumachen.\n";
                cin >> abbruch;
            }
            // Wenn der Abbruch bestaetigt ist, wird man aus der Schleife geworfen.
            if (abbruch == "ja" || abbruch == "Ja" || abbruch == "j" || abbruch =="y") {
                cin.ignore(1000, '\n');
                cout << "Du hast den Kampf abgebrochen und der Puppe " << i * (waffe) << " Schaden gemacht.\n";
                break;
            }
            // Sonst geht der Kampf weiter.
            else {
                cin.ignore(1000, '\n');
                cout << "Anstatt deine Waffe beiseite zu legen, teilst du noch einen Schlag aus.\n";
                continue;
            }
        }
    }

    /* Wenn die Puppe weniger Leben hat, als die Waffe Schaden machen wuerde, wird dieser Block ausgefuehrt.
     * Demnach wird gefragt ob der "letzte Schlag" ausgefuehrt werden soll oder nicht.                      */

    if (puppe < waffe && puppe != 0) {
        cout << "Die Puppe hat noch " << puppe << " Leben.\n"
                "Willst du den letzten Schlag machen?\n";
        string lasthit;
        cin >> lasthit;
        // Sagt man weder ja noch nein, wird man aufgefordert ja oder nein zu sagen.
        while (lasthit != "ja" && lasthit != "Ja" && lasthit != "j" && lasthit != "y" && lasthit != "nein" && lasthit != "Nein" && lasthit != "n") {
            cin.ignore(1000, '\n');
            cout << "Bitte gib [ ja ] ein um der Puppe den letzten Schlag zu geben oder [ nein ] um abzubrechen!\n";
            cin >> lasthit;
        }
        // Sagt man nein wird nochmal nachgefragt ob man den Kampf wirklich abbrechen will.
        if (lasthit == "Nein" || lasthit == "nein" || lasthit == "n") {
            cin.ignore(1000, '\n');
            cout << "Willst du den Kampf wirklich abbrechen?\n"
                    "Dadurch wird das Spiel beendet.\n";
            string notlast;
            cin >> notlast;
            // Sagt man dazu weder ja noch nein, kommt man in diese Schleife.
            while (notlast != "Ja" && notlast != "ja" && notlast != "j" && notlast != "y" && notlast != "Nein" && notlast != "nein" && notlast != "n") {
                cin.ignore(1000, '\n');
                cout << "Bitte gib [ ja ] ein um den Kampf abzubrechen oder [ nein ] um weiterzumachen.\n";
                cin >> notlast;
            }
            // Sagt man ja, wird der Kampf abgebrochen.
            if (notlast == "Ja" || notlast == "ja" || notlast == "j" || notlast == "y") {
                cin.ignore(1000, '\n');
                cout << "Du hast der Puppe " << i * waffe << " Schaden gemacht und den Kampf abgebrochen. \n";
            }
            // Sagt man nein, wird der letzte Schlag durchgefuehrt.
            if (notlast == "Nein" || notlast == "nein" || notlast == "n") {
                cin.ignore(1000, '\n');
                i++;
                cout << "Du hast dich entschlossen deine Waffe ein letztes Mal zu benutzen.\n"
                        "Du hast die Puppe besiegt und ihr " << i * waffe << " Schaden gemacht.\n";
            }
        }
        // Sagt man zum letzten Schlag ja, wird der letzte Schlag ausgefuehrt und der Kampf ist beendet.
        if (lasthit == "Ja" || lasthit == "ja" || lasthit == "j" || lasthit == "y") {
            cin.ignore(1000, '\n');
            i++;
            cout << "Du hast die Puppe besiegt und ihr " << i * waffe << " Schaden gemacht.\n";
        }
    }
    return i;
}