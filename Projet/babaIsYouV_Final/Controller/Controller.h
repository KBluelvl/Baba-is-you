#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>

#include "Model/Model.h"
#include "View/ViewConsole.h"

/**
 * @brief The Controller class
 * Classe liant la vue et le model
 * Affiche, demande et lance les actions faites par le joueur
 */
class Controller {
    Model& _facade;
    ViewConsole& _view;

public:
    /**
     * @brief Controller
     * Constructeur de base
     * @param facade le model qui gère le jeu
     * @param view la vue pour le model
     */
    Controller(Model& facade, ViewConsole& view);

    /**
     * @brief start
     * lance la première demande à l'utilisateur
     */
    void start();

private:

    /**
     * @brief accueil
     * Demande les différentes commandes possibles lors de l'acceuil
     * @return true, si le jeu commence, false, sinon
     */
    bool accueil();

    /**
     * @brief direction
     * Demande les différentes commandes possibles pour le mouvement sur le board
     * @return true, si le jeu continue, false, sinon
     */
    bool direction();

    /**
     * @brief dead
     * Demande les différente commandes de jeu possibles après la mort du player
     * @return true, si le jeu continue, false, sinon
     */
    bool dead();

    /**
     * @brief win
     * Demande les différente commandes de jeu possibles après la victoire
     * @return true, si le jeu continue, false, sinon
     */
    bool win();

    /**
     * @brief getCommandPlayer
     * Demande à l'utilisateur de rentrer un mot correspondant à l'un
     * des mots de la liste en paramètre
     * @param listRightWord la liste des bon mot
     * @return l'entier correspondant
     */
    int getCommandPlayer(std::vector<std::string> listRightWord);

};

#endif // CONTROLLER_H
