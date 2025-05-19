#include "utils.h"
#include "echiquier.h"

Echiquier::Echiquier(bool machine, QMainWindow *parent)
    : QWidget(parent), parent_(parent), machine_(machine)
{
    echec_model_ = new EchecModel(machine);
    setup();
}

Echiquier::~Echiquier()
{
    delete echec_model_;
    delete minuterie1_;
    delete minuterie2_;
}

void Echiquier::setupUi() {
    view_ = new QGraphicsView;
    scene_ = new QGraphicsScene;
    scene_->setSceneRect(0, 0, 8 * TAILLE_CASE_ECHIQUIER, 8 * TAILLE_CASE_ECHIQUIER);
    view_->setScene(scene_);
    view_->setAlignment(Qt::AlignCenter);

    QVBoxLayout* conteneurEchiquier = new QVBoxLayout;
    QHBoxLayout* echiquierLayout = new QHBoxLayout;
    vector<string> images_noires = {PION_NOIR, CHEVALIER_NOIR, FOU_NOIR, TOUR_NOIR, REINE_NOIR};
    vector<string> images_blanches = {PION_BLANC, CHEVALIER_BLANC, FOU_BLANC, TOUR_BLANC, REINE_BLANC};

    pieces_noires_mangees_ = new QVBoxLayout;
    pieces_blanches_mangees_ = new QVBoxLayout;

    // Affichage nombres de pièces capturées
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

    QString couleur(COULEUR_BLANCHE);

    for (size_t i(0); i < tabechiquier_.size(); ++i) {
        for (size_t j(0); j < tabechiquier_[i].size(); ++j) {
            tabechiquier_[i][j] = new CaseEchequier(i, j, couleur);
            couleur = couleur == COULEUR_BLANCHE ? COULEUR_GRIS : COULEUR_BLANCHE;
            scene_->addItem(tabechiquier_[i][j]);
            connect(tabechiquier_[i][j], &CaseEchequier::case_pressee, this, &Echiquier::case_pressee);
            Piece* piece = echec_model_->get_piece(i ,j);
            ajouter_piece(piece);
        }
        couleur = couleur == COULEUR_BLANCHE ? COULEUR_GRIS : COULEUR_BLANCHE;
    }

    QFont font("Century Gothic", 18);
    minuterie1_ = new Minuterie(10);
    minuterie2_ = new Minuterie(10);
    minuterie1_->setFont(font);
    minuterie2_->setFont(font);
    minuterie1_->setAlignment(Qt::AlignLeft);
    minuterie2_->setAlignment(Qt::AlignRight);

    // ajout des layout contenant les pieces mangées
    echiquierLayout->addLayout(pieces_noires_mangees_);
    echiquierLayout->addWidget(view_);
    echiquierLayout->addLayout(pieces_blanches_mangees_);

    conteneurEchiquier->addWidget(minuterie2_);
    conteneurEchiquier->addLayout(echiquierLayout);
    conteneurEchiquier->addWidget(minuterie1_);

    setLayout(conteneurEchiquier);

}

void Echiquier::setup()
{
    setupUi();
    sound_.setSource(QUrl(AUDIO_DEPLACEMENT));
    sound_.setVolume(0.5f);
    connect(echec_model_, &EchecModel::piece_selectionee, this, &Echiquier::afficher_deplacement_possibles);
    connect(echec_model_, &EchecModel::piece_deplacee, this, &Echiquier::deplacer_piece);
    connect(echec_model_, &EchecModel::roi_en_echec, this, &Echiquier::roi_en_echec);
    connect(echec_model_, &EchecModel::roi_en_echec_et_mat, this, &Echiquier::roi_en_echec_et_mat);
    connect(echec_model_, &EchecModel::choix_promotion, this, &Echiquier::choix_promotion);
    connect(echec_model_, &EchecModel::piece_mangee, this, &Echiquier::piece_mangee);
    connect(echec_model_, &EchecModel::piece_promue, this, [this](Piece* piece){
        ajouter_piece(piece);
    });
    minuterie1_->resume();
}

