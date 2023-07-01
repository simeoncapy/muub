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

   setStyleSheet(
        "QMainWindow {background-image:url(\":/images/background-blue.jpg\"); background-position: center;}" );

    int id = QFontDatabase::addApplicationFont(":/fonts/VarelaRound-Regular.ttf");
    QString fontFamily_title = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font_title(fontFamily_title, 20, QFont::Bold);

    ui->mediaCategory->setFont(font_title);
    ui->videoGamesCategory->setFont(font_title);
    ui->time->setFont(font_title);


    ui->logo->setPixmap(QIcon(":/images/logo.svg").pixmap(QSize(100,50)));
    loadGameService();

    QSize iconSize = QSize(32,32);
    ui->bt_add->setIcon(QIcon(":/images/add_icon.svg").pixmap(iconSize));
    ui->bt_add->setText("");
    ui->bt_add->setIconSize(iconSize);
    ui->bt_settings->setIcon(QIcon(":/images/settings_icon.svg").pixmap(iconSize));
    ui->bt_settings->setText("");
    ui->bt_settings->setIconSize(iconSize);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent * event)
{
    ui->time->setText(QTime::currentTime().toString("hh:mm"));
}

void MainWindow::loadGameService()
{
    QSize gameServiceIconSize = QSize(48,48);

    QVector<QString> name_gameService;
    // List should be loaded from file
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
        i++;
    }
}

void MainWindow::on_bt_gs1_clicked()
{
    qDebug() << "Test";
    QProcess *process = new QProcess(this);
    QString file = "C:\\Program Files (x86)\\Microsoft\\Edge\\Application\\msedge.exe";
    process->start(file);
}
