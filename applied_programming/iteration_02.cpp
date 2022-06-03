// Author: enigm4tik
// Date: 25.03.2017 - 10.04.2017
// Description: Zweiter Teil der Uebung Angewandtes Programmieren
/*
 * Prototyp fuer RE bei dem der Spieler gegen Uebungsgegner kaempfen kann.
 * Spiel sollte erneut gestartet werden koennen.
 * Berechnung fuer Angriff nach bestimmter Formel,
 * kritischer Schaden einmal moeglich, bei < 50% Ausdauer.
 */


#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

// KLASSEN
class fighter {
private:
    // Daten der Klasse
    double attr_ge; // Geschick
    double attr_au; // Ausdauer
    int max_au; // Max. Ausdauer
    int attr_aw; // Angriffswert
    double ausr_sch; // Schaden
    float ausr_rs; // Ruestungsschutz
    float mod_weap; // Modifikator der Waffe
    float mod_rues; // Modifikator der Ruestung
    string weapon; // Waffenname
    string ruestung; // Ruestungsname
    int trick;
    string name; // Name des Kaempfers
    string gender; // Geschlecht
    int age; // Alter

public:
    // Habe fuer jedes Attribut einen Seter und Geter gemacht.
    // Habe dafuer die automatische Funktion von CLion verwendet.

    void setAttr_ge(double attr_ge) {
        fighter::attr_ge = attr_ge;
    }

    void setAttr_au(double attr_au) {
        fighter::attr_au = attr_au;
    }

    void setMax_au(int max_au) {
        fighter::max_au = max_au;
    }

    void setAttr_aw(int attr_aw) {
        fighter::attr_aw = attr_aw;
    }

    void setAusr_sch(double ausr_sch) {
        fighter::ausr_sch = ausr_sch;
    }

    void setAusr_rs(float ausr_rs) {
        fighter::ausr_rs = ausr_rs;
    }

    void setMod_weap(float mod_weap) {
        fighter::mod_weap = mod_weap;
    }

    void setMod_rues(float mod_rues) {
        fighter::mod_rues = mod_rues;
    }

    void setWeapon(const string &weapon) {
        fighter::weapon = weapon;
    }

    void setName(const string &name) {
        fighter::name = name;
    }

    void setGender(const string &gender) {
        fighter::gender = gender;
    }

    void setAge(int age) {
        fighter::age = age;
    }

    void setRuestung(const string &ruestung) {
        fighter::ruestung = ruestung;
    }

    void setTrick(int trick) {
        fighter::trick = trick;
    }

    // Geter aller Variablen

    int getAttr_ge() const {
        return attr_ge;
    }

    int getAttr_au() const {
        return attr_au;
    }

    int getMax_au() const {
        return max_au;
    }

    int getAttr_aw() const {
        return attr_aw;
    }

    float getAusr_sch() const {
        return ausr_sch;
    }

    float getAusr_rs() const {
        return ausr_rs;
    }

    float getMod_weap() const {
        return mod_weap;
    }

    float getMod_rues() const {
        return mod_rues;
    }

    const string &getWeapon() const {
        return weapon;
    }

    const string &getName() const {
        return name;
    }

    const string &getGender() const {
        return gender;
    }

    int getAge() const {
        return age;
    }

    const string &getRuestung() const {
        return ruestung;
    }

    int getTrick() const {
        return trick;
    }

    // Constructor fuer Gegner, enthaelt alle Werte!
    fighter(double attr_ge, double attr_au, int max_au, int attr_aw, double ausr_sch, float ausr_rs, float mod_weap, float mod_rues,
            const string &weapon, const string &ruestung, const string &name, const string &gender) : attr_ge(attr_ge),
                                                                                                      attr_au(attr_au),
                                                                                                      max_au(max_au),
                                                                                                      attr_aw(attr_aw),
                                                                                                      ausr_sch(
                                                                                                              ausr_sch),
                                                                                                      ausr_rs(ausr_rs),
                                                                                                      mod_weap(
                                                                                                              mod_weap),
                                                                                                      mod_rues(
                                                                                                              mod_rues),
                                                                                                      weapon(weapon),
                                                                                                      ruestung(
                                                                                                              ruestung),
                                                                                                      name(name),
                                                                                                      gender(gender) {}
    // Die Methode fight bestimmt ob man kaempfen darf oder nicht.
    int fight(){
        double calculation = attr_ge * mod_weap * mod_rues;
        double ge = calculation / attr_ge;
        double ga = ge * attr_aw;
        double angriff = ga + calculation;

        // Randomizer
        srand(time(NULL));
        float hit_lvl = static_cast<float> (rand()) / static_cast<float> (RAND_MAX)*100;
        hit_lvl = static_cast<float> (rand()) / static_cast<float> (RAND_MAX)*100;

        if (hit_lvl < angriff){
            // wenn hit_lvl kleiner ist als angriff darf man kaempfen
            return 1;
        }
        else {
            // sonst nicht.
            return 0;
        }
    }
    // 2 verschiedene fight Methoden.
    // uebergibt man 2 Objekte der Klasse fighter, dann wird gekaempft
    // mit jeweils 1 Sekunde Pause zwischen den Ausgaben
    float fight(class fighter, class fighter);
    // uebergibt man zusaetzlich noch einen String, wird das Abwarten nicht ausgefuehrt und der Kampf wird extrem schnell durchgefuehrt.
    float fight(class fighter, class fighter, string ende);
};

