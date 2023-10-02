#ifndef BOARD_H
#define BOARD_H

#include <vector>

#include "Case.h"
#include "Position.h"

using Carte = std::vector<std::vector<Case>>;;

class Board {
    int _sizeRow, _sizeCol, _numBoard;
    Carte _carte;

public:
    Board() = default;

    /**
     * @brief Board
     * Constructeur du plateau de jeu vide avec sa taille longeur et largeur et son numéro de carte
     * @param sizeRow la longeur des lignes
     * @param sizeCol la longeur des colonnes
     * @param numBoard le n° du plateau de jeu
     */
    Board(int sizeRow, int sizeCol, int numBoard);

    /**
     * @brief Board
     * Constructeur par copie
     * @param ohter la board à copier
     */
    Board(const Board& other);

    /**
     * @brief operator =
     * Constructeur par assignation
     * @param other le board à copier
     * @return le nouveau board
     */
    Board &operator =(const Board& other);

    ~Board() = default;

    // Getteur

    /**
     * @brief getSizeRowAndCol
     * @return la taille des lignes et des colonnes dans une pair
     */
    std::pair<int, int> getSizeRowAndCol() const;

    /**
     * @brief getNumBoard
     * @return le numéro du plateau de jeu
     */
    int getNumBoard() const;

    /**
     * @brief getCarte
     * @return la carte sur laquelle on joue
     */
    Carte getCarte() const; // pas sûr du const

    /**
     * @brief isInside
     * @return true si la position donné est à l'intérieur du board
     */
    bool isInside(Position pos) const;

    // Méthodes du board

    /**
     * @brief addBlock
     * Rajoute un block à la position du dessus d'une case en fonction de sa position
     * @param block le block à rajouter
     */
    void addBlock(std::shared_ptr<Block> block);

    /**
     * @brief removeBlock
     * @param pos la position où remove le block
     * @return un block à la position donné, si aucun block return nullptr
     */
    std::shared_ptr<Block> removeBlock(const std::shared_ptr<Block> &block);

    /**
     * @brief moveBlock
     * Déplace un block d'une position à la nouvelle position
     * @param block Le block à déplacer
     * @param dir la direction où se déplacer
     */
    void moveBlock(const std::shared_ptr<Block>& block, Direction dir);

    /**
     * @brief getBlocksTypeAndSameNameInsideAllBoard
     * Renvoie tout les blocks de même type que <T> et si le nom n'est pas null, renvoie le même type avec le même nom dans une case du board
     * Si, il n'y en a aucun, renvoie un vecteur vide
     * @param pos, la position où le récupérer dans le board
     * @param name le nom du type du block (doit correspondre à son block) Ex: BlockMatériaux "wall", ...
     * @return un vecteur de pointeur de partagé de type T et ayant le même nom, le type T doit être un block ou un enfant de block
     */
    template <typename T>
    inline const std::vector<std::shared_ptr<T>> getBlocksTypeAndSameNameInsidePos(Position pos, const std::string& name = "") const;

    /**
     * @brief getBlocksTypeAndSameNameInsideAllBoard
     * Renvoie tout les blocks de même type que <T> et si le nom n'est pas null, renvoie le même type avec le même nom dans tout le board
     * Si, il n'y en a aucun, renvoie un vecteur vide
     * @param name le nom du type du block (doit correspondre à son block) Ex: BlockMatériaux "wall", ...
     * @return un vecteur de pointeur de partagé de type T et ayant le même nom, le type T doit être un block ou un enfant de block
     */
    template <typename T>
    inline const std::vector<std::shared_ptr<T>> getBlocksTypeAndSameNameInsideAllBoard(const std::string& name = "") const;

    /**
     * @brief getLastBlock
     * @param pos la position de la case
     * @return le dernier block de la case
     */
    std::shared_ptr<Block> getLastBlock(Position pos) const;


    // Affichage

    /**
     * @brief to_String
     * @return string représentant le board
     */
    std::string to_String() const;

    /**
     * @brief to_String
     * @return string représentant le board
     */
    std::string to_StringInforamtions() const;

    /**
     * @brief operator <<
     * L'opérateur d'insertion pour afficher le board dans un flux
     * @param os Le flux de sortie
     * @param obj (Board) à afficher
     * @return Le flux de sortie modifié
     */
    friend std::ostream& operator<<(std::ostream& os, const Board& obj);

};


template<typename T>
const std::vector<std::shared_ptr<T> > Board::getBlocksTypeAndSameNameInsidePos(Position pos, const std::string &name) const {
    static_assert(std::is_base_of<Block, T>::value, "T doit dériver de Block");
    if(!isInside(pos)) {
        throw std::invalid_argument("Board->removeBlock, problème pos (tableau: [" + std::to_string(_sizeRow) +
                                    "," + std::to_string(_sizeCol) + "], pos: " + pos.to_String() + ")");
    }
    return _carte[pos.getRow()][pos.getCol()].getBlocksOfTypeAndSameName<T>(name);
}

template<typename T>
const std::vector<std::shared_ptr<T> > Board::getBlocksTypeAndSameNameInsideAllBoard(const std::string &name) const {
    static_assert(std::is_base_of<Block, T>::value, "T doit dériver de Block");
    std::vector<std::shared_ptr<T>> result;
    for (int row = 0; row < _sizeRow; ++row) {
        for (int col = 0; col < _sizeCol; ++col) {
            auto blocks = _carte[row][col].getBlocksOfTypeAndSameName<T>(name);
//            std::reverse(blocks.begin(), blocks.end());
//            for (int index = 0; index < blocks.size(); ++index) {
                result.insert(result.end(), blocks.begin(), blocks.end());
//                result.push_back(blocks.at(index));
//            }
        }
    }
    return result;
}

#endif // BOARD_H
