#include "game.h"

Game::Game(QWidget *parent)
    : QMainWindow(parent), home_(nullptr), echiquier_(nullptr), conteneur_(nullptr), machine_(false)
{
    setup();
}

void Game::setup()
{
    this->setWindowIcon(QIcon(APP_ICON));
    this->setStyleSheet(
        "QPushButton#Controls{"
        "height: 50px; "
        "font-size: 20px; "
        "}"
    );
    this->setFixedSize(QSize(LARGEUR_HOME, HAUTEUR_HOME));
    home_ = new Home(this);
    connect(home_, SIGNAL(lancer_jeu(bool)), this, SLOT(lancer_jeu(bool)));
    connect(home_, SIGNAL(quitter_jeu()), this, SLOT(quitter_jeu()));
    this->setCentralWidget(home_);
}

void Game::accueil()
{
    this->setFixedSize(QSize(LARGEUR_HOME, HAUTEUR_HOME));
    home_ = new Home(this);
    connect(home_, SIGNAL(lancer_jeu(bool)), this, SLOT(lancer_jeu(bool)));
    connect(home_, SIGNAL(quitter_jeu()), this, SLOT(quitter_jeu()));
    this->setCentralWidget(home_);
}

void Game::recommencer()
{
    QDialog* fenetre = new QDialog;
    fenetre->setWindowTitle("Confirmation");
    QVBoxLayout *layout = new QVBoxLayout;
    QHBoxLayout* btn_group = new QHBoxLayout;
    QPushButton* btn_oui = new QPushButton("Oui");
    QPushButton* btn_non = new QPushButton("Non");
    connect(btn_oui, &QPushButton::clicked, fenetre, [this, fenetre](){
        delete echiquier_;
        echiquier_ = new Echiquier(machine_, this);
        connect(echiquier_, SIGNAL(recommencer()), this, SLOT(recommencer()));
        layout_->addWidget(echiquier_);
        fenetre->accept();
    });
    connect(btn_non, &QPushButton::clicked, fenetre, [fenetre](){
        fenetre->accept();
    });
    btn_group->addWidget(btn_oui);
    btn_group->addWidget(btn_non);
    QLabel* label = new QLabel;
    label->setText("Êtes vous sûr de vouloir commencer une nouvelle partie ? \n");
    layout->addWidget(label);
    layout->addLayout(btn_group);
    fenetre->setLayout(layout);
    fenetre->exec();
}

void Game::lancer_jeu(bool machine)
{
    machine_ = machine;
    delete home_;
    echiquier_ = new Echiquier(machine, this);
    connect(echiquier_, SIGNAL(recommencer()), this, SLOT(recommencer()));
    connect(echiquier_, SIGNAL(aller_accueil()), this, SLOT(accueil()));

    conteneur_ = new QWidget(this);
    layout_ = new QHBoxLayout;
    QVBoxLayout* controls_layout = new QVBoxLayout;
    QWidget* controls_widget = new QWidget;

    btn_recommencer_ = new QPushButton("Nouvelle partie");
    btn_accueil_ = new QPushButton("Menu principal");

    QPixmap cursor(CURSOR);
    cursor = cursor.scaled(QSize(TAILLE_CURSOR, TAILLE_CURSOR));

    btn_recommencer_->setCursor(QCursor(cursor));
    btn_accueil_->setCursor(QCursor(cursor));

    btn_accueil_->setObjectName("Controls");
    btn_recommencer_->setObjectName("Controls");

    connect(btn_accueil_, SIGNAL(clicked(bool)), this, SLOT(accueil()));
    connect(btn_recommencer_, SIGNAL(clicked(bool)), this, SLOT(recommencer()));

    controls_layout->setAlignment(Qt::AlignTop);
    controls_layout->addWidget(btn_accueil_);
    controls_layout->addWidget(btn_recommencer_);

    controls_widget->setLayout(controls_layout);
    controls_widget->setFixedSize(QSize(LARGEUR_CONTROLS, HAUTEUR_CONTROLS));

    //layout->setAlignment(Qt::AlignLeft);
    layout_->addWidget(controls_widget);
    layout_->addWidget(echiquier_);

    conteneur_->setLayout(layout_);
    this->setFixedSize(QSize(LARGEUR_GAME, HAUTEUR_GAME));
    this->setCentralWidget(conteneur_);
}

void Game::quitter_jeu()
{
    this->close();
}

Game::~Game(){}

