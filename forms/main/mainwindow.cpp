#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->mdiArea = new QMdiArea(this);
    //ui->mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    //ui->mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    loadSettings();

    createConnection(databaseType, databaseHost, databaseName, databaseUser, databasePass);


    //setCentralWidget(view);
    setCentralWidget(ui->mdiArea);
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

    connect(ui->actionNomenclature, &QAction::triggered, this, &MainWindow::openNomenclature);
    connect(ui->actionManufacturers, &QAction::triggered, this, &MainWindow::openManufacturers);
}


void MainWindow::aboutMiniShop()
{
    AboutDialog dialog(this);
    dialog.exec();
}

void MainWindow::openManufacturers()
{

    model = new QSqlTableModel(this);
    model->setTable("dicManufacturers");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    QTableView *view = new QTableView(this);
    view->setModel(model);
    view->resizeColumnsToContents();
    view->setSelectionBehavior(QTableView::SelectRows);

    QMdiSubWindow *subWindow = ui->mdiArea->addSubWindow(view);
    subWindow->setWindowTitle("Виробники");
    //view->show();
    subWindow->show();
}

void MainWindow::openNomenclature()
{

    model = new QSqlTableModel(this);
    model->setTable("dicProducts");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    QTableView *view = new QTableView(this);
    view->setModel(model);
    view->resizeColumnsToContents();
    view->setSelectionBehavior(QTableView::SelectRows);

    QMdiSubWindow *subWindow = ui->mdiArea->addSubWindow(view);
    subWindow->setWindowTitle("Товари");
    //view->show();
    subWindow->show();
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
