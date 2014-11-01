#include <QtGui>

#include "MainWindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setFixedSize(800, 600);
    setWindowTitle("Planning algorithms");
    initAlgorithmHandler();
    initMainWindow();

}

MainWindow::~MainWindow()
{
    //Nothing here atm
}

void MainWindow::initAlgorithmHandler()
{
    handler = new AlgorithmHandler;
}

void MainWindow::initMainWindow()
{
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

void MainWindow::createButtonBox()
{
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

void MainWindow::createCanvas()
{
    canvasBox = new QGroupBox(tr("Visual representation"));
    QHBoxLayout *layout = new QHBoxLayout;
    canvas = new Canvas(handler);

    layout -> addWidget(canvas);

    canvasBox -> setLayout(layout);
}

void MainWindow::createPatternBox()
{
    patternBox = new QGroupBox(tr("Pattern"));
    QGridLayout *layout = new QGridLayout;

    first = new QRadioButton(tr("First"));
    first -> setChecked(true);
    second = new QRadioButton(tr("Second"));
    third = new QRadioButton(tr("Third"));
    fourth = new QRadioButton(tr("Custom"));

    connect(first, SIGNAL(toggled(bool)), this, SLOT(firstEnabled(bool)));
    connect(second, SIGNAL(toggled(bool)), this, SLOT(secondEnabled(bool)));
    connect(third, SIGNAL(toggled(bool)), this, SLOT(thirdEnabled(bool)));
    connect(fourth, SIGNAL(toggled(bool)), this, SLOT(customEnabled(bool)));

    firstLabel = new QLabel(handler -> getTask1());
    secondLabel = new QLabel(handler -> getTask2());
    thirdLabel = new QLabel(handler -> getTask3());

    customTextField = new QLineEdit(this);
    customTextField -> setMaxLength(18);

    connect(customTextField, SIGNAL(textChanged(QString)), this, SLOT(customPatternChanged(QString)));

    layout -> addWidget(first, 0, 0);
    layout -> addWidget(firstLabel, 0, 1);
    layout -> addWidget(second, 1, 0);
    layout -> addWidget(secondLabel, 1, 1);
    layout -> addWidget(third, 2, 0);
    layout -> addWidget(thirdLabel, 2, 1);
    layout -> addWidget(fourth, 3, 0);
    layout -> addWidget(customTextField, 3, 1);

    patternBox -> setLayout(layout);
}

void MainWindow::FCFSClicked()
{
    canvas -> changeAlgorithm("FCFS");
    handler -> setCurrentAlgorithm("FCFS");
    canvas -> changeAverageWaitingTime();
    canvas -> update();
}

void MainWindow::SJFClicked()
{
    canvas -> changeAlgorithm("SJF");
    handler -> setCurrentAlgorithm("SJF");
    canvas -> changeAverageWaitingTime();
    canvas -> update();
}

void MainWindow::RRClicked()
{
    canvas -> changeAlgorithm("RR");
    handler -> setCurrentAlgorithm("RR");
    canvas -> changeAverageWaitingTime();
    canvas -> update();
}

void MainWindow::MLClicked()
{
    canvas -> changeAlgorithm("ML");
}

void MainWindow::firstEnabled(bool enabled)
{
    if (enabled == true)
    {
       handler -> setTaskVector(handler -> getTask1().toStdString());
    }
}

void MainWindow::secondEnabled(bool enabled)
{
    if (enabled == true)
    {
       handler -> setTaskVector(handler -> getTask2().toStdString());
    }
}

void MainWindow::thirdEnabled(bool enabled)
{
    if (enabled == true)
    {
       handler -> setTaskVector(handler -> getTask3().toStdString());
    }
}

void MainWindow::customEnabled(bool enabled)
{
    if (enabled == true)
    {
       handler -> setTaskVector(customTextField -> text().toStdString());
    }
}

void MainWindow::customPatternChanged(QString qStr)
{
    if (fourth -> isChecked() == true)
    {
        string str = qStr.toStdString();
        handler -> setTaskVector(str);
    }
}
