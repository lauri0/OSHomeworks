#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGroupBox>
#include <QLabel>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QHBoxLayout><
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

    void initMainWindow();
    void createButtonBox();
    void createCanvasBox();
    void createTextBox();

    QWidget *m_wdg;

    QHBoxLayout *mainLayout;

    QGroupBox *buttonBox;
    QGroupBox *canvasBox;
    QLabel *waitingTime;
    QPushButton *FCFSButton;
    QPushButton *SJFButton;
    QPushButton *RRButton;
    QPushButton *MLButton;

    QMenu *fileMenu;
    QAction *exitAction;
};

#endif // MAINWINDOW_H
