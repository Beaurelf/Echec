#include "echiquier.h"

// utiliser pour enregistrer les couleurs des cases de l'echiquier
std::array<array<QString, 8>,8> couleurs;

Echiquier::Echiquier(bool machine, QMainWindow *parent)
    : QWidget(parent)
{
    echec_model_ = new EchecModel(machine);
    setup();
}

void Echiquier::setup()
{
    QWidget* widget = new QWidget(this);
    QGridLayout* layout = new QGridLayout;
    QString couleur(Utils::COULEUR_BLANCHE);

    for (size_t i(0); i < tabechiquier.size(); ++i) {
        for (size_t j(0); j < tabechiquier[i].size(); ++j) {
            QPushButton* btn = new QPushButton;
            btn->setStyleSheet("background-color:" + couleur);
            if(echec_model_->get_pieces()[i][j] != nullptr){
                QString image =  QString::fromStdString(echec_model_->get_pieces()[i][j]->get_image());
                btn->setIcon(QIcon(image));
                btn->setIconSize(QSize(60,60));
            }
            btn->setFixedSize(QSize(80,80));
            tabechiquier[i][j] = btn;
            connect(tabechiquier[i][j], &QPushButton::clicked, [this, i, j]{case_pressee(i, j);});
            layout->addWidget(tabechiquier[i][j], i, j, 1, 1);

            couleurs[i][j] = couleur == "white" ? Utils::COULEUR_BLANCHE : Utils::COULEUR_NOIR;
            couleur = couleur == "white" ? Utils::COULEUR_NOIR : Utils::COULEUR_BLANCHE;
        }
        couleur = couleur == "white" ? Utils::COULEUR_NOIR : Utils::COULEUR_BLANCHE;
    }

    QFont font("Century Gothic", 16);
    label_joueur = new QLabel;
    label_joueur->setFont(font);

    QString text = (echec_model_->get_joueur_courant() == BLANC) ? "Blanc" : "Noir";
    label_joueur->setText("C'est au tour du joueur " + text);

    layout->addWidget(label_joueur, tabechiquier.size() + 1, 0, 1, tabechiquier.size());

    layout->setSpacing(0);
    widget->setLayout(layout);

    connect(echec_model_, SIGNAL(piece_selectionee()), this, SLOT(afficher_deplacement_possibles()));
    connect(echec_model_, SIGNAL(piece_deplacee(int,int, vector<Position>, vector<Position>)),
            this, SLOT(deplacer_piece(int, int, vector<Position>, vector<Position>)));
    connect(echec_model_, SIGNAL(roi_en_echec()), this, SLOT(roi_en_echec()));
    connect(echec_model_, SIGNAL(choix_promotion(int, int)), this, SLOT(choix_promotion(int, int)));
    connect(echec_model_, SIGNAL(piece_promue(Position)), this, SLOT(piece_promue(Position)));
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
        tabechiquier[position.getY()][position.getX()]->setStyleSheet("background-color:"+couleurs[position.getY()][position.getX()]);
        for (auto& position : echec_model_->ancien_deplacement_possibles())
        {
            if(ancienne_piece_selectionnee->peut_manger(position, echec_model_->get_pieces()))
                tabechiquier[position.getY()][position.getX()]->setStyleSheet("background-color:" + couleurs[position.getY()][position.getX()]);
            else
                tabechiquier[position.getY()][position.getX()]->setIcon(QIcon());
        }
    }

    tabechiquier[piece_selectionnee->get_position().getY()][piece_selectionnee->get_position().getX()]->setStyleSheet("background-color:" + Utils::COULEUR_BELGE);

    for (auto& position : echec_model_->deplacement_possibles())
    {
        if(piece_selectionnee->peut_manger(position, echec_model_->get_pieces()))
            tabechiquier[position.getY()][position.getX()]->setStyleSheet("background-color:" + Utils::COULEUR_ROUGE);
        else
        {
            tabechiquier[position.getY()][position.getX()]->setIcon(QIcon(Utils::MARQUER));
            tabechiquier[position.getY()][position.getX()]->setIconSize(QSize(60,60));
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

    // Création des boutons de confirmation
    QHBoxLayout* buttonsLayout = new QHBoxLayout;
    QPushButton* btnOk = new QPushButton("Confirmer");
    buttonsLayout->addWidget(btnOk);

    // Ajout du layout de boutons au layout principal
    layout_choix->addLayout(buttonsLayout);

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
    fenetre->setFixedSize(QSize(200,200));
    fenetre->exec();
}

void Echiquier::piece_promue(Position pos)
{
    tabechiquier[pos.getY()][pos.getX()]->setStyleSheet("background-color:" + couleurs[pos.getY()][pos.getX()]);
    tabechiquier[pos.getY()][pos.getX()]->setIcon(QIcon());
}

void Echiquier::deplacer_piece(int i, int j, vector<Position> positions_mangeable, vector<Position> positions_non_mangeable)
{
    Piece* piece_deplacee = echec_model_->get_pieces()[i][j];
    // on remet la couleur initiale et on enleve l'icone
    tabechiquier[piece_deplacee->get_ancienne_position().getY()][piece_deplacee->get_ancienne_position().getX()]
        ->setStyleSheet("background-color:" + couleurs[piece_deplacee->get_ancienne_position().getY()][piece_deplacee->get_ancienne_position().getX()]);
    tabechiquier[piece_deplacee->get_ancienne_position().getY()][piece_deplacee->get_ancienne_position().getX()]->setIcon(QIcon());

    // on remet les couleurs initiales
    for (auto& position : positions_mangeable)
        tabechiquier[position.getY()][position.getX()]->setStyleSheet("background-color:" + couleurs[position.getY()][position.getX()]);

    for(auto& position : positions_non_mangeable)
        tabechiquier[position.getY()][position.getX()]->setIcon(QIcon());

    QString image =  QString::fromStdString(piece_deplacee->get_image());
    tabechiquier[i][j]->setIcon(QIcon(image));
    tabechiquier[i][j]->setIconSize(QSize(60,60));

    // on change de joueur
    QString text = (echec_model_->get_joueur_courant() == BLANC) ? "Blanc" : "Noir";
    label_joueur->setText("C'est au tour du joueur " + text);
}

void Echiquier::roi_en_echec()
{
    QString joueur_courant = (echec_model_->get_joueur_courant() == BLANC ? "blanc" : "noir");
    QMessageBox::warning(nullptr, "Échec", "Joueur " + joueur_courant + " votre roi est en échec!\n"
                            "Veuillez déplacer une pièce vous permettant de sortir de l'échec.\n "
                            "Aucune autre pièce que celles vous permettant de sortir de l'échec\n"
                            "ne pourra être jouée.");
}


Echiquier::~Echiquier()
{
    delete echec_model_;
}
