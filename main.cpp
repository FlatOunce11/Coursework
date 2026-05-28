#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMainWindow>

int main(int argc, char *argv[]) {
    QApplication trips(argc, argv);
    QMainWindow tripsWindow;
    QSqlDatabase tripsdb = QSqlDatabase::addDatabase("QSQLITE");
    QSqlQuery tripsquery(tripsdb);
    const char *dbPath = "trips.db";

    tripsdb.setDatabaseName(dbPath);
    tripsdb.open();
    tripsquery.exec(
        "CREATE TABLE IF NOT EXISTS departments ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT," 
        "name TEXT NOT NULL,"
        "phone_number TEXT"
        ")"
    );
    tripsquery.finish();
    tripsquery.exec(
        "CREATE TABLE IF NOT EXISTS workers ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "surname TEXT NOT NULL,"
        "name TEXT NOT NULL,"
        "patronymic TEXT NOT NULL,"
        "departament_id INTEGER,"
        "address TEXT,"
        "phone_number TEXT,"
        "FOREIGN KEY(departament_id) REFERENCES departaments(id)"
        ")"
    );
    tripsquery.finish();
    tripsquery.exec(
        "CREATE TABLE IF NOT EXISTS trips ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "worker_id INTEGER,"
        "city TEXT NOT NULL,"
        "departure_date DATE,"
        "count_days INTEGER,"
        "allowance INTEGER,"
        "price INTEGER,"
        "total INTEGER GENERATED ALWAYS AS ((count_days * allowance) + price) STORED,"
        "FOREIGN KEY(worker_id) REFERENCES workers(id)"
        ")"
    );
    tripsquery.finish();
    tripsdb.close();


    tripsWindow.setWindowTitle("Командировки");
    tripsWindow.resize(800, 600);
    tripsWindow.show();


    return trips.exec();
}
