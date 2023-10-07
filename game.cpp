#include "game.h"

Game::Game(QWidget *parent)
    : QMainWindow(parent)
{
    Home* home = new Home(this);
    this->setFixedSize(QSize(680, 680));
    this->setCentralWidget(home);
}

Game::~Game(){}

