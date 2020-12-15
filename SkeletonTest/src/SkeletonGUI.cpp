#include "SkeletonGUI.h"
#include "ui_SkeletonGUI.h"

#include <SS_Polygon.h>

SS_GUI::SS_GUI(QWidget *parent) :
	QWidget(parent),
	m_polygonItem(new QGraphicsPolygonItem),
	m_scene(new QGraphicsScene),
	m_ui(new Ui::SS_GUI)
{
	m_ui->setupUi(this);

	m_scene->addItem(m_polygonItem);

	m_ui->graphicsViewSkeleton->centerOn(0,0);
	m_ui->graphicsViewSkeleton->setScene(m_scene);
}

SS_GUI::~SS_GUI()
{
	delete m_ui;
}

bool SS_GUI::drawVertexLines(const std::vector<IBK::Line> &vertexLines ){
	QPen penPoly2 (Qt::green, 2, Qt::DashLine);

	size_t scaleFactor = 100;
	double height = m_ui->graphicsViewSkeleton->height();

	for (size_t i = 0; i < vertexLines.size(); ++i) {
		QLine line (vertexLines[i].m_p1.m_x*scaleFactor,height - vertexLines[i].m_p1.m_y*scaleFactor,
					vertexLines[i].m_p2.m_x*scaleFactor, height - vertexLines[i].m_p2.m_y*scaleFactor);

		m_scene->addLine( line, penPoly2);
	}

	m_ui->graphicsViewSkeleton->setScene(m_scene);

	return true;
}

bool SS_GUI::drawPolygon(SKELETON::Polygon poly, const QPen &pen) {

	std::vector< QPointF > eventPoints;

	double height, width;
	size_t scaleFactor = 100;

	height = m_ui->graphicsViewSkeleton->height();
	width = m_ui->graphicsViewSkeleton->width();

	QPolygonF polyDraw;

	if ( poly.points().size() < 3 )
		return false;

	polyDraw.clear();
	for ( SKELETON::Polygon::Point point : poly.points() )
		polyDraw << QPointF ( point.m_x*scaleFactor,
						   height - point.m_y*scaleFactor );

	polyDraw << QPointF (poly.point(0).m_x, poly.point(0).m_y);

	// break;
	m_scene->addPolygon(polyDraw, pen);

	for ( IBK::Line line : poly.skeletonLines() )
		m_scene->addLine( QLineF (	line.m_p1.m_x*scaleFactor,
									height - line.m_p1.m_y*scaleFactor,
									line.m_p2.m_x*scaleFactor,
									height - line.m_p2.m_y*scaleFactor ), pen );

	m_ui->graphicsViewSkeleton->setScene(m_scene);

	return true;
}

//void SS_GUI::wheelEvent(QWheelEvent *event)
//{
//	if(event->delta() > 0)
//	{
//		m_ui->graphicsViewSkeleton->scale(1.05,1.05);
//	}
//	else
//	{
//		m_ui->graphicsViewSkeleton->scale(1/1.05,1/1.05);
//	}
//}

void SS_GUI::mousePressEvent(QMouseEvent * event)
{
//	if ( m_polygonItem->is )
//		m_polygonItem = new QGraphicsPolygonItem;

	// m_ui->graphicsViewSkeleton->setFrameShape(QGraphicsView::NoFrame);
	QPointF sceneCenter = m_ui->graphicsViewSkeleton->mapToScene( m_ui->graphicsViewSkeleton->viewport()->rect().center() );

	// Detect if the click is in the view.
	QPoint remapped = m_ui->graphicsViewSkeleton->mapFromParent( event->pos() );
	if ( m_ui->graphicsViewSkeleton->rect().contains( remapped ) )
	{
		QPointF mousePoint = m_ui->graphicsViewSkeleton->mapToScene( remapped );

		QPolygonF polyTmp = m_polygonItem->polygon();

		polyTmp.append(mousePoint);

		m_polygonItem->setPolygon(polyTmp);

//		m_scene->addEllipse(mousePoint.x(), mousePoint.y(), 5, 5, QPen ( Qt::red ));


		// m_ui->graphicsViewSkeleton->setScene(m_scene);
	}

	event->accept();
//	m_ui->graphicsViewSkeleton->centerOn(sceneCenter);

}

