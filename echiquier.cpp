#include "echiquier.h"

// utiliser pour enregistrer les couleurs des cases de l'echiquier
std::array<array<QString, 8>,8> couleurs;

Echiquier::Echiquier(bool machine, QMainWindow *parent)
    : QWidget(parent), machine(machine)
{
    QWidget* widget = new QWidget(this);
    QGridLayout* layout = new QGridLayout;
    QString couleur(Utils::COULEUR_BLANCHE);

    initialiser();

    for (size_t i(0); i < tabechiquier.size(); ++i) {
        for (size_t j(0); j < tabechiquier[i].size(); ++j) {
            QPushButton* btn = new QPushButton;
            btn->setStyleSheet("background-color:"+couleur);
            if(pieces[i][j] != nullptr){
                QString image =  QString::fromStdString(pieces[i][j]->get_image());
                btn->setIcon(QIcon(image));
                btn->setIconSize(QSize(60,60));
            }
            btn->setFixedSize(QSize(80,80));
            tabechiquier[i][j] = btn;
            connect(tabechiquier[i][j], &QPushButton::clicked,[this, i, j]{deplacer(i, j);});
            layout->addWidget(tabechiquier[i][j], i, j, 1, 1);

            couleur = couleur == "white" ? Utils::COULEUR_NOIR : Utils::COULEUR_BLANCHE;
            couleurs[i][j] = couleur == "white" ? Utils::COULEUR_BLANCHE : Utils::COULEUR_NOIR;
        }
        couleur = couleur == "white" ? Utils::COULEUR_NOIR : Utils::COULEUR_BLANCHE;
    }

    QFont font("Century Gothic", 16);
    label_joueur = new QLabel("C'est le tour du joueur Blanc");
    label_joueur->setFont(font);

    layout->addWidget(label_joueur, tabechiquier.size() + 1, 0, 1, tabechiquier.size());

    layout->setSpacing(0);
    widget->setLayout(layout);
}

void Echiquier::initialiser()
{
    piece_selectionnee = nullptr;
    ancienne_piece_selectionnee = nullptr;
    // initialisation des pieces avec nullptr
    for (size_t i(0); i < tabechiquier.size(); ++i) {
        for (size_t j(0); j < tabechiquier[i].size(); ++j) {
            pieces[i][j] = nullptr;
        }
    }

    //placement des pions
    for (size_t i(0); i < 8; ++i) {
        pieces[1][i] = new Soldat(i, 1, NOIR, i, 1);
        pieces[6][i] = new Soldat(i, 6, BLANC, i, 6);
    }

    pieces[0][0] = new Tour(0, 0, NOIR);
    pieces[0][7] = new Tour(7, 0, NOIR);

    pieces[0][1] = new Chevalier(1, 0, NOIR);
    pieces[0][6] = new Chevalier(6, 0, NOIR);

    pieces[0][2] = new Fou(2, 0, NOIR);
    pieces[0][5] = new Fou(5, 0, NOIR);

    pieces[0][3] = new Reine(3, 0, NOIR);
    pieces[0][4] = new Roi(4, 0, NOIR);

    pieces[7][0] = new Tour(0, 7, BLANC);
    pieces[7][7] = new Tour(7, 7, BLANC);

    pieces[7][1] = new Chevalier(1, 7, BLANC);
    pieces[7][6] = new Chevalier(6, 7, BLANC);

    pieces[7][2] = new Fou(2, 7, BLANC);
    pieces[7][5] = new Fou(5, 7, BLANC);

    pieces[7][3] = new Reine(3, 7, BLANC);
    pieces[7][4] = new Roi(4, 7, BLANC);
}

