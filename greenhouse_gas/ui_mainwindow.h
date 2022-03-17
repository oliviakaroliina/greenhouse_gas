/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *apiLabel;
    QCheckBox *smearCheckBox;
    QCheckBox *statfiCheckBox;
    QLabel *smearStartLabel;
    QLabel *titleLabel;
    QLabel *smearEndLabel;
    QLabel *statfiStartLabel;
    QLabel *stationLabel;
    QCheckBox *hyytialaCheckBox;
    QCheckBox *kumpulaCheckBox;
    QCheckBox *varrioCheckBox;
    QLabel *datasetLabel;
    QCheckBox *inTonnesCheckBox;
    QCheckBox *indexedCheckBox;
    QCheckBox *intensityCheckBox;
    QCheckBox *intensityIndexedCheckBox;
    QLabel *gasLabel;
    QCheckBox *CO2CheckBox;
    QCheckBox *SO2CheckBox;
    QCheckBox *NOxCheckBox;
    QLabel *viewLabel;
    QRadioButton *rawRadioButton;
    QRadioButton *minimumRadioButton;
    QRadioButton *averageRadioButton;
    QRadioButton *maximumRadioButton;
    QCheckBox *emptyAllCheckBox;
    QCheckBox *saveSelectionsCheckBox;
    QPushButton *visualizePushButton;
    QCalendarWidget *smearEndCalendar;
    QCalendarWidget *smearStartCalendar;
    QCalendarWidget *statfiStartCalendar;
    QCalendarWidget *statfiEndCalendar;
    QLabel *statfiEndLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 620);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        apiLabel = new QLabel(centralwidget);
        apiLabel->setObjectName(QString::fromUtf8("apiLabel"));
        apiLabel->setGeometry(QRect(20, 50, 291, 20));
        smearCheckBox = new QCheckBox(centralwidget);
        smearCheckBox->setObjectName(QString::fromUtf8("smearCheckBox"));
        smearCheckBox->setGeometry(QRect(20, 80, 71, 26));
        statfiCheckBox = new QCheckBox(centralwidget);
        statfiCheckBox->setObjectName(QString::fromUtf8("statfiCheckBox"));
        statfiCheckBox->setGeometry(QRect(110, 80, 71, 26));
        smearStartLabel = new QLabel(centralwidget);
        smearStartLabel->setObjectName(QString::fromUtf8("smearStartLabel"));
        smearStartLabel->setGeometry(QRect(350, 50, 141, 20));
        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setGeometry(QRect(270, 10, 261, 31));
        QFont font;
        font.setPointSize(15);
        titleLabel->setFont(font);
        smearEndLabel = new QLabel(centralwidget);
        smearEndLabel->setObjectName(QString::fromUtf8("smearEndLabel"));
        smearEndLabel->setGeometry(QRect(570, 50, 121, 20));
        statfiStartLabel = new QLabel(centralwidget);
        statfiStartLabel->setObjectName(QString::fromUtf8("statfiStartLabel"));
        statfiStartLabel->setGeometry(QRect(350, 270, 121, 20));
        stationLabel = new QLabel(centralwidget);
        stationLabel->setObjectName(QString::fromUtf8("stationLabel"));
        stationLabel->setGeometry(QRect(20, 120, 181, 20));
        hyytialaCheckBox = new QCheckBox(centralwidget);
        hyytialaCheckBox->setObjectName(QString::fromUtf8("hyytialaCheckBox"));
        hyytialaCheckBox->setGeometry(QRect(20, 150, 91, 26));
        kumpulaCheckBox = new QCheckBox(centralwidget);
        kumpulaCheckBox->setObjectName(QString::fromUtf8("kumpulaCheckBox"));
        kumpulaCheckBox->setGeometry(QRect(110, 150, 91, 26));
        varrioCheckBox = new QCheckBox(centralwidget);
        varrioCheckBox->setObjectName(QString::fromUtf8("varrioCheckBox"));
        varrioCheckBox->setGeometry(QRect(210, 150, 91, 26));
        datasetLabel = new QLabel(centralwidget);
        datasetLabel->setObjectName(QString::fromUtf8("datasetLabel"));
        datasetLabel->setGeometry(QRect(20, 360, 121, 20));
        inTonnesCheckBox = new QCheckBox(centralwidget);
        inTonnesCheckBox->setObjectName(QString::fromUtf8("inTonnesCheckBox"));
        inTonnesCheckBox->setGeometry(QRect(20, 390, 131, 26));
        indexedCheckBox = new QCheckBox(centralwidget);
        indexedCheckBox->setObjectName(QString::fromUtf8("indexedCheckBox"));
        indexedCheckBox->setGeometry(QRect(20, 430, 111, 26));
        intensityCheckBox = new QCheckBox(centralwidget);
        intensityCheckBox->setObjectName(QString::fromUtf8("intensityCheckBox"));
        intensityCheckBox->setGeometry(QRect(150, 390, 111, 26));
        intensityIndexedCheckBox = new QCheckBox(centralwidget);
        intensityIndexedCheckBox->setObjectName(QString::fromUtf8("intensityIndexedCheckBox"));
        intensityIndexedCheckBox->setGeometry(QRect(150, 430, 171, 26));
        gasLabel = new QLabel(centralwidget);
        gasLabel->setObjectName(QString::fromUtf8("gasLabel"));
        gasLabel->setGeometry(QRect(20, 190, 221, 20));
        CO2CheckBox = new QCheckBox(centralwidget);
        CO2CheckBox->setObjectName(QString::fromUtf8("CO2CheckBox"));
        CO2CheckBox->setGeometry(QRect(20, 220, 51, 26));
        SO2CheckBox = new QCheckBox(centralwidget);
        SO2CheckBox->setObjectName(QString::fromUtf8("SO2CheckBox"));
        SO2CheckBox->setGeometry(QRect(110, 220, 51, 26));
        NOxCheckBox = new QCheckBox(centralwidget);
        NOxCheckBox->setObjectName(QString::fromUtf8("NOxCheckBox"));
        NOxCheckBox->setGeometry(QRect(210, 220, 51, 26));
        viewLabel = new QLabel(centralwidget);
        viewLabel->setObjectName(QString::fromUtf8("viewLabel"));
        viewLabel->setGeometry(QRect(20, 260, 201, 20));
        rawRadioButton = new QRadioButton(centralwidget);
        rawRadioButton->setObjectName(QString::fromUtf8("rawRadioButton"));
        rawRadioButton->setGeometry(QRect(20, 290, 61, 26));
        minimumRadioButton = new QRadioButton(centralwidget);
        minimumRadioButton->setObjectName(QString::fromUtf8("minimumRadioButton"));
        minimumRadioButton->setGeometry(QRect(150, 290, 81, 26));
        averageRadioButton = new QRadioButton(centralwidget);
        averageRadioButton->setObjectName(QString::fromUtf8("averageRadioButton"));
        averageRadioButton->setGeometry(QRect(20, 320, 71, 26));
        maximumRadioButton = new QRadioButton(centralwidget);
        maximumRadioButton->setObjectName(QString::fromUtf8("maximumRadioButton"));
        maximumRadioButton->setGeometry(QRect(150, 320, 91, 26));
        emptyAllCheckBox = new QCheckBox(centralwidget);
        emptyAllCheckBox->setObjectName(QString::fromUtf8("emptyAllCheckBox"));
        emptyAllCheckBox->setGeometry(QRect(310, 500, 151, 26));
        saveSelectionsCheckBox = new QCheckBox(centralwidget);
        saveSelectionsCheckBox->setObjectName(QString::fromUtf8("saveSelectionsCheckBox"));
        saveSelectionsCheckBox->setGeometry(QRect(490, 500, 121, 26));
        visualizePushButton = new QPushButton(centralwidget);
        visualizePushButton->setObjectName(QString::fromUtf8("visualizePushButton"));
        visualizePushButton->setGeometry(QRect(620, 490, 151, 41));
        visualizePushButton->setFont(font);
        smearEndCalendar = new QCalendarWidget(centralwidget);
        smearEndCalendar->setObjectName(QString::fromUtf8("smearEndCalendar"));
        smearEndCalendar->setGeometry(QRect(570, 70, 211, 191));
        smearEndCalendar->setFirstDayOfWeek(Qt::Monday);
        smearEndCalendar->setHorizontalHeaderFormat(QCalendarWidget::SingleLetterDayNames);
        smearEndCalendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
        smearStartCalendar = new QCalendarWidget(centralwidget);
        smearStartCalendar->setObjectName(QString::fromUtf8("smearStartCalendar"));
        smearStartCalendar->setGeometry(QRect(350, 70, 211, 191));
        smearStartCalendar->setFirstDayOfWeek(Qt::Monday);
        smearStartCalendar->setSelectionMode(QCalendarWidget::SingleSelection);
        smearStartCalendar->setHorizontalHeaderFormat(QCalendarWidget::SingleLetterDayNames);
        smearStartCalendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
        statfiStartCalendar = new QCalendarWidget(centralwidget);
        statfiStartCalendar->setObjectName(QString::fromUtf8("statfiStartCalendar"));
        statfiStartCalendar->setGeometry(QRect(350, 290, 211, 191));
        statfiStartCalendar->setFirstDayOfWeek(Qt::Monday);
        statfiStartCalendar->setSelectionMode(QCalendarWidget::SingleSelection);
        statfiStartCalendar->setHorizontalHeaderFormat(QCalendarWidget::SingleLetterDayNames);
        statfiStartCalendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
        statfiEndCalendar = new QCalendarWidget(centralwidget);
        statfiEndCalendar->setObjectName(QString::fromUtf8("statfiEndCalendar"));
        statfiEndCalendar->setGeometry(QRect(570, 290, 211, 191));
        statfiEndCalendar->setFirstDayOfWeek(Qt::Monday);
        statfiEndCalendar->setSelectionMode(QCalendarWidget::SingleSelection);
        statfiEndCalendar->setHorizontalHeaderFormat(QCalendarWidget::SingleLetterDayNames);
        statfiEndCalendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
        statfiEndLabel = new QLabel(centralwidget);
        statfiEndLabel->setObjectName(QString::fromUtf8("statfiEndLabel"));
        statfiEndLabel->setGeometry(QRect(570, 270, 121, 20));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        apiLabel->setText(QCoreApplication::translate("MainWindow", "Choose where you want to collect the data:", nullptr));
        smearCheckBox->setText(QCoreApplication::translate("MainWindow", "SMEAR", nullptr));
        statfiCheckBox->setText(QCoreApplication::translate("MainWindow", "STATFI", nullptr));
        smearStartLabel->setText(QCoreApplication::translate("MainWindow", "SMEAR start date: ", nullptr));
        titleLabel->setText(QCoreApplication::translate("MainWindow", "GREENHOUSE GAS DATA", nullptr));
        smearEndLabel->setText(QCoreApplication::translate("MainWindow", "SMEAR end date:", nullptr));
        statfiStartLabel->setText(QCoreApplication::translate("MainWindow", "STATFI start date:", nullptr));
        stationLabel->setText(QCoreApplication::translate("MainWindow", "Choose monitoring station:", nullptr));
        hyytialaCheckBox->setText(QCoreApplication::translate("MainWindow", "Hyyti\303\244l\303\244", nullptr));
        kumpulaCheckBox->setText(QCoreApplication::translate("MainWindow", "Kumpula", nullptr));
        varrioCheckBox->setText(QCoreApplication::translate("MainWindow", "V\303\244rri\303\266", nullptr));
        datasetLabel->setText(QCoreApplication::translate("MainWindow", "Choose datasets:", nullptr));
        inTonnesCheckBox->setText(QCoreApplication::translate("MainWindow", "CO2 (in tonnes)", nullptr));
        indexedCheckBox->setText(QCoreApplication::translate("MainWindow", "CO2 indexed", nullptr));
        intensityCheckBox->setText(QCoreApplication::translate("MainWindow", "CO2 intensity", nullptr));
        intensityIndexedCheckBox->setText(QCoreApplication::translate("MainWindow", "CO2 intensity indexed", nullptr));
        gasLabel->setText(QCoreApplication::translate("MainWindow", "Greenhouse gas you want to see:", nullptr));
        CO2CheckBox->setText(QCoreApplication::translate("MainWindow", "CO2", nullptr));
        SO2CheckBox->setText(QCoreApplication::translate("MainWindow", "SO2", nullptr));
        NOxCheckBox->setText(QCoreApplication::translate("MainWindow", "NOx", nullptr));
        viewLabel->setText(QCoreApplication::translate("MainWindow", "Choose how to view the data:", nullptr));
        rawRadioButton->setText(QCoreApplication::translate("MainWindow", "raw", nullptr));
        minimumRadioButton->setText(QCoreApplication::translate("MainWindow", "minimum", nullptr));
        averageRadioButton->setText(QCoreApplication::translate("MainWindow", "average", nullptr));
        maximumRadioButton->setText(QCoreApplication::translate("MainWindow", "maximum", nullptr));
        emptyAllCheckBox->setText(QCoreApplication::translate("MainWindow", "empty all selections", nullptr));
        saveSelectionsCheckBox->setText(QCoreApplication::translate("MainWindow", "save selections", nullptr));
        visualizePushButton->setText(QCoreApplication::translate("MainWindow", "VISUALIZE", nullptr));
        statfiEndLabel->setText(QCoreApplication::translate("MainWindow", "STATFI end date:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
