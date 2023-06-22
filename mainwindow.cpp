#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->time->setText(QTime::currentTime().toString("hh:mm"));
    startTimer(1000);

    QFont fontCategory = QFont("Helvetica", 16, QFont::Bold);
    ui->mediaCategory->setFont(fontCategory);
    ui->videoGamesCategory->setFont(fontCategory);
    ui->time->setFont(fontCategory);

    QPixmap logo(":/images/logo.svg");
    //QIcon(":/images/logo.svg").pixmap(QSize())
    ui->logo->setPixmap(QIcon(":/images/logo.svg").pixmap(QSize()));
    //ui->logo->setMask(logo.mask());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent * event)
{
    ui->time->setText(QTime::currentTime().toString("hh:mm"));
}
