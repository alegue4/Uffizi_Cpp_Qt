#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../set.hpp"
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QtCharts>

using namespace QtCharts;

struct painting {
    QString scuola;
    QString autore;
    QString titolo;
    QString data;
    QString sala;

    painting() : scuola(""), autore(""), titolo(""), data(""), sala("") {}

    painting(QString sc, QString a, QString t, QString d, QString s)
        : scuola(sc), autore(a), titolo(t), data(d), sala(s) {}
};

struct equal_painting {
    bool operator()(const painting &p1, const painting &p2) const {
        return (p1.titolo.toLower() == p2.titolo.toLower());
    }
};

struct equal_double {
    bool operator()(double a, double b) const {
        return (a == b);
    }
};

struct equal_qstring {
    bool operator()(const QString &a, const QString &b) const {
        return (a == b);
    }
};

Set<painting, equal_painting> paintings;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    loadDataCsv("dipinti_uffizi.csv");

    connect(ui->autore_edit, &QLineEdit::textChanged, this, &MainWindow::checkAddLineEditValues);
    connect(ui->data_edit, &QLineEdit::textChanged, this, &MainWindow::checkAddLineEditValues);
    connect(ui->sala_edit, &QLineEdit::textChanged, this, &MainWindow::checkAddLineEditValues);
    connect(ui->titolo_edit, &QLineEdit::textChanged, this, &MainWindow::checkAddLineEditValues);
    connect(ui->scuola_edit, &QLineEdit::textChanged, this, &MainWindow::checkAddLineEditValues);

    this->setMinimumSize(1200, 700);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadDataCsv(const QString& nomeFile) {
    QFile file(nomeFile);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);

    QStringList header = in.readLine().split(','); // Leggi la prima riga (titoli delle colonne)
    ui->paintings_table->setColumnCount(header.size()); // Imposta il numero di colonne
    ui->paintings_table->setHorizontalHeaderLabels(header); // Imposta i titoli delle colonne

    int row = 0;

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = parseCSVLine(line);
        paintings.add(painting(fields[0], fields[1], fields[2], fields[3], fields[4]));
        ui->paintings_table->insertRow(row); // Inserisce una nuova riga nella tabella

        for (int col = 0; col < fields.size(); ++col) {
            QTableWidgetItem* item = new QTableWidgetItem(fields[col]);
            ui->paintings_table->setItem(row, col, item);
        }
        ++row;
    }

    for (int row = 0; row < ui->paintings_table->rowCount(); ++row) {
            for (int col = 0; col < ui->paintings_table->columnCount(); ++col) {
                QTableWidgetItem* item = ui->paintings_table->item(row, col);
                if (item)
                    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            }
        }

    ui->paintings_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    file.close();
}

QStringList MainWindow::parseCSVLine(const QString& line) {
    QStringList fields;

    QString current_field;
    bool inside_quotes = false;

    for (int i = 0; i < line.size(); ++i) {
        const QChar& current_char = line.at(i);

        if (current_char == '"') {
            inside_quotes = !inside_quotes;
            // Controlla se abbiamo incontrato un doppio apice, quindi scorre fino al prossimo doppio apice
            if (line.at(i + 1) == '"') {
                current_field += '"';
                ++i; // Salta il prossimo doppio apice
            }
        } else if (current_char == ',' && !inside_quotes) {
            // Se troviamo una virgola e non siamo all'interno di virgolette, il campo è completo
            fields.append(current_field);
            current_field.clear();
        } else {
            // Altrimenti aggiungi il carattere al campo corrente
            current_field += current_char;
        }
    }

    // Aggiungi l'ultimo campo alla lista
    fields.append(current_field);

    return fields;
}

void MainWindow::updateUI() {
    ui->scuola_edit->setText("");
    ui->autore_edit->setText("");
    ui->titolo_edit->setText("");
    ui->data_edit->setText("");
    ui->sala_edit->setText("");
    ui->titolo_edit2->setText("");
    ui->search_edit->setText("");

    ui->add_btn->setEnabled(false);
}

