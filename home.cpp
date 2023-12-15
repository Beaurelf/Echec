#include "home.h"

Home::Home(QMainWindow *parent) :
    QWidget(parent)
{

    QWidget* widget = new QWidget;
    QWidget* opacityWidget = new QWidget;

    widget->setObjectName("Home");

    QGraphicsOpacityEffect*   opacityEffect = new QGraphicsOpacityEffect;

    //effect->setOpacity(100);

    QVBoxLayout* container = new QVBoxLayout;
    QVBoxLayout* layout = new QVBoxLayout;
    QVBoxLayout* opacityLayout = new QVBoxLayout;

    opacityWidget->setObjectName("OpacityWidget");

    QLabel* welcome = new QLabel("Chess");
    welcome->setAlignment(Qt::AlignCenter);
    QPushButton* btn1 = new QPushButton("J1 VS CPU");
    QPushButton* btn2 = new QPushButton("J1 VS J2");
    QPushButton* btn_quitter = new QPushButton("Quitter");

    QPixmap cursor(":/images/img/cursor.png");
    cursor = cursor.scaled(QSize(120,120));

    btn1->setCursor(QCursor(cursor));
    btn2->setCursor(QCursor(cursor));
    btn_quitter->setCursor(QCursor(cursor));

    connect(btn1 , &QPushButton::clicked,[this, parent]{lancer_jeu(true, parent);});
    connect(btn2 , &QPushButton::clicked,[this, parent]{lancer_jeu(false, parent);});
    connect(btn_quitter , &QPushButton::clicked,[this, parent]{quitter_jeu(parent);});

    layout->addWidget(welcome);
    layout->addWidget(btn1);
    layout->addWidget(btn2);
    layout->addWidget(btn_quitter);

    opacityLayout->addWidget(opacityWidget, Qt::AlignCenter);
    opacityWidget->setLayout(layout);
    opacityWidget->setGraphicsEffect(opacityEffect);

    widget->setLayout(opacityLayout);
    widget->setContentsMargins(150, 150, 150, 150);

    container->addWidget(widget, Qt::AlignCenter);

    setStyleSheet(
        "QWidget#Home{"
        "background-image: url(:/images/img/fond.png); "
        "background-repeat: no-repeat; "
        "background-position: center;"
        "}"
        "QWidget#OpacityWidget{"
        "background: rgba(255, 255, 255, 0.25); "
        "border: 1px solid rgba(255, 255, 255, 0.35);"
        "border-radius: 20px; "
        "}"
        "QLabel{"
        "font-family: Century Gothic; "
        "font-weight: bold; "
        "font-size: 55px; "
        "}"
        "QPushButton{"
        "height: 50px; "
        "font-size: 20px; "
        "}"
    );
    this->setLayout(container);
}

void Home::lancer_jeu(bool machine, QMainWindow* window){
    Echiquier* echiquier = new Echiquier(machine, window);
    window->setFixedSize(QSize(680,680));
    window->setContentsMargins(15, 0, 20, 0);
    window->setCentralWidget(echiquier);
    delete this;
}

void Home::quitter_jeu(QMainWindow* window){
    window->close();
}
Home::~Home(){}
