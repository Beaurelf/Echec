#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <QString>

namespace Utils {

    enum Couleur {BLANC, NOIR};

    enum Type {SOLDAT, TOUR, CHEVALIER, FOU, REINE, ROI};

    const QString COULEUR_BLANCHE = "white";
    const QString COULEUR_NOIR = "#AAAAAC";
    const QString COULEUR_ROUGE = "#D32527";
    const QString COULEUR_BELGE = "#FFDB75";


    const std::string ROI_BLANC = ":/images/img/roi_blanc.jpg";
    const std::string REINE_BLANC = ":/images/img/reine_blanc.jpg";
    const std::string TOUR_BLANC = ":/images/img/tour_blanc.jpg";
    const std::string FOU_BLANC = ":/images/img/fou_blanc.jpg";
    const std::string CHEVALIER_BLANC = ":/images/img/chevalier_blanc.png";
    const std::string PION_BLANC = ":/images/img/pion_blanc.jpg";

    const std::string ROI_NOIR = ":/images/img/roi_noir.jpg";
    const std::string REINE_NOIR = ":/images/img/reine_noir.jpg";
    const std::string TOUR_NOIR = ":/images/img/tour_noir.jpg";
    const std::string FOU_NOIR = ":/images/img/fou_noir.jpg";
    const std::string CHEVALIER_NOIR = ":/images/img/chevalier_noir.jpg";
    const std::string PION_NOIR = ":/images/img/pion_noir.jpg";
    const QString MARQUER = ":/images/img/marquer.jpg";
    const QString CURSOR = ":/images/img/cursor.png";
}

#endif // UTILS_H
