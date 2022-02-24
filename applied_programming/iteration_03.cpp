/* Author: Anna Majewski
 * Date: 25.05.2017 - 14.06.2017
 * Description: Teil 3 der Uebung Angewandtes Programmieren
 *
 * Engine: Abenteuermodus mit Quests, Lebenspunkte statt Ausdauer
 * Quests: 1-3 Gegner, pro besiegtem Gegner 2 Gold, Regeneration nach Erfolg
 * Taverne: 1 Gefaehrten anheuern, teilen bei Sieg
 * Uebung: bleibt wie gehabt, aber pro Sieg erhaelt man 5 EXP
 * mit 10 EXP kann man die Attribute aufwerten
 */

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "vector"
#include "algorithm"
#include <algorithm>
using namespace std;

// KLASSEN
class fighter {
private:
    // Daten der Klasse
    double attr_ge; // Geschick
    double attr_au; // Ausdauer
    double max_au; // Max. Ausdauer
    double attr_aw; // Angriffswert
    double ausr_sch; // Schaden
    float ausr_rs; // Ruestungsschutz
    float mod_weap; // Modifikator der Waffe
    float mod_rues; // Modifikator der Ruestung
    string weapon; // Waffenname
    string ruestung; // Ruestungsname
    int trick;

    string name; // Name des Kaempfers
    double lp; // Lebenspunkte

public:

    string gender; // Geschlecht
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

    void setRuestung(const string &ruestung) {
        fighter::ruestung = ruestung;
    }

    void setTrick(int trick) {
        fighter::trick = trick;
    }

    void setLp(double lp){
        fighter::lp = lp;
    }

    // Geter aller Variablen

    double getLp() const {
        return lp;
    }

    double getAttr_ge() const {
        return attr_ge;
    }

    double getAttr_au() const {
        return attr_au;
    }

    double getMax_au() const {
        return max_au;
    }

    double getAttr_aw() const {
        return attr_aw;
    }

    double getAusr_sch() const {
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

    const string &getRuestung() const {
        return ruestung;
    }

    int getTrick() const {
        return trick;
    }


    // Constructor fuer Gegner, enthaelt alle Werte!
    fighter(double attr_ge, double attr_au, int max_au, int attr_aw, double ausr_sch, float ausr_rs, float mod_weap, float mod_rues,
            const string &weapon, const string &ruestung, const string &name, const string &gender, int lp)
            : attr_ge(attr_ge), attr_au(attr_au), max_au(max_au), attr_aw(attr_aw), ausr_sch(ausr_sch),
              ausr_rs(ausr_rs), mod_weap(mod_weap), mod_rues(mod_rues), weapon(weapon), ruestung(ruestung),
              name(name), gender(gender), lp(lp) {}

    // Die Methode fight() bestimmt ob man kaempfen darf oder nicht.
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

    // Kampfimplementierung
    // Da ich unzufrieden damit war, dass ich bei Uebung 2 ein int aus der Funktion gemacht habe, das ich dann
    // erst wieder zuweisen musste, habe ich diesmal ueberlegt stattdessen Pointer an meine Funktion zu uebergeben.
    // Ausserdem ist die Funktion void und wird bei Aufruf einfach durchgefuehrt. Das ist fuer mich instinktiver.

    // Diese Methode bestimmt den Kampf und wird von allen weiteren nur aufgerufen.
    // Ich war auch unzufrieden, dass ich in Uebung 2 den selben Code immer und immer wieder fuer alle cases verwendet habe.
    // Hier wird das geloest, indem ich innerhalb der Methoden die "Hauptkampfmethode" (fight()) aufrufe!

    void fight(class fighter* hero, class fighter* enemy){
        if (hero->getAttr_au() < hero->getMax_au()/2 && hero->getTrick() == 0){
            int vernichtung = 1 + (rand() % 10);
            hero->setTrick(1);
            if (vernichtung < 7) {
                // success:
                if (hero->getName() == "Bark") {
                    // Trick fuer Bark
                    cout << "[ Einschuechtern! ] ";
                    cout << "Bark stellt sich auf ballt seine Faeuste, schaut in den Himmel und bruellt. "
                            "Das Publikum verstummt und erstarrt waehrend Bark ausholt.\n";
                    //Schritt 1: Werte vorher speichern
                    float mod_before = enemy->getMod_rues();
                    //Schritt 2: Werte veraendern
                    hero->setMod_rues(1.5);
                    //Schritt 3: Kampf
                    hero->fight(hero, enemy);
                    //Schritt 4: Zueruecksetzen
                    hero->setMod_rues(mod_before);
                } else if (hero->getName() == "Elfriede") {
                    // Trick fuer Elfriede
                    cout << "[ Elfengleich! ] ";
                    cout << "Elfi kichert und sprintet um dich herum. Sie springt so schnell, "
                            "dass du mit den Augen kaum hinterherkommst.\n";
                    //Schritt 1: Werte vorher speichern
                    float mod_before = enemy->getMod_rues();
                    //Schritt 2: Werte veraendern
                    hero->setMod_rues(1.8);
                    //Schritt 3: Kampf
                    hero->fight(hero, enemy);
                    //Schritt 4: Zueruecksetzen
                    hero->setMod_rues(mod_before);
                } else if (hero->getName() == "Horst") {
                    // Trick fuer Horst
                    cout << "[ Wuchtschlag! ] ";
                    cout << "Der Zwerg wirbelt seinen Zweihaender und bewegt sich auf dich zu."
                            "Du kannst dich nicht bewegen und er kommt immer naeher.\n";
                    //Schritt 1: Werte vorher speichern - entfaellt.
                    //Schritt 2: Werte veraendern
                    hero->setAusr_sch(hero->getAusr_sch() * 1.5);
                    //Schritt 3: Kampf
                    hero->fight(hero, enemy);
                    //Schritt 4: Zueruecksetzen
                    hero->setAusr_sch(hero->getAusr_sch() / 1.5);
                } else {
                    // Trick fuer Held
                    cout << "[ Urknall! ] ";
                    cout << "Du siehst auf den Boden und gehst in dich. "
                            "Du spuerst eine ungeahnte Kraft in dir. Ist es das, was es heisst ein";
                    if (hero->getGender() == "Heldin") {
                        cout << "e " << hero->getGender();
                    } else {
                        cout << " " << hero->getGender();
                    }
                    cout << " zu sein? ";
                    cout << "Du hoerst das Wort \'Urknall\' in deinem Knopf und holst aus.\n";
                    //Schritt 1: Werte vorher speichern
                    double ge_before = hero->getAttr_ge();
                    //Schritt 2: Werte veraendern
                    hero->setAusr_sch(hero->getAusr_sch() * 2);
                    hero->setAttr_ge(hero->getAttr_ge() * 1.75);
                    //Schritt 3: Kampf
                    hero->fight(hero, enemy);
                    //Schritt 4: Zueruecksetzen
                    hero->setAusr_sch(hero->getAusr_sch() / 2);
                    hero->setAttr_ge(ge_before);
                }
            }
            else {
                cout << "[ Upps! ]"
                        "Der Moment war vielversprechend, aber am Ende ist doch nichts passiert.";
            }
        }
        if (hero->fight() == 0){
            cout << "[ " << enemy->getName() << ": " << enemy->getAttr_au() << " ] "<< hero->getName();
            cout << " hat verfehlt" << endl;
        }
        else if (hero->fight() == 1){
            double ausdauer = enemy->getAttr_au() + enemy->getAusr_rs() - hero->getAusr_sch();
            enemy->setAttr_au(ausdauer);
            if (enemy->getAttr_au() <0){
                enemy->setAttr_au(0);
            }
            cout << "[ " << enemy->getName() << ": " << enemy->getAttr_au() << " ] "<< hero->getName();
            cout << " hat getroffen." << endl;
        }
    };
    void fight(fighter* hero, fighter* enemy, string schnell){
        while (hero->getAttr_au() > 0 && enemy->getAttr_au() > 0){
            if (schnell == "ende") {
                // das bedeutet der Kampf wird mit Abwarten durchgefuehrt.
                hero->fight(hero, enemy);
                usleep(1800000);
                enemy->fight(enemy, hero);
                usleep(1800000);
            }
            else if (schnell == "schnell") {
                // das bedeutet, der Kampf wird ohne Abwarten ausgefuehrt.
                hero->fight(hero, enemy);
                enemy->fight(enemy, hero);
            }
        }
    };
    void fight(class fighter* hero, class fighter* enemy, int runden){
        int iterator = 0;
        while (iterator < runden){
            // das bedeutet, dass der Kamp "runden" oft durchgefuehrt wird. In unserem Fall immer 3.
            fight(hero, enemy);
            usleep(1800000);
            fight(enemy, hero);
            usleep(1800000);
            iterator++;
        }
    };
};

class hero : public fighter {
private:
    int gold;
    int exp;
    bool buddy = 0;
    int id;


public:
    // Defaul Constructor
    hero();
    // Constructor
    hero(double attr_ge, double attr_au, int max_au, int attr_aw, double ausr_sch, float ausr_rs, float mod_weap,
         float mod_rues, const string &weapon, const string &ruestung, const string &name, const string &gender, int lp,
         int gold, int exp, int id) : fighter(attr_ge, attr_au, max_au, attr_aw, ausr_sch, ausr_rs, mod_weap, mod_rues, weapon,
                                      ruestung, name, gender, lp), gold(gold), exp(exp), id(id) {}

    int getGold() const {
        return gold;
    }

    int getExp() const {
        return exp;
    }

    bool getBuddy() const {
        return buddy;
    }

    int getId() const {
        return id;
    }

    void setGold(int gold) {
        hero::gold = gold;
    }

    void setExp(int exp) {
        hero::exp = exp;
    }

    void setBuddy(bool buddy){
        hero::buddy = buddy;
    }

    void setId(int id){
        hero::id = id;
    }

    // Diese Methode ueberlaedt den == Operator, damit ich Vektoren von Helden vergleichen kann.
    friend bool operator==(const hero &name1, const hero &name2);

    // Da meine heroes in Vektoren gesammelt werden, schreibe ich neue Kampffunktionen, die mit Vektoren arbeiten.

