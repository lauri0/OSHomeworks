#include <QtGui>

#include "MainWindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setFixedSize(800, 600);
    setWindowTitle("Planning algorithms");
    initMainWindow();

}

MainWindow::~MainWindow()
{
    //Nothing here atm
}

void MainWindow::initMainWindow() {
    mainLayout = new QVBoxLayout();
    m_wdg = new QWidget();

    createButtonBox();
    createCanvas();

    mainLayout -> addWidget(buttonBox);
    mainLayout -> addWidget(canvas);
    m_wdg -> setLayout(mainLayout);

    setCentralWidget(m_wdg);
}

void MainWindow::createButtonBox() {
    buttonBox = new QGroupBox(tr("Algorithm"));
    QHBoxLayout *layout = new QHBoxLayout();

    FCFSButton = new QPushButton(tr("FCFS"));
    SJFButton = new QPushButton(tr("SJF"));
    RRButton = new QPushButton(tr("RR"));
    MLButton = new QPushButton(tr("ML"));

    layout -> addWidget(FCFSButton);
    layout -> addWidget(SJFButton);
    layout -> addWidget(RRButton);
    layout -> addWidget(MLButton);

    buttonBox -> setLayout(layout);
}

void MainWindow::createCanvas() {
    canvas = new Canvas();
}


