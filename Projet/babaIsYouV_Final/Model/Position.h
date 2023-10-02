#ifndef POSITION_H
#define POSITION_H


/**
 * @brief The Position class
 * Définit une position sur deux axes
 */
#include "Enume.h"
#include <ostream>
class Position {

    int _row; // axe X (row)
    int _col; // axe Y (col)

public:
    /**
     * @brief Position
     * Constructeur de base
     * @param row int Axe X
     * @param col int Axe Y
     */
    Position(int row, int col);

    /**
     * @brief Position
     * Constructeur par copie
     * @param other la position à copier
     */
    Position(const Position& other);

    /**
     * @brief operator =
     * Constructeur par assignation
     * @param other La position à assigner
     * @return La nouvelle position assignée
     */
    Position& operator=(const Position& other);

    /**
     * @brief move
     * Créer une nouvelle position grâce à la direction donnée
     * @param dir la direction vers où se déplacer
     * @return la nouvelle position
     */
    Position move(Direction dir) const;

    /**
     * @brief getRow
     * @return row int Axe X
     */
    int getRow() const;

    /**
     * @brief getCol
     * @return col int Axe Y
     */
    int getCol() const;

    /**
     * @brief to_string
     * @return la position sous format de chaîne de caractères
     */
    std::string to_String() const;

    /**
     * @brief operator ==
     * L'opérateur d'égalité
     * @param other la position à tester
     * @return true si ils sont égaux, sinon, false
     */
    bool operator==(const Position& other) const;

    /**
     * @brief operator <<
     * L'opérateur d'insertion pour afficher une Position dans un flux
     * @param os Le flux de sortie
     * @param position La Position à afficher
     * @return Le flux de sortie modifié
     */
    friend std::ostream& operator<<(std::ostream& os, const Position& position);


};
#endif // POSITION_H
