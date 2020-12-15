/********************************************************************************
** Form generated from reading UI file 'SkeletonGUI.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SKELETONGUI_H
#define UI_SKELETONGUI_H

#include <BM_ZoomMeshGraphicsView.h>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableView>
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
    QTableView *tableView;
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
        tableView = new QTableView(layoutWidget);
        tableView->setObjectName(QStringLiteral("tableView"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tableView->sizePolicy().hasHeightForWidth());
        tableView->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(tableView);

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
        SS_GUI->setWindowTitle(QApplication::translate("SS_GUI", "Form", Q_NULLPTR));
        checkBoxDirection->setText(QApplication::translate("SS_GUI", "change Direction", Q_NULLPTR));
        pushButtonClearAll->setText(QApplication::translate("SS_GUI", "Clear all", Q_NULLPTR));
        Clear->setText(QApplication::translate("SS_GUI", "Clear", Q_NULLPTR));
        pushButtonCalc->setText(QApplication::translate("SS_GUI", "Run Calculation", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SS_GUI: public Ui_SS_GUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SKELETONGUI_H
