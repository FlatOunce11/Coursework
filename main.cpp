#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMainWindow>
#include <QShortcut>

void initdb(QSqlDatabase &tripsdb){
    QSqlQuery tripsquery(tripsdb);
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
    tripsquery.exec(
        "INSERT INTO departments(name, phone_number) VALUES"
        "('Отдел кадров', '+7-391-151-00-01'),"
        "('Отдел дизайна', '+7-391-151-00-02'),"
        "('Отдел програмирования', '+7-391-151-00-03');"
    );
    tripsquery.finish();
    tripsquery.exec(
        "INSERT INTO workers(surname, name, patronymic, departament_id, address, phone_number) VALUES"
        "('Ковальский', 'Алексей', 'Валерьевич', '1', 'ул. Кельвина, д. 506', '+7-392-151-01-01'),"
        "('Осипов', 'Олег', 'Васильевич', '1', 'ул. Ньюэлла, д. 2', '+7-392-151-01-02'),"
        "('Киселев', 'Дмитрий', 'Сергеевич', '1', 'ул. Платиновая, д. 300', '+7-392-151-01-03'),"
        "('Галочкин', 'Максим', 'Сергеевич', '2', 'ул. Баумана, д. 46', '+7-392-151-02-01'),"
        "('Брагин', 'Антон', 'Александрович', '2', 'ул. Телевизорная, д. 215', '+7-392-151-02-02'),"
        "('Андреев', 'Фёдор', 'Александрович', '2', 'ул. Дорожная, д. 85', '+7-392-151-02-03'),"
        "('Кучеров', 'Олег', 'Александрович', '3', 'ул. Калинина, д. 111', '+7-392-151-03-01'),"
        "('Черепанов', 'Андрей', 'Андреевич', '3', 'ул. Марковского, д. 92', '+7-392-151-03-02'),"
        "('Шиманович', 'Никита', 'Дмитриевич', '3', 'ул. Минская, д. 17', '+7-392-151-03-03');"
    );
    tripsquery.finish();
    tripsquery.exec(
        "INSERT INTO trips(worker_id, city, departure_date, count_days, allowance, price) VALUES"
        "(1, 'Тольятти', '2026-03-12', 3, 2300, 15000),"
        "(1, 'Киров', '2026-03-13', 5, 4700, 23400),"
        "(2, 'Пермь', '2026-03-14', 4, 850, 26000),"
        "(2, 'Ижевск', '2026-03-15', 3, 6300, 40000),"
        "(3, 'Екатеринбург', '2026-03-17', 3, 1500, 8500),"
        "(3, 'Челябинск', '2026-03-18', 2, 1750, 8600),"
        "(4, 'Уфа', '2026-03-20', 4, 4800, 24500),"
        "(4, 'Оренбург', '2026-03-21', 2, 1400, 56000),"
        "(5, 'Магнитогорск', '2026-03-22', 1, 1500, 32000),"
        "(5, 'Курган', '2026-03-24', 1, 2600, 26800),"
        "(6, 'Тюмень', '2026-03-25', 1, 2300, 15000),"
        "(6, 'Омск', '2026-03-26', 6, 4700, 23400),"
        "(7, 'Новосибирск', '2026-03-28', 7, 850, 26000),"
        "(7, 'Барнаул', '2026-03-29', 4, 6300, 40000),"
        "(8, 'Новокузнецк', '2026-03-31', 4, 1500, 85000),"
        "(8, 'Кемерово', '2026-04-01', 3, 1750, 81600),"
        "(9, 'Томск', '2026-04-02', 9, 4800, 24500),"
        "(9, 'Красноярск', '2026-04-05', 5, 6000, 27000);"
    );
    tripsquery.finish();        
    tripsdb.close();
}

int main(int argc, char *argv[]) {
    QApplication trips(argc, argv);
    QMainWindow tripsWindow;
    new QShortcut(QKeySequence("CTRL+W"), &tripsWindow, SLOT(close()));
    new QShortcut(QKeySequence("Esc"), &tripsWindow, SLOT(close()));
    QSqlDatabase tripsdb = QSqlDatabase::addDatabase("QSQLITE");
    QSqlQuery tripsquery(tripsdb);
    const char *dbPath = "trips.db";
    tripsdb.setDatabaseName(dbPath);
    new QShortcut(QKeySequence("Ctrl+R"), &tripsWindow, [&]() { initdb(tripsdb); });
    tripsWindow.setWindowTitle("Командировки");
    tripsWindow.resize(800, 600);
    tripsWindow.show();


    return trips.exec();
}
