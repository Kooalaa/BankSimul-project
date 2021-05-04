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
    explicit graphical_transaction_view(ids_t ids, browse_transactions *p_browse_trans,
                                        QWidget *parent = nullptr);
    ~graphical_transaction_view();

private:
    Ui::graphical_transaction_view *ui;
    QChart *p_chart;
    QBarSeries *p_bar_series;
    dll_rest_api *p_rest_api;
    ids_t ids;
    int pages;
    int page;
    QVector<transaction_t> data;
    void data_ready();
    QTimer *p_timer;
    int time;
    Main_window *main_window;
    ids_t *p_ids;
    QChartView *p_chart_view;
    int year = QDate::currentDate().year();
    QBarCategoryAxis *p_axis_x;
    QValueAxis *p_axis_y;
    browse_transactions *p_browse;

private slots:
    void got_page_nums(int pages);
    void got_transactions(QVector<transaction_t> transactions);
    void on_close_btn_clicked();
    void on_previous_year_btn_clicked();
    void on_next_year_btn_clicked();
};

#endif  // GRAPHICAL_TRANSACTION_VIEW_H
