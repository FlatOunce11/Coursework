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