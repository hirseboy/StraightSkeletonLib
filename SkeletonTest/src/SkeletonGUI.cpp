#include "SkeletonGUI.h"
#include "ui_SkeletonGUI.h"

SkeletonGUI::SkeletonGUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SkeletonGUI)
{
    ui->setupUi(this);
}

SkeletonGUI::~SkeletonGUI()
{
    delete ui;
}
