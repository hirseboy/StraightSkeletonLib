#ifndef SKELETONGUI_H
#define SKELETONGUI_H

#include <QWidget>

namespace Ui {
class SkeletonGUI;
}

class SkeletonGUI : public QWidget
{
    Q_OBJECT

public:
    explicit SkeletonGUI(QWidget *parent = nullptr);
    ~SkeletonGUI();

private:
    Ui::SkeletonGUI *ui;
};

#endif // SKELETONGUI_H
