#include "card.h"

card::card(){
    /*************************************************************************
     * * * * * * * * * * * * * * CONSTRUCTOR * * * * * * * * * * * * * * * * *
     ************************************************************************/

    // Hier werden die Farben der Karten initialisiert.
    std::vector<std::string> color;
    color.push_back("pik");
    color.push_back("karo");
    color.push_back("treff");
    color.push_back("heart");

    // Hier werden die Werte der Karten initialisiert.
    std::vector<std::string> value;
    value.push_back("2");
    value.push_back("3");
    value.push_back("4");
    value.push_back("5");
    value.push_back("6");
    value.push_back("7");
    value.push_back("8");
    value.push_back("9");
    value.push_back("10");
    value.push_back("jack");
    value.push_back("queen");
    value.push_back("king");
    value.push_back("ass");

    /* Hier werden die Karten in einen String umgewandelt
     * und in einen String umgewandelt.                 */
    for (int i = 0; i<4; i++){
        std::string card = color[i]; // bsp: i=0, "pik"
        for (int j =0; j<13; j++){
            std::string card2 = card + "_" + value[j]; // bsp: i=0, j=0: "pik_2"
            // Alle Karten in einem Vektor sammeln.
            p_deck->push_back(card2);
        }
    }
    // Hier wird der Stapel gemischt.
    std::random_shuffle (p_deck->begin(), p_deck->end());
}

/*************************************************************************
* * * * * * * * * * * * * TRANSFORMATION * * * * * * * * * * * * * * * * *
 ************************************************************************/
/* In dieser Funktion werden die Strings in QPixmap Objekte umgewandelt.
 * Das geschieht zuerst durch Anfuegen des lokalen Pfades.
 * Danach wird der String in QString umgewandelt.
 * Der QString in ein QPixmap Objekt umgewandelt.
 * Am Schluss wird das in der Schleife an den Vektor angefuegt.
 * Uebergeben werden der Vektor<string> und der Vektor<QPixmap>.
 */

std::vector<QPixmap> card::transform(std::vector<std::string> user, std::vector<QPixmap> vector){
    for (int i = 0; i<5; i++){
        std::string c = "../cards/cards/" + user[i];
        QString qstr = QString::fromStdString(c);
        QPixmap qpix(qstr);
        vector.push_back(qpix);
    }
    return vector;
}

/*************************************************************************
  * * * * * * * * * * * * * * DEAL CARDS * * * * * * * * * * * * * * * * *
 ************************************************************************/
/* In dieser Funktion werden die ersten 5 Karten an den User verteilt.
 * Die Funktion Transform wird verwendet, damit aus den Strings dann
 * QPixmap Objekte werden.
 */

std::vector<QPixmap> card::dealCards(){
    std::vector<std::string> user(p_deck->begin(), p_deck->begin()+5);

    // TRANSFORM FUNKTION
    std::vector<QPixmap>new_vec2 = card::transform(user, user1);

    return new_vec2;
}

/*************************************************************************
* * * * * * * * * * * * * * REDEAL CARDS * * * * * * * * * * * * * * * * *
 ************************************************************************/
/* In dieser Funktion werden die 1. 5 Karten aus dem Vektor entfernt.
 * Das geschieht, weil ja der 1. User bereits 5 Karten hat.
 * Danach werden die naechsten 5 Karten an den User verteilt.
 * Die Funktion Transform wird verwendet, damit aus den Strings dann
 * QPixmap Objekte werden.
 */

std::vector<QPixmap> card::redealCards(){
    p_deck->erase(p_deck->begin(), p_deck->begin()+5);
    std::vector<std::string> next5(p_deck->begin(), p_deck->begin()+5);

    // TRANSFORM FUNKTION
    std::vector<QPixmap>new_vec = transform(next5, user2);

    return new_vec;
}