void MainWindow::checkAddLineEditValues() {
    bool allFilled = !ui->scuola_edit->text().isEmpty() &&
                     !ui->autore_edit->text().isEmpty() &&
                     !ui->titolo_edit->text().isEmpty() &&
                     !ui->data_edit->text().isEmpty() &&
                     !ui->sala_edit->text().isEmpty();

    ui->add_btn->setEnabled(allFilled);
}

void MainWindow::on_add_btn_clicked()
{
    // Ottieni i valori dai QLineEdit
    QString scuola = ui->scuola_edit->text();
    QString autore = ui->autore_edit->text();
    QString titolo = ui->titolo_edit->text();
    QString data = ui->data_edit->text();
    QString sala = ui->sala_edit->text();

    if(!paintings.contains(painting(scuola, autore, titolo, data, sala))) {
        // Inserisci una nuova riga nella QTableWidget
        int row = ui->paintings_table->rowCount();
        ui->paintings_table->insertRow(row);

        paintings.add(painting(scuola, autore, titolo, data, sala));

        // Inserisci i valori nelle colonne della nuova riga
        ui->paintings_table->setItem(row, 0, new QTableWidgetItem(scuola));
        ui->paintings_table->setItem(row, 1, new QTableWidgetItem(autore));
        ui->paintings_table->setItem(row, 2, new QTableWidgetItem(titolo));
        ui->paintings_table->setItem(row, 3, new QTableWidgetItem(data));
        ui->paintings_table->setItem(row, 4, new QTableWidgetItem(sala));
    }

    updateUI();
}


void MainWindow::on_remove_btn_clicked()
{
    QString title = ui->titolo_edit2->text().toLower(); // Ottieni il titolo dal QLineEdit in minuscolo
    for (int row = 0; row < ui->paintings_table->rowCount(); ++row) {
        QTableWidgetItem *titleItem = ui->paintings_table->item(row, 2); // L'indice 2 è la colonna del titolo
        if (titleItem && titleItem->text().toLower() == title) {
            for (set_size i = 0; i < paintings.get_size(); i++) {
                if(paintings[i].titolo.toLower() == title) {
                    paintings.remove(paintings[i]);
                    break;
                }
            }
            ui->paintings_table->removeRow(row); // Rimuovi la riga corrispondente al titolo
            break; // Esci dal ciclo una volta che hai rimosso il dipinto
        }
    }
    updateUI();
}




void MainWindow::on_search_btn_clicked()
{
    QString title = ui->search_edit->text().toLower(); // Ottieni il titolo dalla QLineEdit in minuscolo
    for (int row = 0; row < ui->paintings_table->rowCount(); ++row) {
        QTableWidgetItem *titleItem = ui->paintings_table->item(row, 2); // L'indice 2 è la colonna del titolo
        if (titleItem && titleItem->text().toLower() == title) {
            ui->paintings_table->selectRow(row); // Seleziona l'intera riga corrispondente al titolo
            ui->paintings_table->scrollToItem(titleItem); // Sposta la visualizzazione della tabella alla riga selezionata
            break; // Esci dal ciclo una volta trovato il dipinto
        }
    }
    updateUI();
}





