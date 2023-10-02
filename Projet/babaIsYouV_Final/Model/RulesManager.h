#ifndef RULESMANAGER_H
#define RULESMANAGER_H


#include "Block.h"
#include "Board.h"
#include "Player.h"

#include <map>
#include <memory>

using keyConnecteur = std::pair<std::shared_ptr<BlockConnecteur>, Direction>;
using rule = std::pair<std::shared_ptr<BlockSujet>, std::shared_ptr<BlockAspect>>;


class RulesManager {
    std::map<keyConnecteur, rule> _checkerRules; // L'initialisé avec tout les blockConnecteur, mais sans pair
    std::map<Matériaux, std::map<int, Aspect>> _rulesToMat;

public:

    RulesManager() = default;

    /**
     * @brief RulesManager
     * Constructeur de règle Manager
     * @param board
     */
    RulesManager(Board& board, Player& player);

    ~RulesManager() = default;

    // Méthode

    /**
     * @brief checkRuleConnecteur
     * Check les règles associèes à se blockConnecteur
     * @param bc
     */
    void checkRuleConnecteur(Board& board,  Player& player, std::shared_ptr<BlockConnecteur> bc = nullptr);

    /**
     * @brief getAspectToMat
     * Récupère les aspect (règles) lié à son matériaux
     * @param mat le matériaux
     * @return les aspect
     */
    std::map<int, Aspect> &getAspectToMat(Matériaux mat);


    // Affichage

    /**
     * @brief to_String
     * @return string représentant les règles
     */
    std::string to_String() const;

    /**
     * @brief to_String
     * @return string représentant les règles avec pointeurs
     */
    std::string to_StringInformations() const;

    /**
     * @brief operator <<
     * L'opérateur d'insertion pour afficher les règles dans un flux
     * @param os Le flux de sortie
     * @param obj (Rule) à afficher
     * @return Le flux de sortie modifié
     */
    friend std::ostream& operator<<(std::ostream& os, const RulesManager& obj);



private:
    /**
     * @brief initCheckerRules
     * Initialise par défaut les blockConnecteur
     * @param board le plateau de jeu
     */
    void initCheckerRules(Board& board);

    /**
     * @brief initRulesToMat
     * Initialise par défaut les différents aspects associés à son matériaux
     */
    void initRulesToMat();

    /**
     * @brief creatAndCheckRuleToKeyConnecteur
     * Créer ou check si le keyConnecteur possède une règle et l'associe ou la dissocie
     * à son matériaux
     * @param key la clé composé de blockConnecteur et de la direction
     * @param board le board où check les block
     */
    void creatAndCheckRuleToKeyConnecteur(std::map<keyConnecteur, rule>::iterator& it, Board &board, Player& player);

    /**
     * @brief creatRule
     * Associe une règle au matériaux
     * @param mat la matériaux à qui associer une règle
     * @param asp l'aspect à associer
     * @param board le plateau de jeu
     * @param player le joueur
     */
    void creatRule(Matériaux mat, Aspect asp, Board& board,  Player& player);

    /**
     * @brief removeRule
     * Dissocie une règle au matériaux
     * @param mat la matériaux à qui Dissocier une règle
     * @param asp l'aspect à Dissocier
     * @param player le joueur
     */
    void removeRule(Matériaux mat, Aspect asp, Player& player);

};

#endif // RULESMANAGER_H
