#ifndef SKELETONGUI_H
#define SKELETONGUI_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsPolygonItem>
#include <QWheelEvent>
#include <QTableWidgetItem>
#include <QGraphicsSceneMouseEvent>

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

	bool drawPolygon(SKELETON::Polygon polys, const QPen &pen);

	bool drawVertexLines(const std::vector<IBK::Line> &vertexLines);

	bool						m_draw;		///> sets weather a polygon is drawn

protected:
	//void wheelEvent(QWheelEvent* event) override;

	void mousePressEvent(QMouseEvent* event) override;

	void mouseMoveEvent(QMouseEvent *event) override;

private slots:

	void on_pushButtonContinue_pressed();

	void on_pushButtonCalc_clicked();

	void on_Clear_clicked();

	void on_pushButtonClearAll_clicked();

	void on_pushButtonAddLine_clicked();

	void on_tableWidget_itemChanged(QTableWidgetItem *item);

	void on_pushButtonDeleteLastLine_clicked();

private:

	QGraphicsPolygonItem		*m_polygonItem;
	QPolygonF					m_polygon;
	SKELETON::Polygon			m_tmpPolygon;

	QGraphicsScene				*m_scene;	///> pointer to scene where polygon is drawn
	Ui::SS_GUI					*m_ui;		///> pointer to Ui
};

#endif // SKELETONGUI_H
