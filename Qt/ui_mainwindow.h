/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *leftlayout;
    QHBoxLayout *paintings_layout;
    QTableWidget *paintings_table;
    QVBoxLayout *add_layout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *scuola_edit;
    QLineEdit *autore_edit;
    QLineEdit *titolo_edit;
    QLineEdit *data_edit;
    QLineEdit *sala_edit;
    QPushButton *add_btn;
    QHBoxLayout *remove_layout;
    QLineEdit *titolo_edit2;
    QPushButton *remove_btn;
    QHBoxLayout *search_layout;
    QLineEdit *search_edit;
    QPushButton *search_btn;
    QHBoxLayout *graph_layout;
    QPushButton *pie_graph_btn;
    QPushButton *bar_graph_btn;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(938, 618);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        leftlayout = new QVBoxLayout();
        leftlayout->setObjectName(QString::fromUtf8("leftlayout"));
        paintings_layout = new QHBoxLayout();
        paintings_layout->setObjectName(QString::fromUtf8("paintings_layout"));
        paintings_table = new QTableWidget(centralwidget);
        if (paintings_table->columnCount() < 5)
            paintings_table->setColumnCount(5);
        paintings_table->setObjectName(QString::fromUtf8("paintings_table"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(paintings_table->sizePolicy().hasHeightForWidth());
        paintings_table->setSizePolicy(sizePolicy1);
        paintings_table->setMinimumSize(QSize(700, 0));
        paintings_table->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        paintings_table->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        paintings_table->setRowCount(0);
        paintings_table->setColumnCount(5);

        paintings_layout->addWidget(paintings_table);


        leftlayout->addLayout(paintings_layout);

        add_layout = new QVBoxLayout();
        add_layout->setObjectName(QString::fromUtf8("add_layout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        scuola_edit = new QLineEdit(centralwidget);
        scuola_edit->setObjectName(QString::fromUtf8("scuola_edit"));
        scuola_edit->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(scuola_edit);

        autore_edit = new QLineEdit(centralwidget);
        autore_edit->setObjectName(QString::fromUtf8("autore_edit"));
        autore_edit->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(autore_edit);

        titolo_edit = new QLineEdit(centralwidget);
        titolo_edit->setObjectName(QString::fromUtf8("titolo_edit"));
        titolo_edit->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(titolo_edit);

        data_edit = new QLineEdit(centralwidget);
        data_edit->setObjectName(QString::fromUtf8("data_edit"));
        data_edit->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(data_edit);

        sala_edit = new QLineEdit(centralwidget);
        sala_edit->setObjectName(QString::fromUtf8("sala_edit"));
        sala_edit->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(sala_edit);


        add_layout->addLayout(horizontalLayout);

        add_btn = new QPushButton(centralwidget);
        add_btn->setObjectName(QString::fromUtf8("add_btn"));
        add_btn->setEnabled(false);
        add_btn->setMinimumSize(QSize(200, 0));

        add_layout->addWidget(add_btn);


        leftlayout->addLayout(add_layout);

        remove_layout = new QHBoxLayout();
        remove_layout->setObjectName(QString::fromUtf8("remove_layout"));
        titolo_edit2 = new QLineEdit(centralwidget);
        titolo_edit2->setObjectName(QString::fromUtf8("titolo_edit2"));
        titolo_edit2->setContextMenuPolicy(Qt::NoContextMenu);
        titolo_edit2->setAlignment(Qt::AlignCenter);

        remove_layout->addWidget(titolo_edit2);

        remove_btn = new QPushButton(centralwidget);
        remove_btn->setObjectName(QString::fromUtf8("remove_btn"));
        remove_btn->setEnabled(true);
        remove_btn->setMinimumSize(QSize(200, 0));

        remove_layout->addWidget(remove_btn);


        leftlayout->addLayout(remove_layout);

        search_layout = new QHBoxLayout();
        search_layout->setObjectName(QString::fromUtf8("search_layout"));
        search_edit = new QLineEdit(centralwidget);
        search_edit->setObjectName(QString::fromUtf8("search_edit"));
        search_edit->setMinimumSize(QSize(300, 0));
        search_edit->setFocusPolicy(Qt::ClickFocus);
        search_edit->setEchoMode(QLineEdit::Normal);
        search_edit->setAlignment(Qt::AlignCenter);
        search_edit->setReadOnly(false);
        search_edit->setClearButtonEnabled(false);

        search_layout->addWidget(search_edit);

        search_btn = new QPushButton(centralwidget);
        search_btn->setObjectName(QString::fromUtf8("search_btn"));
        search_btn->setMinimumSize(QSize(200, 0));

        search_layout->addWidget(search_btn);


        leftlayout->addLayout(search_layout);

        graph_layout = new QHBoxLayout();
        graph_layout->setObjectName(QString::fromUtf8("graph_layout"));
        pie_graph_btn = new QPushButton(centralwidget);
        pie_graph_btn->setObjectName(QString::fromUtf8("pie_graph_btn"));

        graph_layout->addWidget(pie_graph_btn);

        bar_graph_btn = new QPushButton(centralwidget);
        bar_graph_btn->setObjectName(QString::fromUtf8("bar_graph_btn"));

        graph_layout->addWidget(bar_graph_btn);


        leftlayout->addLayout(graph_layout);


        horizontalLayout_2->addLayout(leftlayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 938, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        scuola_edit->setPlaceholderText(QApplication::translate("MainWindow", "Inserisci nome Scuola...", nullptr));
        autore_edit->setPlaceholderText(QApplication::translate("MainWindow", "Inserisci nome Autore...", nullptr));
        titolo_edit->setPlaceholderText(QApplication::translate("MainWindow", "Inserisci Titolo dipinto...", nullptr));
        data_edit->setPlaceholderText(QApplication::translate("MainWindow", "Inserisci data...", nullptr));
        sala_edit->setText(QString());
        sala_edit->setPlaceholderText(QApplication::translate("MainWindow", "Inserisci nome sala...", nullptr));
        add_btn->setText(QApplication::translate("MainWindow", "Aggiungi", nullptr));
        titolo_edit2->setPlaceholderText(QApplication::translate("MainWindow", "Inserisci Titolo dipinto da eliminare...", nullptr));
        remove_btn->setText(QApplication::translate("MainWindow", "Rimuovi", nullptr));
        search_edit->setInputMask(QString());
        search_edit->setText(QString());
        search_edit->setPlaceholderText(QApplication::translate("MainWindow", "Inserisci Soggetto/Titolo da cercare...", nullptr));
        search_btn->setText(QApplication::translate("MainWindow", "Cerca", nullptr));
        pie_graph_btn->setText(QApplication::translate("MainWindow", "Genera grafico a torta", nullptr));
        bar_graph_btn->setText(QApplication::translate("MainWindow", "Genera grafico a barre", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
