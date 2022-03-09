#ifndef CARD_H
#define CARD_H
#include <iostream> // Um mit IO Streams arbeiten zu können.
#include <string> // Um Strings verwenden zu können
#include <algorithm> // Um random_shuffle zu verwenden
#include <QPixmap> // Um Bilder auf Labels zu setzen
#include "vector" // Um Vektoren verwenden zu können
#include <QString> // Um std::strings in QStrings umwandeln zu können


class card
{
public:
    card();
    std::vector<QPixmap> dealCards();
    std::vector<QPixmap> redealCards();
    std::vector<QPixmap> transform(std::vector<std::string> user, std::vector<QPixmap> vector);

private:
    std::vector<std::string> deck;
    std::vector<std::string>* p_deck = &deck;
    std::vector<QPixmap> user1;
    std::vector<QPixmap> user2;
};

#endif // CARD_H
