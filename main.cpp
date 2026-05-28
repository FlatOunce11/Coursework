#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QTableView>
#include <QMainWindow>

int main(int argc, char *argv[]) {
    QApplication trips(argc, argv);
    QMainWindow tripsWindow;
    tripsWindow.setWindowTitle("Командировки");
    tripsWindow.resize(800, 600);
    tripsWindow.show();
    return trips.exec();
}