void Echiquier::ajouter_piece(Piece* piece){
    if(piece == nullptr) return;
    PieceItem* p = new PieceItem(piece, echec_model_);
    pieces_[piece] = p;
    connect(p, &PieceItem::piece_appuye, this, &Echiquier::case_pressee);
    connect(p, &PieceItem::piece_relache, this, &Echiquier::case_pressee);
    scene_->addItem(p);
}

void Echiquier::case_pressee(int i, int j)
{
    if(echec_model_->get_piece_selectionnee() == nullptr)
    {
        if(echec_model_->get_piece(i, j) != nullptr && echec_model_->get_piece(i, j)->get_couleur() == echec_model_->get_joueur_courant())
            echec_model_->selectionner_piece(i, j);
    }
    else
    {
        if(echec_model_->get_piece(i, j) != nullptr && echec_model_->get_piece(i, j)->get_couleur() == echec_model_->get_joueur_courant())
        {
            echec_model_->selectionner_piece(i, j);
        }
        else
        {
           echec_model_->deplacer_piece(i, j);
        }
    }
}

void Echiquier::afficher_deplacement_possibles(){
    // i = y et j = x
    Piece* piece_selectionnee = echec_model_->get_piece_selectionnee();
    Piece* ancienne_piece_selectionnee = echec_model_->get_ancienne_piece_selectionnee();
    if(ancienne_piece_selectionnee != nullptr)
    {
        for (auto& position : echec_model_->ancien_deplacement_possibles())
        {
            tabechiquier_[position.getX()][position.getY()]->retirer_marqueur();
        }
    }

    for (auto& position : echec_model_->deplacement_possibles())
    {
        bool est_mangeable = piece_selectionnee->peut_manger(position, echec_model_->get_pieces());
        tabechiquier_[position.getX()][position.getY()]->ajouter_marqueur(est_mangeable);
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
            echec_model_->set_promotion(Type::REINE, i, j);
        else if(choix == 2)
            echec_model_->set_promotion(Type::FOU, i, j);
        else if(choix == 3)
            echec_model_->set_promotion(Type::TOUR, i, j);
        else if(choix == 4)
            echec_model_->set_promotion(Type::CHEVALIER, i, j);
        fenetre->accept();  // Fermer la fenêtre après la confirmation
    });

    // Affichage de la fenêtre
    fenetre->setLayout(conteneur_choix);
    fenetre->setFixedSize(QSize(TAILLE_DIALOG_PROMOTION, TAILLE_DIALOG_PROMOTION));
    fenetre->exec();
}

void Echiquier::deplacer_piece(Piece* piece, vector<Position> positions)
{
    auto it = pieces_.find(piece);
    if(it == pieces_.end() || it->first == nullptr) return; // ca ne peut en principe pas se produire
    it->second->deplacer();
    sound_.play();
    // on remet les couleurs initiales
    for (auto& position : positions)
        tabechiquier_[position.getX()][position.getY()]->retirer_marqueur();
    // on change de joueur
    if(echec_model_->get_joueur_courant() == BLANC) {
        minuterie1_->stop();
        minuterie2_->resume();
    }
    else {
        minuterie2_->stop();
        minuterie1_->resume();
    }
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

void Echiquier::piece_mangee(Piece* piece_mangee)
{
    auto it = pieces_.find(piece_mangee);
    if(it == pieces_.end() || it->first == nullptr) return;
    scene_->removeItem(it->second);
    delete it->second;
    switch (piece_mangee->get_type()) {
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
    label->setText("Le joueur " + joueur_courant + " a remporté cette partie voulez vous jouer une nouvelle partie ? \voulez vous allez au menu principal ? \n");
    layout->addWidget(label);
    layout->addLayout(btn_group);
    fenetre->setLayout(layout);
    fenetre->exec();
}
