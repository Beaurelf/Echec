#include "echiquier.h"

// utiliser pour enregistrer les couleurs des cases de l'echiquier
std::array<array<QString, TAILLE_COULEURS>,TAILLE_COULEURS> couleurs;

Echiquier::Echiquier(bool machine, QMainWindow *parent)
    : QWidget(parent), parent_(parent), machine_(machine)
{
    echec_model_ = new EchecModel(machine);
    setup();
}

void Echiquier::setup()
{
    QWidget* widget = new QWidget(this);
    QHBoxLayout* conteneur = new QHBoxLayout;
    QGridLayout* echiquier = new QGridLayout;
    // pas d'espace entre les cases de l'echiquier
    echiquier->setSpacing(0);
    QString couleur(COULEUR_BLANCHE);
    vector<string> images_noires = {PION_NOIR, CHEVALIER_NOIR, FOU_NOIR, TOUR_NOIR, REINE_NOIR};
    vector<string> images_blanches = {PION_BLANC, CHEVALIER_BLANC, FOU_BLANC, TOUR_BLANC, REINE_BLANC};

    pieces_noires_mangees_ = new QVBoxLayout;
    pieces_blanches_mangees_ = new QVBoxLayout;

    for (size_t i(0); i < images_noires.size(); ++i)
    {
        QHBoxLayout* layout1 = new QHBoxLayout;
        QHBoxLayout* layout2 = new QHBoxLayout;
        QPixmap image_noire(QString::fromStdString(images_noires[i]));
        QPixmap image_blanche(QString::fromStdString(images_blanches[i]));
        QLabel *label_img_blanche = new QLabel;
        QLabel *label_img_noire = new QLabel;
        QLabel *nbre_piece_blanche_capturee = new QLabel("0");
        QLabel *nbre_piece_noire_capturee = new QLabel("0");


        label_img_blanche->setFixedSize(QSize(TAILLE_PIECE_MANGEE, TAILLE_PIECE_MANGEE));
        label_img_blanche->setScaledContents(true);
        label_img_blanche->setPixmap(image_blanche);

        label_img_noire->setFixedSize(QSize(TAILLE_PIECE_MANGEE, TAILLE_PIECE_MANGEE));
        label_img_noire->setScaledContents(true);
        label_img_noire->setPixmap(image_noire);

        layout1->addWidget(nbre_piece_blanche_capturee);
        layout1->addWidget(label_img_blanche);

        layout2->addWidget(label_img_noire);
        layout2->addWidget(nbre_piece_noire_capturee);


        pieces_noires_mangees_->addLayout(layout2);
        pieces_noires_mangees_->addStretch();
        pieces_blanches_mangees_->addLayout(layout1);
        pieces_blanches_mangees_->addStretch();

        pieces_noires_capturees_.push_back(nbre_piece_noire_capturee);
        pieces_blanches_capturees_.push_back(nbre_piece_blanche_capturee);
    }

    for (size_t i(0); i < tabechiquier_.size(); ++i) {
        for (size_t j(0); j < tabechiquier_[i].size(); ++j) {
            QPushButton* btn = new QPushButton;
            btn->setStyleSheet("background-color:" + couleur);
            if(echec_model_->get_pieces()[i][j] != nullptr){
                QString image =  QString::fromStdString(echec_model_->get_pieces()[i][j]->get_image());
                btn->setIcon(QIcon(image));
                btn->setIconSize(QSize(TAILLE_ICON_CASE_ECHIQUIER, TAILLE_ICON_CASE_ECHIQUIER));
            }
            btn->setFixedSize(QSize(TAILLE_CASE_ECHIQUIER, TAILLE_CASE_ECHIQUIER));
            tabechiquier_[i][j] = btn;
            connect(tabechiquier_[i][j], &QPushButton::clicked, [this, i, j]{case_pressee(i, j);});
            echiquier->addWidget(tabechiquier_[i][j], i , j, 1, 1);

            couleurs[i][j] = couleur == COULEUR_BLANCHE ? COULEUR_BLANCHE : COULEUR_NOIR;
            couleur = couleur == COULEUR_BLANCHE ? COULEUR_NOIR : COULEUR_BLANCHE;
        }
        couleur = couleur == COULEUR_BLANCHE ? COULEUR_NOIR : COULEUR_BLANCHE;
    }

    QFont font("Century Gothic", 16);
    label_joueur_ = new QLabel;
    label_joueur_->setFont(font);
    QString text = (echec_model_->get_joueur_courant() == BLANC) ? "Blanc" : "Noir";
    label_joueur_->setText("C'est au tour du joueur " + text);

    echiquier->addWidget(label_joueur_, tabechiquier_.size(), 0, 1, tabechiquier_.size());

    // ajout des layout contenant les pieces mangées
    conteneur->setSpacing(10);
    conteneur->addLayout(pieces_noires_mangees_);
    conteneur->addLayout(echiquier);
    conteneur->addLayout(pieces_blanches_mangees_);

    widget->setLayout(conteneur);

    connect(echec_model_, SIGNAL(piece_selectionee()), this, SLOT(afficher_deplacement_possibles()));
    connect(echec_model_, SIGNAL(piece_deplacee(int, int, vector<Position>, vector<Position>)),
            this, SLOT(deplacer_piece(int, int, vector<Position>, vector<Position>)));
    connect(echec_model_, SIGNAL(roi_en_echec()), this, SLOT(roi_en_echec()));
    connect(echec_model_, SIGNAL(roi_en_echec_et_mat()), this, SLOT(roi_en_echec_et_mat()));
    connect(echec_model_, SIGNAL(choix_promotion(int, int)), this, SLOT(choix_promotion(int, int)));
    connect(echec_model_, SIGNAL(piece_promue(Position)), this, SLOT(piece_promue(Position)));
    connect(echec_model_, SIGNAL(piece_mangee(const Type&)), this, SLOT(piece_mangee(const Type&)));
}

