#include "mainwindow.h"
#include "./ui_mainwindow.h"
//#include <iostrem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget *mainWidget = new QWidget(this);
    QGridLayout *l = new QGridLayout(mainWidget);
    int n = 33;
    int k = 8;
    char symb[20] = "123+-456*/789";
    QStringList symbols = { "1", "2", "3", "log", "ln", "(", ")", "C", "4", "5", "6", "sin", "cos", "+", "-", "x", "7", "8", "9", "tan", "atan", "*", "/", "GR", "0", ".", "sqrt", "asin", "acos", "mod", "^", "=", "cred"};
    for (int i = 0; i < n; i++) {
        QPushButton *m_button = new QPushButton("My", this);
        m_button->setMinimumSize(QSize(50, 50));
        m_button->setMaximumSize(QSize(50, 50));
        m_button->setText(symbols[i]);
        if (i == n - 2) {
            m_button->setStyleSheet("QPushButton {font-size: 20px; background-color: rgb(151,222,183); color: White; border-radius: 600px;}");
        } else if (i == n - 2 - k) {
            m_button->setStyleSheet("QPushButton {font-size: 20px; background-color: rgb(251,122,183); color: White; border-radius: 600px;}");
        } else {
            m_button->setStyleSheet("QPushButton {font-size: 20px; background-color: rgb(151,122,183); color: White; border-radius: 600px;}");
        }
        if (i==n-1) {
            l->addWidget(m_button, 0, 7);
        } else {
            l->addWidget(m_button, i/k+2, i%k);
        }
        QObject::connect(m_button, SIGNAL(clicked()), this, SLOT(setbuttontext()));
    }
    //QLineEdit *res = new QLineEdit();
    l->addWidget(text_sector, 0, 0, 1, 5);
    l->addWidget(res, 1, 0, 1, -1);

    QLabel *xminn = new QLabel("x min");
    l->addWidget(xminn, n/k+4, 0, 1, -1);
    QLabel *xmaxx = new QLabel("x max");
    l->addWidget(xmaxx, n/k+4, 4, 1, -1);
    QLabel *yminn = new QLabel("y min");
    l->addWidget(yminn, n/k+5, 0, 1, -1);
    QLabel *ymaxx = new QLabel("y max");
    l->addWidget(ymaxx, n/k+5, 4, 1, -1);

    l->addWidget(xminn_edit, n/k+4, 1, 1, 3);
    //xminn_edit->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    //xminn_edit->setMinimumWidth(190);
    //xminn_edit->setMinimumHeight(10);
    l->addWidget(xmaxx_edit, n/k+4, 5, 1, 3);
    //xminn_edit->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    //xminn_edit->setMinimumWidth(190);
    //xminn_edit->setMinimumHeight(10);
    l->addWidget(yminn_edit, n/k+5, 1, 1, 3);
    //xminn_edit->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    //xminn_edit->setMinimumWidth(190);
    //xminn_edit->setMinimumHeight(10);
    l->addWidget(ymaxx_edit, n/k+5, 5, 1, 3);
    //xminn_edit->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    //xminn_edit->setMinimumWidth(190);
    //xminn_edit->setMinimumHeight(10);

    QWidget *wid = new QWidget(this);
    QWidget *credit_widget = new QWidget();
    QGridLayout *credit = new QGridLayout(credit_widget);

    QLabel *sum = new QLabel("credit amount");
    QLabel *term = new QLabel("term");
    QLabel *procent = new QLabel("interest rate");
    QLabel *pay_for_month = new QLabel("monthly payments");
    QLabel *overpayment = new QLabel("overpayment");
    QLabel *total_payout = new QLabel("total payout");

    credit->addWidget(sum, 0, 0);
    credit->addWidget(term, 1, 0);
    credit->addWidget(procent, 2, 0);
    credit->addWidget(sum_edit, 0, 1);
    credit->addWidget(term_edit, 1, 1);
    credit->addWidget(procent_edit, 2, 1);
    credit->addWidget(pay_for_month, 4, 0);
    credit->addWidget(overpayment, 6, 0);
    credit->addWidget(total_payout, 5, 0);
    QPushButton *res_credit = new QPushButton("result");
    credit->addWidget(res_credit, 3, 0);
    credit->addWidget(res_c, 4, 1);
    credit->addWidget(res_o, 6, 1);
    credit->addWidget(res_p, 5, 1);
    QObject::connect(res_credit, SIGNAL(clicked()), this, SLOT(calc_credit()));

    stackk->addWidget(plot);
    stackk->addWidget(credit_widget);
    QHBoxLayout *hlayout = new QHBoxLayout(wid);
    hlayout->addWidget(mainWidget);
    hlayout->addWidget(stackk_widget);
    setCentralWidget(wid);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setbuttontext()
{
    QPushButton *button = (QPushButton *)sender();
    QString str = button->text();
    char input[256] = "";
    double output;
    int err = 0;
    QString text = res->text();
    if (str == "C") {
        res->setText("");
    } else if (str == "GR") {
        stackk->setCurrentIndex(0);
        QByteArray ba = text.toLocal8Bit();
        const char *c_str2 = ba.data();
        printf("str2: %s\n", c_str2);
        for (int y=0;y<strlen(c_str2);y++) {
            input[y] = c_str2[y];
        }
        QString xminn_text = xminn_edit->text();
        double xminn_number = xminn_text.toDouble();
        QString xmaxx_text = xmaxx_edit->text();
        double xmaxx_number = xmaxx_text.toDouble();
        QString yminn_text = yminn_edit->text();
        double yminn_number = yminn_text.toDouble();
        QString ymaxx_text = ymaxx_edit->text();
        double ymaxx_number = ymaxx_text.toDouble();
        printf("%f %f %f %f", xminn_number, xmaxx_number, yminn_number, ymaxx_number);
        if (xminn_text == "" || xmaxx_text == "" || yminn_text == "" || ymaxx_text == "") {
            text_sector->setText("Please, input correct number");
        } else {
            int NN = 100;
            QVector<double> xx(NN), yy(NN);
            double a = xminn_number;
            double b = xmaxx_number;
            double h = (b-a)/NN;
            for (int i = 0; i < NN; i++) {
                xx[i] = a+h*i;
                err = main_func(input, &yy[i], xx[i]);
            }
            plot->clearGraphs();
            plot->addGraph();
            plot->graph(0)->setData(xx, yy);
            plot->xAxis->setRange(a-1, b+1);
            plot->yAxis->setRange(yminn_number-1, ymaxx_number+1);
            plot->replot();
        }

    } else if (str == "=") {
        QByteArray ba = text.toLocal8Bit();
        const char *c_str2 = ba.data();
        printf("str2: %s\n", c_str2);
        for (int y=0;y<strlen(c_str2);y++) {
            input[y] = c_str2[y];
        }
        double xx = 0;
        text_sector->setText(c_str2);
        if (flag_x == 1) {
            QString xx_text = res->text();
            xx = xx_text.toDouble();
            for (int j = 0; j < save_input_len; j++) {
                input[j] = save_input[j];
            }
            flag_x = 0;
        }
        if (isx(input)) {
            flag_x = 1;
            for (int i =0 ;i< strlen(c_str2); i++) {
                save_input[i] = c_str2[i];
            }
            save_input_len = strlen(c_str2);
        } else {
            save_input_len = 0;
            flag_x = 0;
        }
        err = main_func(input, &output, xx);
        if (err) {
            text_sector->setText("Please, enter the correct expression");
        } else {
             QString valueAsString = QString::number(output, 'g', 7);
            printf("error = %d\n", err);
            printf("%f\n", output);
            res->setText(valueAsString);
        }
    } else if (str == "cred") {
        printf("ff");
        stackk->setCurrentIndex(1);
    } else {
        res->setText(text+str);
    }
}

void MainWindow::calc_credit()
{
    QString sum_text = sum_edit->text();
    double sum_number = sum_text.toDouble();
    QString term_text = term_edit->text();
    double term_number = term_text.toDouble();
    QString procent_text = procent_edit->text();
    double procent_number = procent_text.toDouble();
    printf("%f %f %f", sum_number, term_number, procent_number);
    if (sum_text == "" || term_text == "" || procent_text == "") {
        text_sector->setText("Please, input correct numbers");
    } else {
        double over = 0;
        double pay;
        double res_credit = s21_calc_credit(sum_number, term_number, procent_number, &over, &pay);
        QString valueAsString = QString::number(res_credit, 'g', 7);
        QString valueAsString2 = QString::number(over, 'g', 7);
        QString valueAsString3 = QString::number(pay, 'g', 7);
        res_c->setText(valueAsString);
        res_o->setText(valueAsString2);
        res_p->setText(valueAsString3);
    }


}