void SS_GUI::on_pushButtonContinue_pressed()
{
	m_draw = true;
}

void SS_GUI::on_pushButtonCalc_clicked()
{

	SKELETON::Polygon skeletonPoly;
	QPolygonF poly ( m_polygonItem->polygon() );

	std::vector< QLineF > bisectorLines;

	size_t scale = 1E3;

	if ( true ) {
		if ( m_ui->checkBoxDirection->isChecked() )
			for ( size_t i=0; i<poly.size(); ++i ) {
				QPointF pointF ( poly[i].x(), poly[i].y() );
				skeletonPoly << SKELETON::Polygon::Point ( pointF.x()/scale, pointF.y()/scale );
			}
		else
			for ( size_t i=poly.size(); i>0; --i ) {
				QPointF pointF ( poly[i-1].x(), poly[i-1].y() );
				skeletonPoly << SKELETON::Polygon::Point ( pointF.x()/scale, pointF.y()/scale );
			}

		skeletonPoly.findSkeletonLines();
		skeletonPoly.findVertexLines();

		for ( size_t i=0; i< poly.size(); ++i )
			bisectorLines.push_back( QLineF ( skeletonPoly.point(i).m_x*scale,
											  skeletonPoly.point(i).m_y*scale,
											  skeletonPoly.point(i).m_x*scale + skeletonPoly.bisector(i).m_x*10000,
											  skeletonPoly.point(i).m_y*scale + skeletonPoly.bisector(i).m_y*10000 ) );


		for ( IBK::Line line : skeletonPoly.skeletonLines() )
			m_scene->addLine( QLineF ( line.m_p1.m_x*scale, line.m_p1.m_y*scale,
									   line.m_p2.m_x*scale,line.m_p2.m_y*scale ),
							  QPen ( Qt::darkGreen, 2, Qt::DashLine ));
		for ( IBK::Line vertexLine : skeletonPoly.vertexLines() )
			m_scene->addLine( QLineF ( vertexLine.m_p1.m_x*scale, vertexLine.m_p1.m_y*scale,
									   vertexLine.m_p2.m_x*scale, vertexLine.m_p2.m_y*scale ),
							  QPen ( Qt::darkRed, 2, Qt::DashLine ));
//		for ( QLineF lineBisector : bisectorLines )
//			m_scene->addLine( lineBisector, QPen ( Qt::darkYellow, 2, Qt::DashLine ));


		for ( std::vector< SKELETON::Polygon::Point > shrinkedPoly : skeletonPoly.shrinkedPolygons()) {
			QPolygonF polyShrinked;
			for ( SKELETON::Polygon::Point shrinkedPolyPoint : shrinkedPoly ) {
				polyShrinked << QPointF ( shrinkedPolyPoint.m_x*scale, shrinkedPolyPoint.m_y*scale );
			}
			polyShrinked << QPointF ( shrinkedPoly[0].m_x*scale, shrinkedPoly[0].m_y*scale );
			m_scene->addPolygon( polyShrinked, QPen ( Qt::darkYellow, 2, Qt::DashLine ));
		}
	}
}

void SS_GUI::on_Clear_clicked()
{
	m_polygon = m_polygonItem->polygon();
	m_scene->clear();
	m_polygonItem = new QGraphicsPolygonItem;
	m_polygonItem->setPolygon(m_polygon);
	m_scene->addItem(m_polygonItem);
}

void SS_GUI::on_pushButtonClearAll_clicked()
{
	m_scene->clear();
	m_polygon.clear();
	m_polygonItem = new QGraphicsPolygonItem;

	m_scene->addItem(m_polygonItem);
}
