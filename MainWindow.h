#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGroupBox>
#include <QLabel>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QRadioButton>

#include "Canvas.h"
#include "AlgorithmHandler.h"

/*namespace Ui {
class MainWindow;
}*/

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void initMainWindow();
    void initAlgorithmHandler();

    void createButtonBox();
    void createCanvas();
    void createPatternBox();

    AlgorithmHandler *handler;

    QWidget *m_wdg;

    QGridLayout *mainLayout;

    QGroupBox *buttonBox;
    QGroupBox *canvasBox;
    QGroupBox *patternBox;

    QLabel *waitingTime;
    QPushButton *FCFSButton;
    QPushButton *SJFButton;
    QPushButton *RRButton;
    QPushButton *MLButton;
    Canvas *canvas;

    QLabel *firstLabel;
    QLabel *secondLabel;
    QLabel *thirdLabel;
    QLabel *fourthLabel;

    QMenu *fileMenu;
    QAction *exitAction;

public slots:
    void FCFSClicked();
    void SJFClicked();
    void RRClicked();
    void MLClicked();

    void firstEnabled(bool enabled);
    void secondEnabled(bool enabled);
    void thirdEnabled(bool enabled);
    void customEnabled(bool enabled);

};

#endif // MAINWINDOW_H
