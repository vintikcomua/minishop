#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

static bool createConnection(const QString &databaseType, const QString &databaseHost, const QString &databaseName, const QString &databaseUser, const QString &databasePass)
{
    //check the presence of the database driver in the system
    if (!QSqlDatabase::drivers().contains("Q"+databaseType.toUpper()))
    {
        QMessageBox::critical(
                    nullptr,
                    QObject::tr("Unable to load database"),
                    QObject::tr("This application needs the %1 database driver").arg(databaseType.toUpper())
                    );
        return false;
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("Q"+databaseType.toUpper());
    db.setHostName(databaseHost);
    db.setDatabaseName(databaseName);
    db.setUserName(databaseUser);
    db.setPassword(databasePass);

    if (!db.open()) {
        QMessageBox::critical(nullptr, QObject::tr("Cannot open database"),
            QObject::tr("Unable to establish a database connection.\n"
                        "This example needs %1 support. Please read "
                        "the Qt SQL driver documentation for information how "
                        "to build it.\n\n"
                        "Click Cancel to exit.").arg(databaseType.toUpper()), QMessageBox::Cancel);
        return false;
    }

    return true;
}

#endif // CONNECTION_H