void Echiquier::case_pressee(int i, int j)
{
    if(echec_model_->get_piece_selectionnee() == nullptr)
    {
        if(echec_model_->get_pieces()[i][j] != nullptr && echec_model_->get_pieces()[i][j]->get_couleur() == echec_model_->get_joueur_courant())
            echec_model_->selectionner_piece(i, j);
    }
    else
    {
        if(echec_model_->get_pieces()[i][j] != nullptr && echec_model_->get_pieces()[i][j]->get_couleur() == echec_model_->get_joueur_courant())
        {
            echec_model_->selectionner_piece(i, j);
        }
        else
        {
            auto position_possibles = echec_model_->deplacement_possibles();
            auto it = find_if(position_possibles.begin(), position_possibles.end(), [&](const Position& pos){
                return pos.egale(j, i);
            });

            if(it != position_possibles.end())
            {
                if(echec_model_->get_pieces()[i][j] != nullptr)
                    echec_model_->manger_piece(i, j);
                else
                    echec_model_->deplacer_piece(i, j);
            }

        }
    }
}

void Echiquier::afficher_deplacement_possibles(){
    // i = y et j = x
    Piece* piece_selectionnee = echec_model_->get_piece_selectionnee();
    Piece* ancienne_piece_selectionnee = echec_model_->get_ancienne_piece_selectionnee();
    if(ancienne_piece_selectionnee != nullptr)
    {
        Position position = ancienne_piece_selectionnee->get_position();
        tabechiquier_[position.getY()][position.getX()]->setStyleSheet("background-color:"+couleurs[position.getY()][position.getX()]);
        for (auto& position : echec_model_->ancien_deplacement_possibles())
        {
            if(ancienne_piece_selectionnee->peut_manger(position, echec_model_->get_pieces()))
                tabechiquier_[position.getY()][position.getX()]->setStyleSheet("background-color:" + couleurs[position.getY()][position.getX()]);
            else
                tabechiquier_[position.getY()][position.getX()]->setIcon(QIcon());
        }
    }

    tabechiquier_[piece_selectionnee->get_position().getY()][piece_selectionnee->get_position().getX()]->setStyleSheet("background-color:" + COULEUR_BELGE);

    for (auto& position : echec_model_->deplacement_possibles())
    {
        if(piece_selectionnee->peut_manger(position, echec_model_->get_pieces()))
            tabechiquier_[position.getY()][position.getX()]->setStyleSheet("background-color:" + COULEUR_ROUGE);
        else
        {
            tabechiquier_[position.getY()][position.getX()]->setIcon(QIcon(MARQUER));
            tabechiquier_[position.getY()][position.getX()]->setIconSize(QSize(TAILLE_ICON_CASE_ECHIQUIER, TAILLE_ICON_CASE_ECHIQUIER));
        }
    }
}

