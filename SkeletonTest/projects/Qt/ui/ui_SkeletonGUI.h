/********************************************************************************
** Form generated from reading UI file 'SkeletonGUI.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SKELETONGUI_H
#define UI_SKELETONGUI_H

#include <BM_ZoomMeshGraphicsView.h>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SS_GUI
{
public:
    QGridLayout *gridLayout;
    QSplitter *splitter;
    BLOCKMOD::ZoomMeshGraphicsView *graphicsViewSkeleton;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEditXValue;
    QLineEdit *lineEditYValue;
    QTableWidget *tableWidget;
    QPushButton *pushButtonAddLine;
    QPushButton *pushButtonDeleteLastLine;
    QPlainTextEdit *plainTextEditLog;
    QCheckBox *checkBoxDirection;
    QPushButton *pushButtonClearAll;
    QPushButton *Clear;
    QPushButton *pushButtonCalc;

    void setupUi(QWidget *SS_GUI)
    {
        if (SS_GUI->objectName().isEmpty())
            SS_GUI->setObjectName(QStringLiteral("SS_GUI"));
        SS_GUI->resize(761, 532);
        gridLayout = new QGridLayout(SS_GUI);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        splitter = new QSplitter(SS_GUI);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        graphicsViewSkeleton = new BLOCKMOD::ZoomMeshGraphicsView(splitter);
        graphicsViewSkeleton->setObjectName(QStringLiteral("graphicsViewSkeleton"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(5);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(graphicsViewSkeleton->sizePolicy().hasHeightForWidth());
        graphicsViewSkeleton->setSizePolicy(sizePolicy);
        splitter->addWidget(graphicsViewSkeleton);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lineEditXValue = new QLineEdit(layoutWidget);
        lineEditXValue->setObjectName(QStringLiteral("lineEditXValue"));

        verticalLayout->addWidget(lineEditXValue);

        lineEditYValue = new QLineEdit(layoutWidget);
        lineEditYValue->setObjectName(QStringLiteral("lineEditYValue"));

        verticalLayout->addWidget(lineEditYValue);

        tableWidget = new QTableWidget(layoutWidget);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (tableWidget->rowCount() < 33)
            tableWidget->setRowCount(33);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(5, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(6, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(7, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(8, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(9, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(10, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(11, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(12, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(13, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(14, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(15, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(16, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(17, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(18, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(19, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(20, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(21, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(22, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(23, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(24, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(25, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(26, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(27, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(28, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(29, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(30, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(31, __qtablewidgetitem33);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(32, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        tableWidget->setItem(0, 0, __qtablewidgetitem35);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        tableWidget->setItem(0, 1, __qtablewidgetitem36);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        tableWidget->setItem(1, 0, __qtablewidgetitem37);
        QTableWidgetItem *__qtablewidgetitem38 = new QTableWidgetItem();
        tableWidget->setItem(1, 1, __qtablewidgetitem38);
        QTableWidgetItem *__qtablewidgetitem39 = new QTableWidgetItem();
        tableWidget->setItem(2, 0, __qtablewidgetitem39);
        QTableWidgetItem *__qtablewidgetitem40 = new QTableWidgetItem();
        tableWidget->setItem(2, 1, __qtablewidgetitem40);
        QTableWidgetItem *__qtablewidgetitem41 = new QTableWidgetItem();
        tableWidget->setItem(3, 0, __qtablewidgetitem41);
        QTableWidgetItem *__qtablewidgetitem42 = new QTableWidgetItem();
        tableWidget->setItem(3, 1, __qtablewidgetitem42);
        QTableWidgetItem *__qtablewidgetitem43 = new QTableWidgetItem();
        tableWidget->setItem(4, 0, __qtablewidgetitem43);
        QTableWidgetItem *__qtablewidgetitem44 = new QTableWidgetItem();
        tableWidget->setItem(4, 1, __qtablewidgetitem44);
        QTableWidgetItem *__qtablewidgetitem45 = new QTableWidgetItem();
        tableWidget->setItem(5, 0, __qtablewidgetitem45);
        QTableWidgetItem *__qtablewidgetitem46 = new QTableWidgetItem();
        tableWidget->setItem(5, 1, __qtablewidgetitem46);
        QTableWidgetItem *__qtablewidgetitem47 = new QTableWidgetItem();
        tableWidget->setItem(6, 0, __qtablewidgetitem47);
        QTableWidgetItem *__qtablewidgetitem48 = new QTableWidgetItem();
        tableWidget->setItem(6, 1, __qtablewidgetitem48);
        QTableWidgetItem *__qtablewidgetitem49 = new QTableWidgetItem();
        tableWidget->setItem(7, 0, __qtablewidgetitem49);
        QTableWidgetItem *__qtablewidgetitem50 = new QTableWidgetItem();
        tableWidget->setItem(7, 1, __qtablewidgetitem50);
        QTableWidgetItem *__qtablewidgetitem51 = new QTableWidgetItem();
        tableWidget->setItem(8, 0, __qtablewidgetitem51);
        QTableWidgetItem *__qtablewidgetitem52 = new QTableWidgetItem();
        tableWidget->setItem(8, 1, __qtablewidgetitem52);
        QTableWidgetItem *__qtablewidgetitem53 = new QTableWidgetItem();
        tableWidget->setItem(9, 0, __qtablewidgetitem53);
        QTableWidgetItem *__qtablewidgetitem54 = new QTableWidgetItem();
        tableWidget->setItem(9, 1, __qtablewidgetitem54);
        QTableWidgetItem *__qtablewidgetitem55 = new QTableWidgetItem();
        tableWidget->setItem(10, 0, __qtablewidgetitem55);
        QTableWidgetItem *__qtablewidgetitem56 = new QTableWidgetItem();
        tableWidget->setItem(10, 1, __qtablewidgetitem56);
        QTableWidgetItem *__qtablewidgetitem57 = new QTableWidgetItem();
        tableWidget->setItem(11, 0, __qtablewidgetitem57);
        QTableWidgetItem *__qtablewidgetitem58 = new QTableWidgetItem();
        tableWidget->setItem(11, 1, __qtablewidgetitem58);
        QTableWidgetItem *__qtablewidgetitem59 = new QTableWidgetItem();
        tableWidget->setItem(12, 0, __qtablewidgetitem59);
        QTableWidgetItem *__qtablewidgetitem60 = new QTableWidgetItem();
        tableWidget->setItem(12, 1, __qtablewidgetitem60);
        QTableWidgetItem *__qtablewidgetitem61 = new QTableWidgetItem();
        tableWidget->setItem(13, 0, __qtablewidgetitem61);
        QTableWidgetItem *__qtablewidgetitem62 = new QTableWidgetItem();
        tableWidget->setItem(13, 1, __qtablewidgetitem62);
        QTableWidgetItem *__qtablewidgetitem63 = new QTableWidgetItem();
        tableWidget->setItem(14, 0, __qtablewidgetitem63);
        QTableWidgetItem *__qtablewidgetitem64 = new QTableWidgetItem();
        tableWidget->setItem(14, 1, __qtablewidgetitem64);
        QTableWidgetItem *__qtablewidgetitem65 = new QTableWidgetItem();
        tableWidget->setItem(15, 0, __qtablewidgetitem65);
        QTableWidgetItem *__qtablewidgetitem66 = new QTableWidgetItem();
        tableWidget->setItem(15, 1, __qtablewidgetitem66);
        QTableWidgetItem *__qtablewidgetitem67 = new QTableWidgetItem();
        tableWidget->setItem(16, 0, __qtablewidgetitem67);
        QTableWidgetItem *__qtablewidgetitem68 = new QTableWidgetItem();
        tableWidget->setItem(16, 1, __qtablewidgetitem68);
        QTableWidgetItem *__qtablewidgetitem69 = new QTableWidgetItem();
        tableWidget->setItem(17, 0, __qtablewidgetitem69);
        QTableWidgetItem *__qtablewidgetitem70 = new QTableWidgetItem();
        tableWidget->setItem(17, 1, __qtablewidgetitem70);
        QTableWidgetItem *__qtablewidgetitem71 = new QTableWidgetItem();
        tableWidget->setItem(18, 0, __qtablewidgetitem71);
        QTableWidgetItem *__qtablewidgetitem72 = new QTableWidgetItem();
        tableWidget->setItem(18, 1, __qtablewidgetitem72);
        QTableWidgetItem *__qtablewidgetitem73 = new QTableWidgetItem();
        tableWidget->setItem(19, 0, __qtablewidgetitem73);
        QTableWidgetItem *__qtablewidgetitem74 = new QTableWidgetItem();
        tableWidget->setItem(19, 1, __qtablewidgetitem74);
        QTableWidgetItem *__qtablewidgetitem75 = new QTableWidgetItem();
        tableWidget->setItem(20, 0, __qtablewidgetitem75);
        QTableWidgetItem *__qtablewidgetitem76 = new QTableWidgetItem();
        tableWidget->setItem(20, 1, __qtablewidgetitem76);
        QTableWidgetItem *__qtablewidgetitem77 = new QTableWidgetItem();
        tableWidget->setItem(21, 0, __qtablewidgetitem77);
        QTableWidgetItem *__qtablewidgetitem78 = new QTableWidgetItem();
        tableWidget->setItem(21, 1, __qtablewidgetitem78);
        QTableWidgetItem *__qtablewidgetitem79 = new QTableWidgetItem();
        tableWidget->setItem(22, 0, __qtablewidgetitem79);
        QTableWidgetItem *__qtablewidgetitem80 = new QTableWidgetItem();
        tableWidget->setItem(22, 1, __qtablewidgetitem80);
        QTableWidgetItem *__qtablewidgetitem81 = new QTableWidgetItem();
        tableWidget->setItem(23, 0, __qtablewidgetitem81);
        QTableWidgetItem *__qtablewidgetitem82 = new QTableWidgetItem();
        tableWidget->setItem(23, 1, __qtablewidgetitem82);
        QTableWidgetItem *__qtablewidgetitem83 = new QTableWidgetItem();
        tableWidget->setItem(24, 0, __qtablewidgetitem83);
        QTableWidgetItem *__qtablewidgetitem84 = new QTableWidgetItem();
        tableWidget->setItem(24, 1, __qtablewidgetitem84);
        QTableWidgetItem *__qtablewidgetitem85 = new QTableWidgetItem();
        tableWidget->setItem(25, 0, __qtablewidgetitem85);
        QTableWidgetItem *__qtablewidgetitem86 = new QTableWidgetItem();
        tableWidget->setItem(25, 1, __qtablewidgetitem86);
        QTableWidgetItem *__qtablewidgetitem87 = new QTableWidgetItem();
        tableWidget->setItem(26, 0, __qtablewidgetitem87);
        QTableWidgetItem *__qtablewidgetitem88 = new QTableWidgetItem();
        tableWidget->setItem(26, 1, __qtablewidgetitem88);
        QTableWidgetItem *__qtablewidgetitem89 = new QTableWidgetItem();
        tableWidget->setItem(27, 0, __qtablewidgetitem89);
        QTableWidgetItem *__qtablewidgetitem90 = new QTableWidgetItem();
        tableWidget->setItem(27, 1, __qtablewidgetitem90);
        QTableWidgetItem *__qtablewidgetitem91 = new QTableWidgetItem();
        tableWidget->setItem(28, 0, __qtablewidgetitem91);
        QTableWidgetItem *__qtablewidgetitem92 = new QTableWidgetItem();
        tableWidget->setItem(28, 1, __qtablewidgetitem92);
        QTableWidgetItem *__qtablewidgetitem93 = new QTableWidgetItem();
        tableWidget->setItem(29, 0, __qtablewidgetitem93);
        QTableWidgetItem *__qtablewidgetitem94 = new QTableWidgetItem();
        tableWidget->setItem(29, 1, __qtablewidgetitem94);
        QTableWidgetItem *__qtablewidgetitem95 = new QTableWidgetItem();
        tableWidget->setItem(30, 0, __qtablewidgetitem95);
        QTableWidgetItem *__qtablewidgetitem96 = new QTableWidgetItem();
        tableWidget->setItem(30, 1, __qtablewidgetitem96);
        QTableWidgetItem *__qtablewidgetitem97 = new QTableWidgetItem();
        tableWidget->setItem(31, 0, __qtablewidgetitem97);
        QTableWidgetItem *__qtablewidgetitem98 = new QTableWidgetItem();
        tableWidget->setItem(31, 1, __qtablewidgetitem98);
        QTableWidgetItem *__qtablewidgetitem99 = new QTableWidgetItem();
        tableWidget->setItem(32, 0, __qtablewidgetitem99);
        QTableWidgetItem *__qtablewidgetitem100 = new QTableWidgetItem();
        tableWidget->setItem(32, 1, __qtablewidgetitem100);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(tableWidget);

        pushButtonAddLine = new QPushButton(layoutWidget);
        pushButtonAddLine->setObjectName(QStringLiteral("pushButtonAddLine"));

        verticalLayout->addWidget(pushButtonAddLine);

        pushButtonDeleteLastLine = new QPushButton(layoutWidget);
        pushButtonDeleteLastLine->setObjectName(QStringLiteral("pushButtonDeleteLastLine"));

        verticalLayout->addWidget(pushButtonDeleteLastLine);

        plainTextEditLog = new QPlainTextEdit(layoutWidget);
        plainTextEditLog->setObjectName(QStringLiteral("plainTextEditLog"));

        verticalLayout->addWidget(plainTextEditLog);

        checkBoxDirection = new QCheckBox(layoutWidget);
        checkBoxDirection->setObjectName(QStringLiteral("checkBoxDirection"));

        verticalLayout->addWidget(checkBoxDirection);

        pushButtonClearAll = new QPushButton(layoutWidget);
        pushButtonClearAll->setObjectName(QStringLiteral("pushButtonClearAll"));

        verticalLayout->addWidget(pushButtonClearAll);

        Clear = new QPushButton(layoutWidget);
        Clear->setObjectName(QStringLiteral("Clear"));

        verticalLayout->addWidget(Clear);

        pushButtonCalc = new QPushButton(layoutWidget);
        pushButtonCalc->setObjectName(QStringLiteral("pushButtonCalc"));

        verticalLayout->addWidget(pushButtonCalc);

        splitter->addWidget(layoutWidget);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);


        retranslateUi(SS_GUI);

        QMetaObject::connectSlotsByName(SS_GUI);
    } // setupUi

    void retranslateUi(QWidget *SS_GUI)
    {
        SS_GUI->setWindowTitle(QApplication::translate("SS_GUI", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("SS_GUI", "x", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("SS_GUI", "y", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem2->setText(QApplication::translate("SS_GUI", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem3->setText(QApplication::translate("SS_GUI", "2", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem4->setText(QApplication::translate("SS_GUI", "3", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem5->setText(QApplication::translate("SS_GUI", "4", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem6->setText(QApplication::translate("SS_GUI", "5", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->verticalHeaderItem(5);
        ___qtablewidgetitem7->setText(QApplication::translate("SS_GUI", "6", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->verticalHeaderItem(6);
        ___qtablewidgetitem8->setText(QApplication::translate("SS_GUI", "7", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->verticalHeaderItem(7);
        ___qtablewidgetitem9->setText(QApplication::translate("SS_GUI", "8", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->verticalHeaderItem(8);
        ___qtablewidgetitem10->setText(QApplication::translate("SS_GUI", "9", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->verticalHeaderItem(9);
        ___qtablewidgetitem11->setText(QApplication::translate("SS_GUI", "10", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->verticalHeaderItem(10);
        ___qtablewidgetitem12->setText(QApplication::translate("SS_GUI", "11", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget->verticalHeaderItem(11);
        ___qtablewidgetitem13->setText(QApplication::translate("SS_GUI", "12", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget->verticalHeaderItem(12);
        ___qtablewidgetitem14->setText(QApplication::translate("SS_GUI", "13", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget->verticalHeaderItem(13);
        ___qtablewidgetitem15->setText(QApplication::translate("SS_GUI", "14", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget->verticalHeaderItem(14);
        ___qtablewidgetitem16->setText(QApplication::translate("SS_GUI", "15", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget->verticalHeaderItem(15);
        ___qtablewidgetitem17->setText(QApplication::translate("SS_GUI", "16", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget->verticalHeaderItem(16);
        ___qtablewidgetitem18->setText(QApplication::translate("SS_GUI", "17", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget->verticalHeaderItem(17);
        ___qtablewidgetitem19->setText(QApplication::translate("SS_GUI", "18", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget->verticalHeaderItem(18);
        ___qtablewidgetitem20->setText(QApplication::translate("SS_GUI", "19", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidget->verticalHeaderItem(19);
        ___qtablewidgetitem21->setText(QApplication::translate("SS_GUI", "20", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidget->verticalHeaderItem(20);
        ___qtablewidgetitem22->setText(QApplication::translate("SS_GUI", "21", nullptr));
        QTableWidgetItem *___qtablewidgetitem23 = tableWidget->verticalHeaderItem(21);
        ___qtablewidgetitem23->setText(QApplication::translate("SS_GUI", "22", nullptr));
        QTableWidgetItem *___qtablewidgetitem24 = tableWidget->verticalHeaderItem(22);
        ___qtablewidgetitem24->setText(QApplication::translate("SS_GUI", "23", nullptr));
        QTableWidgetItem *___qtablewidgetitem25 = tableWidget->verticalHeaderItem(23);
        ___qtablewidgetitem25->setText(QApplication::translate("SS_GUI", "24", nullptr));
        QTableWidgetItem *___qtablewidgetitem26 = tableWidget->verticalHeaderItem(24);
        ___qtablewidgetitem26->setText(QApplication::translate("SS_GUI", "25", nullptr));
        QTableWidgetItem *___qtablewidgetitem27 = tableWidget->verticalHeaderItem(25);
        ___qtablewidgetitem27->setText(QApplication::translate("SS_GUI", "26", nullptr));
        QTableWidgetItem *___qtablewidgetitem28 = tableWidget->verticalHeaderItem(26);
        ___qtablewidgetitem28->setText(QApplication::translate("SS_GUI", "27", nullptr));
        QTableWidgetItem *___qtablewidgetitem29 = tableWidget->verticalHeaderItem(27);
        ___qtablewidgetitem29->setText(QApplication::translate("SS_GUI", "28", nullptr));
        QTableWidgetItem *___qtablewidgetitem30 = tableWidget->verticalHeaderItem(28);
        ___qtablewidgetitem30->setText(QApplication::translate("SS_GUI", "29", nullptr));
        QTableWidgetItem *___qtablewidgetitem31 = tableWidget->verticalHeaderItem(29);
        ___qtablewidgetitem31->setText(QApplication::translate("SS_GUI", "30", nullptr));
        QTableWidgetItem *___qtablewidgetitem32 = tableWidget->verticalHeaderItem(30);
        ___qtablewidgetitem32->setText(QApplication::translate("SS_GUI", "31", nullptr));
        QTableWidgetItem *___qtablewidgetitem33 = tableWidget->verticalHeaderItem(31);
        ___qtablewidgetitem33->setText(QApplication::translate("SS_GUI", "32", nullptr));
        QTableWidgetItem *___qtablewidgetitem34 = tableWidget->verticalHeaderItem(32);
        ___qtablewidgetitem34->setText(QApplication::translate("SS_GUI", "33", nullptr));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem35 = tableWidget->item(0, 0);
        ___qtablewidgetitem35->setText(QApplication::translate("SS_GUI", "-0.27", nullptr));
        QTableWidgetItem *___qtablewidgetitem36 = tableWidget->item(0, 1);
        ___qtablewidgetitem36->setText(QApplication::translate("SS_GUI", "6.46", nullptr));
        QTableWidgetItem *___qtablewidgetitem37 = tableWidget->item(1, 0);
        ___qtablewidgetitem37->setText(QApplication::translate("SS_GUI", "4.76", nullptr));
        QTableWidgetItem *___qtablewidgetitem38 = tableWidget->item(1, 1);
        ___qtablewidgetitem38->setText(QApplication::translate("SS_GUI", "3.78", nullptr));
        QTableWidgetItem *___qtablewidgetitem39 = tableWidget->item(2, 0);
        ___qtablewidgetitem39->setText(QApplication::translate("SS_GUI", "3.92", nullptr));
        QTableWidgetItem *___qtablewidgetitem40 = tableWidget->item(2, 1);
        ___qtablewidgetitem40->setText(QApplication::translate("SS_GUI", "-3.27", nullptr));
        QTableWidgetItem *___qtablewidgetitem41 = tableWidget->item(3, 0);
        ___qtablewidgetitem41->setText(QApplication::translate("SS_GUI", "-5.08", nullptr));
        QTableWidgetItem *___qtablewidgetitem42 = tableWidget->item(3, 1);
        ___qtablewidgetitem42->setText(QApplication::translate("SS_GUI", "-5.29", nullptr));
        QTableWidgetItem *___qtablewidgetitem43 = tableWidget->item(4, 0);
        ___qtablewidgetitem43->setText(QApplication::translate("SS_GUI", "-15.17", nullptr));
        QTableWidgetItem *___qtablewidgetitem44 = tableWidget->item(4, 1);
        ___qtablewidgetitem44->setText(QApplication::translate("SS_GUI", "-0.64", nullptr));
        QTableWidgetItem *___qtablewidgetitem45 = tableWidget->item(5, 0);
        ___qtablewidgetitem45->setText(QApplication::translate("SS_GUI", "-20.44", nullptr));
        QTableWidgetItem *___qtablewidgetitem46 = tableWidget->item(5, 1);
        ___qtablewidgetitem46->setText(QApplication::translate("SS_GUI", "6.32", nullptr));
        QTableWidgetItem *___qtablewidgetitem47 = tableWidget->item(6, 0);
        ___qtablewidgetitem47->setText(QApplication::translate("SS_GUI", "-13.03", nullptr));
        QTableWidgetItem *___qtablewidgetitem48 = tableWidget->item(6, 1);
        ___qtablewidgetitem48->setText(QApplication::translate("SS_GUI", "8.18", nullptr));
        QTableWidgetItem *___qtablewidgetitem49 = tableWidget->item(7, 0);
        ___qtablewidgetitem49->setText(QApplication::translate("SS_GUI", "-12.7", nullptr));
        QTableWidgetItem *___qtablewidgetitem50 = tableWidget->item(7, 1);
        ___qtablewidgetitem50->setText(QApplication::translate("SS_GUI", "3.33", nullptr));
        QTableWidgetItem *___qtablewidgetitem51 = tableWidget->item(8, 0);
        ___qtablewidgetitem51->setText(QApplication::translate("SS_GUI", "-8.28", nullptr));
        QTableWidgetItem *___qtablewidgetitem52 = tableWidget->item(8, 1);
        ___qtablewidgetitem52->setText(QApplication::translate("SS_GUI", "7.02", nullptr));
        QTableWidgetItem *___qtablewidgetitem53 = tableWidget->item(9, 0);
        ___qtablewidgetitem53->setText(QApplication::translate("SS_GUI", "-6.55", nullptr));
        QTableWidgetItem *___qtablewidgetitem54 = tableWidget->item(9, 1);
        ___qtablewidgetitem54->setText(QApplication::translate("SS_GUI", "1.35", nullptr));
        QTableWidgetItem *___qtablewidgetitem55 = tableWidget->item(10, 0);
        ___qtablewidgetitem55->setText(QApplication::translate("SS_GUI", "-3.95", nullptr));
        QTableWidgetItem *___qtablewidgetitem56 = tableWidget->item(10, 1);
        ___qtablewidgetitem56->setText(QApplication::translate("SS_GUI", "7.17", nullptr));
        QTableWidgetItem *___qtablewidgetitem57 = tableWidget->item(11, 0);
        ___qtablewidgetitem57->setText(QApplication::translate("SS_GUI", "-2.77", nullptr));
        QTableWidgetItem *___qtablewidgetitem58 = tableWidget->item(11, 1);
        ___qtablewidgetitem58->setText(QApplication::translate("SS_GUI", "0.33", nullptr));
        QTableWidgetItem *___qtablewidgetitem59 = tableWidget->item(12, 0);
        ___qtablewidgetitem59->setText(QApplication::translate("SS_GUI", "-1.36", nullptr));
        QTableWidgetItem *___qtablewidgetitem60 = tableWidget->item(12, 1);
        ___qtablewidgetitem60->setText(QApplication::translate("SS_GUI", "10.09", nullptr));
        QTableWidgetItem *___qtablewidgetitem61 = tableWidget->item(13, 0);
        ___qtablewidgetitem61->setText(QApplication::translate("SS_GUI", "2.87", nullptr));
        QTableWidgetItem *___qtablewidgetitem62 = tableWidget->item(13, 1);
        ___qtablewidgetitem62->setText(QApplication::translate("SS_GUI", "11.54", nullptr));
        QTableWidgetItem *___qtablewidgetitem63 = tableWidget->item(14, 0);
        ___qtablewidgetitem63->setText(QApplication::translate("SS_GUI", "6.36", nullptr));
        QTableWidgetItem *___qtablewidgetitem64 = tableWidget->item(14, 1);
        ___qtablewidgetitem64->setText(QApplication::translate("SS_GUI", "9.04", nullptr));
        QTableWidgetItem *___qtablewidgetitem65 = tableWidget->item(15, 0);
        ___qtablewidgetitem65->setText(QApplication::translate("SS_GUI", "11.22", nullptr));
        QTableWidgetItem *___qtablewidgetitem66 = tableWidget->item(15, 1);
        ___qtablewidgetitem66->setText(QApplication::translate("SS_GUI", "6.18", nullptr));
        QTableWidgetItem *___qtablewidgetitem67 = tableWidget->item(16, 0);
        ___qtablewidgetitem67->setText(QApplication::translate("SS_GUI", "8.882", nullptr));
        QTableWidgetItem *___qtablewidgetitem68 = tableWidget->item(16, 1);
        ___qtablewidgetitem68->setText(QApplication::translate("SS_GUI", "11.7", nullptr));
        QTableWidgetItem *___qtablewidgetitem69 = tableWidget->item(17, 0);
        ___qtablewidgetitem69->setText(QApplication::translate("SS_GUI", "11.991", nullptr));
        QTableWidgetItem *___qtablewidgetitem70 = tableWidget->item(17, 1);
        ___qtablewidgetitem70->setText(QApplication::translate("SS_GUI", "10.64", nullptr));
        QTableWidgetItem *___qtablewidgetitem71 = tableWidget->item(18, 0);
        ___qtablewidgetitem71->setText(QApplication::translate("SS_GUI", "12.52", nullptr));
        QTableWidgetItem *___qtablewidgetitem72 = tableWidget->item(18, 1);
        ___qtablewidgetitem72->setText(QApplication::translate("SS_GUI", "7.3", nullptr));
        QTableWidgetItem *___qtablewidgetitem73 = tableWidget->item(19, 0);
        ___qtablewidgetitem73->setText(QApplication::translate("SS_GUI", "12.21", nullptr));
        QTableWidgetItem *___qtablewidgetitem74 = tableWidget->item(19, 1);
        ___qtablewidgetitem74->setText(QApplication::translate("SS_GUI", "3.79", nullptr));
        QTableWidgetItem *___qtablewidgetitem75 = tableWidget->item(20, 0);
        ___qtablewidgetitem75->setText(QApplication::translate("SS_GUI", "8.92", nullptr));
        QTableWidgetItem *___qtablewidgetitem76 = tableWidget->item(20, 1);
        ___qtablewidgetitem76->setText(QApplication::translate("SS_GUI", "2.38", nullptr));
        QTableWidgetItem *___qtablewidgetitem77 = tableWidget->item(21, 0);
        ___qtablewidgetitem77->setText(QApplication::translate("SS_GUI", "8.1", nullptr));
        QTableWidgetItem *___qtablewidgetitem78 = tableWidget->item(21, 1);
        ___qtablewidgetitem78->setText(QApplication::translate("SS_GUI", "5.5", nullptr));
        QTableWidgetItem *___qtablewidgetitem79 = tableWidget->item(22, 0);
        ___qtablewidgetitem79->setText(QApplication::translate("SS_GUI", "7.69", nullptr));
        QTableWidgetItem *___qtablewidgetitem80 = tableWidget->item(22, 1);
        ___qtablewidgetitem80->setText(QApplication::translate("SS_GUI", "2.24", nullptr));
        QTableWidgetItem *___qtablewidgetitem81 = tableWidget->item(23, 0);
        ___qtablewidgetitem81->setText(QApplication::translate("SS_GUI", "5.3", nullptr));
        QTableWidgetItem *___qtablewidgetitem82 = tableWidget->item(23, 1);
        ___qtablewidgetitem82->setText(QApplication::translate("SS_GUI", "4.8", nullptr));
        QTableWidgetItem *___qtablewidgetitem83 = tableWidget->item(24, 0);
        ___qtablewidgetitem83->setText(QApplication::translate("SS_GUI", "7.17", nullptr));
        QTableWidgetItem *___qtablewidgetitem84 = tableWidget->item(24, 1);
        ___qtablewidgetitem84->setText(QApplication::translate("SS_GUI", "5.71", nullptr));
        QTableWidgetItem *___qtablewidgetitem85 = tableWidget->item(25, 0);
        ___qtablewidgetitem85->setText(QApplication::translate("SS_GUI", "8.16", nullptr));
        QTableWidgetItem *___qtablewidgetitem86 = tableWidget->item(25, 1);
        ___qtablewidgetitem86->setText(QApplication::translate("SS_GUI", "6.25", nullptr));
        QTableWidgetItem *___qtablewidgetitem87 = tableWidget->item(26, 0);
        ___qtablewidgetitem87->setText(QApplication::translate("SS_GUI", "8.01", nullptr));
        QTableWidgetItem *___qtablewidgetitem88 = tableWidget->item(26, 1);
        ___qtablewidgetitem88->setText(QApplication::translate("SS_GUI", "7.04", nullptr));
        QTableWidgetItem *___qtablewidgetitem89 = tableWidget->item(27, 0);
        ___qtablewidgetitem89->setText(QApplication::translate("SS_GUI", "5.01", nullptr));
        QTableWidgetItem *___qtablewidgetitem90 = tableWidget->item(27, 1);
        ___qtablewidgetitem90->setText(QApplication::translate("SS_GUI", "5.96", nullptr));
        QTableWidgetItem *___qtablewidgetitem91 = tableWidget->item(28, 0);
        ___qtablewidgetitem91->setText(QApplication::translate("SS_GUI", "5.08", nullptr));
        QTableWidgetItem *___qtablewidgetitem92 = tableWidget->item(28, 1);
        ___qtablewidgetitem92->setText(QApplication::translate("SS_GUI", "7.81", nullptr));
        QTableWidgetItem *___qtablewidgetitem93 = tableWidget->item(29, 0);
        ___qtablewidgetitem93->setText(QApplication::translate("SS_GUI", "4.49", nullptr));
        QTableWidgetItem *___qtablewidgetitem94 = tableWidget->item(29, 1);
        ___qtablewidgetitem94->setText(QApplication::translate("SS_GUI", "6.73", nullptr));
        QTableWidgetItem *___qtablewidgetitem95 = tableWidget->item(30, 0);
        ___qtablewidgetitem95->setText(QApplication::translate("SS_GUI", "4.8", nullptr));
        QTableWidgetItem *___qtablewidgetitem96 = tableWidget->item(30, 1);
        ___qtablewidgetitem96->setText(QApplication::translate("SS_GUI", "5.02", nullptr));
        QTableWidgetItem *___qtablewidgetitem97 = tableWidget->item(31, 0);
        ___qtablewidgetitem97->setText(QApplication::translate("SS_GUI", "2.93", nullptr));
        QTableWidgetItem *___qtablewidgetitem98 = tableWidget->item(31, 1);
        ___qtablewidgetitem98->setText(QApplication::translate("SS_GUI", "6.97", nullptr));
        QTableWidgetItem *___qtablewidgetitem99 = tableWidget->item(32, 0);
        ___qtablewidgetitem99->setText(QApplication::translate("SS_GUI", "4.23", nullptr));
        QTableWidgetItem *___qtablewidgetitem100 = tableWidget->item(32, 1);
        ___qtablewidgetitem100->setText(QApplication::translate("SS_GUI", "8.27", nullptr));
        tableWidget->setSortingEnabled(__sortingEnabled);

        pushButtonAddLine->setText(QApplication::translate("SS_GUI", "Add Line", nullptr));
        pushButtonDeleteLastLine->setText(QApplication::translate("SS_GUI", "Delete Last Line", nullptr));
        checkBoxDirection->setText(QApplication::translate("SS_GUI", "change Direction", nullptr));
        pushButtonClearAll->setText(QApplication::translate("SS_GUI", "Clear all", nullptr));
        Clear->setText(QApplication::translate("SS_GUI", "Clear", nullptr));
        pushButtonCalc->setText(QApplication::translate("SS_GUI", "Run Calculation", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SS_GUI: public Ui_SS_GUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SKELETONGUI_H
