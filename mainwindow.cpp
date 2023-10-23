#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./testDB.db");
    if(db.open()){
        qDebug("Open");

    }
    else
        qDebug("Not Open");

    query = new QSqlQuery(db);
    query->exec("CREATE TABLE Calls(Who INT, Whom INT, Time INT, Val INT);");

    model = new QSqlTableModel(this, db);
    model->setTable("Calls");

    QString headers[4] = {"Кто", "Кого", "Время", "Длительность"};
    for(int i = 0; i < model->columnCount();i++)
        model->setHeaderData(i, Qt::Horizontal, headers[i]);

    model->select();

    ui->tableView->setModel(model);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    model->insertRow(model->rowCount());
}

void MainWindow::on_pushButton_2_clicked()
{
    model->removeRow(row);
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    row = index.row();
}
