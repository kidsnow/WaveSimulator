#include "mainwindow.h"
#include "gridrenderer.h"
#include <QApplication>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;

    QGridLayout *mainLayout = window.findChild<QGridLayout*>("contentLayout");

    QPushButton *button1 = new QPushButton("One");
    QPushButton *button2 = new QPushButton("Two");

    QHBoxLayout *contentLayout = new QHBoxLayout;
    contentLayout->addWidget(button1);
    contentLayout->addWidget(button2);

    QVBoxLayout *rendererLayout = new QVBoxLayout();
    GridRenderer *renderer = new GridRenderer();
    rendererLayout->addWidget(renderer);

    mainLayout->addLayout(contentLayout, 0, 2);
    mainLayout->addLayout(rendererLayout, 0, 1);

    window.show();

    return app.exec();
}
