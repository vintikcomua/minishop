#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dialogs/aboutdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createMenuBar();
    createActions();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createMenuBar()
{

}

void MainWindow::createActions() {

    connect(ui->quitAction, &QAction::triggered, this, &MainWindow::close);
    connect(ui->aboutAction, &QAction::triggered, this, &MainWindow::aboutMiniShop);
}


void MainWindow::aboutMiniShop()
{
    AboutDialog dialog(this);
    dialog.exec();
}
