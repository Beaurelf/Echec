#ifndef UTILS_H
#define UTILS_H

#include "position.h"
#include <string>
#include <QString>

class Piece;

namespace Utils {

    typedef  std::unordered_map<Position, Piece*, HashPosition> Pieces;

    enum Couleur {BLANC, NOIR};

    enum Type {SOLDAT, TOUR, CHEVALIER, FOU, REINE, ROI};

    const QString COULEUR_BLANCHE = "white";
    const QString COULEUR_NOIR = "black";
    const QString COULEUR_GRIS = "#AAAAAC";
    const QString COULEUR_ROUGE = "#D32527";
    const QString COULEUR_BELGE = "#CCAD78";
    const QString COULEUR_MARRON = "#7E5430";


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
    const QString APP_ICON = ":/images/img/app_icon.png";

    const QString AUDIO_DEPLACEMENT = "qrc:/audios/audio/audio_deplacement.wav";

    const int TAILLE_CASE_ECHIQUIER = 80;
    const int TAILLE_ICON_CASE_ECHIQUIER = 60;
    const int TAILLE_CURSOR = 60;
    const int HAUTEUR_HOME = 680;
    const int LARGEUR_HOME = 680;
    const int HAUTEUR_GAME = 750;
    const int LARGEUR_GAME = 975;
    const int HAUTEUR_CONTROLS = 680;
    const int LARGEUR_CONTROLS = 200;
    const int TAILLE_COULEURS = 8;
    const int TAILLE_ECHIQUIER = 8;
    const int TAILLE_PIECES = 8;
    const int MIN_POSITION = 0;
    const int MAX_POSITION = 8;
    const int TAILLE_DIALOG_PROMOTION = 200;
    const int TAILLE_PIECE_MANGEE = 25;
    const int CONTRAINTE_HOME = 150;
}

#endif // UTILS_H
