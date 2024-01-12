#ifndef HOME_H
#define HOME_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QGraphicsEffect>
#include <QPushButton>
#include <QPixmap>


class Home : public QWidget
{
    Q_OBJECT

public:
    explicit Home(QMainWindow* parent = nullptr);
    ~Home();

signals:
    void lancer_jeu(bool machine);
    void quitter_jeu();
};
#endif // HOME_H
