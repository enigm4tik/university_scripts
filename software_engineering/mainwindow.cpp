#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "card.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_stapel_clicked(){

    // Erstellen des Objekts carddeck und den Pointer darauf.
    card carddeck;
    card* p_carddeck= &carddeck;

    // Erstellen der Vektoren fuer User1 und User2.
    std::vector<QPixmap> user1;
    std::vector<QPixmap> user2;

    // Anwenden der Funktionen dealCards fuer den 1. User
    // und redealCards fuer den 2. User.

    user1 = p_carddeck->dealCards();
    user2 = p_carddeck->redealCards();

    /* Zuweisen von den Pixmaps auf die Labels.
     * Ich habe ein Array fuer alle QLabel* erstellt.
     * Danach kann man ueber diese iterieren um die Pixmap Objekte zu setzen.
     */

    // QLabel* Array
    QLabel *me[5];
    me[0] = ui->me1;
    me[1] = ui->me2;
    me[2] = ui->me3;
    me[3] = ui->me4;
    me[4] = ui->me5;

    // Schleife ueber die Pixmaps.
    for (int i = 0; i<5; i++){
        me[i]->setPixmap(user1[i]);
    }

    // QLabel* Array
    QLabel *opp[5];
    opp[0] = ui->opp1;
    opp[1] = ui->opp2;
    opp[2] = ui->opp3;
    opp[3] = ui->opp4;
    opp[4] = ui->opp5;

    // Schleife ueber die Pixmaps.
    for (int i = 0; i<5; i++){
        opp[i]->setPixmap(user2[i]);
    }
}
