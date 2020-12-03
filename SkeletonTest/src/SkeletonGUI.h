#ifndef SKELETONGUI_H
#define SKELETONGUI_H

#include <QWidget>
#include <QGraphicsScene>

#include <SS_Polygon.h>

namespace Ui {
class SS_GUI;
}

class SS_GUI : public QWidget
{
    Q_OBJECT

public:
	explicit SS_GUI(QWidget *parent = nullptr);
	~SS_GUI();

	bool drawPolygons(const std::vector<SKELETON::Polygon> &polys);

private:

	QGraphicsScene				*m_scene;	///> pointer to scene where polygon is drawn
	Ui::SS_GUI					*m_ui;		///> pointer to Ui
};

#endif // SKELETONGUI_H
