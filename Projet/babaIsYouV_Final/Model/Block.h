#ifndef BLOCK_H
#define BLOCK_H

#include "Position.h"
#include <memory>
#include <string>

/**
 * @brief The Block class
 * Block de base qui est le block parent de tous les autres blocks
 */
class Block {
protected:
    std::string _name; // Le nom du block
    Position _pos; // La position du block
    int _indexCase; // L'index dans la case

public:

    /**
     * @brief Block
     * Constructeur d'un block de base
     * @param name le nom du type
     * @param pos la position dans le board
     */
    Block(std::string name, Position pos): _name{name}, _pos{pos} {}

    virtual ~Block() = default;

  /**
   * @brief MoveBlock
   * Change la position du block en fonction de la direction
   * @param dir la direction où se déplacer
   */
    void MoveBlock(Direction dir) {_pos = _pos.move(dir);}

  /**
   * @brief getName
   * @return un string constant qui est le nom du block
   */
  const std::string getName() const {return _name;}

  /**
   * @brief getPosition
   * @return La &Position const qui est la position du block dans le board
   */
  const Position &getPosition() const {return _pos;}

  /**
   * @brief getIndexCase
   * @return l'index du block dans la case
   */
  int getIndexCase() const {return _indexCase;}

  /**
   * @brief setIndexCase
   * @param indexCase change l'index de la case
   */
  void setIndexCase(int indexCase) {_indexCase = indexCase;}

  /**
   * @brief clone
   * Permet de retourner le même block qui ne fait référence à personne
   * @return /
   */
  virtual std::shared_ptr<Block> clone() const = 0;

  /**
   * @brief to_String
   * @return un string qui représente le block qui est à redéfinir
   */
  virtual std::string to_String() const = 0;

  /**
   * @brief operator ==
   * L'opérateur d'égalité
   * @param other la Block à tester
   * @return true si ils sont égaux par leur nom, sinon, false
   */
  bool operator==(const Block& block) {return _name == block._name;}

  /**
   * @brief operator <<
   * L'opérateur d'insertion pour afficher un block dans un flux
   * @param os Le flux de sortie
   * @param block à afficher
   * @return Le flux de sortie modifié
   */
  friend std::ostream &operator<<(std::ostream& os, const Block& block) {return os << block.to_String();}
};

/**
 * @brief The Block class
 * Block de matériaux qui est un block enfant du block
 */
class BlockMatériaux : public Block {
    Matériaux _mat; // Le matériaux du block
    Direction _dir; // La direction pour la règle move

public:
    /**
     * @brief BlockMatériaux
     * Constructeur d'un blockMatériaux
     * @param mat le nom du type de block et qui sera transformé dans le bon matériaux
     * @param pos du block dans le board
     * @param dir la direction du block
     */
    BlockMatériaux(std::string mat, Position pos, Direction dir): Block{mat, pos}, _mat{convStringToMatériaux(mat)}, _dir{dir} {}

    /**
     * @brief getMatériaux
     * @return le matériaux du block
     */
    Matériaux getMatériaux() const {return _mat;}

    /**
     * @brief setMatériaux
     * Change le matériaux actuelle et le nom, par un nouveau matériaux et le nouveau nom
     * @param newMat le nouveau matériaux
     */
    void setMatériaux(Matériaux newMat){ _mat = newMat; _name = convMatériauxToString(newMat);}

    /**
     * @brief getDirection
     * @return la direction où le block peut se déplacer si controlé par la règle move
     */
    Direction getDirection() const {return _dir;}

    /**
     * @brief clone
     * @return le même blockMatériaux, mais sans nouvelle référence
     */
    std::shared_ptr<Block> clone() const override {return std::make_shared<BlockMatériaux>(*this);}

    /**
     * @brief to_String
     * @return un string qui représente le blockMatériaux
     */
    std::string to_String() const override {return displayMatériaux(_mat);};
};

/**
 * @brief The BlockText class
 * Block permetant de regrouper les blockTexts ensamble et est un enfant de block
 */
class BlockText : public Block {
public:
    BlockText(std::string name, Position pos): Block{name, pos} {}
    virtual std::string to_String() const = 0;
   virtual std::shared_ptr<Block> clone() const = 0;
};

/**
 * @brief The BlockSujet class
 * Block de sujet qui est un block enfant du block
 */
class BlockSujet : public BlockText {
    Sujet _suj; // Le sujet d'une règle
    Matériaux _mat; // Le matériaux affecté

public:
    /**
     * @brief BlockSujet
     * Constructeur d'un blockSujet
     * @param suj le nom du type de block et qui sera transformé dans le bon sujet
     */
    BlockSujet(std::string suj, Position pos): BlockText{suj, pos}, _suj{convStringToSujet(suj)}, _mat{convSujetToMatériaux(_suj)} {}

    /**
     * @brief getSujet
     * @return le sujet du block
     */
    Sujet getSujet() const {return _suj;}

    /**
     * @brief getMatériaux
     * @return le matériaux lié à son sujet
     */
    Matériaux getMatériaux() const {return _mat;}

    /**
     * @brief clone
     * @return le même BlockSujet, mais sans nouvelle référence
     */
    std::shared_ptr<Block> clone() const override {return std::make_shared<BlockSujet>(*this);}

    /**
     * @brief to_String
     * @return un string qui représente le BlockSujet
     */
    std::string to_String() const override {return displaySujet(_suj);}
};

/**
 * @brief The BlockSujet class
 * Block de connecteur qui est un block enfant du block
 */
class BlockConnecteur : public BlockText {
    Connecteur _con; // Le connecteur d'une règle

public:
    /**
     * @brief BlockConnecteur
     * Constructeur d'un BlockConnecteur
     * @param con le nom du type de block et qui sera transformé dans le bon connecteur
     */
    BlockConnecteur(std::string con, Position pos): BlockText{con, pos}, _con{convStringToConnecteur(con)} {}
    /**
     * @brief getConnecteur
     * @return le connecteur du block
     */
    Connecteur getConnecteur() const {return _con;}

    /**
     * @brief clone
     * @return le même BlockConnecteur, mais sans nouvelle référence
     */
    std::shared_ptr<Block> clone() const override {return std::make_shared<BlockConnecteur>(*this);}

    /**
     * @brief to_String
     * @return un string qui représente le BlockConnecteur
     */
    std::string to_String() const override {return displayConnecteur(_con);}
};

/**
 * @brief The BlockSujet class
 * Block de aspect qui est un block enfant du block
 */
class BlockAspect : public BlockText {
    Aspect _asp; // La règle à affecté sur un sujet (matériaux)

public:
    /**
     * @brief BlockAspect
     * Constructeur d'un BlockAspect
     * @param con le nom du type de block et qui sera transformé dans le bon aspect
     */
    BlockAspect(std::string asp, Position pos): BlockText{asp, pos}, _asp{convStringToAspect(asp)} {}

    /**
     * @brief getAspect
     * @return l'aspect (règle) du block
     */
    Aspect getAspect() const {return _asp;}

    /**
     * @brief clone
     * @return le même BlockAspect, mais sans nouvelle référence
     */
    std::shared_ptr<Block> clone() const override {return std::make_shared<BlockAspect>(*this);}

    /**
     * @brief to_String
     * @return un string qui représente le BlockAspect
     */
    std::string to_String() const override {return displayAspect(_asp);}
};


#endif // BLOCK_H
