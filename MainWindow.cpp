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
    mainLayout = new QGridLayout;
    m_wdg = new QWidget();

    createPatternBox();
    createButtonBox();
    createCanvas();

    mainLayout -> addWidget(patternBox, 0, 0);
    mainLayout -> addWidget(buttonBox, 1, 0);
    mainLayout -> addWidget(canvasBox, 2, 0);

    m_wdg -> setLayout(mainLayout);

    setCentralWidget(m_wdg);
}

void MainWindow::createButtonBox() {
    buttonBox = new QGroupBox(tr("Algorithm"));
    QHBoxLayout *layout = new QHBoxLayout;

    FCFSButton = new QPushButton(tr("FCFS"));
    SJFButton = new QPushButton(tr("SJF"));
    RRButton = new QPushButton(tr("RR"));
    MLButton = new QPushButton(tr("ML"));

    connect(FCFSButton, SIGNAL(clicked()), this, SLOT(FCFSClicked()));
    connect(SJFButton, SIGNAL(clicked()), this, SLOT(SJFClicked()));
    connect(RRButton, SIGNAL(clicked()), this, SLOT(RRClicked()));
    connect(MLButton, SIGNAL(clicked()), this, SLOT(MLClicked()));

    layout -> addWidget(FCFSButton);
    layout -> addWidget(SJFButton);
    layout -> addWidget(RRButton);
    layout -> addWidget(MLButton);

    buttonBox -> setLayout(layout);
}

void MainWindow::createCanvas() {
    canvasBox = new QGroupBox(tr("Visual representation"));
    QHBoxLayout *layout = new QHBoxLayout;
    canvas = new Canvas();

    layout -> addWidget(canvas);

    canvasBox -> setLayout(layout);
}

void MainWindow::createPatternBox() {
    patternBox = new QGroupBox(tr("Pattern"));
    QVBoxLayout *layout = new QVBoxLayout;

    QRadioButton *first = new QRadioButton(tr("First"));
    QRadioButton *second = new QRadioButton(tr("Second"));
    QRadioButton *third = new QRadioButton(tr("Third"));
    QRadioButton *fourth = new QRadioButton(tr("Custom"));

    layout -> addWidget(first);
    layout -> addWidget(second);
    layout -> addWidget(third);
    layout -> addWidget(fourth);

    patternBox -> setLayout(layout);
}

void MainWindow::FCFSClicked() {
    canvas -> changeAlgorithm("FCFS");
}

void MainWindow::SJFClicked() {
    canvas -> changeAlgorithm("SJF");
}

void MainWindow::RRClicked() {
    canvas -> changeAlgorithm("RR");
}

void MainWindow::MLClicked() {
    canvas -> changeAlgorithm("ML");
}
