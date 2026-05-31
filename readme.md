# коментарии к коду

## действия с окном

|код|объяснение|
|-|-|
|QApplication trips(argc, argv);|создание объекта приложения trips с переменными окружения(argc, argv)|
|QMainWindow tripsWindow;|создание объекта окна tripsWindow|
|tripsWindow.setWindowTitle("Командировки");|Заголовок окна - Командировки|
|tripsWindow.resize(800, 600);|Размер окна - 800х600|
|tripsWindow.show();|Показ окна на экране|
|return trips.exec();|просто return|

## действия с бд

|код|объяснение|
|-|-|
|QSqlDatabase tripsdb = QSqlDatabase::addDatabase("QSQLITE");|Создание объекта tripsdb, c драйвером бд QSQLITE|
|QSqlQuery tripsquery(tripsdb);|Создание объекта tripsquery с которым можно делать запросы к объекту tripsdb|
|const char *dbPath = "trips.db";|относительный путь к файлу бд|
|tripsdb.setDatabaseName(dbPath);|файл бд создается автоматически|
|tripsdb.open();|открытие бд|
|tripsquery.exec()|запросы к бд|
|"CREATE TABLE IF NOT EXISTS имя_таблицы"|создать таблицу если ещё не создана|
|"id INTEGER PRIMARY KEY AUTOINCREMENT,"|id - первичный ключ в таблице|
|"name TEXT NOT NULL,"|текстовое поле, которое не должно быть пустым|
|"phone_number TEXT"|текстовое поле|
|"departament_id INTEGER,"|числовое поле|
|"departure_date DATE,"|поле с датой|
|"FOREIGN KEY(departament_id) REFERENCES departaments(id)"|подключение внешнего ключа из таблицы departaments|
|"total INTEGER GENERATED ALWAYS AS ((count_days * allowance) + price) STORED,"|подсчет общей стоимости поездки|
|tripsquery.finish();|завершение запроса к бд|
|tripsdb.close();|закрытие бд|

## удобство использования

|код|объяснение|
|-|-|
|new QShortcut(QKeySequence("CTRL+W"), &tripsWindow, SLOT(close()));|сочетание клавиш, закрывающее окно tripsWindow. сохранен в динамичекой памяти|