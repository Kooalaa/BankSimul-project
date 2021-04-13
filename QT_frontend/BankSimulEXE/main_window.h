#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QDialog>

#include "nosta.h"
#include "saldo.h"
#include "selaa.h"
#include "talleta.h"

namespace Ui {
class Main_window;
}

class Main_window : public QDialog {
    Q_OBJECT

public:
    explicit Main_window(QWidget *parent = nullptr);
    ~Main_window();

private slots:

    void on_Selaa_tilitapahtumia_clicked();

    void on_Talleta_rahaa_clicked();

    void on_Nosta_rahaa_clicked();

    void on_Nayta_saldo_clicked();

    void on_Kirjaudu_ulos_clicked();

private:
    Ui::Main_window *ui;
    Nosta *pnosta;
    Selaa *pselaa;
    Saldo *psaldo;
    Talleta *ptalleta;
};

#endif  // MAIN_WINDOW_H