float fighter::fight(fighter hero, fighter enemy) {
    srand(time(NULL));
    // Die Variable zufall bestimmt welcher Satz ausgegeben wird.
    int zufall = 1 + (rand() % 100);

    if (hero.fight() == 0) {
        cout << "[ " << enemy.getName() << ": " << enemy.getAttr_au() << " ] "<< hero.getName();
        if (zufall < 15) {
            cout << " holt aus, macht einen grossen Schritt und rutscht aus.\n"
                    "Alle Zuschauer kichern...\n";
        }
        if (zufall >= 15 && zufall < 30) {
            cout << " ruft einen Schrei, hebt die Waffe ueber den Kopf und schlaegt daneben...\n";
        }
        if (zufall >= 30 && zufall < 45) {
            cout << " haelt sich den Kopf und stolpert rueckwaerts...\n";
        }
        if (zufall >= 45 && zufall < 55) {
            cout << " sieht den Gegner an und ist ploetzlich eingeschuechtert...\n";
        }
        if (zufall >= 55 && zufall < 65) {
            cout << " sieht die Waffe an. Sie scheint ploetzlich unendlich schwer, sie kann nicht gehoben werden.\n";
        }
        if (zufall >= 65 && zufall < 75) {
            cout << " hoert wie die Zuschauer den Gegner anfeuern und laesst die Waffe fallen.\n";
        }
        if (zufall >= 75 && zufall < 85) {
            cout
                    << " verfaellt in Rage und laeuft auf den Gegner zu. Der macht einen Schritt zur Seite und die Runde ist vertan.\n";
        }
        if (zufall >= 85 && zufall < 100) {
            cout << " verlangt nach einem Glas Wasser und setzt sich hin. Jeder braucht einmal Rast.\n";
        }
        // usleep verzoegert die Ausgabe
       usleep(1800000);
        // die Ausdauer des Gegners wird uebergeben.
        return enemy.getAttr_au();
    }
    else if (hero.fight() == 1) {
        double ausdauer;
        ausdauer = enemy.getAttr_au() + enemy.getAusr_rs() - hero.getAusr_sch();
        enemy.setAttr_au(ausdauer);
        cout << "[ " << enemy.getName() << ": " << enemy.getAttr_au() << " ] "<< hero.getName();
        if (zufall < 15) {
            cout << " macht einen Schlag und trifft genau auf den Kopf des Gegners.\n";
        }
        if (zufall >= 15 && zufall <30) {
            cout << " holt aus und trifft in die Magengegend.\n";
        }
        if (zufall >=30 && zufall <45) {
            cout << " ruft einen Schrei und stuermt auf den Gegner los und trifft ihn mit der Waffe.\n";
        }
        if (zufall >=45 && zufall <55) {
            cout << " macht einen eleganten Sprung und laesst die Waffe auf den Gegner niederfahren.\n";
        }
        if (zufall >=55 && zufall <65) {
            cout << " wirft die Waffe und trifft den Gegner, das hat niemand erwartet.\n";
        }
        if (zufall >=65 && zufall <75) {
            cout << " hoert wie das Publikum jubelt und wird davon motiviert. Der Schlag sitzt.\n";
        }
        if (zufall >=75 && zufall <=100) {
            cout << " tritt den Gegner zuerst und trifft ihn dann mit der Waffe.\n";
        }
        // usleep verzoegert die Ausgabe
       usleep(1800000);
        // die Ausdauer des Gegners wird uebergeben.
        return enemy.getAttr_au();
    }
}
float fighter::fight(fighter hero, fighter enemy, string ende) {
    srand(time(NULL));
    float zufall = static_cast<float> (rand()) / static_cast<float> (RAND_MAX)*100;
    zufall = static_cast<float> (rand()) / static_cast<float> (RAND_MAX)*100;

    if (hero.fight() == 0) {
        cout << "[ " << enemy.getName() << ": " << enemy.getAttr_au() << " ] "<< hero.getName();
        if (zufall < 15) {
            cout << " holt aus, macht einen grossen Schritt und rutscht aus.\n"
                    "Alle Zuschauer kichern...";
        }
        if (zufall >= 15 && zufall < 30) {
            cout << " ruft einen Schrei, hebt die Waffe ueber den Kopf und schlaegt daneben...\n";
        }
        if (zufall >= 30 && zufall < 45) {
            cout << " haelt sich den Kopf und stolpert rueckwaerts...\n";
        }
        if (zufall >= 45 && zufall < 55) {
            cout << " sieht den Gegner an und ist ploetzlich eingeschuechtert...\n";
        }
        if (zufall >= 55 && zufall < 65) {
            cout << " sieht die Waffe an. Sie scheint ploetzlich unendlich schwer, sie kann nicht gehoben werden.\n";
        }
        if (zufall >= 65 && zufall < 75) {
            cout << " hoert wie die Zuschauer den Gegner anfeuern und laesst die Waffe fallen.\n";
        }
        if (zufall >= 75 && zufall < 85) {
            cout
                    << " verfaellt in Rage und laeuft auf den Gegner zu. Der macht einen Schritt zur Seite und die Runde ist vertan.\n";
        }
        if (zufall >= 85 && zufall < 100) {
            cout << " verlangt nach einem Glas Wasser und setzt sich hin. Jeder braucht einmal Rast.\n";
        }
        return enemy.getAttr_au();
    }
    else if (hero.fight() == 1) {
        float ausdauer;
        ausdauer = enemy.getAttr_au() + enemy.getAusr_rs() - hero.getAusr_sch();
        enemy.setAttr_au(ausdauer);
        cout << "[ " << enemy.getName() << ": " << enemy.getAttr_au() << " ] "<< hero.getName();
        if (zufall < 15) {
            cout << " macht einen Schlag und trifft genau auf den Kopf des Gegners.\n";
        }
        if (zufall >= 15 && zufall <30) {
            cout << " holt aus und trifft in die Magengegend.\n";
        }
        if (zufall >=30 && zufall <45) {
            cout << " ruft einen Schrei und stuermt auf den Gegner los und trifft ihn mit der Waffe.\n";
        }
        if (zufall >=45 && zufall <55) {
            cout << " macht einen eleganten Sprung und laesst die Waffe auf den Gegner niederfahren.\n";
        }
        if (zufall >=55 && zufall <65) {
            cout << " wirft die Waffe und trifft den Gegner, das hat niemand erwartet.\n";
        }
        if (zufall >=65 && zufall <75) {
            cout << " hoert wie das Publikum jubelt und wird davon motiviert. Der Schlag sitzt.\n";
        }
        if (zufall >=75 && zufall <=100) {
            cout << " tritt den Gegner zuerst und trifft ihn dann mit der Waffe.\n";
        }
        return enemy.getAttr_au();
    }
}

