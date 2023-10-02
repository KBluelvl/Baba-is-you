#ifndef PARTIE_H
#define PARTIE_H

#include <memory>

#include "Board.h"
#include "Enume.h"
#include "Player.h"
#include "RulesManager.h"

class Partie {
    Player _player {};
    Board _board;
    RulesManager _rulesManager;
    State _state = State::START;

public:
    Partie() = default;

    /**
     * @brief Partie
     * Constructeur d'une partie avec un nouveau plateau de jeu
     * @param board le plateau de jeu
     */
    Partie(Board board);

    /**
     * @brief Partie
     * Constucteur par copie
     * @param other la partie à copier
     */
    Partie(const Partie& other);

//    /**
//     * @brief Partie
//     * Constucteur par copie
//     * @param other la partie à copier
//     */
//    Partie(const Board& other);

    /**
     * @brief operator =
     * opérateur d'assignation
     * @param other la partie à copier
     * @return la nouvelle partie
     */
    Partie& operator=(const Partie& other);

//    /**
//     * @brief operator =
//     * opérateur d'assignation
//     * @param other la partie à copier
//     * @return la nouvelle partie
//     */
//    Partie& operator=(const Board& other);

    // Getteur

    /**
     * @brief getPlayer
     * @return le joueur de la partie
     */
    const Player &getPlayer() const;

    /**
     * @brief getBoard
     * @return le plateau de jeu
     */
    const Board &getBoard() const;

    /**
     * @brief getState
     * @return l'état de jeu
     */
    const State& getState() const;

    void setState(State state);

    /**
     * @brief getRulesManager
     * @return les règles du jeu
     */
    const RulesManager& getRulesManager() const;

    // Méthode

    /**
     * @brief move
     * Bouge le joueur dans la direction donnée
     * @param dir la direction où se déplacer
     */
    void movePlayer(Direction dir); // L'endroit où l'on rajouterait Keke, après le mouvement du joueur, on bouge tout les blocks de keke

    /**
     * @brief moveBlock
     * Permet de bouger un block dans une direction donné
     * @param pos la position où prendre le block
     * @param dir la direction ou déplacer se block
     */
    bool moveBlock(const std::shared_ptr<Block> &block, Direction dir, bool isPlayer = false);

    /**
     * @brief applyRule
     * Applique les différentes règles du jeu
     * @param ToTest la position où prendre les règles
     * @return true si il peut se déplacer, sinon false
     */
    bool applyRule(Aspect asp, const std::shared_ptr<Block> &block, Direction dir, bool isPlayer);


    // Méthode player

    /**
     * @brief addMatériauxToPlayer
     * Rajoute un matériaux au joueur en prenant tout les blocks correspondant dans le board
     * @param mat le matériaux à rajouter
     */
    void addMatériauxToPlayer(Matériaux mat);

    /**
     * @brief removeMatériauxToPlayer
     * Retire un matériaux au joueur
     * @param mat le matériaux à retirer
     */
    void removeMatériauxToPlayer(Matériaux mat);


    // Affichage

    /**
     * @brief to_String
     * @return string représentant la partie
     */
    std::string to_String() const;

    /**
     * @brief to_String
     * @return string représentant la partie
     */
    std::string to_StringInformations() const;

    /**
     * @brief operator <<
     * L'opérateur d'insertion pour afficher la partie dans un flux
     * @param os Le flux de sortie
     * @param obj (Partie) à afficher
     * @return Le flux de sortie modifié
     */
    friend std::ostream& operator<<(std::ostream& os, const Partie& obj);
};

#endif // PARTIE_H
