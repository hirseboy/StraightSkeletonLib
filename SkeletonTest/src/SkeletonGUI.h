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

	bool drawVertexLines(const std::vector<IBK::Line> &vertexLines);

protected:
	void mousePressEvent(QMouseEvent* event) override;

private slots:

	void on_pushButtonCalc_clicked();

	void on_pushButtonClearAll_clicked();

	void on_tableWidget_cellChanged(int row, int column);

	void on_pushButtonDeleteLastPoint_clicked();

private:
	/*! Formats the polygon. */
	void formatPolygon();

	bool						m_draw;		///> sets weather a polygon is drawn

	QGraphicsPolygonItem		*m_polygonItem;
	QPolygonF					m_polygon;
	SKELETON::Polygon			m_tmpPolygon;

	QGraphicsScene				*m_scene;	///> pointer to scene where polygon is drawn
	Ui::SS_GUI					*m_ui;		///> pointer to Ui
};

#endif // SKELETONGUI_H
