#include "SkeletonGUI.h"
#include "ui_SkeletonGUI.h"

#include <SS_Polygon.h>
#include <SS_Constants.h>

SS_GUI::SS_GUI(QWidget *parent) :
	QWidget(parent),
	m_polygonItem(new QGraphicsPolygonItem),
	m_scene(new QGraphicsScene),
	m_ui(new Ui::SS_GUI)
{
	m_ui->setupUi(this);

	m_scene->addItem(m_polygonItem);
	formatPolygon();

	m_ui->graphicsViewSkeleton->centerOn(0,0);
	m_ui->graphicsViewSkeleton->setScene(m_scene);
	m_ui->graphicsViewSkeleton->setSceneRect(QRect(0,0, 1000, 1500));
	
	setMouseTracking(true);
	m_ui->graphicsViewSkeleton->setMouseTracking(true);
}

SS_GUI::~SS_GUI() {
	delete m_ui;
}


bool SS_GUI::drawVertexLines(const std::vector<IBK::Line> &vertexLines ){
	QPen penPoly2 (Qt::green, 2, Qt::DashLine);

	for (size_t i = 0; i < vertexLines.size(); ++i) {
		QLine line (vertexLines[i].m_p1.m_x*SKELETON::UI_CONVERSION_FACTOR, - vertexLines[i].m_p1.m_y*SKELETON::UI_CONVERSION_FACTOR,
					vertexLines[i].m_p2.m_x*SKELETON::UI_CONVERSION_FACTOR, - vertexLines[i].m_p2.m_y*SKELETON::UI_CONVERSION_FACTOR);

		m_scene->addLine( line, penPoly2);
	}

	m_ui->graphicsViewSkeleton->setScene(m_scene);

	return true;
}


void SS_GUI::mousePressEvent(QMouseEvent * event) {
	m_ui->tableWidget->blockSignals(true);

	m_scene->clear();
	m_polygonItem = new QGraphicsPolygonItem();
	m_scene->addItem(m_polygonItem);
	formatPolygon();

	// Detect if the click is in the view.
	QPoint remapped = m_ui->graphicsViewSkeleton->mapFromParent( event->pos() );
	if ( m_ui->graphicsViewSkeleton->rect().contains( remapped ) )
	{
		QPointF addedPoint = m_ui->graphicsViewSkeleton->mapToScene( remapped );

		m_scene->addEllipse(addedPoint.x(), addedPoint.y(), 5, 5, QPen ( Qt::red ));
		m_polygon.push_back(addedPoint);
	}

	m_ui->tableWidget->setRowCount(m_polygon.size());
	QPolygonF drawingPoly;
	for (unsigned int i=0; i < m_polygon.size(); ++i) {
		m_ui->tableWidget->setItem(i, 0, new QTableWidgetItem( QString("%1").arg( m_polygon[i].x()/SKELETON::UI_CONVERSION_FACTOR, 3, 'g') ) );
		m_ui->tableWidget->setItem(i, 1, new QTableWidgetItem( QString("%1").arg(-m_polygon[i].y()/SKELETON::UI_CONVERSION_FACTOR, 3, 'g') ) );
	}
	m_polygonItem->setPolygon(m_polygon);

	m_ui->tableWidget->blockSignals(false);
	event->accept();
}


