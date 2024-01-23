#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("127.0.0.1");
    db.setPort(5432);
    db.setDatabaseName("MyTestDB");
    //db.setUserName("QtUser");
    //db.setPassword("QtUser");
    db.setUserName("postgres");
    db.setPassword("user");


    if (db.open())
    {
        qDebug() << "Connected";
    }
    else
    {
        qDebug() << "Fail";
        return 0;
    }

    QString command = "SELECT my_user.username, department.name AS deptname "
                      "FROM (SELECT * FROM users WHERE status = 0) AS my_user "
                      "INNER JOIN department ON department.id = my_user.deptid";
    QSqlQuery query(db);
    if (query.exec(command))
    {
        qDebug() << "Enter IF";
        while (query.next())
        {
            qDebug() << query.value("username").toString() << query.value("deptname").toString();
        }
    }

    return a.exec();
}
