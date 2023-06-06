#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#ifdef __cplusplus
extern"C"
{
#endif

#include "backcalc.h"

#ifdef __cplusplus
}
#endif
#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QtCore>
#include <QLabel>
#include <QLineEdit>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QLineEdit *res = new QLineEdit();
    QLabel *text_sector = new QLabel();
    QCustomPlot *plot = new QCustomPlot();
    QLineEdit *xminn_edit = new QLineEdit();
    QLineEdit *xmaxx_edit = new QLineEdit();
    QLineEdit *yminn_edit = new QLineEdit();
    QLineEdit *ymaxx_edit = new QLineEdit();
    QWidget *stackk_widget = new QWidget();
    QStackedLayout *stackk = new QStackedLayout(stackk_widget);
    QLineEdit *sum_edit = new QLineEdit();
    QLineEdit *term_edit = new QLineEdit();
    QLineEdit *procent_edit = new QLineEdit();
    QLabel *res_c = new QLabel();
    QLabel *res_o = new QLabel();
    QLabel *res_p = new QLabel();
    char save_input[256];
    int flag_x = 0;
    int save_input_len = 0;
private:
    Ui::MainWindow *ui;

private slots:
    void setbuttontext();
    void calc_credit();
};
#endif // MAINWINDOW_H
