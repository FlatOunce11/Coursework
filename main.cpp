#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMainWindow>
#include <QShortcut>
#include <QTabWidget>
#include <QTableView>
#include <QSqlTableModel>
#include <QBoxLayout>
#include <QPushButton>

void initdb(QSqlDatabase &tripsdb){
    QSqlQuery tripsquery(tripsdb);
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
        "FOREIGN KEY(departament_id) REFERENCES departments(id)"
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
        "INSERT OR REPLACE INTO departments(id, name, phone_number) VALUES"
        "(1, 'Отдел кадров', '+7-391-151-00-01'),"
        "(2, 'Отдел дизайна', '+7-391-151-00-02'),"
        "(3, 'Отдел програмирования', '+7-391-151-00-03');"
    );
    tripsquery.finish();
    tripsquery.exec(
        "INSERT OR REPLACE INTO workers(id, surname, name, patronymic, departament_id, address, phone_number) VALUES"
        "(1, 'Ковальский', 'Алексей', 'Валерьевич', '1', 'ул. Кельвина, д. 506', '+7-392-151-01-01'),"
        "(2, 'Осипов', 'Олег', 'Васильевич', '1', 'ул. Ньюэлла, д. 2', '+7-392-151-01-02'),"
        "(3, 'Киселев', 'Дмитрий', 'Сергеевич', '1', 'ул. Платиновая, д. 300', '+7-392-151-01-03'),"
        "(4, 'Галочкин', 'Максим', 'Сергеевич', '2', 'ул. Баумана, д. 46', '+7-392-151-02-01'),"
        "(5, 'Брагин', 'Антон', 'Александрович', '2', 'ул. Телевизорная, д. 215', '+7-392-151-02-02'),"
        "(6, 'Андреев', 'Фёдор', 'Александрович', '2', 'ул. Дорожная, д. 85', '+7-392-151-02-03'),"
        "(7, 'Кучеров', 'Олег', 'Александрович', '3', 'ул. Калинина, д. 111', '+7-392-151-03-01'),"
        "(8, 'Черепанов', 'Андрей', 'Андреевич', '3', 'ул. Марковского, д. 92', '+7-392-151-03-02'),"
        "(9, 'Шиманович', 'Никита', 'Дмитриевич', '3', 'ул. Минская, д. 17', '+7-392-151-03-03');"
    );
    tripsquery.finish();
    tripsquery.exec(
        "INSERT OR REPLACE INTO trips(id, worker_id, city, departure_date, count_days, allowance, price) VALUES"
        "(1, 1, 'Тольятти', '2026-03-12', 3, 2300, 15000),"
        "(2, 1, 'Киров', '2026-03-13', 5, 4700, 23400),"
        "(3, 2, 'Пермь', '2026-03-14', 4, 850, 26000),"
        "(4, 2, 'Ижевск', '2026-03-15', 3, 6300, 40000),"
        "(5, 3, 'Екатеринбург', '2026-03-17', 3, 1500, 8500),"
        "(6, 3, 'Челябинск', '2026-03-18', 2, 1750, 8600),"
        "(7, 4, 'Уфа', '2026-03-20', 4, 4800, 24500),"
        "(8, 4, 'Оренбург', '2026-03-21', 2, 1400, 56000),"
        "(9, 5, 'Магнитогорск', '2026-03-22', 1, 1500, 32000),"
        "(10, 5, 'Курган', '2026-03-24', 1, 2600, 26800),"
        "(11, 6, 'Тюмень', '2026-03-25', 1, 2300, 15000),"
        "(12, 6, 'Омск', '2026-03-26', 6, 4700, 23400),"
        "(13, 7, 'Новосибирск', '2026-03-28', 7, 850, 26000),"
        "(14, 7, 'Барнаул', '2026-03-29', 4, 6300, 40000),"
        "(15, 8, 'Новокузнецк', '2026-03-31', 4, 1500, 85000),"
        "(16, 8, 'Кемерово', '2026-04-01', 3, 1750, 81600),"
        "(17, 9, 'Томск', '2026-04-02', 9, 4800, 24500),"
        "(18, 9, 'Красноярск', '2026-04-05', 5, 6000, 27000);"
    );
    tripsquery.finish();
}
int main(int argc, char *argv[]) {
    QApplication trips(argc, argv);
    QMainWindow tripsWindow;
    QSqlDatabase tripsdb = QSqlDatabase::addDatabase("QSQLITE");
    QSqlQuery tripsquery(tripsdb);
    const char *dbPath = "trips.db";
    tripsdb.setDatabaseName(dbPath);
    if (!tripsdb.open()) return 1;
    tripsdb.exec("PRAGMA foreign_keys = ON;");
    initdb(tripsdb); 
    QWidget *mainWidget = new QWidget(&tripsWindow);
    QHBoxLayout *mainLayout = new QHBoxLayout(mainWidget);
    QWidget *leftButtonPanel = new QWidget(&tripsWindow);
    QVBoxLayout *leftButtonLayout = new QVBoxLayout(leftButtonPanel);
    QPushButton *button1 = new QPushButton("Добавить строку (i)", leftButtonPanel);
    QPushButton *button2 = new QPushButton("Удалить строку (d)", leftButtonPanel);
    QPushButton *button3 = new QPushButton("кнопка 3", leftButtonPanel);
    leftButtonPanel->setFixedWidth(300);
    leftButtonLayout->addWidget(button1);
    leftButtonLayout->addWidget(button2);
    leftButtonLayout->addWidget(button3);
    leftButtonLayout->addStretch();
    QTabWidget *tripsWindowTab = new QTabWidget(&tripsWindow);
    QSqlTableModel *depatrmentsTable = new QSqlTableModel(nullptr, tripsdb);
    depatrmentsTable->setTable ("departments");
    depatrmentsTable->select();
    QTableView *depatrmentsTab = new QTableView;
    depatrmentsTab->setModel(depatrmentsTable);
    tripsWindowTab->addTab(depatrmentsTab, "Отделы");
    QSqlTableModel *workersTable = new QSqlTableModel(nullptr, tripsdb);
    workersTable->setTable ("workers");
    workersTable->select();
    QTableView *workersTab = new QTableView;
    workersTab->setModel(workersTable);
    tripsWindowTab->addTab(workersTab, "Сотрудники");
    QSqlTableModel *tripsTable = new QSqlTableModel(nullptr, tripsdb);
    tripsTable->setTable ("trips");
    tripsTable->select();
    QTableView *tripsTab = new QTableView;
    tripsTab->setModel(tripsTable);
    tripsWindowTab->addTab(tripsTab, "Командировки");
    mainLayout->addWidget(leftButtonPanel);
    mainLayout->addWidget(tripsWindowTab);
    new QShortcut(QKeySequence("CTRL+W"), &tripsWindow, SLOT(close()));
    new QShortcut(QKeySequence("Esc"), &tripsWindow, SLOT(close()));
    new QShortcut(QKeySequence("1"), &tripsWindow, [&]() {tripsWindowTab->setCurrentIndex(0);});
    new QShortcut(QKeySequence("2"), &tripsWindow, [&]() {tripsWindowTab->setCurrentIndex(1);});
    new QShortcut(QKeySequence("3"), &tripsWindow, [&]() {tripsWindowTab->setCurrentIndex(2);});
    QObject::connect(button1, &QPushButton::clicked, [=]() {
        int selectTab = tripsWindowTab->currentIndex();
        switch (selectTab){
        case 0:
            depatrmentsTable->insertRow(depatrmentsTable->rowCount());
            break;
        case 1:
            workersTable->insertRow(workersTable->rowCount());
            break;
        case 2:
            tripsTable->insertRow(tripsTable->rowCount());
            break;
        }
    });
    tripsWindow.setWindowTitle("Курсовая Работа - БД Командировки");
    tripsWindow.resize(900, 700);
    tripsWindow.show();
    tripsWindow.setCentralWidget(mainWidget);
    return trips.exec();
}