#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtSql>
#include <QMessageBox>
#include <QSettings>
#include <QCloseEvent>

#include "connection.h"
#include "dialogs/aboutdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

        QString databaseType = "";
        QString databaseHost = "";
        QString databaseName = "";
        QString databaseUser = "";
        QString databasePass = "";

        QSqlTableModel *model;
    private:
        Ui::MainWindow *ui;

        void createMenuBar();
        void createActions();
        void loadSettings();
        void saveSettings();

    protected:
        void closeEvent(QCloseEvent *event) override;

    private slots:
        void aboutMiniShop();
        void openNomenclature();
};
#endif // MAINWINDOW_H