// INT MAIN
int main() {
    // Default Werte des Helden eingetragen.
    fighter hero(60, 150, 150, 30, 6, 2, 1.0, 0.7,  "Schwert", "Eisen", "Link", "Held");
    hero.setTrick(0);
    fighter* hero_pointer;
    hero_pointer = &hero;
    // Gegner festlegen, falls keiner gewaehlt wird: Bark der Ork
    fighter enemy(10, 200, 200, 40, 5, 1, 0.8, 0.9, "Keule", "Leder", "Bark", "Held");
    enemy.setTrick(0);
    fighter* pointer;
    pointer = &enemy;

    cout << "THE CRAFT OF WAR\n";
    // Deklaration der Funktion Menue
    int menue();
    menue();
    // Schleife, damit man zwischen den Auswahlpunkten hin- und herwechseln kann.
    while(int again = 1){
        int selection;
        cin >> selection;
        switch(selection) {
            case 1: {
                cout << "Du stehst vor dem Eingang und siehst noch einmal an dir herab.\n"
                     "Bist du wirklich bereit? \n"
                     "Gerade, als du deine Hand erhebst um das Tor zu beruehren, erklingt die Stimme eines alten Mannes.\n";
                cout << "\'Bist du eine [ Heldin ] oder ein [ Held ]?\'\n";
                string gender;
                cin >> gender;
                // Abfrage ob Geschlecht richtig ist.
                // Wenn es weder Heldin, heldin, held noch Held ist, dann muss man erneut eingeben.
                while (gender != "heldin" && gender != "Heldin" && gender != "w" && gender != "f" && gender != "held" && gender != "Held" && gender != "m") {
                    cin.ignore(1000, '\n');
                    cout << "\'...? Das habe ich jetzt nicht verstanden.\'\n"
                            "\'Bitte sag mir ob du ein [ Held ] oder eine [ Heldin ] bist, "
                            "damit ich mehr von dir erfahren kann.\'\n";
                    cin >> gender;
                }
                cout << "\'Ah. Ein";
                // Wenn man eine Heldin ist (Gross- und Kleinschreibung egal), wird man so angesprochen.
                if (gender == "heldin" || gender == "Heldin" || gender == "w" || gender == "f") {
                    cin.ignore(1000, '\n');
                    hero.setGender("Heldin");
                    cout << "e " << hero.getGender() << "?\'\n";
                }
                    // Sonst ist man ein Held.
                else {
                    cin.ignore(1000, '\n');
                    hero.setGender("Held");
                    cout << " " << hero.getGender() << "?\'\n";
                }
                cout << "Ein lauter Knall erhallt. Es klang als waere ein schweres, altes Buch zugeschlagen worden.\n"
                        "\'Wie es in der Prophezeiung geschrieben steht!\'\n"
                     "\'Sag mir, " << hero.getGender() << ", wie ist dein Name?\'\n";
                string name;
                getline(cin, name);
                // Abfrage ob Name stimmt.
                cout << "\'Dein Name ist " << name
                     << "? Ist das richtig?\'\n";
                //Variable für Antwort.
                string answer;
                cin >> answer;
                //Solange cin nicht leer ist wird der Inhalt von cin ueberprueft.
                while (cin){
                    // Wenn die Antwort weder ja noch nein ist, kommt man in diese Schleife.
                    while (answer != "ja" && answer != "Ja" && answer != "y" && answer != "j" && answer != "nein" && answer != "Nein" && answer != "n") {
                        cout << "\'Oh, verstehst du meine Sprache nicht?\'\n"
                                "Du siehst das Tor einen Spalt oeffnen und den alten Mann hervortreten.\n"
                                "\'Antworte bitte einfach mit [ ja ]\', der alte Mann nickt, \'oder [ nein ].\', er schuettelt den Kopf.\n"
                                "\'Dein Name ist " << name << ". "
                                "Ist das richtig?\'\n";
                        cin >> answer;
                        continue;
                    }
                    // Ist die Antwort nein, n oder Nein muss man den Namen nochmal eingeben.
                    while (answer == "nein" || answer == "Nein" || answer == "n") {
                        cout << "\'Ups. Ich bin wohl etwas schwerhoerig. Wie ist dein Name?\'\n";
                        cin.ignore();
                        getline(cin, name);
                        cout << "'Dein Name ist " << name << ". "
                                "Ist das richtig?'\n";
                        cin >> answer;
                        continue;
                    }
                    // Ist die Antwort ja, y, j oder Ja kommt man weiter.
                    if (answer == "ja" || answer == "Ja" || answer == "y" || answer == "j") {
                        cout << "\'Hab ich also richtig verstanden.\'\n";
                        hero.setName(name);
                        break;
                     }
                }
                cout << "\'" << hero.getName() <<", mir wurde schon von deiner Reise berichtet.\'\n"
                        "\'Lange und weit bist du gereist um zu mir zu gelangen und mit mir zu trainieren.\'\n"
                        "\'Du bist dir hoffentlich im Klaren darueber, dass es nicht leicht wird.\'\n"
                        "\'Wenn du beschliesst zu bleiben, wirst du mit meinen anderen Schuelern trainieren.\'\n"
                        "Du ziehst etwas am Tor und es gibt nach. Du beschliesst einzutreten.\n";

                // Ende des Blocks, Menue fuer naechste Auswahl.
                menue();
                continue;
            }
            case 2: {
                // Erklaerung wieso man eine Waffe aussuchen soll.
                cout << "Du folgst dem alten Mann waehrend er dir etwas erzaehlt.\n"
                        "Die Eindruecke um dich herum sind zu interessant um dich auf die Geschichte zu konzentrieren.\n"
                        "\'... und deshalb kommen die talentiertesten Kaempfer der ganzen Welt zu mir.\', beendet er seine Gedanken.\n"
                        "Du aergerst dich, dass du diese Geschichte verpasst hast, spuerst aber etwas Stolz, \n"
                        "weil er vermutlich auch dich in diese Gruppe zaehlt.\n"
                        "Du siehst dich um und erkennst wohin er dich gefuehrt hat - in eine Waffenkammer.\n"
                        "\n"
                        "Speere, Schwerter und Waffen aus aller Welt liegen an einem fuer sie vorgesehenen Platz.\n"
                        "Du hast noch nie so viele Waffen auf einmal gesehen und versuchst das alles erst einmal aufzunehmen.\n"
                        "\n'Da du gerade erst zu uns gekommen bist, kann ich dir nur unsere Uebungswaffen anbieten.\'\n"
                        "Er geht zu einem Tisch, der in einer Ecke des Raumes steht. \nAuf ihm liegen 3 abgenutzte Waffen. \n\n"
                        "\'Der [ Speer ] ist leicht und kann dir helfen, deine Geschicklichkeit zu erhoehen.\'\n"
                        "\'Das [ Schwert ] ist die beliebteste Waffe, liegt gut in der Hand und teilt guten Schaden aus.\'\n"
                        "\'Der [ Morgenstern ] ist schwer zu handhaben, macht aber bei einem Treffer enormen Schaden.\'\n"
                        "\'Welche der Waffen willst du verwenden?\', fragt er und nickt dir aufmunternd zu.\n";
                string waffe;
                cin >> waffe;
                // Wenn keine der richtigen Waffen ausgesucht wird, kommt man in diese Schleife
                while (waffe != "speer" && waffe != "Speer" && waffe != "spear" && waffe != "1"
                       && waffe != "schwert" && waffe != "Schwert" && waffe != "sword" && waffe != "2"
                       && waffe != "morgenstern" && waffe != "Morgenstern" && waffe != "morningstar" && waffe != "3"
                       && waffe != "bogen" && waffe != "Bogen" && waffe != "bow" && waffe != "4") {
                    cin.ignore(1000, '\n');
                    cout << "\'Ich sagte doch, dass du am Anfang nur eine dieser 3 Waffen nutzen kannst: \n";
                    cout << "[ Speer ], [ Schwert ], oder [ Morgenstern ].\'\n";
                    cin >> waffe;
                }
                // sonst in die dafuer vorgesehene
                // innerhalb der Abfrage wird festgelegt welche Waffe man nutzt und was die Attribute der Waffe sind
                if (waffe == "speer" || waffe == "Speer" || waffe == "spear" || waffe == "1") {
                    hero.setWeapon("Speer");
                    hero.setMod_weap(1.3);
                    hero.setAusr_sch(4);
                    cout << "Du hebst den Speer, siehst ihn dir von allen Seiten an.\n"
                            "Du beschliesst er wird dir eine gute Waffe sein.\n"
                            "Geringer Schaden, aber gute Geschicklichkeit, deine Geschwindigkeit, ist was dich auszeichnet.\n";
                    }
                else if (waffe == "schwert" || waffe == "Schwert" || waffe == "sword" || waffe == "2") {
                    hero.setWeapon("Schwert");
                    hero.setMod_weap(1.0);
                    hero.setAusr_sch(6);
                    cout << "Du hebst das Schwert und faehrst ueber die Klinge.\n"
                            "Es scheint noch ziemlich scharf zu sein. Das Schwert wird dir gut dienen.\n"
                            "Guter Schaden und Geschicklichkeit, mit deiner Technik muss es passen.\n";
                }
                else if (waffe == "morgenstern" || waffe == "Morgenstern" || waffe == "morningstar" || waffe == "3") {
                    hero.setWeapon("Morgenstern");
                    hero.setMod_weap(0.7);
                    hero.setAusr_sch(10);
                    cout << "Du hebst den Morgenstern und die Kette wirkt schwer. \n"
                            "Es wird sicher schwierig mit ihm umzugehen, aber du bist sicher du lernst es schnell.\n"
                            "Enormer Schaden, wer braucht da Geschicklichkeit?\n";
                }
                    // Easter Egg: ein gutes Spiel braucht einen Bogen...
                else if (waffe == "bogen" || waffe == "Bogen" || waffe == "bow" || waffe == "4") {
                    hero.setWeapon("Bogen");
                    hero.setMod_weap(2.0);
                    hero.setAusr_sch(20);
                    cout << "Du drehst dich herum und nimmst einen der Boegen der an der Wand haengt. \n"
                            "Du weisst, dass das nicht eine der richtigen Waffen ist, aber du machst eben was du magst.\n"
                            "Enormer Schaden, riesige Geschichklichkeit! Du Cheater.\n";
                }
                else {
                    //
                    cout << "Du hast dir keine Waffe ausgesucht.";
                    cout << "Deshalb gebe ich dir einfach ...";
                    hero.setWeapon("Schwert");
                    hero.setMod_weap(1.0);
                    hero.setAusr_sch(6);
                    cout << " " << hero.getWeapon() << "\n";
                }
                // Ende des Blocks, Menue fuer naechste Auswahl.
                menue();
                continue;
            }
            case 3: {
                // Einfuehrung zur Auswahl der Ruestung.
                cout << "Mit deinem " << hero.getWeapon() << "in der Hand begleitest du den alten Mann zum naechsten Raum.\n"
                        "Von innen wirkt er fast wie ein Zelt. Ueberall liegen Stoffe und halbfertige Ruestungen.\n"
                        "Der alte Mann sieht an dir herab und wieder hinauf.\n"
                        "'Wir haben noch alte Ruestungen fuer dich, bei denen es nicht schade ist, \n"
                        "wenn sie beim Training kaputt gehen.\'\n"
                        "'Diese Materialien habe ich zu bieten...\'\n"
                        "'[ Stoff ] beeintraechtigt deine Bewegungen kaum, aber er schuetzt dich auch nicht.\'\n"
                        "'[ Leder ] engt deine Geschicklichkeit etwas ein, aber du wirst geschuetzt.\'\n"
                        "'[ Eisen ] macht deine Bewegungen traege, haelt aber deine Gegner zurueck.\'\n"
                        "\'Welche Ruestung willst du nehmen?\'\n";
                string material;
                cin >> material;
                // Weder Stoff, Leder noch Eisen angegeben, man kommt in diese Schleife.
                while (material != "Stoff" && material != "stoff"
                       && material != "Leder" && material != "leder"
                       && material != "Eisen" && material != "eisen"
                       && material != "nothing" && material != "nichts" && material != "nackt"
                        ) {
                    cout << "\'Manchmal ist es, als wolltest du nur testen, was ich von deinen Antworten halte...\'\n"
                            "\'Ich habe leider kein anderes Material, als die, die ich vorgestellt habe.\'\n"
                            "\'Wieso suchst du dir nicht eines von diesen aus: [ Stoff ], [ Leder ], [ Eisen ]\'\n";
                    cin >> material;
                }
                // Sonst geht es hier weiter.
                if (material == "Stoff" || material == "stoff"){
                    hero.setRuestung("Stoff");
                    hero.setMod_rues(1.00);
                    hero.setAusr_rs(0);
                    cout << "Du entscheidest dich fuer die leichte Ruestung, weil du zuversichtlich bist,"
                            "dass dich niemand treffen wird.\n";
                    cout << "Du ziehst dir die Ruestung an, sie ist ein bisschen zu gross, "
                            "aber fuer den Anfang wird sie reichen.\n";
                }
                else if (material == "Leder" || material == "leder"){
                    hero.setRuestung("Leder");
                    hero.setMod_rues(0.9);
                    hero.setAusr_rs(1);
                    cout << "Du entscheidest dich fuer Leder, weil du zwar Schutz willst, "
                            "aber dich in deinen Bewegungen nicht einschraenken willst.\n";
                    cout << "Du ziehst dir die Ruestung an, sie ist ein bisschen zu gross, "
                            "aber fuer den Anfang wird sie reichen.\n";
                }
                else if (material == "Eisen" || material == "eisen"){
                    hero.setRuestung("Eisen");
                    hero.setMod_rues(0.7);
                    hero.setAusr_rs(2);
                    cout << "Du entscheidest dich fuer die schwere Ruestung, weil du lieber sichergehen willst, "
                            "dass dich nichts treffen kann.\n";
                    cout << "Du ziehst dir die Ruestung an, sie ist ein bisschen zu gross, "
                            "aber fuer den Anfang wird sie reichen.\n";
                }
                    // Easter Egg: der User will nackt kaempfen...
                else if (material == "nichts" || material == "nothing" || material == "nackt"){
                    hero.setRuestung("des Kaisers neue Kleider");
                    hero.setMod_rues(0.1);
                    hero.setAusr_rs(0);
                    cout << "\' ICH WILL DES KAISERS NEUE KLEIDER!\' bruellst du ploetzlich. \n"
                            "Du ziehst dich aus und stehst jetzt nackt da. "
                            "Diese Ruestung ist komisch, aber naja, das ist deine Entscheidung.\n";
                }
                menue();
                continue;
            }
            case 4: {
                // Einfuehrung fuer die Gegner
                cout << "Der alte Mann sieht an dir herab und kann sich ein Kichern nicht verkneifen.\n";
                if (hero.getRuestung() == "des Kaisers neue Kleider"){
                    cout << "Du siehst schon etwas lustig aus, wie du da komplett nackt dastehst.\n";
                }
                else {
                    cout << "Du siehst schon etwas lustig aus, mit deiner Ruestung aus " << hero.getRuestung() << ", die an keiner Ecke passt und dem alten" << hero.getWeapon() << " in der Hand.\n";
                }
                cout << "Du schielst zu ihm herueber, aber du willst dir deine Unsicherheit nicht anmerken lassen.\n"
                        "'Ich will dir meine 2 besten Schueler und meine beste Schuelerin vorstellen\'\n"
                        "Du hoerst das tiefe Lachen zweier wohl sehr grosser Maenner und die aufgeregte Erzaehlung einer helleren Stimme.\n"
                        "\'Horst, Bark... Elfi? Kommt bitte zu mir... \'\n"
                        "Du erkennst die Stimmen zu den Gesichtern, hast dich aber bei ihren Groessen geirrt,"
                        "als du erkennst dass zwar ein Ork, aber auch ein Zwerg zu dir heruebertrotten.\n"
                        "Zumindest hast du dich bei der hellen Stimme nicht geirrt, denn die schlanke Elfe grinst dich an.\n"
                        "\'Darf ich vorstellen?\'\n"
                        "\'[ Bark ], der Ork ist unser staerkster Held.\'\n"
                        "Du siehst, dass der Zwerg mit dieser Aussage unzufrieden ist.\n"
                        "\'[ Horst ], der Borst sieht zwar nicht nach viel aus, aber ich wuerde ihn nicht unterschaetzen...\'\n"
                        "Der Zwerg stampft auf, weiss aber, dass er seinem Meister wohl nicht widersprechen darf.\n"
                        "\'Zu guter Letzt haben wir [ Elfriede ], die Elfe, die .. naja sie ist eine Elfe und hier bei mir.\'\n"
                        "\'Meine 3 Lehrlinge werden mit dir trainieren. Sag mir, gegen wen du kaempfen willst.\'\n"
                        "[ Bark ], [ Horst ] oder [ Elfriede ]? \n";
                string gegner;
                cin >> gegner;
                // Weder Ork, Elf noch Borst angegeben, man kommt in diese Schleife.
                while (gegner != "ork" && gegner != "Ork" && gegner != "bark" && gegner != "Bark" &&
                       gegner != "elf" && gegner != "Elf" && gegner != "elfriede" && gegner != "Elfriede" &&
                       gegner != "Borst" && gegner != "borst" && gegner != "horst" && gegner != "Horst") {
                    cout << "Der Zwerg lacht leise... 'Ich habe sie dir doch gerade vorgestellt..\'\n"
                            "\'Ihre Namen sind [ Bark ], der Ork, [ Horst ], der Borst und [ Elfriede ] die Elfe.\'\n"
                            "\'Gegen wen moechtest du kaempfen?\'\n";
                    cin >> gegner;
                }
                // sonst kommt man in die richtige Abfrage
                if (gegner == "ork" || gegner == "Ork" || gegner == "bark" || gegner == "Bark"){
                    // wenn man bereits diesen Gegner besiegt hat, kann man den Gegner noch einmal waehlen
                    // damit er wieder Ausdauer bekommt trinkt er einen Trank.
                    // ist bei den 3 Gegnern gleich
                    if (enemy.getName() == "Bark" && enemy.getAttr_au() <= 0){
                        cout << "Du hast gerade gegen " << enemy.getName() << " gekaempft und er ist komplett erschoepft.";
                        cout << "Er trinkt einen speziellen Trank und kann sich so komplett vom Kampf erholen.\n";
                    }
                    // Die Werte werden per Pointer an den enemy uebergeben und so geaendert.
                    pointer->setAttr_ge(10);
                    pointer->setAttr_au(200);
                    pointer->setMax_au(200);
                    pointer->setAttr_aw(40);
                    pointer->setAusr_sch(5);
                    pointer->setAusr_rs(1);
                    pointer->setMod_weap(0.8);
                    pointer->setMod_rues(0.9);
                    pointer->setWeapon("Keule");
                    pointer->setRuestung("Leder");
                    pointer->setName("Bark");
                    pointer->setGender("m");
                    pointer->setTrick(0);

                    cout << "Der Ork streckt sich und du fuehlst dich ein bisschen eingeschuechtert.\n"
                            "Er sieht mit jeder Bewegung staerker aus.\n"
                            "Du nimmst deine Waffe fester in die Hand und schluckst. Augen zu und durch.\n";
                }
                else if (gegner == "elf" || gegner == "Elf" || gegner == "elfriede" || gegner == "Elfriede"){
                    if (enemy.getName() == "Elfriede" && enemy.getAttr_au() <= 0){
                        cout << "Du hast gerade gegen " << enemy.getName() << " gekaempft und sie ist komplett erschoepft.";
                        cout << "Sie trinkt einen speziellen Trank und kann sich so komplett vom Kampf erholen.\n";
                    }
                    pointer->setAttr_ge(70);
                    pointer->setAttr_au(50);
                    pointer->setMax_au(50);
                    pointer->setAttr_aw(15);
                    pointer->setAusr_sch(4.5);
                    pointer->setAusr_rs(1);
                    pointer->setMod_weap(1.0);
                    pointer->setMod_rues(1.0);
                    pointer->setWeapon("Elfenspeer");
                    pointer->setRuestung("Stoff");
                    pointer->setName("Elfriede");
                    pointer->setGender("f");
                    pointer->setTrick(0);

                    cout << "Die Elfe macht einen eleganten Sprung und landet in einer Verbeugung. \n"
                            "Die anderen beiden klatschen und lachen leise. \nDu hast das Gefuehl, "
                            "sie wissen etwas, das du nicht weisst.\n";
                }
                else if (gegner == "Borst" || gegner == "borst" || gegner == "horst" || gegner == "Horst"){
                    if (enemy.getName() == "Horst" && enemy.getAttr_au() <= 0){
                        cout << "Du hast gerade gegen " << enemy.getName() << " gekaempft und er ist komplett erschoepft.";
                        cout << "Er trinkt einen speziellen Trank und kann sich so komplett vom Kampf erholen.\n";
                    }
                    pointer->setAttr_ge(40);
                    pointer->setAttr_au(70);
                    pointer->setMax_au(70);
                    pointer->setAttr_aw(20);
                    pointer->setAusr_sch(7);
                    pointer->setAusr_rs(2.5);
                    pointer->setMod_weap(0.9);
                    pointer->setMod_rues(0.7);
                    pointer->setWeapon("Zweihaender");
                    pointer->setRuestung("Eisen");
                    pointer->setName("Horst");
                    pointer->setGender("m");
                    pointer->setTrick(0);

                    cout << "Der Borst ruempft die Nase. Er denkt du unterschaetzt ihn, "
                            "aber diesen Fehler haben schon andere vor dir begangen.\n"
                            "Er nimmt seinen Zweihaender in die Hand und stupst dich an, damit du dich in die Arena bewegst.\n ";
                }
                menue();
                continue;
            }
            case 5: {
                // Wenn man beim Kampf verloren hat und nochmal kaempfen will, bekommt man diese Meldung
                if (hero.getAttr_au() <= 0) {
                    cout << "Du hast leider nicht genug Ausdauer um noch einmal zu kaempfen.\n";
                }
                    // Wenn der Gegner keine Ausdauer mehr hat, kommt man hier hinein.
                else if (enemy.getAttr_au() <= 0) {
                    cout << "\'" << enemy.getName() << ", hat nicht mehr genug Ausdauer um noch einmal zu kaempfen.'\n";
                    cout << "\'Such dir einen neuen Gegner aus.\'\n";
                    // Wenn der Held weniger als 50 Ausdauer hat, trinkt er einen Trank, damit er wieder kaempfen kann.
                    if (hero.getAttr_au() < 50) {
                    cout << "Damit der Kampf fair bleibt, trinkst du einen Trank, der etwas Ausdauer wiederherstellt.\n";
                    hero.setAttr_au(hero.getAttr_au()+80);
                    cout << "Du hast jetzt wieder " << hero.getAttr_au() << " Ausdauer.";
                        // Damit der Held seinen Trick wieder anwenden kann, muss der auch zurueckgesetzt werden.
                        hero.setTrick(0);
                    }
                }
                else {
                    // Der Kampf.
                    cout << "Der alte Mann geht voraus und erklaert die Regeln. \n"
                            "\'Im Grunde ist alles erlaubt, aber bitte bleibt fair. Immerhin seid ihr Helden...\'\n";
                }
                // Rundenanzahl
                int rounds = 0;
                while (hero.getAttr_au() > 0 && enemy.getAttr_au() > 0){
                    string kaempfen;
                    cout << "Wie viele Runden soll der Kampf gehen?\n";
                    // Man kann aussuchen wie viele Runden man kaempfen moechte.
                    cout << "[ 1 ] Runde\n" // 1 Runde
                            "[ 3 ] Runden\n" // 3 Runden
                            "[ ende ] bis zum Ende!\n" // bis zum Schluss
                            "Fuer Ungeduldige: nutze [ schnell ] um den Kampf ohne Abwarten durchzufuehren.\n"; // bis zum Schluss aber ohne sleep.
                    cin >> kaempfen;
                    // Wenn keine der richtigen Angaben gemacht wird, kommt man hier hinein
                    while (kaempfen != "1" && kaempfen != "3" && kaempfen != "ende" && kaempfen != "fast" && kaempfen != "schnell") {
                        cout << "Du hast die Wahl zwischen einer Runde, 3 Runden und eine Zusammenfassung des Kampfes bis zum Ende.\n"
                                "Welche Auswahl moechtest du treffen? [ 1 ], [ 3 ], [ ende ]\n"
                                "Fuer ungeduldige: nutze [ schnell ] um den Kampf ohne Abwarten durchzufuehren.\n";
                        cin >> kaempfen;
                    }
                    // sonst hier hinein.
                    if (kaempfen == "1") {
                        // Wenn der Held weniger als die Haelfte seiner Ausdauer hat, und der Held den Trick noch nicht gemacht hat,
                        // wird der Trick ausgefuehrt.
                        if (hero.getAttr_au() < hero.getMax_au()/2 && hero.getTrick() == 0) {
                            int vernichtung = 1 + (rand() % 10);
                            // 70/100 Chance, dass man den Trick macht.
                            if (vernichtung <7) {
                            //do trick
                                cout << "[ Urknall! ] ";
                                cout << "Du siehst auf den Boden und gehst in dich. "
                                        "Du spuerst eine ungeahnte Kraft in dir. Ist es das, was es heisst ein";
                                if (hero.getGender() == "Heldin") {
                                    cout << "e " << hero.getGender();
                                }
                                else {
                                    cout << " " << hero.getGender();
                                }
                                cout << " zu sein? ";
                                cout << "Du hoerst das Wort \'Urknall\' in deinem Knopf und holst aus.\n";
                                // erstens: die Modifier einfuegen
                                hero.setAusr_sch(hero.getAusr_sch() * 2);
                                double ge_before = hero.getAttr_ge();
                                double ge_neu = hero.getAttr_ge() * 1.75;
                                hero.setAttr_ge(ge_neu);
                                // zweitens: den Kampf durchfuehren
                                float held = hero.fight(hero, enemy);
                                enemy.setAttr_au(held);
                                float feind = enemy.fight(enemy, hero);
                                hero.setAttr_au(feind);
                                // drittens: speichern, dass der Trick durchgefuehrt wurde
                                hero.setTrick(1);
                                // viertens: Modifier zuruecksetzen
                                hero.setAusr_sch(hero.getAusr_sch() / 2);
                                hero.setAttr_ge(ge_before);
                            }
                        }
                            // das selbe wird auch fuer die Gegner durchgefuehrt
                        else if (enemy.getAttr_au() < enemy.getMax_au()/2 && enemy.getTrick() == 0) {
                            int vernichtung = 1 + (rand() % 10);
                            // 70/100 Chance, dass man den Trick macht.
                            if (vernichtung <7) {
                            //do trick
                                // nulltens: Herausfinden wer der Gegner ist
                                if (enemy.getName() == "Bark" || enemy.getName() == "Elfriede") {
                                    float mod_before = enemy.getMod_rues();
                                    if (enemy.getName() == "Bark") {
                                        cout << "[ Einschuechtern! ] ";
                                        cout
                                                << "Bark stellt sich auf ballt seine Faeuste, schaut in den Himmel und bruellt."
                                                        "Das Publikum verstummt und erstarrt waehrend Bark ausholt.\n";
                                        // erstens: die Modifier einfuegen
                                        enemy.setMod_rues(1.5);
                                        // zweitens: den Kampf durchfuehren
                                        float feind = enemy.fight(enemy, hero);
                                        hero.setAttr_au(feind);
                                        float held = hero.fight(hero, enemy);
                                        enemy.setAttr_au(held);
                                        // drittens: speichern, dass der Trick durchgefuehrt wurde
                                        enemy.setTrick(1);
                                        // viertens: Modifier zuruecksetzen
                                        enemy.setMod_rues(mod_before);
                                    } else if (enemy.getName() == "Elfriede") {
                                        cout << "[ Elfengleich! ] ";
                                        cout << "Elfi kichert und sprintet um dich herum. Sie springt so schnell, "
                                                "dass du mit den Augen kaum hinterherkommst.\n";
                                        // erstens: die Modifier einfuegen
                                        enemy.setMod_rues(1.8);
                                        // zweitens: den Kampf durchfuehren
                                        float feind = enemy.fight(enemy, hero);
                                        hero.setAttr_au(feind);
                                        float held = hero.fight(hero, enemy);
                                        enemy.setAttr_au(held);
                                        // drittens: speichern, dass der Trick durchgefuehrt wurde
                                        enemy.setTrick(1);
                                        // viertens: Modifier zuruecksetzen
                                        enemy.setMod_rues(mod_before);
                                    }
                                }
                                else if (enemy.getName() == "Horst") {
                                    cout << "[ Wuchtschlag! ] ";
                                    cout << "Der Zwerg wirbelt seinen Zweihaender und bewegt sich auf dich zu."
                                            "Du kannst dich nicht bewegen und er kommt immer naeher.\n";
                                    // erstens: die Modifier einfuegen
                                    enemy.setAusr_sch(enemy.getAusr_sch() * 1.5);
                                    // zweitens: den Kampf durchfuehren
                                    float feind = enemy.fight(enemy, hero);
                                    hero.setAttr_au(feind);
                                    float held = hero.fight(hero, enemy);
                                    enemy.setAttr_au(held);
                                    // drittens: speichern, dass der Trick durchgefuehrt wurde
                                    enemy.setTrick(1);
                                    // viertens: Modifier zuruecksetzen
                                    enemy.setAusr_sch(enemy.getAusr_sch() / 1.5);
                                }
                            }
                        }
                        else {
                            float held = hero.fight(hero, enemy);
                            enemy.setAttr_au(held);
                            float feind = enemy.fight(enemy, hero);
                            hero.setAttr_au(feind);
                            rounds++;
                        }
                        cout << "\nDer Kampf dauerte " << rounds << " Runden.\n";
                    }
                    else if (kaempfen == "3") {
                        int count = 0;
                        while (count < 3) {
                            if (hero.getAttr_au() >0 && enemy.getAttr_au()>0) {
                                // Wenn der Held weniger als die Haelfte seiner Ausdauer hat, und der Held den Trick noch nicht gemacht hat,
                                // wird der Trick ausgefuehrt.
                                if (hero.getAttr_au() < hero.getMax_au()/2 && hero.getTrick() == 0) {
                                    int vernichtung = 1 + (rand() % 10);
                                    // 70/100 Chance, dass man den Trick macht.
                                    if (vernichtung <7) {
                                        //do trick
                                        cout << "[ Urknall! ] ";
                                        cout << "Du siehst auf den Boden und gehst in dich. "
                                                "Du spuerst eine ungeahnte Kraft in dir. Ist es das, was es heisst ein";
                                        if (hero.getGender() == "Heldin") {
                                            cout << "e " << hero.getGender();
                                        }
                                        else {
                                            cout << " " << hero.getGender();
                                        }
                                        cout << " zu sein? ";
                                        cout << "Du hoerst das Wort \'Urknall\' in deinem Knopf und holst aus.\n";
                                        // erstens: die Modifier einfuegen
                                        hero.setAusr_sch(hero.getAusr_sch() * 2);
                                        double ge_before = hero.getAttr_ge();
                                        double ge_neu = hero.getAttr_ge() * 1.75;
                                        hero.setAttr_ge(ge_neu);
                                        // zweitens: den Kampf durchfuehren
                                        float held = hero.fight(hero, enemy);
                                        enemy.setAttr_au(held);
                                        float feind = enemy.fight(enemy, hero);
                                        hero.setAttr_au(feind);
                                        // drittens: speichern, dass der Trick durchgefuehrt wurde
                                        hero.setTrick(1);
                                        // viertens: Modifier zuruecksetzen
                                        hero.setAusr_sch(hero.getAusr_sch() / 2);
                                        hero.setAttr_ge(ge_before);
                                    }
                                }
                                    // das selbe wird auch fuer die Gegner durchgefuehrt
                                if (enemy.getAttr_au() < enemy.getMax_au()/2 && enemy.getTrick() == 0) {
                                    int vernichtung = 1 + (rand() % 10);
                                    // 70/100 Chance, dass man den Trick macht.
                                    if (vernichtung <7) {
                                        //do trick
                                        // nulltens: Herausfinden wer der Gegner ist
                                        if (enemy.getName() == "Bark" || enemy.getName() == "Elfriede") {
                                            float mod_before = enemy.getMod_rues();
                                            if (enemy.getName() == "Bark") {
                                                cout << "[ Einschuechtern! ] ";
                                                cout
                                                        << "Bark stellt sich auf ballt seine Faeuste, schaut in den Himmel und bruellt."
                                                                "Das Publikum verstummt und erstarrt waehrend Bark ausholt.\n";
                                                // erstens: die Modifier einfuegen
                                                enemy.setMod_rues(1.5);
                                                // zweitens: den Kampf durchfuehren
                                                float feind = enemy.fight(enemy, hero);
                                                hero.setAttr_au(feind);
                                                float held = hero.fight(hero, enemy);
                                                enemy.setAttr_au(held);
                                                // drittens: speichern, dass der Trick durchgefuehrt wurde
                                                enemy.setTrick(1);
                                                // viertens: Modifier zuruecksetzen
                                                enemy.setMod_rues(mod_before);
                                            } else if (enemy.getName() == "Elfriede") {
                                                cout << "[ Elfengleich! ] ";
                                                cout << "Elfi kichert und sprintet um dich herum. Sie springt so schnell, "
                                                        "dass du mit den Augen kaum hinterherkommst.\n";
                                                // erstens: die Modifier einfuegen
                                                enemy.setMod_rues(1.8);
                                                // zweitens: den Kampf durchfuehren
                                                float feind = enemy.fight(enemy, hero);
                                                hero.setAttr_au(feind);
                                                float held = hero.fight(hero, enemy);
                                                enemy.setAttr_au(held);
                                                // drittens: speichern, dass der Trick durchgefuehrt wurde
                                                enemy.setTrick(1);
                                                // viertens: Modifier zuruecksetzen
                                                enemy.setMod_rues(mod_before);
                                            }
                                        }
                                        else if (enemy.getName() == "Horst") {
                                            cout << "[ Wuchtschlag! ] ";
                                            cout << "Der Zwerg wirbelt seinen Zweihaender und bewegt sich auf dich zu."
                                                    "Du kannst dich nicht bewegen und er kommt immer naeher.\n";
                                            // erstens: die Modifier einfuegen
                                            enemy.setAusr_sch(enemy.getAusr_sch() * 1.5);
                                            // zweitens: den Kampf durchfuehren
                                            float feind = enemy.fight(enemy, hero);
                                            hero.setAttr_au(feind);
                                            float held = hero.fight(hero, enemy);
                                            enemy.setAttr_au(held);
                                            // drittens: speichern, dass der Trick durchgefuehrt wurde
                                            enemy.setTrick(1);
                                            // viertens: Modifier zuruecksetzen
                                            enemy.setAusr_sch(enemy.getAusr_sch() / 1.5);
                                        }
                                    }
                                }
                                else {
                                    float held = hero.fight(hero, enemy);
                                    enemy.setAttr_au(held);
                                    float feind = enemy.fight(enemy, hero);
                                    hero.setAttr_au(feind);
                                    rounds++;
                                }
                                count++;
                            }
                            else {
                                count++;
                            }
                        }
                        cout << "\nDer Kampf dauerte " << rounds << " Runden.\n";
                    }
                    else if(kaempfen == "fast" || kaempfen == "schnell") {
                        while (hero.getAttr_au() > 0 && enemy.getAttr_au() > 0) {
                            // Wenn der Held weniger als die Haelfte seiner Ausdauer hat, und der Held den Trick noch nicht gemacht hat,
                            // wird der Trick ausgefuehrt.
                            if (hero.getAttr_au() < hero.getMax_au()/2 && hero.getTrick() == 0) {
                                int vernichtung = 1 + (rand() % 10);
                                // 70/100 Chance, dass man den Trick macht.
                                if (vernichtung <7) {
                                    //do trick
                                    cout << "[ Urknall! ] ";
                                    cout << "Du siehst auf den Boden und gehst in dich. "
                                            "Du spuerst eine ungeahnte Kraft in dir. Ist es das, was es heisst ein";
                                    if (hero.getGender() == "Heldin") {
                                        cout << "e " << hero.getGender();
                                    }
                                    else {
                                        cout << " " << hero.getGender();
                                    }
                                    cout << " zu sein? ";
                                    cout << "Du hoerst das Wort \'Urknall\' in deinem Knopf und holst aus.\n";
                                    // erstens: die Modifier einfuegen
                                    hero.setAusr_sch(hero.getAusr_sch() * 2);
                                    double ge_before = hero.getAttr_ge();
                                    double ge_neu = hero.getAttr_ge() * 1.75;
                                    hero.setAttr_ge(ge_neu);
                                    // zweitens: den Kampf durchfuehren
                                    float held = hero.fight(hero, enemy, "fast");
                                    enemy.setAttr_au(held);
                                    float feind = enemy.fight(enemy, hero, "fast");
                                    hero.setAttr_au(feind);
                                    // drittens: speichern, dass der Trick durchgefuehrt wurde
                                    hero.setTrick(1);
                                    // viertens: Modifier zuruecksetzen
                                    hero.setAusr_sch(hero.getAusr_sch() / 2);
                                    hero.setAttr_ge(ge_before);
                                }
                            }
                                // das selbe wird auch fuer die Gegner durchgefuehrt
                            else if (enemy.getAttr_au() < enemy.getMax_au()/2 && enemy.getTrick() == 0) {
                                int vernichtung = 1 + (rand() % 10);
                                // 70/100 Chance, dass man den Trick macht.
                                if (vernichtung <7) {
                                    //do trick
                                    // nulltens: Herausfinden wer der Gegner ist
                                    if (enemy.getName() == "Bark" || enemy.getName() == "Elfriede") {
                                        float mod_before = enemy.getMod_rues();
                                        if (enemy.getName() == "Bark") {
                                            cout << "[ Einschuechtern! ] ";
                                            cout
                                                    << "Bark stellt sich auf ballt seine Faeuste, schaut in den Himmel und bruellt."
                                                            "Das Publikum verstummt und erstarrt waehrend Bark ausholt.\n";
                                            // erstens: die Modifier einfuegen
                                            enemy.setMod_rues(1.5);
                                            // zweitens: den Kampf durchfuehren
                                            float feind = enemy.fight(enemy, hero, "fast");
                                            hero.setAttr_au(feind);
                                            float held = hero.fight(hero, enemy, "fast");
                                            enemy.setAttr_au(held);
                                            // drittens: speichern, dass der Trick durchgefuehrt wurde
                                            enemy.setTrick(1);
                                            // viertens: Modifier zuruecksetzen
                                            enemy.setMod_rues(mod_before);
                                        }
                                        else if (enemy.getName() == "Elfriede") {
                                            cout << "[ Elfengleich! ] ";
                                            cout << "Elfi kichert und sprintet um dich herum. Sie springt so schnell, "
                                                    "dass du mit den Augen kaum hinterherkommst.\n";
                                            // erstens: die Modifier einfuegen
                                            enemy.setMod_rues(1.8);
                                            // zweitens: den Kampf durchfuehren
                                            float feind = enemy.fight(enemy, hero, "fast");
                                            hero.setAttr_au(feind);
                                            float held = hero.fight(hero, enemy, "fast");
                                            enemy.setAttr_au(held);
                                            // drittens: speichern, dass der Trick durchgefuehrt wurde
                                            enemy.setTrick(1);
                                            // viertens: Modifier zuruecksetzen
                                            enemy.setMod_rues(mod_before);
                                        }
                                    }
                                    else if (enemy.getName() == "Horst") {
                                        cout << "[ Wuchtschlag! ] ";
                                        cout << "Der Zwerg wirbelt seinen Zweihaender und bewegt sich auf dich zu."
                                                "Du kannst dich nicht bewegen und er kommt immer naeher.\n";
                                        // erstens: die Modifier einfuegen
                                        enemy.setAusr_sch(enemy.getAusr_sch() * 1.5);
                                        // zweitens: den Kampf durchfuehren
                                        float feind = enemy.fight(enemy, hero, "fast");
                                        hero.setAttr_au(feind);
                                        float held = hero.fight(hero, enemy, "fast");
                                        enemy.setAttr_au(held);
                                        // drittens: speichern, dass der Trick durchgefuehrt wurde
                                        enemy.setTrick(1);
                                        // viertens: Modifier zuruecksetzen
                                        enemy.setAusr_sch(enemy.getAusr_sch() / 1.5);
                                    }
                                }
                            }
                            else {
                                float held = hero.fight(hero, enemy, "fast");
                                enemy.setAttr_au(held);
                                float feind = enemy.fight(enemy, hero, "fast");
                                hero.setAttr_au(feind);
                                rounds++;
                            }
                        }
                        cout << "\nDu machst einen Blick auf eine Tafel, auf der sich die Statistik dieses Kampfes befindet:\n\n"
                                "STATISTIK\n"
                             << enemy.getName() << " vs. " << hero.getName() << "\n"
                             << enemy.getWeapon() << " vs. " << hero.getWeapon() << "\n"
                             << enemy.getRuestung() << " vs. " << hero.getRuestung() << "\n"
                             << "Der Kampf dauerte " << rounds << " Runden.\n";
                    }
                    else {
                        while (hero.getAttr_au() > 0 && enemy.getAttr_au() > 0) {
                            // Wenn der Held weniger als die Haelfte seiner Ausdauer hat, und der Held den Trick noch nicht gemacht hat,
                            // wird der Trick ausgefuehrt.
                            if (hero.getAttr_au() < hero.getMax_au()/2 && hero.getTrick() == 0) {
                                int vernichtung = 1 + (rand() % 10);
                                // 70/100 Chance, dass man den Trick macht.
                                if (vernichtung <7) {
                                    //do trick
                                    cout << "[ Urknall! ] ";
                                    cout << "Du siehst auf den Boden und gehst in dich. "
                                            "Du spuerst eine ungeahnte Kraft in dir. Ist es das, was es heisst ein";
                                    if (hero.getGender() == "Heldin") {
                                        cout << "e " << hero.getGender();
                                    }
                                    else {
                                        cout << " " << hero.getGender();
                                    }
                                    cout << " zu sein? ";
                                    cout << "Du hoerst das Wort \'Urknall\' in deinem Knopf und holst aus.\n";
                                    // erstens: die Modifier einfuegen
                                    hero.setAusr_sch(hero.getAusr_sch() * 2);
                                    double ge_before = hero.getAttr_ge();
                                    double ge_neu = hero.getAttr_ge() * 1.75;
                                    hero.setAttr_ge(ge_neu);
                                    // zweitens: den Kampf durchfuehren
                                    float held = hero.fight(hero, enemy);
                                    enemy.setAttr_au(held);
                                    float feind = enemy.fight(enemy, hero);
                                    hero.setAttr_au(feind);
                                    // drittens: speichern, dass der Trick durchgefuehrt wurde
                                    hero.setTrick(1);
                                    // viertens: Modifier zuruecksetzen
                                    hero.setAusr_sch(hero.getAusr_sch() / 2);
                                    hero.setAttr_ge(ge_before);
                                }
                            }
                                // das selbe wird auch fuer die Gegner durchgefuehrt
                            else if (enemy.getAttr_au() < enemy.getMax_au()/2 && enemy.getTrick() == 0) {
                                int vernichtung = 1 + (rand() % 10);
                                // 70/100 Chance, dass man den Trick macht.
                                if (vernichtung <7) {
                                    //do trick
                                    // nulltens: Herausfinden wer der Gegner ist
                                    if (enemy.getName() == "Bark" || enemy.getName() == "Elfriede") {
                                        float mod_before = enemy.getMod_rues();
                                        if (enemy.getName() == "Bark") {
                                            cout << "[ Einschuechtern! ] ";
                                            cout
                                                    << "Bark stellt sich auf ballt seine Faeuste, schaut in den Himmel und bruellt."
                                                            "Das Publikum verstummt und erstarrt waehrend Bark ausholt.\n";
                                            // erstens: die Modifier einfuegen
                                            enemy.setMod_rues(1.5);
                                            // zweitens: den Kampf durchfuehren
                                            float feind = enemy.fight(enemy, hero);
                                            hero.setAttr_au(feind);
                                            float held = hero.fight(hero, enemy);
                                            enemy.setAttr_au(held);
                                            // drittens: speichern, dass der Trick durchgefuehrt wurde
                                            enemy.setTrick(1);
                                            // viertens: Modifier zuruecksetzen
                                            enemy.setMod_rues(mod_before);
                                        }
                                        else if (enemy.getName() == "Elfriede") {
                                            cout << "[ Elfengleich! ] ";
                                            cout << "Elfi kichert und sprintet um dich herum. Sie springt so schnell, "
                                                    "dass du mit den Augen kaum hinterherkommst.\n";
                                            // erstens: die Modifier einfuegen
                                            enemy.setMod_rues(1.8);
                                            // zweitens: den Kampf durchfuehren
                                            float feind = enemy.fight(enemy, hero);
                                            hero.setAttr_au(feind);
                                            float held = hero.fight(hero, enemy);
                                            enemy.setAttr_au(held);
                                            // drittens: speichern, dass der Trick durchgefuehrt wurde
                                            enemy.setTrick(1);
                                            // viertens: Modifier zuruecksetzen
                                            enemy.setMod_rues(mod_before);
                                        }
                                    }
                                    else if (enemy.getName() == "Horst") {
                                        cout << "[ Wuchtschlag! ] ";
                                        cout << "Der Zwerg wirbelt seinen Zweihaender und bewegt sich auf dich zu."
                                                "Du kannst dich nicht bewegen und er kommt immer naeher.\n";
                                        // erstens: die Modifier einfuegen
                                        enemy.setAusr_sch(enemy.getAusr_sch() * 1.5);
                                        // zweitens: den Kampf durchfuehren
                                        float feind = enemy.fight(enemy, hero);
                                        hero.setAttr_au(feind);
                                        float held = hero.fight(hero, enemy);
                                        enemy.setAttr_au(held);
                                        // drittens: speichern, dass der Trick durchgefuehrt wurde
                                        enemy.setTrick(1);
                                        // viertens: Modifier zuruecksetzen
                                        enemy.setAusr_sch(enemy.getAusr_sch() / 1.5);
                                    }
                                }
                            }
                            else {
                                float held = hero.fight(hero, enemy);
                                enemy.setAttr_au(held);
                                float feind = enemy.fight(enemy, hero);
                                hero.setAttr_au(feind);
                                rounds++;
                            }
                        }
                        cout << "Du machst einen Blick auf eine Tafel, auf der sich die Statistik dieses Kampfes befindet:\n"
                                "STATISTIK\n"
                                << enemy.getName() << " vs. " << hero.getName() << "\n"
                                << enemy.getWeapon() << " vs. " << hero.getWeapon() << "\n"
                                << enemy.getRuestung() << " vs. " << hero.getRuestung() << "\n"
                                << "Der Kampf dauerte " << rounds << "Runden.";
                    }
                    if (hero.getAttr_au() <= 0) {
                        cout << "\n\'Du wurdest besiegt.\'\n"
                                "Das Publikum ist still und sie alle unterdruecken ein Schmunzeln.\n"
                                "\'Du bist neu hier und meine Lehrlinge sind wirklich gut.\'\n";
                        cout << enemy.getName() << " hat noch " << enemy.getAttr_au() << " Ausdauer.\n";

                    }
                    else if (enemy.getAttr_au() <= 0) {
                        cout << "\nDu hast deinen Gegner besiegt!\n"
                                "Das Publikum ist erstaunt und klatscht leise.\n";
                        cout << "Dein Gegner gibt dir die Hand und du bist richtig stolz.\n"
                                "\'Du hast noch " << hero.getAttr_au() << " Ausdauer.\'\n"
                                "\'Wenn du moechtest kannst du dir einen neuen Gegner aussuchen und weiterkaempfen.\'\n";
                    }
                    else {
                        cout << "\n";
                        cout << hero.getName() << " hat noch " << hero.getAttr_au() << " Ausdauer.\n";
                        cout << enemy.getName() << " hat noch " << enemy.getAttr_au() << " Ausdauer.\n\n";
                    }

                }
                menue();
                continue;
            }
            case 6: {
                // Wenn man exit aussucht.
                void credits();
                credits();
                break;
            }
            default: {
                // Abfangen von Nonsense-Eingabe weil Zahl erwartet wird.
                if (cin.fail()){
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                cout << "War nichts fuer dich dabei? Such doch einfach einen Punkt im Menue aus.\n"
                        "Gib eine der Zahlen in den eckigen Klammern ein.";
                menue();
                continue;
            }
        }
        break;
    }

    // return 0 weil int main
    return 0;
}
int menue(){
    cout << "\n________Menue_______\n";
    cout << "[ 1 ] Held erstellen\n"
            "[ 2 ] Waffenwahl\n"
            "[ 3 ] Ruestungswahl\n"
            "[ 4 ] Gegnerwahl\n"
            "[ 5 ] Kampf\n"
            "[ 6 ] Exit\n";
}

void credits() {
    cout << "\nCREDITS\n\n"
            "Projekt Manager: Teacher\n"
            "Original Story: enigm4tik\n"
            "Programmierung: enigm4tik\n"
            "Programmierung Support: Teacher, learncpp.com\n"
            "Alpha Tester: Brother\n"
            "Besonderes Dankeschoen: Rainstorm Entertainment und dem Spieler dieses Spiels\n";
};