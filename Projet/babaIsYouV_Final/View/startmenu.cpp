#include "startmenu.h"
#include "ui_startmenu.h"

StartMenu::StartMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartMenu)
{
    ui->setupUi(this);
}

StartMenu::~StartMenu()
{
    delete ui;
}

void StartMenu::on_playButton_clicked()
{
    emit playClicked();
}


void StartMenu::on_exitButton_clicked()
{
    emit exitClicked();
}


void StartMenu::on_saveButton_clicked()
{
    emit saveClicked();
}


void StartMenu::on_helpButton_clicked()
{
    emit helpClicked();
}

