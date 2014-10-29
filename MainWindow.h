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
    void createButtonBox();
    void createCanvas();
    void createPatternBox();

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

    QMenu *fileMenu;
    QAction *exitAction;
};

#endif // MAINWINDOW_H