void MainWindow::on_pie_graph_btn_clicked()
{
    int num_rows = ui->paintings_table->rowCount(); // Ottieni il numero di righe nella QTableWidget
    if (num_rows > 0) {
        QMap<QString, int> schoolCounts; // Mappa per tenere traccia del numero di dipinti per scuola

        // Ciclo per raccogliere i dati dalla QTableWidget
        for (int row = 0; row < num_rows; ++row) {
            QString school = ui->paintings_table->item(row, 0)->text(); // L'indice 0 contiene il nome della scuola
            // Se la scuola è già nella mappa, incrementa il contatore
            if (schoolCounts.contains(school)) {
                schoolCounts[school]++;
            } else { // Altrimenti, aggiungi la scuola alla mappa con il contatore a 1
                schoolCounts.insert(school, 1);
            }
        }

        // Creazione del grafico a torta
        QPieSeries *series = new QPieSeries();
        QMapIterator<QString, int> it(schoolCounts);

        while (it.hasNext()) {
            it.next();
            QString school = it.key();
            double count = it.value();

            double percentage = (count / num_rows) * 100; // Calcolo della percentuale

            series->append(school, percentage); // Aggiungi la fetta al grafico
        }

        // Creazione del grafico e configurazione
        QChart *chart = new QChart();
        chart->addSeries(series);

        series->setLabelsVisible(); // Per abilitare le etichette delle fette
        QPieSlice *slice;
        for (int i = 0; i < series->slices().size(); ++i) {
            slice = series->slices().at(i);
            slice->setLabel(QString("%1\n%2%").arg(slice->label()).arg(slice->percentage()*100, 0, 'f', 1));
        }

        chart->setTitle("Percentuale dipinti per scuola");
        QFont title_font;
        title_font.setPointSize(18); // Imposta la grandezza del testo a 18 punti
        chart->setTitleFont(title_font);

        // Abilita la legenda e la imposta a destra
        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignRight);

        // Creazione della vista del grafico e visualizzazione
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        // Creazione di una nuova finestra
        QWidget *chartWindow = new QWidget();
        chartWindow->setMinimumSize(1500, 800);
        QVBoxLayout *layout = new QVBoxLayout(chartWindow);
        layout->addWidget(chartView);

        // Mostra la nuova finestra
        chartWindow->show();
    }
}


void MainWindow::on_bar_graph_btn_clicked()
{
    int num_rows = ui->paintings_table->rowCount(); // Ottieni il numero di righe nella QTableWidget
    if (num_rows > 0) {
        QMap<QString, int> paintings_per_date; // Mappa per tenere traccia del numero di dipinti per data

        // Ciclo per raccogliere i dati dalla QTableWidget
        for (int row = 0; row < num_rows; ++row) {
            QString date = ui->paintings_table->item(row, 3)->text(); // L'indice 3 contiene il campo Data
            // Se la data è già nella mappa, incrementa il contatore
            if (paintings_per_date.contains(date)) {
                paintings_per_date[date]++;
            } else { // Altrimenti, aggiungi la data alla mappa con il contatore a 1
                paintings_per_date.insert(date, 1);
            }
        }

        // Creazione del grafico a barre
        QBarSet *bar_set = new QBarSet("Numero di dipinti");
        QStringList categories;

        QMapIterator<QString, int> it(paintings_per_date);
        while (it.hasNext()) {
            it.next();
            QString date = it.key();
            int count = it.value();

            *bar_set << count; // Aggiungi il conteggio al set delle barre
            categories << date; // Aggiungi la data come categoria
        }

        // Creazione della serie a barre e aggiunta del set
        QBarSeries *series = new QBarSeries();
        series->append(bar_set);

        // Creazione del grafico
        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Numero di dipinti per data");
        QFont title_font;
        title_font.setPointSize(18); // Imposta la grandezza del testo a 18 punti
        chart->setTitleFont(title_font);

        // Configurazione dell'asse X con le date
        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        axisX->append(categories); // Imposta le categorie sull'asse X
        axisX->setLabelsAngle(90);
        chart->addAxis(axisX, Qt::AlignBottom);

        // Configura l'asse Y con i valori numerici (conteggio dei dipinti)
        QValueAxis *axisY = new QValueAxis();
        chart->addAxis(axisY, Qt::AlignLeft); // Posiziona l'asse Y a sinistra
        series->attachAxis(axisY);

        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignRight);

        // Creazione della vista del grafico e visualizzazione in una nuova finestra
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        QWidget *chartWindow = new QWidget();
        chartWindow->setMinimumSize(1500, 800);
        QVBoxLayout *layout = new QVBoxLayout(chartWindow);
        layout->addWidget(chartView);

        chartWindow->show();
    }
}