void Echiquier::afficher_deplacement_possibles(int i, int j){
    // i = y et j = x
    if(pieces[i][j] != nullptr){
        if(piece_selectionnee == nullptr){
            if(pieces[i][j]->get_couleur() == joueur_courant){
                piece_selectionnee = pieces[i][j];
                tabechiquier[i][j]->setStyleSheet("background-color:" + Utils::COULEUR_BELGE);

                for (auto position : piece_selectionnee->positions_possibles(pieces)) {
                    if(piece_selectionnee->manger(position, pieces)){
                        tabechiquier[position.getY()][position.getX()]->setStyleSheet("background-color:" + Utils::COULEUR_ROUGE);
                    }else{
                        tabechiquier[position.getY()][position.getX()]->setIcon(QIcon(":/images/img/marquer.jpg"));
                        tabechiquier[position.getY()][position.getX()]->setIconSize(QSize(60,60));
                    }
                }
            }
        }
        else{
            if(pieces[i][j]->get_couleur() == joueur_courant){
                // on remet la couleur de la case
                tabechiquier[piece_selectionnee->get_position().getY()][piece_selectionnee->get_position().getX()]
                    ->setStyleSheet("background-color:" + couleurs[piece_selectionnee->get_position().getY()][piece_selectionnee->get_position().getX()]);
                ancienne_piece_selectionnee = piece_selectionnee;
                piece_selectionnee = pieces[i][j];
                tabechiquier[i][j]->setStyleSheet("background-color:" + Utils::COULEUR_BELGE);

                if(not piece_selectionnee->get_position().egale(ancienne_piece_selectionnee->get_position())){
                    for (auto position : ancienne_piece_selectionnee->positions_possibles(pieces)) {
                        if(ancienne_piece_selectionnee->manger(position, pieces)){
                            tabechiquier[position.getY()][position.getX()]->setStyleSheet("background-color:"+couleurs[position.getY()][position.getX()]);
                        }else{
                            tabechiquier[position.getY()][position.getX()]->setIcon(QIcon());
                        }
                    }
                    for (auto position : piece_selectionnee->positions_possibles(pieces)) {
                        if(piece_selectionnee->manger(position, pieces)){
                            tabechiquier[position.getY()][position.getX()]->setStyleSheet("background-color:" + Utils::COULEUR_ROUGE);
                        }else{
                            tabechiquier[position.getY()][position.getX()]->setIcon(QIcon(":/images/img/marquer.jpg"));
                            tabechiquier[position.getY()][position.getX()]->setIconSize(QSize(60,60));
                        }
                    }
                }
            }
        }
    }
}

void Echiquier::deplacer(int i, int j){
    bool deplacement_valide(false);
    // i = y et j = x
    //On teste si le deplacement est valide en regardant si (j,i) = (x,y) ou x,y correspondent aux differents deplacements de la piece selectionnee
    if((piece_selectionnee != nullptr) and not (piece_selectionnee->positions_possibles(pieces).empty())){
        for(auto position : piece_selectionnee->positions_possibles(pieces)){
            if((i == position.getY()) and (j == position.getX())){
                deplacement_valide = true;
                break;
            }
        }
    }

    if(deplacement_valide){
        // si le deplacemet est valide on remet le pointeur pieces[x de la piece selectionnee][y de la piece selectionnee] au pointeur nul
        pieces[piece_selectionnee->get_position().getY()][piece_selectionnee->get_position().getX()] = nullptr;

        // remettre la couleur
        tabechiquier[piece_selectionnee->get_position().getY()][piece_selectionnee->get_position().getX()]
            ->setStyleSheet("background-color:" + couleurs[piece_selectionnee->get_position().getY()][piece_selectionnee->get_position().getX()]);

        for (auto position : piece_selectionnee->positions_possibles(pieces)) {
            if(piece_selectionnee->manger(position, pieces)){
                tabechiquier[position.getY()][position.getX()]->setStyleSheet("background-color:"+couleurs[position.getY()][position.getX()]);
            }else{
                tabechiquier[position.getY()][position.getX()]->setIcon(QIcon());
            }
        }

        //on enleve l'icone de la piece a la precedente position
        tabechiquier[piece_selectionnee->get_position().getY()][piece_selectionnee->get_position().getX()]->setIcon(QIcon());

        // on modifie la position de la piece selectionnee
        piece_selectionnee->se_deplacer(j, i, pieces);

        // on libere la memoire si la piece i j est non nulle
        if(pieces[i][j] != nullptr){
            delete pieces[i][j];
            pieces[i][j] = nullptr;
        }

        // on l'assigne a pieces[i][j]
        pieces[i][j] = piece_selectionnee;

        // on met l'icone correspondante a la nouvelle position de la piece
        QString image =  QString::fromStdString(piece_selectionnee->get_image());
        tabechiquier[i][j]->setIcon(QIcon(image));
        tabechiquier[i][j]->setIconSize(QSize(60,60));

        // On renitialise les pointeurs piece selectionnee et ancienne piece selectionnee au pointeur nul
        piece_selectionnee = nullptr;
        ancienne_piece_selectionnee = nullptr;

        // on change de joueur
        if(joueur_courant == BLANC){
            joueur_courant = NOIR;
            label_joueur->setText("C'est au tour du joueur Noir");
        }else{
            joueur_courant = BLANC;
            label_joueur->setText("C'est au tour du joueur Blanc");
        }
    }else{
        afficher_deplacement_possibles(i, j);
    }
}

Echiquier::~Echiquier()
{
    delete piece_selectionnee;
    piece_selectionnee = nullptr;
    delete ancienne_piece_selectionnee;
    ancienne_piece_selectionnee = nullptr;
    // initialisation des pieces avec nullptr
    for (size_t i(0); i < tabechiquier.size(); ++i) {
        for (size_t j(0); j < tabechiquier[i].size(); ++j) {
            delete pieces[i][j];
            pieces[i][j] = nullptr;
        }
    }
}