void Echiquier::choix_promotion(int i, int j)
{

    QDialog* fenetre = new QDialog;
    fenetre->setWindowTitle("Promotion du Pion");

    QGroupBox *groupbox = new QGroupBox("Faites votre choix", fenetre);
    QVBoxLayout* layout_choix = new QVBoxLayout;
    QVBoxLayout* conteneur_choix = new QVBoxLayout;

    // Création des boutons radio pour le choix de la pièce
    QButtonGroup* group_choix = new QButtonGroup(fenetre);
    QRadioButton *reine = new QRadioButton("Reine");
    QRadioButton *fou = new QRadioButton("Fou");
    QRadioButton *tour = new QRadioButton("Tour");
    QRadioButton *chevalier = new QRadioButton("Chevalier");

    group_choix->addButton(reine, 1);
    group_choix->addButton(fou, 2);
    group_choix->addButton(tour, 3);
    group_choix->addButton(chevalier, 4);
    group_choix->setExclusive(true);
    reine->setChecked(true); // Reine sélectionnée par défaut

    // Ajout des boutons radio au layout
    layout_choix->addWidget(reine);
    layout_choix->addWidget(fou);
    layout_choix->addWidget(tour);
    layout_choix->addWidget(chevalier);

    // Création de bouton de confirmation
    QPushButton* btnOk = new QPushButton("Confirmer");

    // Ajout du layout de boutons au layout principal
    layout_choix->addWidget(btnOk);

    // Configuration du layout de la groupbox
    groupbox->setLayout(layout_choix);
    conteneur_choix->addWidget(groupbox);

    // Connexion des boutons à leurs slots
    connect(btnOk, &QPushButton::clicked, fenetre, [this, fenetre, group_choix, i, j]() {
        int choix = group_choix->checkedId();
        if(choix == 1)
            echec_model_->set_promotion(Type::REINE, j, i);
        else if(choix == 2)
            echec_model_->set_promotion(Type::FOU, j, i);
        else if(choix == 3)
            echec_model_->set_promotion(Type::TOUR, j, i);
        else if(choix == 4)
            echec_model_->set_promotion(Type::CHEVALIER, j, i);
        fenetre->accept();  // Fermer la fenêtre après la confirmation
    });

    // Affichage de la fenêtre
    fenetre->setLayout(conteneur_choix);
    fenetre->setFixedSize(QSize(TAILLE_DIALOG_PROMOTION, TAILLE_DIALOG_PROMOTION));
    fenetre->exec();
}

void Echiquier::piece_promue(Position pos)
{
    tabechiquier_[pos.getY()][pos.getX()]->setStyleSheet("background-color:" + couleurs[pos.getY()][pos.getX()]);
    tabechiquier_[pos.getY()][pos.getX()]->setIcon(QIcon());
}

