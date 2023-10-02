#ifndef LOADER_H
#define LOADER_H

#include <filesystem>
#include <fstream>
#include <regex>

#include "board.h"

static const std::filesystem::path currentFilePath(__FILE__);
static const std::filesystem::path parentPath = currentFilePath.parent_path().parent_path();
static const std::filesystem::path relatifFolderPathNew = parentPath / "resources/maps/new";
static const std::filesystem::path relatifFolderPathSave = parentPath / "resources/maps/save";

/**
 * @brief The Loader class
 * Permet la création des maps à l'aide des fichiers textes
 * stockées dans les ressources et les stocks dans un vector
 */
class Loader {
    std::vector<Board> _listMap;
    std::vector<Board> _listSave;

    public:
    Loader();

    /**
     * @brief getBoard
     * Récupère le board dans la liste à la position donné en paramètre
     * @param index le n° du board dans la liste
     * @return le board sélectionné
     */
    Board getBoard(int index = 0);

    /**
     * @brief getSave
     * @return le board créer et sauvegarder dans un fichier
     */
    Board getSave();

    /**
     * @brief setSave
     * Seuvegarde de la partie
     * @param board la map à sauvegarder
     */
    void setSave(const Board board);

    /**
     * @brief getSize
     * @return le nbr de map jouable
     */
    int getSize() const;

    /**
     * @brief isThereSave
     * @return true, si il y a une map de save de chargé
     */
    bool isThereSave() const;


    private:

    /**
     * @brief readDirectory
     * @param folderPath le chemin du dossier où lire les fichiers
     * @return la liste de tous les fichiers contenue sdans le dossier passé en paramètre
     */
    std::vector<std::filesystem::path> readDirectory(const std::filesystem::path& folderPath);

    /**
     * @brief readFileText
     * Lis tout les fichiers.txt se trouvant dans le dossier passé en paramètre
     * et créer les board pour les stocks dans la réf de vector passé en paramètre
     * @param pathDir le dossier où lire les fichiers
     * @param listStockBoard l'endroit où stocker les boards créés
     */
    void readFileText(std::filesystem::path pathDir, std::vector<Board> &listStockBoard);

    /**
     * @brief creatFileText
     * Créer un fichier.txt contenant le contenue d'une map à un moment donné.
     * Si le fichier.txt existe déjà, le supprime et le recréer.
     * Si le fichier.txt existe pas, créer un fichier.txt
     * @param board la board à save dans un fichier.txt
     */
    void creatFileText(const Board board);

    /**
     * @brief creatRightBlock
     * Créer le bon block en testant de construire chaque type de block différents et le renvoie.
     * Si le block n'a pas pu être construit, invoque une erreur, arrétant le programme.
     * @param name le nom du type du block
     * @param dirIndex la diraction pour le block
     * @return le block construit ou une erreur si aucun block construit
     */
    std::shared_ptr<Block> creatRightBlock(std::string name, Position pos, int dirIndex);

    /**
     * @brief extractNumLevel
     * Extrait le numéro de level
     * @param levelName le nom du level ou prendre le n°
     * @return le n° du level
     */
    int extractNumLevel(std::string levelName);
};

#endif // LOADER_H