void SS_GUI::on_pushButtonCalc_clicked() {

	SKELETON::Polygon skeletonPoly;
	std::vector< QLineF > bisectorLines;

	if ( m_ui->checkBoxDirection->isChecked() ) {
		for ( unsigned int i = 0; i < m_polygon.size(); ++i ) {

			QPointF pointF (    m_polygon[i].x(),
								- m_polygon[i].y() );

			skeletonPoly << SKELETON::Polygon::Point (   pointF.x() / SKELETON::UI_CONVERSION_FACTOR,
														-pointF.y() / SKELETON::UI_CONVERSION_FACTOR );
		}
	} else {
		for ( unsigned int i = m_polygon.size(); i > 0; --i ) {

			QPointF pointF (    m_polygon[i-1].x(),
					- m_polygon[i-1].y() );

			skeletonPoly << SKELETON::Polygon::Point ( pointF.x() / SKELETON::UI_CONVERSION_FACTOR,
													   pointF.y() / SKELETON::UI_CONVERSION_FACTOR );
		}
	}

	try {
		skeletonPoly.initialize(false);
		skeletonPoly.findSkeletonLines();
		skeletonPoly.findVertexLines();

	} catch (IBK::Exception &ex) {
		m_ui->plainTextEditLog->appendPlainText(ex.what());
	}

	const std::vector<SKELETON::Polygon::Point> &points = skeletonPoly.points();
	for ( size_t i=0; i < points.size(); ++i ) {
		if( skeletonPoly.size() == 0 )
			continue;
		bisectorLines.push_back( QLineF ( points[i].m_x * SKELETON::UI_CONVERSION_FACTOR,
										  points[i].m_y * SKELETON::UI_CONVERSION_FACTOR,
										  points[i].m_x * SKELETON::UI_CONVERSION_FACTOR + skeletonPoly.bisector(i).m_x*10000,
										  points[i].m_y * SKELETON::UI_CONVERSION_FACTOR + skeletonPoly.bisector(i).m_y*10000 ) );
	}

	for (const IBK::Line &line : skeletonPoly.skeletonLines() ) {
		m_scene->addLine( QLineF (  line.m_p1.m_x * SKELETON::UI_CONVERSION_FACTOR,
									-line.m_p1.m_y * SKELETON::UI_CONVERSION_FACTOR,
									line.m_p2.m_x * SKELETON::UI_CONVERSION_FACTOR,
									-line.m_p2.m_y * SKELETON::UI_CONVERSION_FACTOR ),
						  QPen ( Qt::darkGreen, 5, Qt::SolidLine ));
	}
	for (const IBK::Line &vertexLine : skeletonPoly.vertexLines() ) {
		m_scene->addLine( QLineF (  vertexLine.m_p1.m_x * SKELETON::UI_CONVERSION_FACTOR,
									-vertexLine.m_p1.m_y * SKELETON::UI_CONVERSION_FACTOR,
									vertexLine.m_p2.m_x * SKELETON::UI_CONVERSION_FACTOR,
									-vertexLine.m_p2.m_y * SKELETON::UI_CONVERSION_FACTOR),
						  QPen ( Qt::darkRed, 2, Qt::DashLine ));
	}

	for (unsigned int i = 1; i < skeletonPoly.shrinkedPolygons().size(); ++i) {

		const std::vector< SKELETON::Polygon::Point > shrinkedPoly = skeletonPoly.shrinkedPolygons()[i];
		QPolygonF polyShrinked;

		if ( !shrinkedPoly.empty() ) {
			for (const SKELETON::Polygon::Point &shrinkedPolyPoint : shrinkedPoly ) {
				polyShrinked << QPointF (  shrinkedPolyPoint.m_x * SKELETON::UI_CONVERSION_FACTOR,
										   -shrinkedPolyPoint.m_y * SKELETON::UI_CONVERSION_FACTOR );
			}
			polyShrinked << QPointF ( shrinkedPoly[0].m_x * SKELETON::UI_CONVERSION_FACTOR,
					-shrinkedPoly[0].m_y * SKELETON::UI_CONVERSION_FACTOR);

			m_scene->addPolygon( polyShrinked, QPen ( Qt::green, 1, Qt::DashLine ));
		}
	}
}


void SS_GUI::on_pushButtonClearAll_clicked() {
	m_scene->clear();
	m_polygonItem = new QGraphicsPolygonItem();
	m_scene->addItem(m_polygonItem);
	formatPolygon();
	m_polygon.clear();
	m_ui->tableWidget->setRowCount(0);
}

void SS_GUI::on_tableWidget_cellChanged(int row, int column)  {
	Q_ASSERT(m_polygon.size() == m_ui->tableWidget->rowCount());

	m_scene->clear();
	m_polygonItem = new QGraphicsPolygonItem();
	m_scene->addItem(m_polygonItem);
	formatPolygon();

	bool ok;
	double x = m_ui->tableWidget->item(row, 0)->text().toDouble(&ok);
	double y = m_ui->tableWidget->item(row, 1)->text().toDouble(&ok);

	if (!ok) {
		m_ui->tableWidget->item(row, 0)->setText(QString("%1").arg(m_polygon[row].x() / SKELETON::UI_CONVERSION_FACTOR));
		m_ui->tableWidget->item(row, 1)->setText(QString("%1").arg(m_polygon[row].y() / SKELETON::UI_CONVERSION_FACTOR));
		return;
	}

	m_polygon[row].setX(x * SKELETON::UI_CONVERSION_FACTOR);
	m_polygon[row].setY(y * SKELETON::UI_CONVERSION_FACTOR);

	m_polygonItem->setPolygon(m_polygon);
}

void SS_GUI::formatPolygon() {
	Q_ASSERT(m_polygonItem != nullptr);
	m_polygonItem->setPen(QPen(Qt::red, 5));
}


void SS_GUI::on_pushButtonDeleteLastPoint_clicked() {
	if (m_polygon.isEmpty())
		return;

	m_scene->clear();
	m_polygonItem = new QGraphicsPolygonItem();
	m_scene->addItem(m_polygonItem);
	formatPolygon();

	m_polygon.pop_back();
	m_polygonItem->setPolygon(m_polygon);
}

