#ifndef MINUTERIE_H
#define MINUTERIE_H

#include <QLabel>
#include <QTimer>

class Minuterie : public QLabel
{
    Q_OBJECT
public:
    Minuterie(int minute, int seconde = 0, QWidget* obj = nullptr);
    ~Minuterie();
    void stop();
    void resume();
    QString to_string();

public slots:
    void update();

signals:
    void timeout();

private:
    int minutes_;
    int secondes_;
    QTimer* timer_;
};

#endif // MINUTERIE_H
