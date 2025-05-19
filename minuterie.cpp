#include "minuterie.h"
#include "qdebug.h"
#include <iomanip>
#include <sstream>

Minuterie::Minuterie(int minute, int seconde, QWidget *obj): QLabel(obj), minutes_(minute), secondes_(seconde){
    timer_ = new QTimer(this);
    setText(to_string());
    connect(timer_, &QTimer::timeout, this, &Minuterie::update);
}

Minuterie::~Minuterie() {
    delete timer_;
}

void Minuterie::update(){
    secondes_--;
    if(secondes_ == -1){
        minutes_--;
        secondes_ = 59;
        if(minutes_ == -1){
            stop();
            emit timeout();
        }
    }
    if(minutes_ >= 0) {
        setText(to_string());
    }
}

void Minuterie::stop() {
    timer_->stop();
}

void Minuterie::resume(){
    timer_->start(1000);
}

QString Minuterie::to_string(){
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << minutes_
        << ":"
        << std::setw(2) << std::setfill('0') << secondes_;
    return QString::fromStdString(oss.str());
}
