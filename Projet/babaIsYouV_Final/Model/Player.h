#ifndef PLAYER_H
#define PLAYER_H

#include <map>
#include <vector>
#include <memory>
#include <algorithm>

#include "Block.h"
#include "Enume.h"

/**
 * @brief The Player class
 * Classe stockant les pointeurs des blocks controlé par le joueur
 */
class Player {
    std::map<Matériaux, std::vector<std::shared_ptr<BlockMatériaux>>> _controlBlocks;

public:
    Player() = default;
    ~Player() = default;

//    /**
//     * @brief Player
//     * Constructeur par copie
//     * @param other le joueur à copier
//     */
//    Player(const Player& other);

//    /**
//     * @brief operator =
//     * Constructeur par assigantion
//     * @param other le joueur à copier
//     * @return le joueur copié
//     */
//    Player operator=(const Player& other);

    // Getteur

    const std::map<Matériaux, std::vector<std::shared_ptr<BlockMatériaux>>>& getPlayer() const;

    bool isAlive() const;

    // Méthode

    /**
     * @brief addMatériaux
     * Rajoute un nouveau matériaux controlé par le joueur avec ces blocks
     * @param newControl est le nouveau matériaux et ses pointeurs des blocks dans le tableau à rajouter
     */
    void addMatériaux(std::pair<Matériaux, std::vector<std::shared_ptr<BlockMatériaux>>> newControl);

    /**
     * @brief removeMatériaux
     * Supprime un matériaux controlé par le joueur
     * @param mat le matériaux à retirer du joueur
     */
    void removeMatériaux(Matériaux& mat);

    /**
     * @brief removePtrUnused
     * Check et supprime les pointeur qui ne font plus référence à aucun block sauf eux même
     */
    void removePtrUnused();

    /**
     * @brief clearPlayer
     * Remove tout le player
     */
    void clearPlayer();


    // Affichage

    /**
     * @brief to_String
     * @return l'affichage sous forme du string du player
     */
    std::string to_String() const;

    /**
     * @brief to_String
     * @return l'affichage sous forme du string du player
     */
    std::string to_StringInforamtion() const;

    /**
     * @brief operator <<
     * L'opérateur d'insertion pour afficher un player dans un flux
     * @param os Le flux de sortie
     * @param player à afficher
     * @return Le flux de sortie modifié
     */
    friend std::ostream& operator<<(std::ostream& os, const Player& player);

};

#endif // PLAYER_H
