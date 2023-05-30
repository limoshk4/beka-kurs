//Основной файл главного окна
#include "mainwindow.h"
//Конструктор главного окна
MainWindow::MainWindow(QWidget *parent)
   : QMainWindow(parent)
{
    createWidgets();//Создание виджетов
    createLayout();//Создание компановки
    connectSignals();//Подключение сигналов
}
//Деструктор главного окна
MainWindow::~MainWindow()
{
}
//Создание виджетов
void MainWindow::createWidgets()
{
    saveAction = new QAction("&Save",this);//Действие "Сохранить"
    openAction = new QAction("&Open", this);//Действие "Открыть"
    brChannelAction = new QAction("&BR-Channel", this);//Действие "BR-канал"
    gbChannelAction = new QAction("&GB-Channel", this);//Действие "GB-канал"
    rgChannelAction = new QAction("&RG-Channel", this);//Действие "RG-канал"
    toolBar = new QToolBar;//Панель инструментов
    addToolBar(toolBar);//Добавление панели инструментов
    toolBar->addAction(openAction);//Добавления действия "Открыть" на панель инструментов
    toolBar->addSeparator();//Добавления разделителя
    toolBar->addAction(brChannelAction);//Добавления действия "BR-канал" на панель инструментов
    toolBar->addAction(gbChannelAction);//Добавления действия "GB-канал" на панель инструментов
    toolBar->addAction(rgChannelAction);//Добавления действия "RG-канал" на панель инструментов
    toolBar->addAction(saveAction);//Добавления действия "Сохранить" на панель инструментов
    originalImageLabel = new QLabel(this);//Метка для отображения изображения изображения
    originalImageLabel->setAlignment(Qt::AlignCenter);//Выравнивания метки по центру
    originalImageLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);//Растяжения метки
    // Устанавливаем размеры главного окна
    setMinimumSize(1920, 1080);
}
//Создание компановки
void MainWindow::createLayout()
{
    QWidget *centralWidget = new QWidget(this);//Центральный виджет
    setCentralWidget(centralWidget);//установка центрального виджета
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);//Вертикальная компановка
    mainLayout->addWidget(originalImageLabel);//Добавления метки в компановку
    centralWidget->setLayout(mainLayout);//Установка компановки для центрального виджета
}
//Подключения сигналов
void MainWindow::connectSignals()
{
           //Подключения действия "Открыть" к слоту открытия изображения
           connect(openAction,&QAction::triggered, this, &MainWindow::openImage);
           //Подключения действия "BR-канал" к слоту смешивания каналов BR
           connect(brChannelAction, &QAction::triggered, this, &MainWindow::mixBRChannels);
           //Подключения действия "GB-канал" к слоту смешивания каналов GB
           connect(gbChannelAction, &QAction::triggered, this, &MainWindow::mixGBChannels);
           //Подключения действия "RG-каналы" к слоту смешивания каналов RG
           connect(rgChannelAction, &QAction::triggered, this, &MainWindow::mixRGChannels);
           //Подключения действия "Сохранить" к слоту сохранения отображаемого изображения
           connect(saveAction, &QAction::triggered,this, &MainWindow::saveDisplayedImage);
       }
       //Слот открытия изображения
       void MainWindow::openImage()
     {
       //Диалоговое окно выбора файла
       QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files (*.png *.jpg *.bmp)"));
       if (!fileName.isEmpty()) {
       originalImage.load(fileName);//Загрузка изображения из файла
       originalImageLabel->setPixmap(QPixmap::fromImage(originalImage).scaled(originalImageLabel->size()));//Устоновка изображения на метку
       }
       }
//Слот смешивания каналов RG
void MainWindow::mixRGChannels()
{
mixedRGImage = originalImage;//Создания копии оригинального изображения
//Смешивания каналов RG путем замены значений красного и зеленого канала
for (int y = 0; y < mixedRGImage.height(); y++) {
for (int x = 0; x < mixedRGImage.width(); x++) {
QRgb pixel = mixedRGImage.pixel(x, y);
int red = qRed(pixel);
int green = qGreen(pixel);
mixedRGImage.setPixel(x, y, qRgb(green, green, red));
}
}
//Обновления отображаемого изображения на метке
originalImageLabel->setPixmap(QPixmap::fromImage(mixedRGImage).scaled(originalImageLabel->size()));
}
//Слот смешивания каналов GB
void MainWindow::mixGBChannels()
 {
mixedGBImage = originalImage;//Создание копии оригинального
//Смешивания каналов GB путем замены значений зеленого и синего каналов
for (int y = 0; y < mixedGBImage.height(); y++) {
for (int x = 0; x < mixedGBImage.width(); x++) {
QRgb pixel = mixedGBImage.pixel(x, y);
int green = qGreen(pixel);
int blue = qBlue(pixel);
mixedGBImage.setPixel(x, y, qRgb(green, blue, blue));
}
}
//Обновления отображаемого изображения на метке
originalImageLabel->setPixmap(QPixmap::fromImage(mixedGBImage).scaled(originalImageLabel->size()));
}
//Слот смешивания каналов BR
void MainWindow::mixBRChannels()
{
mixedBRImage = originalImage;//Создание копии оригинального
//Смешивания каналов BR путем замены значений зеленого и синего каналов
for (int y = 0; y < mixedBRImage.height(); y++) {
for (int x = 0; x < mixedBRImage.width(); x++) {
QRgb pixel = mixedBRImage.pixel(x, y);
int blue = qBlue(pixel);
int red = qRed(pixel);
mixedBRImage.setPixel(x, y, qRgb(red, blue, red));
}
}
//Обновления отображаемого изображения на метке
originalImageLabel->setPixmap(QPixmap::fromImage(mixedBRImage).scaled(originalImageLabel->size()));
}
//Слот сохранения отображаемого изображения
void MainWindow::saveDisplayedImage()
{
           //Диалоговое окно сохранения файла
           QString fileName = QFileDialog::getSaveFileName(this, "Save Image", QDir::homePath(), "Image Files (*.jpeg)");
           if (!fileName.isEmpty()) {
               QPixmap pixmap = originalImageLabel->grab();//Получения изображения с метки
               pixmap.save(fileName);//Сохранения изображения в файл
           }
       }
