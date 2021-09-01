#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clog.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QIcon>
#include <iostream>
#include <random>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setWindowIcon(QIcon(QStringLiteral("./logo.png")));
    ui->setupUi(this);
    m_delegate = QSharedPointer<ItemDelegate>(new ItemDelegate(this));
    ui->candidateView->setItemDelegate(m_delegate.get());       //为视图设置委托
    ui->candidateView->setSpacing(15);                   //为视图设置控件间距
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readCsv(){
    QFile inFile(fileName);
    QStringList lines;/*行数据*/

    if (inFile.open(QIODevice::ReadOnly))
    {
        QTextStream stream_text(&inFile);
        while (!stream_text.atEnd())
        {
            lines.push_back(stream_text.readLine());
        }
        candidates.clear();
        for (int j = 0; j < lines.size(); j++)
        {
            QString line = lines.at(j);
            QStringList split = line.split(",");/*列数据*/
            if(j == 0){ // 第一行是班级名称
                className = split.at(0);
                continue;
            }
            if(j == 1){continue;} // 第二行是列名
            if(split.size() >= 5){
                QString englishName{split.at(3)};
                englishName.remove(QChar('"')).remove(QChar(' '));
                candidates.append(Student{split.at(0), englishName, split.at(2)});
            }
        }
        inFile.close();
    }
}
void MainWindow::on_selNameListBox_clicked()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "~/", tr("Comma-Seperated Values(*.csv)"));
    if(fileName.isEmpty()){
        QMessageBox::warning(this, "Warning", "Invalid file path!");
        return;
    }
    readCsv();
    prepareData();
}

void MainWindow::putCandinateToItem(){
    if(m_model == nullptr){
        CLOG_ERROR("m_model is nullptr!");
        return;
    }
    m_model->clear();
    for (int i = 0; i < candidates.size(); ++i) {
        QStandardItem *Item = new QStandardItem;
        Item->setData(candidates.at(i).groupBelongsTo, Qt::UserRole);  // 设置默认组0
        Item->setData(QVariant::fromValue(candidates.at(i)), Qt::UserRole+1);//整体存取
        m_model->appendRow(Item);      //追加Item
    }
}

void MainWindow::prepareData(){
    m_model = QSharedPointer<QStandardItemModel>(new QStandardItemModel());

    putCandinateToItem();

    // TODO: this should not be here.
    m_proxyModel = QSharedPointer<QSortFilterProxyModel>(new QSortFilterProxyModel(ui->candidateView));
    m_proxyModel->setSourceModel(m_model.get());
    m_proxyModel->setFilterRole(Qt::UserRole);
    m_proxyModel->setDynamicSortFilter(true);
    ui->candidateView->setModel(m_proxyModel.get());                  //为委托设置模型
    ui->candidateView->setViewMode(QListView::IconMode); //设置Item图标显示
    ui->candidateView->setDragEnabled(false);            //控件不允许拖动
}

void MainWindow::on_groupButton_clicked()
{
    int groupNumber = candidates.size() / groupMateAmount;
    if(groupNumber <= 0 or groupNumber > 15){
        int atLeast = candidates.size() / 15;
        int atMost = candidates.size() / 1;
        QString warn = QString("Unsupported person per group: %1. Please set it to %2~%3.").arg(groupMateAmount).arg(atLeast).arg(atMost);
        QMessageBox::warning(this, "Warning", warn);
        return;
    }
    std::mt19937 g(rd());
    std::shuffle(candidates.begin(), candidates.end(), g);
    int groupNow = 1;
    int fraction = candidates.size() - groupMateAmount * groupNumber;
    int groupAssigned = 0;
    for(auto iter = candidates.begin();iter < candidates.end();++iter){
        iter->groupBelongsTo = groupNow;
        groupAssigned += 1;
        if((groupAssigned == groupMateAmount and groupNow < (groupNumber - fraction)) or (groupAssigned == groupMateAmount + 1)){
            groupNow += 1;
            groupAssigned = 0;
        }
    }

    putCandinateToItem();

}


void MainWindow::on_groupNumberBox_valueChanged(int arg1)
{
    groupMateAmount = arg1;
    CLOG_INFO("groupNumber changed to %d", arg1);
}

void MainWindow::resizeEvent(QResizeEvent *event){
    putCandinateToItem();
}

