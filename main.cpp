//Подключение заголовочного файла MainWindow
#include "mainwindow.h"
//Подключение заголовочного файла QApplication
#include <QApplication>
//Создание экземпляра приложения
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;//Создания экземпляра главного окна
    w.show();//Отображения главного канала

    return a.exec();//Запуск основного цикла приложения и ожидание событий
}
