#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadSettings();

    createConnection(databaseType, databaseHost, databaseName, databaseUser, databasePass);

    model = new QSqlTableModel(this);
    model->setTable("riCurrencyRatesLast");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    QTableView *view = new QTableView(this->centralWidget());
    view->setModel(model);
    view->resizeColumnsToContents();
    view->show();

    createMenuBar();
    createActions();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{

    saveSettings();
    event->accept();
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

void MainWindow::loadSettings()
{
    QSettings settings("minishop.ini",
                       QSettings::IniFormat);

    settings.beginGroup("Database");
        databaseType = settings.value("type","sqlite").toString();
        databaseHost = settings.value("host","localhost").toString();
        databaseName = settings.value("name","DB/minishop.db").toString();
        databaseUser = settings.value("user","user").toString();
        databasePass = settings.value("pass","pass").toString();
    settings.endGroup();
}

void MainWindow::saveSettings()
{
    QSettings settings("minishop.ini",
                       QSettings::IniFormat);

    settings.beginGroup("Database");
        settings.setValue("type", databaseType);
        settings.setValue("host", databaseHost);
        settings.setValue("name", databaseName);
        settings.setValue("user", databaseUser);
        settings.setValue("pass", databasePass);
    settings.endGroup();
}
