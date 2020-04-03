#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    int display(struct LinkedListNode *);

private slots:
    void on_pushButton_Search_Flights_2_clicked();

    void on_pushButton_Exit_clicked();

    void on_pushButton_Exit_3_clicked();

    void on_pushButton_Book_a_Flight_clicked();

    void on_pushButton_Back_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
