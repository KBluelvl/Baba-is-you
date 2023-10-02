#ifndef MODEL_H
#define MODEL_H

#include "CommandManager.h"
#include "Loader.h"
#include "OO.h"
#include "Partie.h"

/**
 * @brief The Model class
 * Classe Façade réunissant toutes les méthodes
 * indispensable au bon déroulement d'une partie
 */
class Model : Observable {
    Loader _loader;
    Partie _partie;
    CommandManager _commandManager;
    std::vector<Observer*> _observerList;

public:
    Model() = default;

    // Getteur

    /**
     * @brief getSizeNewBoard
     * @return le nombre de map à jouer
     */
    int getSizeNewBoard() const;

    /**
     * @brief getThereIsSave
     * @return true si il y a une map save à charger, false, sinon
     */
    bool getThereIsSave() const;

    /**
     * @brief getState
     * @return l'état de la partie en cours
     */
    const State& getState() const;

    /**
     * @brief getBoard
     * @return le plateau de jeu
     */
    const Board& getBoard() const;

    /**
     * @brief sizeBoard
     * @return la taille de la ligne et de la colonne du board
     */
    const std::pair<int, int> sizeBoard() const;

    /**
     * @brief getPlayer
     * @return le joueur
     */
    const Player& getPlayer() const;

    /**
     * @brief getRulesManager
     * @return les règles du jeu
     */
    const RulesManager& getRulesManager() const;

    /**
     * @brief isEmptyUndo
     * @return True si la stack Undo est vide et false si non
     */
    bool isEmptyUndo() const;

    /**
     * @brief isEmptyRedo
     * @return True si la stack Redo est vide et false si non
     */
    bool isEmptyRedo() const;


    // Méthode chargement/save

    /**
     * @brief loadSave
     * Charge la save
     * @return true, si il arrive à la charger, false, sinon
     */
    bool loadSave();

    /**
     * @brief loadNew
     * Charge la map 0
     * @return true, si il arrive à la charger, false, sinon
     */
    bool loadNew();

    /**
     * @brief restartBoard
     * Recharge le même niveau sur lequelle était la partie
     * @return true, si il arrive à la charger, false, sinon
     */
    bool restartBoard();

    /**
     * @brief nextBoard
     * Charge le prochain niveau si il y en a un
     * @return true, si oui, false, sinon
     */
    bool nextBoard();

    /**
     * @brief saveBoard
     * Sauvegarde le board
     * @return true si il a réussi, false, sinon
     */
    bool saveBoard();

    /**
     * @brief setPartie
     * Permet de raplacer une partie en cours de jeu
     * @param partie la partie à changer
     * @return true, si ça à fonctionné, false, sinon
     */
    bool setPartie(Partie partie);

    // Interaction Board

    /**
     * @brief move
     * Déplace les blocks du joueur en fonction de
     * la direction et de la possibilité de s'y déplacer
     * @param dir où se déplacer
     */
    void move(Direction dir);

    /**
     * @brief executeMove
     * Créer la commande move et la sauvegarde si
     * le déplacement c'est bien passé
     * @param dir où se déplacer
     */
    void executeMove(Direction dir);

    /**
     * @brief undoMove
     * Reviens sur un mouvement
     */
    void undoMove();

    /**
     * @brief redoMove
     * Reviens sur un retour en arrière d'un mouvement
     */
    void redoMove();


    // Observable interface

    void add(Observer* obs) override;
    void notifyObserver() override;

};

#endif // MODEL_H
