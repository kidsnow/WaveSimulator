#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    QMessageBox::information(this, "title", "HelloQT!");
}

void MainWindow::on_actionOpen_triggered()
{
    QMessageBox::information(this, "title", "Open!!");
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionHorizontally_triggered()
{

}

void MainWindow::on_actionVertically_triggered()
{

}
