#ifndef _SETTING_
#define _SETTING_
    #include <string>
    #include <QString>

    // couleur des joueurs
    enum Couleur {BLANC, NOIR};

    enum Type {SOLDAT, TOUR, CHEVALIER, FOU, REINE, ROI};

    class Utils {
        public:
            static const QString COULEUR_BLANCHE;
            static const QString COULEUR_NOIR ;
            static const QString COULEUR_ROUGE ;
            static const QString COULEUR_BELGE ;


            //Images des differentes pieces
            static const std::string ROI_BLANC ;
            static const std::string REINE_BLANC ;
            static const std::string TOUR_BLANC ;
            static const std::string FOU_BLANC ;
            static const std::string CHEVALIER_BLANC ;
            static const std::string PION_BLANC ;

            static const std::string ROI_NOIR ;
            static const std::string REINE_NOIR ;
            static const std::string TOUR_NOIR ;
            static const std::string FOU_NOIR ;
            static const std::string CHEVALIER_NOIR;
            static const std::string PION_NOIR;

            static const QString MARQUER;
    };

#endif
