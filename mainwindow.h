#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class GCodeOptimizerQt; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onButtonInputBrowseClicked();
    void onButtonOutputBrowseClicked();
    void onButtonOptimizeClicked();

private:
    Ui::GCodeOptimizerQt *ui;
};
