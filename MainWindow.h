#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QDialog>
#include <QGroupBox>
#include <QLabel>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QLineEdit>
#include <QMenu>
#include <QAction>
#include <QMenuBar>

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
    void createMenus();
    void createMenuActions();

    AlgorithmHandler *handler;

    QWidget *m_wdg;

    QGridLayout *mainLayout;

    QMenu *fileMenu;
    QMenu *optionsMenu;

    QAction *exitAction;
    QAction *compactView;
    QAction *normalView;

    QGroupBox *buttonBox;
    QGroupBox *canvasBox;
    QGroupBox *patternBox;

    QLabel *waitingTime;
    QPushButton *FCFSButton;
    QPushButton *SJFButton;
    QPushButton *RRButton;
    QPushButton *MLButton;

    QRadioButton *first;
    QRadioButton *second;
    QRadioButton *third;
    QRadioButton *fourth;

    Canvas *canvas;

    QLabel *firstLabel;
    QLabel *secondLabel;
    QLabel *thirdLabel;
    QLabel *fourthLabel;

    QLineEdit *customTextField;

public slots:
    void FCFSClicked();
    void SJFClicked();
    void RRClicked();
    void MLClicked();

    void firstEnabled(bool enabled);
    void secondEnabled(bool enabled);
    void thirdEnabled(bool enabled);
    void customEnabled(bool enabled);

    void exitApp();
    void setNormalView();
    void setCompactView();

    void customPatternChanged(QString qStr);

};

#endif // MAINWINDOW_H
