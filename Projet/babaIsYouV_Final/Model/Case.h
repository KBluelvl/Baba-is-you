#ifndef CASE_H
#define CASE_H

#include <vector>
#include <memory>

#include "Block.h"


/**
 * @brief The Case class
 * Une case qui stock les block sous forme de pointeurs et est gérer comme une stack (LIFO)
 * Elle permet retirer/ajouter des blocks au dessus de la pile et checker les règles
 */
class Case {
    std::vector<std::shared_ptr<Block>> _stackBlock; // vecteur qui se comporte comme une stack

public:
    /**
     * @brief Case
     * Constructeur d'une case, en y placant un block de vide, immuable et un autre non immuable.
     * @param pos la position de la case dans le board
     */
    Case(Position pos);

    /**
     * @brief Case
     * Constructeur par copie
     * @param other la case à copier
     */
    Case(const Case& other);

    /**
     * @brief operator =
     * Constructeur par assignation
     * @param other la case à copier
     * @return la nouvelle case
     */
    Case& operator=(const Case& other);

    ~Case() = default;

    /**
     * @brief operator ==
     * Redéfinit l'opérateur d'égalité
     * @param other la case à vérifier
     * @return true ,si elle sont égale, false, sinon
     */
    bool operator==(const Case& other);

    // Getteur

    /**
     * @brief getBlocksOfTypeAndSameName
     * Renvoie si name = NULL, tout les pointeurs partagé de blocks du même type.
     * Renvoie Si name != NULL, tout les pointeurs partagé de blocks du même type et du même nom
     * @param name le nom du type du block (doit correspondre à son block) Ex: BlockMatériaux "wall", ...
     * @return un vecteur de pointeur de partagé de type T et ayant le même nom, le type T doit être un block ou un enfant de block
     */
    template <typename T>
    inline const std::vector<std::shared_ptr<T>> getBlocksOfTypeAndSameName(const std::string& name = "") const;

    /**
     * @brief getLastBlock
     * @return un pointeur partagé de block du dernier sur la pile, si aucun sur la pile, renvoie nullptr
     */
    const std::shared_ptr<Block> getLastBlock() const;

    /**
     * @brief getAllBlock
     * @return tous les pointeurs partagé de blocks de la case
     */
    const std::vector<std::shared_ptr<Block>> getAllBlock() const;

    /**
     * @brief size
     * @return la taille de la case, sans le block Immuable
     */
    int size() const;

    /**
     * @brief isEmpty
     * @return true si il est vide (prend pas en compte le block immuable, sinon false
     */
    bool isEmpty() const;

    // Méthodes

    /**
     * @brief removeLast
     * @return le dernier block de la pile, nullptr, si il y en a pas
     */
    std::shared_ptr<Block> removeLast();

    /**
     * @brief removeLast
     * @return le dernier block de la pile, nullptr, si il y en a pas
     */
    std::shared_ptr<Block> removeIndex(int index);

    /**
     * @brief addlast
     * Rajoute au dessus de la case
     * @param block le block à rajouter
     */
    void addlast(std::shared_ptr<Block> block);

    // Affichage

    /**
     * @brief to_String
     * @return string représentant une case
     */
    std::string to_String() const;

    /**
     * @brief to_String
     * @return string représentant une case
     */
    std::string to_StringInFormation() const;

    /**
     * @brief operator <<
     * L'opérateur d'insertion pour afficher une Case dans un flux
     * @param os Le flux de sortie
     * @param obj (case) à afficher
     * @return Le flux de sortie modifié
     */
    friend std::ostream& operator<<(std::ostream& os, const Case& obj);
};

template<typename T>
const std::vector<std::shared_ptr<T> > Case::getBlocksOfTypeAndSameName(const std::string &name) const { // Changer l'index si on veut prendre le block immuable
    static_assert(std::is_base_of<Block, T>::value, "T doit dériver de Block");

    std::vector<std::shared_ptr<T>> result;

    for (int index = 1; index <= size(); ++index) {
        if (std::shared_ptr<T> typedBlock = std::dynamic_pointer_cast<T>(_stackBlock.at(index))) { // Vérifie le type du block
            if(name == "") {
                result.push_back(typedBlock); // ajoute que ceux du même type sans vérifier le nom
            } else {
                if(name == _stackBlock.at(index)->getName()) {
                    result.push_back(typedBlock); // Ajoute ceux du même type et du même nom.
                }
            }
        }
    }

    return result;
}

#endif // CASE_H