void Echiquier::deplacer_piece(int i, int j, vector<Position> positions_mangeable, vector<Position> positions_non_mangeable)
{
    Piece* piece_deplacee = echec_model_->get_pieces()[i][j];
    // on remet la couleur initiale et on enleve l'icone
    tabechiquier_[piece_deplacee->get_ancienne_position().getY()][piece_deplacee->get_ancienne_position().getX()]
        ->setStyleSheet("background-color:" + couleurs[piece_deplacee->get_ancienne_position().getY()][piece_deplacee->get_ancienne_position().getX()]);
    tabechiquier_[piece_deplacee->get_ancienne_position().getY()][piece_deplacee->get_ancienne_position().getX()]->setIcon(QIcon());

    // on remet les couleurs initiales
    for (auto& position : positions_mangeable)
        tabechiquier_[position.getY()][position.getX()]->setStyleSheet("background-color:" + couleurs[position.getY()][position.getX()]);

    for(auto& position : positions_non_mangeable)
        tabechiquier_[position.getY()][position.getX()]->setIcon(QIcon());

    QString image =  QString::fromStdString(piece_deplacee->get_image());
    tabechiquier_[i][j]->setIcon(QIcon(image));
    tabechiquier_[i][j]->setIconSize(QSize(TAILLE_ICON_CASE_ECHIQUIER, TAILLE_ICON_CASE_ECHIQUIER));

    // on change de joueur
    QString text = (echec_model_->get_joueur_courant() == BLANC) ? "Blanc" : "Noir";
    label_joueur_->setText("C'est au tour du joueur " + text);
}

void Echiquier::update_nbre_pieces_capturees(int index)
{
    if(echec_model_->get_joueur_courant() == NOIR)
    {
        int nbre_pieces_capturees = pieces_blanches_capturees_[index]->text().toInt();
        pieces_blanches_capturees_[index]->setText(QString::number(nbre_pieces_capturees + 1));
    }
    else
    {
        int nbre_pieces_capturees = pieces_noires_capturees_[index]->text().toInt();
        pieces_noires_capturees_[index]->setText(QString::number(nbre_pieces_capturees + 1));
    }
}

void Echiquier::piece_mangee(const Type& type)
{
    switch (type) {
    case SOLDAT:
        update_nbre_pieces_capturees(0);
        break;
    case CHEVALIER:
        update_nbre_pieces_capturees(1);
        break;
    case FOU:
        update_nbre_pieces_capturees(2);
        break;
    case TOUR:
        update_nbre_pieces_capturees(3);
        break;
    case REINE:
        update_nbre_pieces_capturees(4);
        break;
    default:
        break;
    }
}

void Echiquier::roi_en_echec()
{
    QString joueur_courant = (echec_model_->get_joueur_courant() == BLANC ? "blanc" : "noir");
    QMessageBox::warning(nullptr, "Échec", "Joueur " + joueur_courant + " votre roi est en échec!\n"
                            "Veuillez déplacer une pièce vous permettant de sortir de l'échec.\n"
                            "Aucune autre pièce que celles vous permettant de sortir de l'échec\n"
                            "ne pourra être jouée.");
}

void Echiquier::roi_en_echec_et_mat()
{
    QString joueur_courant = (echec_model_->get_joueur_courant() == BLANC ? "noir" : "blanc");
    QDialog* fenetre = new QDialog;
    fenetre->setWindowTitle("Echec et mat");
    QVBoxLayout *layout = new QVBoxLayout;
    QHBoxLayout* btn_group = new QHBoxLayout;
    QPushButton* btn_recommencer = new QPushButton("Nouvelle partie");
    QPushButton* btn_menu = new QPushButton("Aller au menu");
    connect(btn_recommencer, &QPushButton::clicked, fenetre, [this, fenetre](){
        emit recommencer();
        fenetre->accept();
    });
    connect(btn_menu, &QPushButton::clicked, fenetre, [this, fenetre](){
        emit aller_accueil();
        fenetre->accept();
    });
    btn_group->addWidget(btn_recommencer);
    btn_group->addWidget(btn_menu);
    QLabel* label = new QLabel;
    label->setText("Le joueur " + joueur_courant + " a remporté cette partie voulez vous jouer une nouvelle partie ? \nou allez au menu principal ? \n");
    layout->addWidget(label);
    layout->addLayout(btn_group);
    fenetre->setLayout(layout);
    fenetre->exec();
}


Echiquier::~Echiquier()
{
    delete echec_model_;
}
