#include "Loader.h"
#include <iostream>

Loader::Loader() {
    readFileText(relatifFolderPathNew, _listMap);
    readFileText(relatifFolderPathSave, _listSave);
}

Board Loader::getBoard(int index){
    return _listMap[index];
}

Board Loader::getSave() {return _listSave[0];}

void Loader::setSave(const Board board) {
    creatFileText(board);
    _listSave.clear();
    readFileText(relatifFolderPathSave, _listSave);
}

int Loader::getSize() const{
    return _listMap.size();
}

bool Loader::isThereSave() const {return _listSave.empty();}

std::vector<std::filesystem::path> Loader::readDirectory(const std::filesystem::path& folderPath) {
    std::vector<std::filesystem::path> savePath;
    for (auto& entry : std::filesystem::directory_iterator(folderPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            savePath.emplace_back(entry.path());
        }
    }
    return savePath;
}

void Loader::readFileText(std::filesystem::path pathDir, std::vector<Board>& listStockBoard) {
    std::vector<std::filesystem::path> listFilePath {readDirectory(pathDir)};
    for (const auto& filePath : listFilePath) {

        std::ifstream curFile(filePath);
        if (!curFile.is_open()) {
            throw std::runtime_error("Failed to open file: " + filePath.string());
        }

        // Récupération du nom de fichier
        std::string fileName = filePath.filename().string();
        int numLevel = extractNumLevel(fileName);


        std::string line;
        int width, lenght;
        // Lecture des deux premières informations
        curFile >> width >> lenght;
    //    std::cout << "x width: " << width << ", y lenght: " << lenght << std::endl;

        curFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        Board board {width, lenght, numLevel};

        while(getline(curFile, line)) { //placmeent des blocks
            std::istringstream word(line);
            std::string sub;
            std::string mot;
            int x;
            int y;
            int dirIndex {0};

            word >> mot >> x >> y >> dirIndex; //Récupération des informations



    //        cout << "début ligne n°: " << endl;
    //        cout << line << endl;
    //        cout << mot << " " << x << " " << y << " " << dirIndex << endl;


            Position pos {x,y};
            board.addBlock(creatRightBlock(mot, pos, dirIndex)); // lance une erreur complète
        }
        listStockBoard.emplace_back(board);
    }
}

void Loader::creatFileText(const Board board) {
    std::string nameFile = "save_" + std::to_string(board.getNumBoard()) + ".txt";
    std::string cheminComplet = relatifFolderPathSave.string() + "/" + nameFile;
    for (const auto& entry : std::filesystem::directory_iterator(relatifFolderPathSave)) {
        if (entry.is_regular_file()) {
            std::filesystem::remove(entry);
        }
    }

//    cout << "Chemin complet du fichier " << cheminComplet << endl;
    std::ofstream fichier(cheminComplet);
    fichier << board.getSizeRowAndCol().first << " " << board.getSizeRowAndCol().second << "\n";

    for (int x = 0; x < board.getSizeRowAndCol().first; ++x) {
        for (int y = 0; y < board.getSizeRowAndCol().second; ++y) {
            for (const auto& block  : board.getCarte()[x][y].getAllBlock()) {
                fichier << block->getName() << " " << x << " " << y << " ";
                if(const auto& bMat = std::dynamic_pointer_cast<BlockMatériaux>(block)) {
                    fichier << convDirectionToInt(bMat->getDirection());
                }
                fichier << "\n";
            }
        }
    }
    fichier.close();
}

std::shared_ptr<Block> Loader::creatRightBlock(std::string name, Position pos, int dirIndex) {
    Direction dir = convIntToDirection(dirIndex);
    try {
        return std::make_shared<BlockMatériaux>(name, pos, dir);
    } catch (...) {    try {
            return std::make_shared<BlockSujet>(name, pos);
        } catch (...) {
            try {
                return std::make_shared<BlockConnecteur>(name, pos);
            } catch (...) {
                try {
                    return std::make_shared<BlockAspect>(name, pos);
                } catch (...) {
                    throw std::invalid_argument("Aucun block correct n'a pu être créé");
                }
            }
        }
    }
}

int Loader::extractNumLevel(std::string levelName) {
    std::regex rgx("\\d+"); // expression régulière pour trouver un ou plusieurs chiffres
    std::smatch match;
    std::regex_search(levelName, match, rgx);
    try {
        return std::stoi(match[0]);
    } catch (...) {
        std::cout << "erreur d'extraction du n° du level {" << levelName << "}." << std::endl;
        return -1;
    }
}
