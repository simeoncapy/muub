#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->time->setText(QTime::currentTime().toString("hh:mm"));
    startTimer(1000);
    this->showMaximized();

    /*QPixmap bkgnd(":/images/background-blue.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::KeepAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);*/

    setDesign();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setDesign()
{
    QSize iconSize = QSize(32,32);
    QColor white(Qt::white);


    setStyleSheet(
        "QMainWindow {background-image:url(\":/images/background-blue2.jpg\"); "
        "background-position: center;}"
        );

    int id = QFontDatabase::addApplicationFont(":/fonts/VarelaRound-Regular.ttf");
    QString fontFamily_title = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font_title(fontFamily_title, 24, QFont::Bold);

    ui->mediaCategory->setFont(font_title);
    ui->videoGamesCategory->setFont(font_title);
    ui->time->setFont(font_title);


    ui->logo->setPixmap(QIcon(":/images/logo.svg").pixmap(QSize(100,50)));
    loadGameService();

    //ui->bt_add->setIcon(QIcon(":/images/add_icon.svg").pixmap(iconSize));
    QPixmap pixmap = recolorSvg(":/images/add_icon.svg", white, iconSize);
    ui->bt_add->setIcon(QIcon(pixmap));
    ui->bt_add->setText("");
    ui->bt_add->setIconSize(iconSize);

    ui->bt_settings->setIcon(QIcon(recolorSvg(":/images/settings_icon.svg", white, iconSize)));
    ui->bt_settings->setText("");
    ui->bt_settings->setIconSize(iconSize);

    ui->saMedia->widget()->setMaximumHeight(150);
    ui->saMedia->setMaximumHeight(150);
    ui->saVideoGames->widget()->setMaximumHeight(150);
    ui->saVideoGames->setMaximumHeight(150);
    for(int i = 0 ; i < 10 ; i++)
    {
        QPushButton* bt = new QPushButton("Test ");
        bt->setMinimumSize(200,100);
        bt->setMaximumSize(200,100);
        ui->saMedia->widget()->layout()->addWidget(bt);
    }
}

void MainWindow::timerEvent(QTimerEvent * event)
{
    ui->time->setText(QTime::currentTime().toString("hh:mm"));
}

void MainWindow::loadGameService()
{
    QSize gameServiceIconSize = QSize(48,48);

    QVector<QString> name_gameService;
    // TODO List should be loaded from file
    name_gameService << "EA" << "Epic_Games" << "Steam" << "Ubisoft";

    int i = 0;
    foreach (QString gs, name_gameService) {
        try{
            m_list_gameService.insert(gs, (QPushButton*)ui->layout_gameService->itemAt(i)->widget());
            m_list_gameService[gs]->setIcon(QIcon(":/images/" + gs + "_logo.svg").pixmap(gameServiceIconSize));
        }
        catch(QException e)
        {
            if(i>4)
                qCritical() << "Impossible to load more services (" + QString(e.what()) + ")";
            else
                qCritical() << "Unable to load the icon (" + QString(e.what()) + ")";

            break;
        }

        m_list_gameService[gs]->setText("");
        m_list_gameService[gs]->setIconSize(gameServiceIconSize);

        QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect();
        effect->setBlurRadius(1); //Adjust accordingly
        effect->setOffset(3,3); //Adjust accordingly
        m_list_gameService[gs]->setGraphicsEffect(effect);
        //m_list_gameService[gs]->setStyle();
        m_list_gameService[gs]->installEventFilter(this);
        i++;
    }
}

QPixmap MainWindow::recolorSvg(const QString& path, const QColor& color, const QSize& size)
{
    QSvgRenderer renderer(path);
    QImage image(size, QImage::Format_ARGB32);
    image.fill(Qt::transparent);

    QPainter painter(&image);
    renderer.render(&painter);

    // Recolor the image
    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            QColor pixelColor = image.pixelColor(x, y);
            if (pixelColor.alpha() > 0) {
                // Check if the pixel color is the stroke color
                if (pixelColor != Qt::transparent && pixelColor != Qt::white) {
                    // Set the desired color while preserving the alpha and stroke width
                    QColor newColor(color);
                    newColor.setAlpha(pixelColor.alpha());
                    painter.setPen(newColor);
                    painter.setBrush(newColor);
                }
                painter.drawPoint(x, y);
            }
        }
    }

    return QPixmap::fromImage(image);
}

void MainWindow::on_bt_gs1_clicked()
{
    qDebug() << "Test";
    QProcess *process = new QProcess(this);
    QString file = "C:\\Program Files (x86)\\Microsoft\\Edge\\Application\\msedge.exe";
    process->start(file);
}

void MainWindow::resizeEvent(QResizeEvent*)
{
    ui->banner->setMinimumHeight((int)(0.33 * this->height()));
}

bool MainWindow::eventFilter(QObject* obj, QEvent* event)
{
    if(event->type() == QEvent::KeyPress)
    {
        qDebug() << "Key!";
        //QKeyEvent keyEvent = QKeyEvent(*event);
    }
    auto pushButton = qobject_cast<QPushButton*>(obj);
    if (nullptr != pushButton)
    {
        if (event->type() == QEvent::FocusIn)
        {
            qDebug() << "Focus in";
            QSize sz = QSize(ui->banner->height(), ui->banner->height());
            QIcon icon = pushButton->icon();
            QPixmap pixmap = icon.pixmap(sz).scaled(sz, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            ui->banner->setPixmap(pixmap);
        }
    }

    return QWidget::eventFilter(obj, event);
}
