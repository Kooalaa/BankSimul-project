#include "graphical_transaction_view.h"

#include <QDebug>

#include "browse_transactions.h"
#include "main_window.h"
#include "ui_graphical_transaction_view.h"

graphical_transaction_view::graphical_transaction_view(ids_t ids,
                                                       browse_transactions *p_browse_trans,
                                                       QWidget *parent)
    : QDialog(parent), ui(new Ui::graphical_transaction_view) {
    ui->setupUi(this);
    this->p_browse = p_browse_trans;
    p_timer = new QTimer;
    connect(p_timer, &QTimer::timeout, this, [this] {
        time -= 1;
        if (time == 0)
            on_close_btn_clicked();
        else
            ui->timer_label->setNum(time);
    });

    this->ids = ids;
    p_rest_api = new dll_rest_api;
    connect(p_rest_api, &dll_rest_api::transactions_pages, this,
            &graphical_transaction_view::got_page_nums);
    connect(p_rest_api, qOverload<QVector<transaction_t>>(&dll_rest_api::info_ready), this,
            &graphical_transaction_view::got_transactions);
    p_rest_api->get_transaction_year(ids.account_id, QDate::currentDate().year());

    p_chart = new QChart;
    p_chart_view = new QChartView(p_chart);
    p_axis_x = new QBarCategoryAxis;
    p_axis_y = new QValueAxis;
    p_bar_series = new QBarSeries;
    ui->verticalLayout->insertWidget(0, p_chart_view);

    QStringList categories;
    categories << "Tammi"
               << "Helmi"
               << "Maalis"
               << "Huhti"
               << "Touko"
               << "Kesä"
               << "Heinä"
               << "Elo"
               << "Syys"
               << "Loka"
               << "Marras"
               << "Joulu";
    p_axis_x->append(categories);
    p_chart->addAxis(p_axis_x, Qt::AlignBottom);
    p_chart->addAxis(p_axis_y, Qt::AlignLeft);
}

graphical_transaction_view::~graphical_transaction_view() {
    delete ui;
    delete p_rest_api;
    delete p_chart;
    delete p_timer;
}

void graphical_transaction_view::data_ready() {
    QBarSet *p_bar_set = new QBarSet(QString().setNum(year));
    QVector<double> months(12);
    foreach (transaction_t transaction, data) {
        QDate date = QDate::fromString(transaction.date, Qt::ISODate);
        if (date.year() == year) {
            qDebug() << transaction.sum << ":" << transaction.date;
            months[date.month() - 1] += transaction.sum;
        }
    }
    foreach (double month, months) {
        qDebug() << month;
        *p_bar_set << month;
    }
    p_bar_series->clear();
    p_bar_series->append(p_bar_set);
    p_chart->removeSeries(p_bar_series);
    p_chart->addSeries(p_bar_series);

    double min = *std::min_element(months.constBegin(), months.constEnd());
    double max = *std::max_element(months.constBegin(), months.constEnd());
    qDebug() << min << max;
    p_axis_y->setRange(std::floor(max < -min ? min : -max), std::ceil(max < -min ? -min : max));
    p_bar_series->attachAxis(p_axis_x);
    p_bar_series->attachAxis(p_axis_y);

    this->show();
    ui->timer_label->setNum(time = 10);
    p_timer->start(1000);
    p_browse->close();
}

void graphical_transaction_view::got_page_nums(int pages) {
    this->pages = pages;
    page = 0;
    p_rest_api->get_transactions(ids.account_id, page++);
}

void graphical_transaction_view::got_transactions(QVector<transaction_t> transactions) {
    foreach (transaction_t transaction, transactions) {
        qDebug() << transaction.sum;
        data.append(transaction);
    }
    /*if (page <= pages - 1)
        p_rest_api->get_transactions(ids.account_id, page++);
    else*/
    data_ready();
}

void graphical_transaction_view::on_close_btn_clicked() {
    p_browse->show();
    this->close();
    this->~graphical_transaction_view();
}

void graphical_transaction_view::on_previous_year_btn_clicked() {
    year--;
    p_rest_api->get_transaction_year(ids.account_id, year);
    qDebug() << this->width() << "x" << this->height();
}

void graphical_transaction_view::on_next_year_btn_clicked() {
    year++;
    p_rest_api->get_transaction_year(ids.account_id, year);
}

/*
 *      QDate date = QDate::fromString(transaction.date, Qt::ISODate);
 *      qDebug() << date.toString(Qt::RFC2822Date);
 *      QRegExp reg_exp("([A-z]{3})");
 *      reg_exp.indexIn(date.toString(Qt::RFC2822Date));
 *      qDebug() << reg_exp.capturedTexts();
 */
