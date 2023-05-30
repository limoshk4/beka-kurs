//Защита от повторного включения заголовочного файла
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QLabel>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QToolBar>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QPushButton>
class MainWindow : public QMainWindow
{
   Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);//Конструктор главного окна
    ~MainWindow();//Деструктор главного окна
private slots:
    void saveDisplayedImage();//Слот для сохранения отображаемого изображения
    void openImage();//Слот для открытия изображения
    void mixRGChannels();//Слот для смешивания каналов RG
    void mixGBChannels();//Слот для смешивания каналов GB
    void mixBRChannels();//Слот для смешивания каналов BR
private:
    QToolBar *toolBar;//Панель инструментов
    QAction *saveAction;//Действия "Сохранить"
    QAction *openAction;//Действия "Открыть"
    QAction *brChannelAction;//Действия "BR-канал"
    QAction *gbChannelAction;//Действия "GB-канал"
    QAction *rgChannelAction;//Действия "RG-канал"
    QLabel *originalImageLabel;//Метка для отображения оригинального изображения
    QLabel *mixedRGImageLabel;//Метка для отбражения смешанного изображения с каналами RG
    QLabel *mixedGBImageLabel;//Метка для отображения смешанного избражения с каналами GB
    QLabel *mixedBRImageLabel;//Метка для отображения смешанного изображения с каналами BR
    QPushButton *openButton;//Кнопка "Открыть"
    QImage originalImage;//Оригинальное изображения
    QImage mixedRGImage;//Изображения с смешанными каналами RG
    QImage mixedGBImage;//Изображения с смешанными каналами GB
    QImage mixedBRImage;//Изображения с смешанными каналами BR
    void createWidgets();//Создание виджетов
    void createLayout();//Создание компоновки
    void connectSignals();//Подключение сигналов
};
#endif // MAINWINDOW_H
