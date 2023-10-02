#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPixmap>
#include <iostream>
#include <qevent.h>
#include "qlabel.h"
#include <vector>
#include "QMovie"

MainWindow::MainWindow(Model& facade,QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow), _facade{facade} {
    _facade.loadNew();
    ui->setupUi(this);
    _stackedWidget = new QStackedWidget;
    initStartMenu();
    QWidget *widget = initGridLayout();
    initHelpWidget();
    _stackedWidget->addWidget(_startMenu);
    _stackedWidget->addWidget(widget);
    _stackedWidget->addWidget(_helpWidget);
    _stackedWidget->setFixedSize(_startMenu->size());
    connect(_startMenu, &StartMenu::playClicked, this, &MainWindow::setGame);
    connect(_startMenu, &StartMenu::exitClicked, this, &QWidget::close);
    connect(_startMenu, &StartMenu::saveClicked, this, &MainWindow::setSave);
    connect(_startMenu, &StartMenu::helpClicked, this, &MainWindow::setHelp);
    connect(_helpWidget, &helpWidget::backClicked, this, &MainWindow::setStart);
    this->setCentralWidget(_stackedWidget);
    this->setWindowTitle("Baba is you");
    adjustSize();
}

MainWindow::MainWindow(const MainWindow& other) : _facade{other._facade} {}

void MainWindow::setupBoard(bool verif) {
    std::pair<int, int> sizeBoard = oldVec.getSizeRowAndCol();
    for (int x = 0; x < sizeBoard.first; ++x) {
        for (int y = 0; y < sizeBoard.second; ++y) {
            if(verif) {
                if(!(oldVec.getCarte()[y][x] == _facade.getBoard().getCarte()[y][x])){
                    initBoard(x, y);
                }
            }else {
                initBoard(x, y);
            }
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    oldVec = _facade.getBoard();
    if (event->key() == Qt::Key_Up){
        _facade.executeMove(Direction::NORD);
    } else if(event->key() == Qt::Key_Down){
        _facade.executeMove(Direction::SUD);
    } else if(event->key() == Qt::Key_Left){
        _facade.executeMove(Direction::OUEST);
    } else if(event->key() == Qt::Key_Right){
        _facade.executeMove(Direction::EST);
    } else if(event->key() == Qt::Key_U){
        if(!_facade.isEmptyUndo()) {
            _facade.undoMove();
        }
    } else if(event->key() == Qt::Key_R){
        if(!_facade.isEmptyRedo()) {
            _facade.redoMove();
        }
    } else if(event->key() == Qt::Key_S){
        _facade.saveBoard();
    } else if(event->key() == Qt::Key_Q || event->key() == Qt::Key_Escape){
        setStart();
    }
    if(_facade.getState() == State::WIN) {
       _facade.nextBoard();
    } else if(_facade.getState() == State::LOOSE) {
        _facade.restartBoard();
        setupBoard(false);
    }
}

QWidget* MainWindow::initGridLayout() {
    oldVec = _facade.getBoard();
    _gridLayout = new QGridLayout();
    _gridLayout->setSpacing(0);
    std::pair<int, int> sizeBoard = _facade.sizeBoard();
    for (int x = 0; x < sizeBoard.first; ++x) {
        for (int y = 0; y < sizeBoard.second; ++y) {
            initBoard(x,y);
        }
    }
    QWidget *widget = new QWidget;
    widget->setLayout(_gridLayout);
    return widget;
}

void MainWindow::initStartMenu() {
    _startMenu = new StartMenu();
}

void MainWindow::initHelpWidget() {
    _helpWidget = new helpWidget();
}

void MainWindow::initBoard(int x,int y) {
    QPixmap pixVoid(":/resources/images/void.png");
    QLabel *label = new QLabel();
    label->setPixmap(pixVoid);
    _gridLayout->addWidget(label,x,y);
    QMovie combined;
    for(const auto& b : _facade.getBoard().getCarte()[y][x].getAllBlock()){
        QMovie* movie;
        if(!images.count(b->getName())){
            std::string str = ":/resources/images/"+b->getName()+".gif";
            movie = new QMovie(str.c_str());
            images[b->getName()] = movie;
            } else{
                movie = images.at(b->getName());
            }
            QLabel* label = new QLabel();
            label->setMovie(movie);
            label->setScaledContents(true);
            _gridLayout->addWidget(label,x,y);
            movie->start();
    }
}

void MainWindow::setStart() {
    _stackedWidget->setCurrentIndex(0);
    _stackedWidget->setFixedSize(_startMenu->minimumSize());
    adjustSize();
}

void MainWindow::setHelp() {
    _stackedWidget->setCurrentIndex(2);
}

void MainWindow::setGame() {
    _facade.loadNew();
    startGame();
}

void MainWindow::setSave() {
    _facade.loadSave();
    startGame();
}

void MainWindow::startGame() {
    _stackedWidget->setCurrentIndex(1);
    _stackedWidget->setFixedSize(_gridLayout->minimumSize());
    adjustSize();
}

MainWindow::~MainWindow() {
    delete ui; 
}

