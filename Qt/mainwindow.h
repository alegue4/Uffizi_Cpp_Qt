#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void loadDataCsv(const QString& nomeFile);
    QStringList parseCSVLine(const QString& line);

    void on_add_btn_clicked();

    void on_remove_btn_clicked();

    void on_search_btn_clicked();

    void on_pie_graph_btn_clicked();

    void on_bar_graph_btn_clicked();

private:
    Ui::MainWindow *ui;
    void updateUI();
    void checkAddLineEditValues();
};
#endif // MAINWINDOW_H
