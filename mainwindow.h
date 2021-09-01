#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QSortFilterProxyModel>
#include <QSharedPointer>
#include <random>
#include "Student.h"
#include "ItemDelegate.h"

#define DESKTOP_WIDTH 1920/2
#define DESKTOP_HEIGHT 1080/2

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_selNameListBox_clicked();
    void on_groupButton_clicked();

    void on_groupNumberBox_valueChanged(int arg1);
private:
    Ui::MainWindow *ui;
    QString fileName{};
    QString className{};
    QVector<Student> candidates{};

    QSharedPointer<ItemDelegate> m_delegate;                 //委托
    QSharedPointer<QSortFilterProxyModel> m_proxyModel;

    QSharedPointer<QStandardItemModel> m_model;
    int groupMateAmount{1};
    std::random_device rd;

private:
    void readCsv();
    void prepareData();
    void putCandinateToItem();
    void resizeEvent(QResizeEvent* event);
};
#endif // MAINWINDOW_H