    int battle(){

        double calculation = this->getAttr_ge() * this->getMod_weap() * this->getMod_rues();
        double ge = calculation / this->getAttr_ge();
        double ga = ge * this->getAttr_aw();
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
    void battle(class hero* hero, class hero* enemy){
        if (hero->getAttr_au() < hero->getMax_au()/2 && hero->getTrick() == 0){
            int vernichtung = 1 + (rand() % 10);
            hero->setTrick(1);
            if (vernichtung < 7) {
                // success:
                if (hero->getName() == "Borsts Horst"){
                    // Trick fuer Borsts Horst
                    cout << "[ Torkelschlag! ] ";
                    cout << "Borsts Horst sieht auf den Boden und sammelt seine Kraefte, dann torkelt er seinem Gegner entgegen." << endl;
                    //Schritt 1: Werte vorher speichern
                    //entfaellt.
                    //Schritt 2: Werte veraendern
                    hero->setAusr_sch(hero->getAusr_sch()*1.2);
                    //Schritt 3: Kampf
                    hero->fight(hero, enemy);
                    //Schritt 4: Zueruecksetzen
                    hero->setAusr_sch(hero->getAusr_sch()/1.2);
                }
                else if (hero->getName() == "Tark der Ork"){
                    // Trick fuer Tark
                    cout << "[ Bruell an dat vor mia! ] ";
                    cout << "Tark der Ork macht sich gross und breit und oeffnet sein riesiges Maul zu einem fuerchterlichen Schrei!" << endl;
                    //Schritt 1: Werte vorher speichern
                    // entfaellt
                    //Schritt 2: Werte veraendern
                    hero->setAttr_ge(hero->getAttr_ge()*1.7);
                    //Schritt 3: Kampf
                    hero->fight(hero, enemy);
                    //Schritt 4: Zueruecksetzen
                    hero->setAttr_ge(hero->getAttr_ge()/1.7);
                }
                else if (hero->getName() == "Speerzahn der Pitbull"){
                    // Trick fuer Speerzahn
                    cout << "[ Welpenblick! ] ";
                    cout << "Der Pitbull dreht sich auf seinen Bauch, laesst seine Zunge heraushaengen und schaut seinen Gegner mit einem niedlichen Blick an" << endl;
                    //Schritt 1: Werte vorher speichern
                    //entfaellt
                    //Schritt 2: Werte veraendern
                    hero->setAttr_ge(hero->getAttr_ge()*1.8);
                    //Schritt 3: Kampf
                    hero->fight(hero, enemy);
                    //Schritt 4: Zueruecksetzen
                    hero->setAttr_ge(hero->getAttr_ge()/1.8);
                }
                else if (hero->getName() == "Holzaa Quernik"){
                    // Trick fuer Holzaa
                    cout << "[ Doppelschuss! ] ";
                    cout << "Holzaa nimmt zwei Pfeile aus seinem Koecher, legt sie an und zielt direkt auf das Gesicht seines Gegners." << endl;
                    //Schritt 1: Werte vorher speichern
                    //entfaellt
                    //Schritt 2: Werte veraendern
                    hero->setAttr_ge(hero->getAttr_ge()*2.0);
                    //Schritt 3: Kampf
                    hero->fight(hero, enemy);
                    //Schritt 4: Zueruecksetzen
                    hero->setAttr_ge(hero->getAttr_ge()/2.0);
                }
                else if (hero->getName() == "Grimmzack Arg Pack"){
                    // Trick fuer Grimmzack
                    cout << "[ Bremer Feuer! ] ";
                    cout << "Wutentbrandt und mit Feuer in seinem Blick rast der kleine Zwerg auf seinen Gegner los." << endl;
                    //Schritt 1: Werte vorher speichern
                    //entfaellt
                    //Schritt 2: Werte veraendern
                    // Da nicht dasteht was veraendert wird, nehme ich wie bei den Gegnern einfach das Geschick!!
                    hero->setAttr_ge(hero->getAttr_ge()*1.6);
                    //Schritt 3: Kampf
                    hero->fight(hero, enemy);
                    //Schritt 4: Zueruecksetzen
                    hero->setAttr_ge(hero->getAttr_ge()/1.6);
                }
                else if (hero->getName() == "Akro der Wikinger"){
                    // Trick fuer Akro
                    cout << "[ Odins Schlag! ] ";
                    cout << "Der Himmel tut sich auf und ein Blitzschlag trifft direkt in das Schwert des Wikingers." << endl;
                    //Schritt 1: Werte vorher speichern
                    //entfaellt
                    //Schritt 2: Werte veraendern
                    // Da nicht dasteht was veraendert wird, nehme ich wie bei den Gegnern einfach das Geschick!!
                    hero->setAttr_ge(hero->getAttr_ge()*1.9);
                    //Schritt 3: Kampf
                    hero->fight(hero, enemy);
                    //Schritt 4: Zueruecksetzen
                    hero->setAttr_ge(hero->getAttr_ge()/1.9);
                }
                else if (hero->getName() == "Eloya die Waldelfe"){
                    // Trick fuer Eloya
                    cout << "[ Falkenauge! ] ";
                    cout << "Die Elfe macht einen Handstand und zieht den Bogen mit ihren Zehen an. Was fuer ein Schauspiel." << endl;
                    //Schritt 1: Werte vorher speichern
                    //entfaellt
                    //Schritt 2: Werte veraendern
                    // Da nicht dasteht was veraendert wird, nehme ich wie bei den Gegnern einfach das Geschick!!
                    hero->setAttr_ge(hero->getAttr_ge()*2.9);
                    //Schritt 3: Kampf
                    hero->fight(hero, enemy);
                    //Schritt 4: Zueruecksetzen
                    hero->setAttr_ge(hero->getAttr_ge()/2.9);
                }
                else if (hero->getName() == "Anna"){
                    // Trick fuer Grimmzack
                    cout << "[ Noergelei! ] ";
                    cout << "Das Kind faengt an eine laaange Geschichte zu erzaehlen und immer wieder hoert man nur 'Hae?!'." << endl;
                    //Schritt 1: Werte vorher speichern
                    //entfaellt
                    //Schritt 2: Werte veraendern
                    // Da nicht dasteht was veraendert wird, nehme ich wie bei den Gegnern einfach das Geschick!!
                    hero->setAttr_ge(hero->getAttr_ge()*2.6);
                    //Schritt 3: Kampf
                    hero->fight(hero, enemy);
                    //Schritt 4: Zueruecksetzen
                    hero->setAttr_ge(hero->getAttr_ge()/2.6);
                }
                else {
                    // Trick fuer Held
                    cout << "[ Urknall! ] ";
                    cout << "Du siehst auf den Boden und gehst in dich. "
                            "Du spuerst eine ungeahnte Kraft in dir. Ist es das, was es heisst ein";
                    if (hero->getGender() == "Heldin") {
                        cout << "e " << hero->getGender();
                    }
                    else {
                        cout << " " << hero->getGender();
                    }
                    cout << " zu sein? ";
                    cout << "Du hoerst das Wort \'Urknall\' in deinem Knopf und holst aus.\n";
                    //Schritt 1: Werte vorher speichern
                    double ge_before = hero->getAttr_ge();
                    //Schritt 2: Werte veraendern
                    hero->setAusr_sch(hero->getAusr_sch() * 2);
                    hero->setAttr_ge(hero->getAttr_ge()*1.75);
                    //Schritt 3: Kampf
                    hero->fight(hero, enemy);
                    //Schritt 4: Zueruecksetzen
                    hero->setAusr_sch(hero->getAusr_sch() / 2);
                    hero->setAttr_ge(ge_before);
                }
            }
            else {
                cout << "[ Upps! ]"
                        "Der Moment war vielversprechend, aber am Ende ist doch nichts passiert.";
            }
        }
        if (hero->fight() == 0){
            hero->setAttr_au(hero->getAttr_au()-(hero->getAusr_sch()/2));
            cout << "[ " << enemy->getName() << ": " << enemy->getLp() << " | " << enemy->getAttr_au() << " ] "<< hero->getName();
            cout << " hat verfehlt" << endl;
        }
        else if (hero->fight() == 1){
            double ausdauer = hero->getAusr_sch() - enemy->getAusr_rs();
            enemy->setAttr_au(enemy->getAttr_au()-ausdauer/2);
            enemy->setLp(enemy->getLp()-ausdauer);
            if (enemy->getAttr_au() <0){
                enemy->setAttr_au(0);
            }
            if (enemy->getLp() <0){
                enemy->setLp(0);
            }
            cout << "[ " << enemy->getName() << ": " << enemy->getLp() << " | " << enemy->getAttr_au() << " ] "<< hero->getName();
            cout << " hat getroffen." << endl;
        }
    }
};

bool operator== (const hero &name1, const hero &name2){
    // Ueberladung von dem == Operator um 2 Helden miteinander zu vergleichen
    return name1.getId() == name2.getId();
}

// INT MAIN
int main() {
    // Default Werte des Helden eingetragen.
    hero user(60, 150, 150, 40, 6, 1, 1, 0.9, "Uebungsschwert", "Leder", "Link", "Held", 250, 5, 0, 1);
    user.setTrick(0);
    fighter* player;
    hero* playuser;
    playuser = &user;
    player = &user;
    // Gegner festlegen, falls keiner gewaehlt wird: Bark der Ork
    fighter enemy(10, 200, 200, 40, 5, 1, 0.8, 0.9, "Keule", "Leder", "Bark", "Ork", 0);
    enemy.setTrick(0);
    fighter* sparing;
    sparing = &enemy;

    // Vektor der alle Gegner enthalten wird. Per Zufall werden dann zwischen 1 und 3 Gegner mit push_back hinzugefuegt.
    vector<hero> villains2;
    vector<hero> *p_villains2;
    p_villains2 = &villains2;

    // Vektor, der die good guys enthalten wird.
    vector<hero> goods2;
    vector<hero> *p_good2;
    p_good2 = &goods2;
    p_good2->push_back(user);

    // Vektor, der die Reihenfolge der Namen der Kaempfer enthaelt.
    vector<hero> order2;
    vector<hero> *p_order2;
    p_order2 = &order2;
    p_order2->push_back(user);

    cout << "THE CRAFT OF WAR\n";
    // Deklaration der Menues
    void menue();
    void mentrain();
    void menquest();

    menue();
    // Schleife, damit man zwischen den Auswahlpunkten hin- und herwechseln kann.
    while(int again = 1) {
        int selection;
        cin >> selection;
        switch (selection) {
            case 1: {// Helderstellen
                cout << "'Aufstehen!!' \n"
                        "Du hoerst es an der Tuer klopfen. Die Stimme eines kleinen Kindes weckt dich unsanft.\n"
                        "'Hey!! Du! Aufstehen!'\n"
                        "Du machst muede deine Augen auf und kraechzt etwas Unverstaendliches.\n";
                cout << "'Hae? Was hast du denn fuer eine Stimme?'\n"
                        "Erklaer dem Kind wer du bist:\n"
                        "'Ich bin eine [ Heldin ], was glaubst du wer du bist?'\n"
                        "'Ich bin ein [ Held ], was glaubst du wer du bist?'\n";
                string gender;
                cin >> gender;
                // Abfrage ob Geschlecht richtig ist.
                // Wenn es weder Heldin, heldin, held noch Held ist, dann muss man erneut eingeben.
                while (gender != "heldin" && gender != "Heldin" && gender != "w" && gender != "f" && gender != "held" && gender != "Held" && gender != "m") {
                    cin.ignore(1000, '\n');
                    cout << "Wieder hoerst du nur ein lautes \'Hae???\'.\n"
                            "Sag dem Kind ob du eine [ Heldin ] oder ein [ Held ] bist.\n";
                    cin >> gender;
                }
                // Wenn man eine Heldin ist (Gross- und Kleinschreibung egal), wird man so angesprochen.
                if (gender == "heldin" || gender == "Heldin" || gender == "w" || gender == "f") {
                    cin.ignore(1000, '\n');
                    user.setGender("Heldin");
                    cout << "'Was??? Du bist eine " << user.getGender() << "?!\n";
                }
                    // Sonst ist man ein Held.
                else {
                    cin.ignore(1000, '\n');
                    user.setGender("Held");
                    cout << "'Was??? Du bist ein " << user.getGender() << "?!\n";
                }
                cout << "Jetzt reicht es. 'Natuerlich!', rufst du durch die Tuer.\n"
                        "'Hast du noch nicht von mir gehoert?'\n"
                        "Sag dem Kind deinen Namen.\n";
                string name;
                getline(cin, name);
                if (name == "Bark" || name == "Elfriede" || name == "Horst" || name == "Anna"
                        || name == "Borsts Horst" || name == "Tark der Ork" || name == "Speerzahn der Pitbull" ||
                        name == "Holzaa Quernik" || name == "Grimmzack Arg Pack" || name == "Akro der Wikinger" ||
                        name == "Eloya"){
                    // da ich die Tricks des Kampfes anhand von Namen bestimme, darf der User keinen dieser Namen waehlen.
                    cout << "___UPPS___\nDu weisst es zwar noch nicht, aber du wirst deinen Namensvetter bald kennenlernen."
                            "\nSuch dir bitte einen anderen Namen aus.\n"
                            "Also nochmal, wie heisst du? ;)" << endl;
                    getline(cin, name);
                }
                // Abfrage ob Name stimmt.
                cout << "'Du heisst " << name << "?', fragt das Kind, diesmal neugierig.\n"
                        "Antworte dem Kind:\n"
                        "'[ Ja ], natuerlich heisse ich " << name << ".'\n"
                        "'[ Nein ], das war natuerlich ein Scherz.'\n";
                //Variable für Antwort.
                string answer;
                cin >> answer;
                //Solange cin nicht leer ist wird der Inhalt von cin ueberprueft.
                while (cin){
                    // Wenn die Antwort weder ja noch nein ist, kommt man in diese Schleife.
                    while (answer != "ja" && answer != "Ja" && answer != "y" && answer != "j" && answer != "nein" && answer != "Nein" && answer != "n") {
                        cout << "'Hae?! Du murmelst doch, da verstehe ich kein Wort.'\n"
                                "Heisst du " << name << "?\n"
                                "'[ Ja ], sagte ich doch.'\n"
                                "'[ Nein ], so heisse ich nicht.'\n";
                        cin >> answer;
                        continue;
                    }
                    // Ist die Antwort nein, n oder Nein muss man den Namen nochmal eingeben.
                    while (answer == "nein" || answer == "Nein" || answer == "n") {
                        cout << "'Mach dich nicht lustig ueber mich.', sagt das Kind enttaeuscht.\n"
                                "'Wie heisst du denn dann??\', hoerst du es fragen.\n";
                        cin.ignore();
                        getline(cin, name);
                        cout << "'Ist das diesmal dein Name? " << name << "?', fragt das Kind.\n";
                        cin >> answer;
                        continue;
                    }
                    // Ist die Antwort ja, y, j oder Ja kommt man weiter.
                    if (answer == "ja" || answer == "Ja" || answer == "y" || answer == "j") {
                        cout << "'Ah! Okay, von dir habe ich noch nie gehoert.', sagt das Kind in seiner jugendlichen Unschuld.\n"
                                "Den Stich hast du nicht erwartet. \n"
                                "'Na warte...', denkst du dir, 'dir werde ich es noch zeigen.'\n";
                        user.setName(name);
                        break;
                    }
                }
                cout << "Du stehst auf und gehst an die Tuer.\n"
                        "Das Kind schaut dich mit grossen Augen an und du begibst dich auf den Weg ins Dorf.\n"
                        "'Was machst du eigentlich hier?', fragst du das Kind.\n"
                        "'Ich hab den Kuerzeren gezogen und muss dich jetzt begleiten.'\n"
                        "Du denkst dir, dass ihr beide wohl keine Freunde werdet.\n";

                // Ende des Blocks, Menue fuer naechste Auswahl.
                menue();
                continue;
            }
            case 2: {// Uebungsmodus
                while (int training = 1){
                    int ubung;
                    mentrain();
                    cin >> ubung;
                    switch(ubung){
                        case 1: { // Waffenwahl
                            cout << "Das Kind nimmt dich unverhofft an die Hand und zieht dich zum Schmied.\n"
                                    "'Was soll denn das?', rufst du veraergert, waehrend du durch die Tuer stolperst.\n"
                                    "'Du musst dir eine Waffe aussuchen, wenn du Ueben willst', sagt das Kind ungeduldig.\n"
                                    "'Du gehst so langsam, dass schon der halbe Tag vorbei ist'.\n"
                                    "Die Schmiedin, die diese Szene miterlebt hat, kommt gut gelaunt auf dich zu.\n"
                                    "'Ja, das Kind hat recht. Was kann ich fuer dich tun?'\n"
                                    "'Ich habe leider kein Gold dabei, kannst du mir eine Waffe leihen?', fragst du etwas unsicher.\n"
                                    "Die Schmiedin kennt natuerlich die Geschichten von deinen Heldentaten und will dir beseite stehen.\n"
                                    "'Ich kann dir zum Ueben eine Waffe leiehn.'\n\n"
                                    "Der [ Speer ] ist zwar nicht so stark, aber du kannst damit geschickt kaempfen.\n"
                                    "Das [ Schwert ] ist ein guter Allrounder. Ich empfehle es oft und gerne.\n"
                                    "Der [ Morgenstern ] ist eine Klasse fuer sich. Stark aber schwer zu fuehren.\n\n"
                                    "'Welche haettest du denn gerne?'\n";
                            string waffe;
                            cin >> waffe;
                            // Wenn keine der richtigen Waffen ausgesucht wird, kommt man in diese Schleife
                            while (waffe != "speer" && waffe != "Speer" && waffe != "spear" && waffe != "1"
                                   && waffe != "schwert" && waffe != "Schwert" && waffe != "sword" && waffe != "2"
                                   && waffe != "morgenstern" && waffe != "Morgenstern" && waffe != "morningstar" && waffe != "3"
                                   && waffe != "bogen" && waffe != "Bogen" && waffe != "bow" && waffe != "4") {
                                cin.ignore(1000, '\n');
                                cout << "'Ich sage dir das wirklich oft, aber ich habe nichts ausser diesen Waffen fuer dich.'\n"
                                        "Das Kind kichert, 'So schwer war die Frage aber nicht...'\n"
                                        "Was soll es sein?\n "
                                        "[ Speer ], [ Schwert ] oder [ Morgenstern ] \n";
                                cin >> waffe;
                            }
                            // sonst in die dafuer vorgesehene
                            // innerhalb der Abfrage wird festgelegt welche Waffe man nutzt und was die Attribute der Waffe sind
                            if (waffe == "speer" || waffe == "Speer" || waffe == "spear" || waffe == "1") {
                                user.setWeapon("Uebungsspeer");
                                user.setMod_weap(1.3);
                                user.setAusr_sch(4);
                                cout << "'Hae? Wieso nimmst du denn den Speer?', sagt das Kind unglaeubig.\n"
                                        "'Was weisst du schon. Ich bin hervorragend mit dem Speer!' entgegnest du ungeduldig.\n";
                            }
                            else if (waffe == "schwert" || waffe == "Schwert" || waffe == "sword" || waffe == "2") {
                                user.setWeapon("Uebungsschwert");
                                user.setMod_weap(1.0);
                                user.setAusr_sch(6);
                                cout << "'Hae?' Wieso nimmst du das Schwert? Total. Langweilig.', sagt das Kind amuesiert.\n"
                                        "'Dir kann man es nicht recht machen. Sei einfach leise...', sagst du waehrend du dein Schwert betrachtest.\n";
                            }
                            else if (waffe == "morgenstern" || waffe == "Morgenstern" || waffe == "morningstar" || waffe == "3") {
                                user.setWeapon("Uebungsmorgenstern");
                                user.setMod_weap(0.7);
                                user.setAusr_sch(10);
                                cout << "'Hae? Wie solll man denn mit einem Morgenstern kaempfen??\', fragt das Kind unglaeubig.\n"
                                        "'Tja, gekonnt ist eben gekonnt!', entgegnest du amuesiert.\n";
                            }
                                // Easter Egg: ein gutes Spiel braucht einen Bogen...
                            else if (waffe == "bogen" || waffe == "Bogen" || waffe == "bow" || waffe == "4") {
                                user.setWeapon("Uebungsbogen");
                                user.setMod_weap(2.0);
                                user.setAusr_sch(20);
                                cout << "'Hae? Du darfst nicht einfach so einen Bogen nehmen!!', sagt das Kind strafend.\n"
                                        "'Kind, ich weiss, was ich kann und nicht kann und jetzt komm mit.\n";
                            }
                            else {
                                //
                                cout << "'Hae? Wie sind wir hier hin gekommen?', fragt dich das Kind.\n"
                                        "'Hoer zu, wir nehmen einfach dieses Schwert hier und verziehen uns.', sagst du schnell.\n";
                                user.setWeapon("Uebungsschwert");
                                user.setMod_weap(1.0);
                                user.setAusr_sch(6);
                            }
                            cout << "Du nickst der Schmiedin zu und versprichst ihr, die Waffe zuerueckzubringen.\n"
                                    "Das Kind kichert, weil du nicht mal daran gedacht hast dein Gold mitzunehmen.\n";
                            // Ende des Blocks, Menue fuer naechste Auswahl.
                            continue;
                        }
                        case 2: { // Rustungswahl
                            // Einfuehrung zur Auswahl der Ruestung.
                            cout << "Schon wieder packt dich das ungeduldige Kind an deiner Hand.\n"
                                    "Es zerrt dich zum naechsten Laden. Hat es denn vergessen, dass du kein Gold dabei hast?\n"
                                    "Du betritts den Schneider und gruesst hoeflich, dann stupst du das Kind an.\n"
                                    "'Wir gruessen, wenn wir in einen Raum kommen...', fluesterst du.\n"
                                    "'Hae? Ich hab doch was gesagt! Du hast es nur noch nicht gehoert... guten Tag....'\n"
                                    "Der Schneider laechelt euch an und fragt euch, 'Was kann ich heute fuer euch Zwei tun?\n"
                                    "Du hebst eine Braue und schuettelst den Kopf leicht.\n"
                                    "'Ich brauche eine Ruestung, aber ich habe leider kein Gold dabei, koennte ich mir etwas ausleihen?', fragst du wieder unsicher.\n"
                                    "Der Schneider nickt langsam in Gedanken und antwortet dann, 'Ja... ich habe zwar Ruestungen, aber so stark sind die nicht...'\n"
                                    "'Ein Bettler darf nicht waehlerisch sein', denkst du und folgst ihm in den naechsten Raum.\n"
                                    "'Ich habe die folgenden Ruestungen fuer dich.\n\n"
                                    "Weicher, bequemer [ Stoff ], der dich zumindest etwas schuetzt.\n"
                                    "Weiches, altes [ Leder ], das viele Schlaege abwehren wird.\n"
                                    "Gutes, altes [ Eisen ], das ziemlich schwer ist, aber viel aushaelt.\n\n"
                                    "'Woraus soll ich dir eine Ruestung zaubern, mein Kind?', fragt er.\n";
                            string material;
                            cin >> material;
                            // Weder Stoff, Leder noch Eisen angegeben, man kommt in diese Schleife.
                            while (material != "Stoff" && material != "stoff" && material != "1"
                                   && material != "Leder" && material != "leder" && material != "2"
                                   && material != "Eisen" && material != "eisen" && material != "3"
                                   && material != "nothing" && material != "nichts" && material != "nackt" && material != "4"
                                    ) {
                                cout << "'Hm. Hast du nicht zugehoert? Ich habe nur ...\n"
                                        "[ Stoff ], [ Leder ] und [ Eisen ]. \n"
                                        "Sag dem Schneider, was du gerne haettest.\n";
                                cin >> material;
                            }
                            // Sonst geht es hier weiter.
                            if (material == "Stoff" || material == "stoff" || material == "1"){
                                user.setRuestung("Stoff");
                                user.setMod_rues(1.00);
                                user.setAusr_rs(0);
                                cout << "'Hae? Stoff ist total langweilig. Wow!! Daraus koennte ich dir eine Ruestung machen!', ruft das Kind unzufrieden.\n"
                                        "'Kannst du eben nicht, sonst haette ich jetzt schon eine Ruestung', erwiderst du trotzig.\n";
                            }
                            else if (material == "Leder" || material == "leder" || material == "2"){
                                user.setRuestung("Leder");
                                user.setMod_rues(0.9);
                                user.setAusr_rs(1);
                                cout << "'Hae? Leder passt ueberhaupt nicht zu dir. Du bist viel zu gewoenlich.', lacht das Kind dich aus.\n"
                                        "'Was? W-Was? Du hast keine Ahnung wer ich bin, Kind.\n";
                            }
                            else if (material == "Eisen" || material == "eisen" || material == "3"){
                                user.setRuestung("Eisen");
                                user.setMod_rues(0.7);
                                user.setAusr_rs(2);
                                cout << "'Hae?' Natuerlich nimmst du dir Eisen, du feige Nuss', zieht dich das Kind auf.\n"
                                        "'Ich bin einfach gerne geschuetzt. Du wirst das auch noch lernen.\n";
                            }
                                // Easter Egg: der User will nackt kaempfen...
                            else if (material == "nichts" || material == "nothing" || material == "nackt" || material == "4"){
                                user.setRuestung("des Kaisers neue Kleider");
                                user.setMod_rues(0.1);
                                user.setAusr_rs(0);
                                cout << "'Hae? Wieso ziehst du dich denn aus?? Wo bin ich hier nur reingeraten, sagt das Kind und dreht sich weg.\n"
                                        "'Ich mache was ICH will und wenn du so alt bist wie ich, wirst du genauso denken!', antwortest du ohne Scham.\n";
                            }
                            if (user.getRuestung() == "des Kaisers neue Kleider"){
                                cout << "Der Schmied kichert, 'Na, so bist du wohl gewappnet...' und nickt dir zu.\n"
                                        "'Vielen Dank, dass ich mich bei Ihnen ausziehen durfte!, antwortest du.\n"
                                        "Das Kind schuettelt nur den Kopf.\n";
                            }
                            else {
                                cout << "Der Schmied betrachtet dich, 'Die Ruestung steht dir, ich hoffe du bleibst am Leben um sie mir irgendwann zu bezahlen.', und nickt dir zu.\n"
                                        "'Sie wissen, ich mache NIE Schulden!', sagst du etwas unsicher.\n"
                                        "Das Kind schuettelt den Kopf.\n";
                            }
                            continue;
                        }
                        case 3: { // Gegnerwahl
                            // Einfuehrung fuer die Gegner
                            cout << "Das Kind nimmt dich an deiner Ruestung und zieht dich in Richtung Hauptplatz.\n"
                                    "Dort ist es ziemlich laut und du siehst deinen alten Meister mit seinen Lehrlingen.\n"
                                    "Du warst lange nicht mehr hier, aber du erinnerst dich noch an deine Freunde aus alten Zeiten.\n"
                                    "\nDa war [ Bark ], der Ork, der ziemlich viel aushaelt und stark ist.\n"
                                    "Die flinke [ Elfriede ], der Elf, die mit ihrem Geschick ihre Groesse wieder gut macht.\n"
                                    "Und zuletzt noch [ Horst ], der Zwerg, der mittlerweile nicht einmal so klein aussieht.\n"
                                    "\nDas Kind staunt ein leises 'Hae...', als alle freundlich auf dich zukommen.\n"
                                    "Mit wem willst du heute ueben?\n";
                            string gegner;
                            cin >> gegner;
                            // Weder Ork, Elf noch Borst angegeben, man kommt in diese Schleife.
                            while (gegner != "ork" && gegner != "Ork" && gegner != "bark" && gegner != "Bark" &&
                                   gegner != "elf" && gegner != "Elf" && gegner != "elfriede" && gegner != "Elfriede" &&
                                   gegner != "Borst" && gegner != "borst" && gegner != "horst" && gegner != "Horst") {
                                cout << "'Hae? Du kennst doch die Helden der Stadt!', sagt das Kind vorwurfsvoll.\n"
                                        "'[ Bark ], [ Elfriede ] und [ Horst ]'. Beim letzten Wort wird das Kind ganz aufgeregt.\n"
                                        "Horst hat wohl einen Fan. Aber gegen wen willst du kaempfen?\n";
                                cin >> gegner;
                            }
                            // sonst kommt man in die richtige Abfrage
                            if (gegner == "ork" || gegner == "Ork" || gegner == "bark" || gegner == "Bark"){
                                // wenn man bereits diesen Gegner besiegt hat, kann man den Gegner noch einmal waehlen
                                // damit er wieder Ausdauer bekommt trinkt er einen Trank.
                                // ist bei den 3 Gegnern gleich
                                if (enemy.getName() == "Bark" && enemy.getAttr_au() <= 0){
                                    cout << "'Du hast Bark schon besiegt. Er setzt sich hin und nimmt einen Trank zu sich um wieder auf die Beine zu kommen.\n"
                                            "Die leere Flasche wirft er dem Kind zu, die sie auffaengt und haelt als waere es eine Trophaee.\n";
                                }
                                // Die Werte werden per Pointer an den enemy uebergeben und so geaendert.
                                sparing->setAttr_ge(10);
                                sparing->setAttr_au(200);
                                sparing->setMax_au(200);
                                sparing->setAttr_aw(40);
                                sparing->setAusr_sch(5);
                                sparing->setAusr_rs(1);
                                sparing->setMod_weap(0.8);
                                sparing->setMod_rues(0.9);
                                sparing->setWeapon("Keule");
                                sparing->setRuestung("Leder");
                                sparing->setName("Bark");
                                sparing->setGender("Gegner");
                                sparing->setTrick(0);

                                cout << "Bark lacht und klopft dir auf die Schulter, 'Wenn es sein soll, lass uns eben etwas trainieren.'\n"
                                        "Das Kind ist ganz baff. So nah war es noch nie bei einem echten Helden!\n";
                            }
                            else if (gegner == "elf" || gegner == "Elf" || gegner == "elfriede" || gegner == "Elfriede"){
                                if (enemy.getName() == "Elfriede" && enemy.getAttr_au() <= 0){
                                    cout << "'Du hast Elfriede schon besiegt. Sie nimmt einen Trank zu sich um wieder auf die Beine zu kommen.\n"
                                            "Sie nimmt eine Bluete aus ihren Haaren und steckt sie dem Kind an und das Kind vor Staunen kaum fassen was geschieht.\n";
                                }
                                sparing->setAttr_ge(70);
                                sparing->setAttr_au(50);
                                sparing->setMax_au(50);
                                sparing->setAttr_aw(15);
                                sparing->setAusr_sch(4.5);
                                sparing->setAusr_rs(0);
                                sparing->setMod_weap(1.0);
                                sparing->setMod_rues(1.0);
                                sparing->setWeapon("Elfenspeer");
                                sparing->setRuestung("Stoff");
                                sparing->setName("Elfriede");
                                sparing->setGender("Gegnerin");
                                sparing->setTrick(0);

                                cout << "Elfi laeuft auf dich zu und laesst sich von dir fangen, 'Du willst also gegen MICH kaempfen?'.\n"
                                        "'Elfi, lass uns dem Kind zeigen was wir drauf haben, einverstanden?'\n";
                            }
                            else if (gegner == "Borst" || gegner == "borst" || gegner == "horst" || gegner == "Horst"){
                                if (enemy.getName() == "Horst" && enemy.getAttr_au() <= 0){
                                    cout << "'Du hast Horst schon besiegt. Er setzt sich hin und nimmt einen Trank zu sich um wieder auf die Beine zu kommen.\n"
                                            "Das Kind stammelt und staunt stumm. Der Zwerg ist mit dem Kind auf Augenhoehe und erzaehlt einen schmutzigen Witz, den das Kind nicht versteht.\n";
                                }
                                sparing->setAttr_ge(40);
                                sparing->setAttr_au(70);
                                sparing->setMax_au(70);
                                sparing->setAttr_aw(20);
                                sparing->setAusr_sch(7);
                                sparing->setAusr_rs(2.5);
                                sparing->setMod_weap(0.9);
                                sparing->setMod_rues(0.7);
                                sparing->setWeapon("Zweihaender");
                                sparing->setRuestung("Eisen");
                                sparing->setName("Horst");
                                sparing->setGender("m");
                                sparing->setTrick(0);

                                cout << "'Natuerlich willst du gegen mich kaempfen', sagt er waehrend er seine Axt geschickt dreht.\n"
                                        "'Horst, das waere nicht das erste Mal, das ich dich besiege...', sagst du um ihn zu aergern.\n";
                            }
                            continue;
                        }
                        case 4: { // Kampf
                            // Wenn man beim Kampf verloren hat und nochmal kaempfen will, bekommt man diese Meldung
                            if (user.getAttr_au() <= 0) {
                                cout << "Du hast leider nicht genug Ausdauer um noch einmal zu kaempfen.\n";
                            }
                                // Wenn der Gegner keine Ausdauer mehr hat, kommt man hier hinein.
                            else if (enemy.getAttr_au() <= 0) {
                                cout << "\'" << enemy.getName() << ", hat nicht mehr genug Ausdauer um noch einmal zu kaempfen.'\n";
                                cout << "\'Such dir einen neuen Gegner aus.\'\n";
                                // Wenn der Held weniger als 50 Ausdauer hat, trinkt er einen Trank, damit er wieder kaempfen kann.
                                if (user.getAttr_au() < 50) {
                                    cout << "Damit der Kampf fair bleibt, trinkst du einen Trank, der etwas Ausdauer wiederherstellt.\n";
                                    user.setAttr_au(user.getAttr_au()+80);
                                    cout << "Du hast jetzt wieder " << user.getAttr_au() << " Ausdauer.";
                                    // Damit der Held seinen Trick wieder anwenden kann, muss der auch zurueckgesetzt werden.
                                    user.setTrick(0);
                                }
                            }
                            else {
                                // Der Kampf.
                                cout << "Eine kleine Traube von Dorfbewohnerin hat sich um den Hauptplatz versammelt.\n"
                                        "Du warst lange nicht hier, jeder will sehen was aus dir geworden ist.\n"
                                        "'Hae? Was stehst du dnen noch rum!! Kaempf jetzt!!, schlaegt dir das Kind vor.\n"
                                        "'Ist ja schon gut.', sagst du ungeduldig.\n";
                            }
                            // Rundenanzahl
                            int rounds = 0;
                            while (user.getAttr_au() > 0 && enemy.getAttr_au() > 0){
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
                                    cout << "Waehle die Anzahl an Runden.";
                                    cin >> kaempfen;
                                }
                                // sonst hier hinein.
                                if (kaempfen == "1") {
                                    user.fight(player, sparing);
                                    usleep(1800000);
                                    enemy.fight(sparing, player);
                                    usleep(1800000);
                                }
                                else if (kaempfen == "3") {
                                    user.fight(player, sparing, 3);
                                }
                                else if(kaempfen == "fast" || kaempfen == "schnell") {
                                    user.fight(player, sparing, "schnell");
                                }
                                else if (kaempfen == "ende") {
                                    user.fight(player, sparing, "ende");
                                }

                                if (player->getAttr_au() == 0){
                                    cout << "Du klopfst dir den Staub von deiner Ruestung und siehst wie das Kind enttaeuscht wegsieht.\n"
                                            "Was fuer eine Schande." << endl;
                                    cout << "\n______Statistik_____\n"
                                            << user.getName() << " [ Held ] " << enemy.getName() << "\n"
                                            << user.getWeapon() << " [ Waffe ] " << enemy.getWeapon() << "\n"
                                            << user.getRuestung() << " [ Ruestung ] " << enemy.getRuestung() << "\n";
                                }
                                else if (sparing -> getAttr_au() == 0){
                                    cout << sparing->getName() << " laesst sich von dir aufhelfen.\n"
                                            "'Du kaempfst immer noch gut, sagt der " << sparing->getGender() << ".\n"
                                            "Du fuehlst dich etwas staerker und ueberlegst noch einen Trainingskampf durchzufuehren." << endl;
                                    user.setExp(user.getExp()+5);
                                    cout << "Du hast Erfahrung erhalten.\n"
                                            "'Wenn du so weiter machst, muessen wir noch in die Buecherei und was ... Lernen...', wirft dir das Kind vor.\n";
                                    cout << "\n______Statistik_____\n"
                                            << user.getName() << " [ Held ] " << enemy.getName() << "\n"
                                            << user.getWeapon() << " [ Waffe ] " << enemy.getWeapon() << "\n"
                                            << user.getRuestung() << " [ Ruestung ] " << enemy.getRuestung() << "\n";
                                }
                            }
                            continue;
                        }
                        case 5: { // Exit
                            cout << "'Hae? Muessen wir wirlich schon gehen?', fragt das Kind etwas enttaeuscht.\n"
                                    "'Weisst du Kind, ich habe auch noch andere Dinge zu tun.' erklaerst du ihm.\n"
                                    "Willst du den Trainingsmodus wirklich beenden?\n"
                                    "Du kannst weiterkaempfen und Erfahrung sammeln." << endl;
                            string leave;
                            cin >> leave;
                            while (leave != "ja" && leave != "Ja" && leave != "yes"
                                   && leave != "Yes" && leave != "1" && leave != "nein"
                                   && leave != "Nein" && leave != "no" && leave != "No" &&
                                    leave != "2"){
                                cout << "Bitte antworte mit Ja oder Nein, dann haben wir keine Probleme.\n";
                                cin >> leave;
                            }
                            if (leave == "ja" || leave == "Ja" || leave == "yes" || leave == "Yes" || leave == "1"){
                                cout << "Das Kind seufzt und du nimmst es bei der Hand, damit ihr gemeinsam gehen koennt.\n";
                                break;
                            }
                            else if (leave == "nein" || leave == "Nein" || leave == "no" || leave == "No" || leave == "2"){
                                cout << "Du kannst dem Kind doch keinen Wunsch abschlagen.\n"
                                        "Du drehst dich um und bleibst noch etwas.\n";
                            }
                            continue;
                        }
                        default: { // exit maybe
                            if (cin.fail()){
                                cin.clear();
                                cin.ignore(1000, '\n');
                            }
                            cout << "Als Erzaehler der Geschichte will ich dir nur erklaeren, dass du einfach eine der Zahlen im Menue waehlen kannst.\n"
                                    "So faellt es mir auch leichter die Geschichte zu erzaehlen. Also sei so gut und waehle etwas aus dem Menue aus." << endl;
                            continue;
                        }
                    }
                    menue();
                    // wenn man aus diesem Case herausgeht, kann man sich den Punkt aus dem hoeheren Menue aussuchen.
                    break;
                }
                continue;
            }
            case 3: {// Abenteuermodus
                while (int abenteuer = 1){
                    int quest;
                    menquest();
                    cin >> quest;
                    switch(quest) {
                        case 1: { // Waffenwahl
                            cout << "Du erzaehlst gerade eine lustige Geschichte, als du einen fahrenden Haendler bemerkst.\n"
                                    "Fuer deinen Quest kannst du neue Waffen wirklich gut gebrauchen.\n"
                                    "Das Kind hofft, dass du auch hier ohne Gold auskommst, aber das hat bisher gut geklappt.\n"
                                    "Du begruesst den Haendler und fragst ihn nach Waffen, die er vielleicht fuer dich hat.\n"
                                    "Der Haendler erkennt dich sofort und ist mehr als nur bereit, dir die besten Waffen zu schenken!\n"
                                    "Das wirkt etwas komisch fuer dich, aber du streckst dich stolz und bedankst dich hoeflich.\n"
                                    "'Kennen dich die Leute wirklich?, fragt das Kind neugierig.\n"
                                    "'Kannst du mal sehen, und jetzt lass die Erwachsenen reden.', sagst du etwas herablassend.\n"
                                    "Du hoffst dass dir das Kind nicht uebel nimmt.\n"
                                    "Der Haendler zeigt dir seine Waffen und fragt dich welche du gerne haettest.\n\n"
                                    "'Ich habe einen soliden [ Speer ], der Ihnen gewiss gut dienen wird.'\n"
                                    "'Ich habe ausserdem ein [ Einhandschwert ], das ziemlich neu ist.'\n"
                                    "'Zuletzte habe ich noch einen [ Morgenstern ], der enormen Schaden zufuegt.'\n\n"
                                    "Das Kind schmunzelt, 'Was hat es nur mit diesen Morgensternen auf sich?'.\n"
                                    "Welche Waffe wirst du nehmen?" << endl;
                            string waffe;
                            cin >> waffe;
                            // Wenn keine der richtigen Waffen ausgesucht wird, kommt man in diese Schleife
                            while (waffe != "speer" && waffe != "Speer" && waffe != "spear" && waffe != "1"
                                   && waffe != "schwert" && waffe != "Schwert" && waffe != "sword" && waffe != "2"
                                   && waffe != "morgenstern" && waffe != "Morgenstern" && waffe != "morningstar" && waffe != "3"
                                   && waffe != "bogen" && waffe != "Bogen" && waffe != "bow" && waffe != "4") {
                                cin.ignore(1000, '\n');
                                cout << "Der Haendler sieht dich verlegen an, 'Ich .. weiss nicht was Sie von mir wollen.'\n"
                                        "Ich habe einen [ Speer ], ein [ Einhandschwert ] und einen [ Morgenstern ].\n"
                                        "'Ach, dieses Theater haben wir schon den ganzen Tag. " << user.getGender() << ", verstehen Sie?'\n"
                                        "Welche Waffe willst du nehmen? (Sie ist umsonst.)\n";
                                cin >> waffe;
                            }
                            // sonst in die dafuer vorgesehene
                            // innerhalb der Abfrage wird festgelegt welche Waffe man nutzt und was die Attribute der Waffe sind
                            if (waffe == "speer" || waffe == "Speer" || waffe == "spear" || waffe == "1") {
                                user.setWeapon("Speer");
                                user.setMod_weap(1.5);
                                user.setAusr_sch(8);
                                cout << "'Hae? Ein Speer ist eine komische Wahl, aber naja, wer weiss, du bist ja auch komisch.', witztelt das Kind.\n"
                                        "'Ich bin spitze mit einem Speer ... verstehst du .. weil Speere spitz sind...', versuchst du einen Scherz.\n";
                            }
                            else if (waffe == "einhandschwert" || waffe == "Einhandschwert" || waffe == "sword" || waffe == "2") {
                                user.setWeapon("Einhandschwert");
                                user.setMod_weap(1.4);
                                user.setAusr_sch(10);
                                cout << "'Hae? Wieso denn Einhand.. schwert? Du koenntest eh nie einen Zweihaender tragen', lacht das Kind.\n"
                                        "'Was? Ich trag dich gleich...', drohst du.\n";
                            }
                            else if (waffe == "morgenstern" || waffe == "Morgenstern" || waffe == "morningstar" || waffe == "3") {
                                user.setWeapon("Morgenstern");
                                user.setMod_weap(0.85);
                                user.setAusr_sch(16);
                                cout << "'Hae?' Morgensterne sind unpraktisch!! Wieso nimmst du so etwas?', meckert das Kind.\n"
                                        "'Wie oft noch, ich mache was ich will. " << user.getGender() << ", verstanden?', erklaerst du.\n";
                            }
                                // Easter Egg: ein gutes Spiel braucht einen Bogen...
                            else if (waffe == "bogen" || waffe == "Bogen" || waffe == "bow" || waffe == "4") {
                                user.setWeapon("Uebungsbogen");
                                user.setMod_weap(2.0);
                                user.setAusr_sch(20);
                                cout << "'Hae?' Wo hast du jetzt einen Bogen wieder her?', fragt das Kind verwundert.\n"
                                        "'Tja, Magie... oder so?', kicherst du leise.\n";
                            }
                            else {
                                //
                                cout << "'Hae?', das Kind ist erschoepft.\n"
                                        "Du nimmst ein Schwert und steckst es vorsichtig ein.\n";
                                user.setWeapon("Schwert");
                                user.setMod_weap(1.4);
                                user.setAusr_sch(10);
                            }
                            cout << "Ihr bedankt euch noch bei dem Haendler und macht euch auf den Weg.\n"
                                    "Da es langsam dunkel wird, wollt ihr euch beeilen um nicht in der Nacht in den Wald zu muessen.\n";
                            // Ende des Blocks, Menue fuer naechste Auswahl.
                            continue;
                        }
                        case 2: { // Rustungswahl
                            // Einfuehrung zur Auswahl der Ruestung.
                            cout << "Gemeinsam mit dem Kind wandert ihr die lange Strasse entlang und erzaehlt euch einen schlechten Witz nach dem anderen.\n"
                                    "Wer haette gedacht, dass so ein Kind so lustig sein kann? Du auf jeden Fall nicht. \n"
                                    "Auf einmal bleibt das Kind stehen und sprintet los. Langsam trottest du ihm hinterher, da es nicht weit kommt.\n"
                                    "Es steht vor einer Kiste, die bereits geoeffnet wurde.\n"
                                    "'Warst du das?', fragst du etwas mahnend. Aber das Kind erklaert dir, dass die Kiste schon so war.\n"
                                    "Du siehst dich um und entdeckst qualitativ hochwertige Ruestungen und kannst dein Glueck kaum fassen.\n"
                                    "Eine leichte Ruestung aus [ Leinen ] liegt ganz oben.\n"
                                    "Eine robuste Ruestung aus [ Starrleder ] liegt darunter.\n"
                                    "Und die nagelneue Ruestung aus [ Adamant ] liegt am Boden der Kiste\n"
                                    "Welche Ruestung willst du mitnehmen?\n";
                            string material;
                            cin >> material;
                            // Weder Stoff, Leder noch Eisen angegeben, man kommt in diese Schleife.
                            while (material != "Leinen" && material != "leinen" && material != "1"
                                   && material != "Starrleder" && material != "starrleder" && material != "2"
                                   && material != "Adamant" && material != "adamant" && material != "3"
                                    ) {
                                cout << "Ich kann dir immer nur wieder sagen, dass dieses Spiel darauf beruht, dass du auswaehlst, was ich vorgebe.\n"
                                        "Ich erfinde das ja nicht einfach so nebenbei. Welche der Ruestungen willst du nehmen?\n"
                                        "[ Leinen ], [ Starrleder ] oder [ Adamant ]?\n";
                                cin >> material;
                            }
                            // Sonst geht es hier weiter.
                            if (material == "Leinen" || material == "leinen" || material == "1"){
                                user.setRuestung("Leinen");
                                user.setMod_rues(1.00);
                                user.setAusr_rs(0);
                                cout << "'Oh wow!! Die Ruestung ist voll schoen! Aber die haelt ja nichts aus!', bemerkt das Kind.\n"
                                        "'Ich halte aus, die Ruestung wird nichtmal von einer Waffe beruehrt werden!', erklaerst du.\n";
                            }
                            else if (material == "Starrleder" || material == "starrleder" || material == "2"){
                                user.setRuestung("Starrleder");
                                user.setMod_rues(0.9);
                                user.setAusr_rs(1);
                                cout << "'Diese Ruestung steht dir sogar! Aber gewoehn dich nicht an Komplimente...', trotzt das Kind.\n"
                                        "'Das ist das netteste, das du heute zu mir gesagt hast, du Rotzloeffel.', lachst du laut auf.\n";
                            }
                            else if (material == "Adamant" || material == "adamant" || material == "3"){
                                user.setRuestung("Adamant");
                                user.setMod_rues(0.7);
                                user.setAusr_rs(2);
                                cout << "'Von solchen Ruestungen habe ich bisher nur gelesen!', staunt das Kind leise.\n"
                                        "'Ich auch', nickst du, 'und jetzt gehoert sie mir!'\n";
                            }
                            cout << "Du wirfst dir die Ruestung um und hinterlegst einen Zettel.\n"
                                    "_______________\n\n"
                                    "Vielen Dank.\n"
                                    "gezeichnet, \n"
                                    << user.getName() <<
                                                      "\n______________" << endl;
                            continue;
                        }
                        case 3: { // Gefaehrtenwahl
                            if (user.getBuddy() == 1){
                                cout << "Du hast schon einen Gefaehrten angeheuert.\n"
                                        "Wenn du wirklich so stark bist, wie du meinst, solltest ihr das zu zweit hinbekommen.\n"
                                        "Solltest du deinen Gefaehrten verlieren, kannst du dir einen neuen anheuern.\n"
                                        "Diese Taverne hat beeindruckende Traenke, vlt. findest du deinen alten Gefaehrten sogar wieder.\n";
                                continue;
                            }
                            else{
                                cout << "Auf eurem Weg zum Wald entdeckst du eine kleine Taverne und fragst dich kurz, ob du mit dem Kind hinein kannst.\n"
                                        "Aber du beschliesst, dass es in deiner Begleitung keine Angst haben muss und ihr betretet das Haus.\n"
                                        "Ein wohliger Geruch und die bekannte Waerme empfaengt euch, gemeinsam mit lautem Lachen.\n"
                                        "Ihr setzt euch an die Bar und sprecht die Wirtin an.\n"
                                        "'Hallo, wir suchen Leute, die uns begleiten', kommt dir das Kind zuvor.\n"
                                        "'Na hoer mal, wie klingt denn das. Ich bin stark genug fuer uns beide, aber kennen Sie .. jemanden, der Arbeit sucht?\n"
                                        "Die Wirtin nickt in die Richtung eines Tisches, wo sich 3 Gesellen niedergelassen haben und laut miteinander zanken.\n"
                                        "'Die 3 wollen immer einen Kampf, wenn Ihr einen bieten koennt.', sagt sie.\n\n"
                                        "[ Grimmzack ] der Zwerg ist schlau und stark.\n"
                                        "[ Akro ] der Seefahrer ist nur fuer kurze Zeit hier und noch nicht so stark.\n"
                                        "[ Eloya ] die Waldelfe ist extrem geschickt, aber ihre Ausdauer ist gering.\n"
                                        "\nWer darf es denn sein?\n";
                                string sidekick;
                                cin >> sidekick;
                                // Weder Stoff, Leder noch Eisen angegeben, man kommt in diese Schleife.
                                while (sidekick != "Grimzack" && sidekick != "grimzack" && sidekick != "zwerg" && sidekick != "Zwerg" && sidekick != "1"
                                       && sidekick != "Akro" && sidekick != "akro" && sidekick != "seefahrer" && sidekick != "Seefahrer" && sidekick != "2"
                                       && sidekick != "Eloya" && sidekick != "eloya" && sidekick != "waldelfe" && sidekick != "Waldelfe" && sidekick != "3"
                                       && sidekick != "Anna" && sidekick != "anna" && sidekick != "kind" && sidekick != "Kind" && sidekick != "4"){
                                    cout << "'Ich habe dir alle vorgestellt, hast du so ein schlechtes Gedaechtnis?', fragt die Wirtin.\n"
                                            "Das Kind lacht leise, aber es wird langsam muede.\n"
                                            "[ Grimzack ], [ Akro ] oder [ Eloya ].\n";
                                    cin >> sidekick;
                                }
                                // Randomizer der entscheidet ob sich jemand anschliessen wird.
                                // 90% dass man sich anschliesst, wenn nicht, dann muss man wieder kommen.
                                int rekrutierung = 1 + (rand() % 10);
                                // Sonst geht es hier weiter.
                                if (sidekick == "Grimzack" || sidekick == "grimzack" || sidekick == "zwerg" || sidekick == "Zwerg" || sidekick == "1"){
                                    if (rekrutierung >1){
                                        hero buddy(25, 150, 150, 35, 15, 3, 0.75, 0.8, "Zweihaendige Axt", "Kettenhemd", "Grimmzack Arg Pack", "Zwerg", 200, 750, 0, 2);
                                        cout << "Der Zwerg kommt langsam auf dich zu, stellt seine Axt ab und nickt dir zu.\n"
                                                "'Das Gold ist, was mich anzieht, nicht Eure Gesellschaft.', murmelt er.\n"
                                                "Der Zwerg hat sich euch angeschlossen.\n";
                                        p_good2->push_back(buddy);
                                        user.setBuddy(1);
                                    }
                                    else {
                                        cout << "Der Zwerg will sich nicht anschliessen. Frag noch einmal oder such dir jemand anderen aus.";
                                    }
                                }
                                else if (sidekick == "Akro" || sidekick == "akro" || sidekick == "seefahrer" || sidekick == "Seefahrer" || sidekick == "2"){
                                    if (rekrutierung >1) {
                                        hero buddy(40, 130, 130, 40, 11, 2, 0.85, 0.9, "Kurzschwert", "Hartes Leder", "Akro der Wikinger", "Seefahrer", 160, 100, 0, 3);
                                        cout << "Akro baut sich vor dir auf und spricht in einem lustigen Akzent.\n"
                                                "'In Ordnung, ich kaempfe gerne in Gesellschaft.', versichert er dir.\n"
                                                "Der Seefahrer hat sich euch angeschlossen.";
                                        p_good2->push_back(buddy);
                                        user.setBuddy(1);
                                    }
                                    else {
                                        cout << "Die Waldelfe will sich nicht anschliessen. Frag noch einmal oder such dir jemand anderen aus.\n";
                                    }
                                }
                                else if (sidekick == "Eloya" || sidekick == "eloya" || sidekick == "waldelfe" || sidekick == "Waldelfe" || sidekick == "3"){
                                    if (rekrutierung >1) {
                                        hero buddy(60, 100, 100, 40, 15, 1, 1.1, 1.0, "Bogen", "Weiche Lederruestung", "Eloya", "Waldelfe", 100, 0, 0, 4);
                                        cout << "Die Waldelfe setzt sich zu euch, unterhaelt sich freundlich mit dem Kind und ignoriert dich zuerst.\n"
                                                "'Hoer zu, wer mit so einem Kind auskommt, mit dem komme ich auch aus. Ich bin dabei.', beschliesst sie.\n"
                                                "Die Waldelfe hat sich euch angeschlossen.";
                                        p_good2->push_back(buddy);
                                        user.setBuddy(1);
                                    }
                                    else {
                                        cout << "Die Waldelfe will sich nicht anschliessen. Frag noch einmal oder such dir jemand anderen aus.\n";
                                    }
                                }
                                    // Easter Egg: der User kaempft gegen mich
                                else if (sidekick == "Anna" || sidekick == "anna" || sidekick == "kind" || sidekick == "kind" || sidekick == "4"){
                                    if (rekrutierung >9){
                                        hero buddy(10, 100, 100, 50, 20, 3, 2.0, 0.2, "Faust", "Bequeme Stofffetzen", "Anna", "Barbarin", 300, 0, 0, 5);
                                        cout << "'Du hast mich nie gefragt wie ich heisse', meckert Anna.\n"
                                                "'Aber wenn du so fragst, werde ich mit dir kaempfen!', beschliesst sie."
                                                "Das Kind hat sich dir angeschlossen.";

                                        p_good2->push_back(buddy);
                                        user.setBuddy(1);
                                    }
                                    else {
                                        cout << "Anna, das Kind, will sich nicht anschliessen. Frag noch einmal oder such dir jemand anderen aus.\n";
                                    }
                                }
                                if (user.getBuddy() == 1){
                                    cout << "Gemeinsam mit deinem Gefaehrten macht ihr euch auf den Weg in den Wald!\n";
                                }
                                else {
                                    cout << "Du ueberlegst noch, ob du die Leute noch einmal belaestigen willst oder alleine losziehst.\n";
                                }
                                continue;
                            }
                        }
                        case 4: { // Questwahl
                            if (p_villains2->size() >= 1) {
                                cout << "Du hast bereits eine Aufgabe, wenn du diese erfuellst, koennen wir uns eine neue aussuchen!\n";
                            }
                            else {
                                cout << "Du findest das grosse schwarze Brett und siehst 3 Quests, die nach dir rufen.\n\n"
                                        "Der 1. Quest ist [ leicht ], man soll nur einen Boesewicht besiegen\n"
                                        "Der 2. Quest ist [ mittel ], man muss jetzt 2 Gegner suchen und bekaempfen\n"
                                        "Der 3. Quest ist [ schwer ], da man sogar 3 Gegner besiegen muss\n\n"
                                        "Welche Schwierigkeit willst du probieren?\n"
                                        "Denk daran, du kannst einen Quest nicht ablegen, du musst ihn beenden.\n" << endl;
                                string quests;
                                cin >> quests;
                                while (quests != "leicht" && quests != "1" && quests != "easy"
                                        && quests != "mittel" && quests != "2" && quests != "medium"
                                        && quests != "schwer" && quests != "3" && quests != "hard"){
                                    cout << "'Hae? Die Frage war doch wirklich nicht schwer!!', meckert das Kind.\n"
                                            "Welche Schwierigkeit moechtest du?\n"
                                            "[ leicht ], [ mittel ] oder [ schwer ]\n";
                                    cin >> quests;
                                }
                                // Definition der Gegner. Einer - 3 von ihnen wird vorgestellt und ein Kopfgeld auf sie ausgesetzt.
                                hero villain1(30, 60, 60, 20, 8, 3, 0.8, 0.7, "Zweihaender", "Eisenruestung", "Borsts Horst", "Gauner", 100, 20, 0, 6);
                                hero villain2(10, 200, 200, 35, 10, 1, 0.75, 0.95, "Stachelkeule", "Gemischte Ruestung", "Tark der Ork", "Ork", 300, 15, 0, 7);
                                hero villain3(40, 100, 100, 20, 14, 0, 1, 1, "Gebiss", "Schuppenfell", "Speerzahn der Pitbull", "Hund", 50, 0, 0, 8);
                                hero villain4(50, 90, 90, 50, 13, 1, 0.9, 1.0, "Kurzbogen", "Verstaerktes Leinen", "Holzaa Quernik", "Goblin", 110, 30, 0, 9);

                                // Sonst geht es hier weiter.
                                if (quests == "leicht" || quests == "1" || quests == "easy"){
                                    // Sucht man nur 1 Gegner aus wird mit 25% ein Gegner ausgesucht.
                                    int rand_geg = 1 + (rand() % 4);
                                    if (rand_geg == 1) {
                                        p_villains2->push_back(villain1);
                                    }
                                    else if (rand_geg == 2) {
                                        p_villains2->push_back(villain2);
                                    }
                                    else if (rand_geg == 3) {
                                        p_villains2->push_back(villain3);
                                    }
                                    else if (rand_geg == 4) {
                                        p_villains2->push_back(villain4);
                                    }
                                    cout << "Auf dem Zettel steht geschrieben: \n\n"
                                            "Der folgende Boesewicht ist zu erschlagen:\n";
                                    cout << villains2[0].getName() << endl;
                                }
                                else if (quests == "mittel" || quests == "2" || quests == "medium"){
                                    // Sucht man 2 Gegner aus, hat man 6 moegliche Kombinationen.
                                    int rand_geg = 1 + (rand() % 6);
                                    if (rand_geg == 1) {
                                        p_villains2->push_back(villain1);
                                        p_villains2->push_back(villain2);
                                    }
                                    else if (rand_geg == 2) {
                                        p_villains2->push_back(villain2);
                                        p_villains2->push_back(villain3);
                                    }
                                    else if (rand_geg == 3) {
                                        p_villains2->push_back(villain3);
                                        p_villains2->push_back(villain4);
                                    }
                                    else if (rand_geg == 4) {
                                        p_villains2->push_back(villain2);
                                        p_villains2->push_back(villain4);
                                    }
                                    else if (rand_geg == 5) {
                                        p_villains2->push_back(villain1);
                                        p_villains2->push_back(villain3);
                                    }
                                    else if (rand_geg == 6) {
                                        p_villains2->push_back(villain1);
                                        p_villains2->push_back(villain4);
                                    }
                                    cout << "Auf dem Zettel steht geschrieben: \n\n"
                                            "Die folgenden Boesewichte sind zu erschlagen:\n";
                                    cout << villains2[1].getName() << endl;
                                    cout << villains2[0].getName() << endl;
                                }
                                else if (quests == "schwer" || quests == "3" || quests == "hard"){
                                    // Wenn man 3 Gegner aussucht, gibt es wieder nur 4 Moeglichkeiten
                                    int rand_geg = 1 + (rand() % 4);
                                    if (rand_geg == 1) {
                                        p_villains2->push_back(villain1);
                                        p_villains2->push_back(villain2);
                                        p_villains2->push_back(villain3);
                                    }
                                    else if (rand_geg == 2) {
                                        p_villains2->push_back(villain1);
                                        p_villains2->push_back(villain2);
                                        p_villains2->push_back(villain4);
                                    }
                                    else if (rand_geg == 3) {
                                        p_villains2->push_back(villain1);
                                        p_villains2->push_back(villain3);
                                        p_villains2->push_back(villain4);
                                    }
                                    else if (rand_geg == 4) {
                                        p_villains2->push_back(villain2);
                                        p_villains2->push_back(villain3);
                                        p_villains2->push_back(villain4);
                                    }
                                    cout << "Auf dem Zettel steht geschrieben: \n\n"
                                            "Die folgenden Boesewichte sind zu erschlagen:\n";
                                    cout << villains2[0].getName() << endl;
                                    cout << villains2[1].getName() << endl;
                                    cout << villains2[2].getName() << endl;
                                }
                            }
                            cout << "\nMit dem Quest in deinem Inventar, machst du dich gemeinsam mit dem Kind auf den Weg tiefer in den Wald.\n";
                            continue;
                        }
                        case 5: { // Adventure
                            if (p_villains2->size() == 0){
                                cout << "Du stehst vor dem Wald und denkst dir, dass du wohl etwas vergessen hast.\n"
                                        "Ohne Quest kannst du hier nichts erreichen.\n"
                                        "Geh zurueck zum schwarzen Brett und hol dir einen Quest.\n";}
                            else {
                                cout << "Du betrittst den dunklen Wald und schon siehst du dunkle Gestalten auf dich zukommen.\n"
                                        "Der Kampf beginnt noch ehe du dich bereitmachen kannst.\n\n" << endl;
                                vector<hero>container2;

                                container2.insert(container2.begin(), p_good2->begin()+1, p_good2->end());
                                container2.insert(container2.begin()+container2.size(), p_villains2->begin(), p_villains2->end());

                               while (container2.size() >1 ){
                                    if (container2[0].getAttr_au() >= container2[1].getAttr_au() &&
                                        container2[0].getAttr_au() >= container2[2].getAttr_au() &&
                                        container2[0].getAttr_au() >= container2[3].getAttr_au()){
                                        p_order2->push_back(container2[0]);
                                        container2.erase(container2.begin());
                                    }
                                    else if (container2[1].getAttr_au() >= container2[0].getAttr_au() &&
                                             container2[1].getAttr_au() >= container2[2].getAttr_au() &&
                                             container2[1].getAttr_au() >= container2[3].getAttr_au()){
                                        p_order2->push_back(container2[1]);
                                        container2.erase(container2.begin()+1);
                                    }
                                    else if (container2[2].getAttr_au() >= container2[0].getAttr_au() &&
                                             container2[2].getAttr_au() >= container2[1].getAttr_au() &&
                                             container2[2].getAttr_au() >= container2[3].getAttr_au()){
                                        p_order2->push_back(container2[2]);
                                        container2.erase(container2.begin()+2);
                                    }
                                    else if (container2[3].getAttr_au() >= container2[0].getAttr_au() &&
                                             container2[3].getAttr_au() >= container2[1].getAttr_au() &&
                                             container2[3].getAttr_au() >= container2[2].getAttr_au()){
                                        p_order2->push_back(container2[3]);
                                        container2.erase(container2.begin()+3);
                                    }
                                }
                                if (container2.size() == 1){
                                    p_order2->push_back(container2[0]);
                                    container2.erase(container2.begin(), container2.begin());
                                }
                                int goodsize = goods2.size();
                                int badsize = villains2.size();
                                while (player->getAttr_au() > 0 && player->getLp() > 0){
                                    if (badsize == 0){
                                        cout << "Du hast deinen Quest erfuellt!\n"
                                                "Das Kind schaut dich mit grossen Augen an und ist von den Socken!\n"
                                                "Du hast es geschafft, das Kind sieht dich endlich als " << user.getGender() <<"!\n" << endl;
                                        if (goodsize > 1){
                                            // user hat ienen Gefaehrten, der nicht gestorben ist
                                            user.setGold(user.getGold()+villains2.size());
                                        }
                                        else {
                                            user.setGold(user.getGold()+villains2.size()*2);
                                        }
                                        break;
                                    }
                                    for (int i = 0; i < order2.size(); i++) {
                                        if (find(goods2.begin(), goods2.end(), order2[i]) != goods2.end()) {
                                            int zufall = 1 + (rand() % badsize);
                                            hero *kaempfer;
                                            kaempfer = &order2[i];
                                            hero *gegnerle;
                                            gegnerle = &villains2[zufall - 1];
                                            order2[i].battle(kaempfer, gegnerle);
                                            villains2[zufall - 1].setAttr_au((gegnerle->getAttr_au()));
                                            villains2[zufall - 1].setLp(gegnerle->getLp());
                                            if (villains2[zufall - 1].getAttr_au() <= 0) {
                                                for (int j = -3; j <= 3; j++) {
                                                    if (villains2[zufall - 1].getId() == order2[j].getId()) {
                                                        cout << villains2[zufall-1].getName() << " ist komplett erschoepft und kann nicht mehr weiterkaempfen." << endl;
                                                        order2.erase(order2.begin() + i + j);
                                                        badsize -= 1;
                                                        continue;
                                                    }
                                                }
                                            }
                                            if (villains2[zufall-1].getLp() <= 0){
                                                for (int j = -3; j <= 3; j++) {
                                                    if (villains2[zufall - 1].getId() == order2[j].getId()) {
                                                        cout << "[ Vernichtung! ] " << villains2[zufall-1].getName() << " liegt auf dem harten Boden und geniesst den letzten Atemzug." << endl;
                                                        order2.erase(order2.begin() + i + j);
                                                        badsize -= 1;
                                                        continue;
                                                    }
                                                }
                                            }
                                        }
                                        else if (find(villains2.begin(), villains2.end(), order2[i]) != villains2.end()) {
                                            int zufall = 1 + (rand() % goodsize);
                                            hero *kaempfer2;
                                            kaempfer2 = &order2[i];
                                            hero *gegnerle2;
                                            gegnerle2 = &goods2[zufall - 1];
                                            order2[i].battle(kaempfer2, gegnerle2);
                                            order2[i].setAttr_au(kaempfer2->getAttr_au());
                                            goods2[zufall - 1].setAttr_au((gegnerle2->getAttr_au()));
                                            if (goods2[zufall - 1].getAttr_au() <= 0) {
                                                for (int j = -3; j <= 3; j++) {
                                                    if (goods2[zufall - 1].getId() == order2[j].getId()) {
                                                        cout << "[ Vernichtung! ]" << goods2[zufall-1].getName() << " stuerzt zu Boden und bleibt besiegt liegen." << endl;
                                                        order2.erase(order2.begin() + i + j);
                                                        goodsize -= 1;
                                                        user.setBuddy(0);
                                                        continue;
                                                    }
                                                    if(goods2[zufall -1].getId() == 1){
                                                        player->setAttr_au(0);
                                                    }
                                                }
                                            }
                                            if (goods2[zufall - 1].getLp() <= 0) {
                                                for (int j = -3; j <= 3; j++) {
                                                    if (goods2[zufall - 1].getId() == order2[j].getId()) {
                                                        cout << goods2[zufall-1].getName() << " liegt mit dem Gesicht nach unten auf dem Boden. Eine tiefe Trauer befaellt die Umstehenden." << endl;
                                                        order2.erase(order2.begin() + i + j);
                                                        user.setBuddy(0);
                                                        goodsize -= 1;
                                                        continue;
                                                    }
                                                    if(goods2[zufall -1].getId() == 1){
                                                        player->setLp(0);
                                                    }
                                                }
                                            }
                                        }
                                        usleep(1800000);
                                    }
                                }
                                if (player->getAttr_au() <= 0 || player->getLp() <= 0){
                                    cout << "Erschoepft packst du deine Ruestung und deine Waffe weg.\n"
                                            "'Hae? Und das soll es jetzt gewesen sein?', fragt das Kind enttaeuscht.\n"
                                            "'Ich dachte du waerst stark und kannst alle schaffen.'\n"
                                            "Geknickt macht ihr euch auf den Heimweg." << endl;
                                    break;
                                }
                            }

                            continue;
                        }
                        case 6: { // Exit
                            cout << "Willst du das Abenteuer ruhen lassen?\n" << endl;
                            string really;
                            cin >> really;
                            while (really != "ja" && really != "Ja" && really != "yes"
                                   && really != "Yes" && really != "1" && really != "nein"
                                   && really != "Nein" && really != "no" && really != "No" &&
                                    really != "2"){
                                cout << "Bitte antworte mit [ Ja ] oder [ Nein ] damit wir uns verstehen.\n";
                                cin >> really;
                            }
                            if (really == "ja" || really == "Ja" || really == "yes" || really == "Yes" || really == "1"){
                                cout << "In Ordnung, ich setze dich wieder vor die Tore des Dorfes.\n";
                                break;
                            }
                            else if (really == "nein" || really == "Nein" || really == "no" || really == "No" || really == "2"){
                                cout << "Wenn du noch bleiben willst, ist das auch in Ordnung.\n";
                            }
                            continue;
                        }
                        default: { // default case, wenn man nicht 1-6 verwendet
                            if (cin.fail()){
                                cin.clear();
                                cin.ignore(1000, '\n');
                            }
                            cout << "Als Erzaehler der Geschichte, glaube ich dir nicht, dass du noch nicht weisst wie das Menue funktioniert.\n"
                                    "Bitte suche eine Zahl aus und dann haben wir den Salat nicht mehr.\n" << endl;
                            continue;
                        }
                    }
                    menue();
                    break;
                }
                continue;
            }
            case 4: { // EXP Exchange
                if (user.getExp() < 10){
                    cout << "Du hast zu wenig Erfahrung um dich wieterzubilden. Mache ein paar Trainingskaempfe und dann sehen wir uns wieder.\n";
                    menue();
                    continue;
                }
                else {
                    cout << "Du betrittst mit dem Kind gemeinsam die Buecherei.\n"
                            "Die Ruhe und das Wissen sind praktisch spuerbar und du beschliesst dich, etwas in den Buechern zu stoebern.\n"
                            "Woruber moechtest du mehr erfahren?\n"
                            "(Das Attribut, das du aussuchst wird um 1 erhoeht.\n"
                            "\n[ Geschick ], [ Ausdauer ], [ Angriffswert ] oder [ Lebenspunkte ]?\n";
                    string attr;
                    cin >> attr;
                    while (attr != "ge" && attr != "Ge" && attr != "GE" && attr != "geschick" && attr != "Geschick" && attr != "1"
                           && attr != "au" && attr != "Au" && attr != "AU" && attr != "ausdauer" && attr != "Ausdauer" && attr != "2"
                           && attr != "aw" && attr != "Aw" && attr != "AW" && attr != "angriffswert" && attr != "Angriffswert" && attr != "3"
                           && attr != "lp" && attr != "Lp" && attr != "LP" && attr != "lebenspunkte" && attr != "Lebenspunkte" && attr != "4"){
                        cout << "'Hae? Das habe ja sogar ich verstanden..., sag doch einfach was du wissen willst und ich finde das Buch.' schlaegt das Kind vor\n"
                                "[ Geschick ], [ Ausdauer ], [ Angriffswert ] oder [ Lebenspunkte ]?\n";
                        cin >> attr;
                    }
                    if (attr == "ge" || attr == "Ge" || attr == "GE" || attr == "geschick" || attr == "Geschick" || attr == "1"){
                        cout << "Das Kind verschwindet kurz und du hoerst ein leises 'Hae?' und musst schmunzeln.\n"
                                "Es taucht mit einem Buch ueber 'Geschick' auf und du beginnst zu lesen." << endl;
                        user.setAttr_ge(user.getAttr_ge()+1);
                        user.setExp(user.getExp()-10);
                    }
                    else if (attr == "au" || attr == "Au" || attr == "AU" || attr == "ausdauer" || attr == "Ausdauer" || attr == "2"){
                        cout << "Das Kind verschwindet kurz und du hoerst ein leises 'Hae?' und musst schmunzeln.\n"
                                "Es taucht mit einem riesigen, aber duennen Buch ueber 'Ausdauer' auf und du versuchst dich zu konzentrieren.\n";
                        user.setAttr_au(user.getAttr_au()+1);
                        user.setExp(user.getExp()-10);
                    }
                    else if (attr == "aw" || attr == "Aw" || attr == "AW" || attr == "angriffswert" || attr == "Angriffswert" || attr == "3"){
                        cout << "Das Kind verschwindet kurz und du hoerst ein leises 'Hae?' und musst schmunzeln.\n"
                                "Es taucht auf, taucht wieder unter, wirft ein Buch zur Seite und kommt dann mit einem Zettel zurueck.\n"
                                "'Ausdauer - oder wie man laenger kaempft', steht darauf. Du liest es schnell durch.\n";
                        user.setAttr_aw(user.getAttr_aw()+1);
                        user.setExp(user.getExp()-10);
                    }
                    else if (attr == "lp" || attr == "Lp" || attr == "LP" || attr == "lebenspunkte" || attr == "Lebenspunkte" || attr == "4"){
                        cout << "Das Kind verschwindet kurz und du hoerst ein leises 'Hae?' und musst schmunzeln.\n"
                                "Es erklaert dir kurz alles was du ueber das Leben wissen musst, und fragt dich am Schluss ob du noch Fragen hast.\n"
                                "Du sagst, du haettest nur eine: 'Hae?!' und ihr beide lacht so laut, dass man euch rauswirft.\n";
                        user.setLp(user.getLp()+1);
                        user.setExp(user.getExp()-10);
                    }
                    cout << "Voll gestaerkt mit Wissen und einem kleinen Buch, das du dem Kind spaeter schenken moechtest, macht ihr euch gemeinsam auf den Weg.\n";
                    menue();
                    continue;
                }

                continue;
            }
            case 5: { // Exit
                cout << "Willst du aus dem Spiel raus?" << endl;
                string exit;
                cin >> exit;
                while (exit != "ja" && exit != "Ja" && exit != "yes"
                       && exit != "Yes" && exit != "1" && exit != "nein"
                       && exit != "Nein" && exit != "no" && exit != "No" &&
                       exit != "2"){
                    cout << "Wie immer, einfach nur [ ja ] oder [ nein ] sagen!\n";
                    cin >> exit;
                }
                if (exit == "ja" || exit == "Ja" || exit == "yes" || exit == "Yes" || exit == "1"){
                    cout << "Vielen Dank, dass du das Spiel gespielt hast.\n";
                    break;
                }
                else if (exit == "nein" || exit == "Nein" || exit == "no" || exit == "No" || exit == "2"){
                    cout << "'Hae?' Dann bleib noch!!'\n";
                }
                continue;
            }
            default: { // default case, wenn man nicht 1-6 verwendet
                if (cin.fail()){
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                cout << "Such dir bitte eine Zahl zwischen 1 und 5 aus und dann geht das Abenteuer schon los!\n" << endl;
                menue();
                continue;
            }
        }
        break;
    }
        // return 0 weil int main
    return 0;
};
void menue(){
    cout << "\n________Menue_______\n";
    cout << "[ 1 ] Aufwachen!\n"
            "[ 2 ] Trainieren!\n"
            "[ 3 ] Auf ins Abenteuer!\n"
            "[ 4 ] Lesen!\n"
            "[ 5 ] Beenden!\n";
};

void mentrain(){
    cout << "\n______Training______\n";
    cout << "[ 1 ] Waffen!\n"
            "[ 2 ] Ruestungen!\n"
            "[ 3 ] Gegner?\n"
            "[ 4 ] Trainieren!\n"
            "[ 5 ] Weg hier!\n";
};

void menquest(){
    cout << "\n________Quest_______\n";
    cout << "[ 1 ] Waffen!\n"
            "[ 2 ] Ruestungen!\n"
            "[ 3 ] Taverne!\n"
            "[ 4 ] Schwarzes Brett!\n"
            "[ 5 ] Auf in den Kampf!\n"
            "[ 6 ] Raus hier!\n";

};

void credits(){
    cout << "\nCREDITS - CRAFT OF WAR\n\n"
            "Projekt Manager: Gerald Holzmann\n"
            "Original Story: Anna Majewski\n"
            "Programmierung: Anna Majewski\n"
            "Programmierung Support: Gerald Holzmann, learncpp.com\n"
            "Alpha Tester: Jacek Majewski\n"
            "Besonderes Dankeschoen: Rainstorm Entertainment und dem Spieler dieses Spiels\n";
};