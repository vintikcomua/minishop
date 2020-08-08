#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //check the presence of the database driver in the system
    if (!QSqlDatabase::drivers().contains("QSQLITE"))
        QMessageBox::critical(
                    this,
                    tr("Unable to load database"),
                    tr("This demo needs the SQLITE driver")
                    );

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
