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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SS_GUI
{
public:
    QGridLayout *gridLayout;
    BLOCKMOD::ZoomMeshGraphicsView *graphicsViewSkeleton;
    QPushButton *pushButtonContinue;

    void setupUi(QWidget *SS_GUI)
    {
        if (SS_GUI->objectName().isEmpty())
            SS_GUI->setObjectName(QStringLiteral("SS_GUI"));
        SS_GUI->resize(761, 532);
        gridLayout = new QGridLayout(SS_GUI);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        graphicsViewSkeleton = new BLOCKMOD::ZoomMeshGraphicsView(SS_GUI);
        graphicsViewSkeleton->setObjectName(QStringLiteral("graphicsViewSkeleton"));

        gridLayout->addWidget(graphicsViewSkeleton, 0, 0, 1, 1);

        pushButtonContinue = new QPushButton(SS_GUI);
        pushButtonContinue->setObjectName(QStringLiteral("pushButtonContinue"));

        gridLayout->addWidget(pushButtonContinue, 1, 0, 1, 1);


        retranslateUi(SS_GUI);

        QMetaObject::connectSlotsByName(SS_GUI);
    } // setupUi

    void retranslateUi(QWidget *SS_GUI)
    {
        SS_GUI->setWindowTitle(QApplication::translate("SS_GUI", "Form", Q_NULLPTR));
        pushButtonContinue->setText(QApplication::translate("SS_GUI", "Continue", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SS_GUI: public Ui_SS_GUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SKELETONGUI_H
