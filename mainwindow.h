#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QFontDatabase>
#include <QPushButton>
#include <QException>
#include <QGraphicsDropShadowEffect>
#include <QProcess>
#include <QSvgRenderer>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void on_bt_gs1_clicked();

private:
    Ui::MainWindow *ui;
    QMap<QString, QPushButton*> m_list_gameService;

    void timerEvent(QTimerEvent *event);
    void loadGameService();
    QPixmap recolorSvg(const QString& path, const QColor& color, const QSize& size);
    void setDesign();
};
#endif // MAINWINDOW_H
