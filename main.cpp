#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QTableView>
#include <QMainWindow>

int main(int argc, char *argv[]) {
    QApplication trips(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("trips.db");
    db.open();
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS departments ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "name TEXT, phone TEXT)");
    QMainWindow window;
    QTableView *tableView = new QTableView(&window);
    QSqlTableModel *model = new QSqlTableModel(nullptr);
    model->setTable("departments");  
    model->select();
    tableView->setModel(model);
    window.setCentralWidget(tableView);
    window.resize(800, 700);
    window.show();

    return trips.exec();
}
