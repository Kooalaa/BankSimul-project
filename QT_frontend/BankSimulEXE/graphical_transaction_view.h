#ifndef GRAPHICAL_TRANSACTION_VIEW_H
#define GRAPHICAL_TRANSACTION_VIEW_H

#include <dll_rest_api.h>

#include <QDialog>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <algorithm>
#include <cmath>

using namespace QtCharts;

class browse_transactions;

namespace Ui {
class graphical_transaction_view;
}

class Main_window;

class graphical_transaction_view : public QDialog {
    Q_OBJECT

public:
    explicit graphical_transaction_view(ids_t ids, Main_window *p_main_window,
                                        browse_transactions *browse_trans,
                                        QWidget *parent = nullptr);
    ~graphical_transaction_view();

private:
    // Pointers
    Ui::graphical_transaction_view *ui;
    QChart *p_chart;
    QBarSeries *p_bar_series;
    QBarCategoryAxis *p_axis_x;
    QValueAxis *p_axis_y;
    QChartView *p_chart_view;
    dll_rest_api *p_rest_api;
    Main_window *p_main_window;
    browse_transactions *p_browse;
    QTimer *p_timer;

    // Variables
    ids_t ids;
    QVector<transaction_t> data;
    int time;
    int year = QDate::currentDate().year();

    // Funktio
    void data_ready();

private slots:
    void got_transactions(QVector<transaction_t> transactions);
    void on_close_btn_clicked();
    void on_previous_year_btn_clicked();
    void on_next_year_btn_clicked();
    void on_transactions_btn_clicked();
};

#endif  // GRAPHICAL_TRANSACTION_VIEW_H
