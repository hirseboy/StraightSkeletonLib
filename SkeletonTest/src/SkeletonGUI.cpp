#include "SkeletonGUI.h"
#include "ui_SkeletonGUI.h"

SS_GUI::SS_GUI(QWidget *parent) :
	QWidget(parent),
	m_scene(new QGraphicsScene),
	m_ui(new Ui::SS_GUI)
{
	m_ui->setupUi(this);

}

SS_GUI::~SS_GUI()
{
	delete m_ui;
}

bool SS_GUI::drawPolygons(const std::vector<SKELETON::Polygon> &polys) {

	QPainter *painter;
	QPen penPoly (Qt::black, 1, Qt::SolidLine);
	QPen penEvent (Qt::red, 1, Qt::SolidLine);
	QPen penLine (Qt::blue, 2, Qt::SolidLine);
	std::vector< QPointF > eventPoints;

	double height, width;
	size_t scaleFactor = 100;

	height = m_ui->graphicsViewSkeleton->height();
	width = m_ui->graphicsViewSkeleton->width();

	QPolygonF poly2;

	for ( SKELETON::Polygon poly : polys) {

		if ( poly.points().empty() )
			continue;

		poly2.clear();
		for ( SKELETON::Polygon::Point point : poly.points() )
			poly2 << QPointF ( point.m_x*scaleFactor,
							   height - point.m_y*scaleFactor );

		poly2 << poly2[0];

		for ( SKELETON::Polygon::Event event : poly.events() ) {
			eventPoints.push_back( QPointF ( width - event.m_point.m_x*scaleFactor,
											 height - event.m_point.m_y*scaleFactor ) );
			double rad = 5;
			m_scene->addEllipse(event.m_point.m_x*scaleFactor-rad,
								height - event.m_point.m_y*scaleFactor-rad,
								rad*2.0,
								rad*2.0, penEvent, QBrush(Qt::SolidPattern));
		}
		// break;
		m_scene->addPolygon(poly2, penPoly);

		for ( IBK::Line line : poly.skeletonLines() )
			m_scene->addLine( QLineF (	line.m_p1.m_x*scaleFactor,
										height - line.m_p1.m_y*scaleFactor,
										line.m_p2.m_x*scaleFactor,
										height - line.m_p2.m_y*scaleFactor ), penLine );
	}

	m_ui->graphicsViewSkeleton->setScene(m_scene);

	return true;
}

void SS_GUI::wheelEvent(QWheelEvent *event)
{
	if(event->delta() > 0)
	{
		m_ui->graphicsViewSkeleton->scale(1.05,1.05);
	}
	else
	{
		m_ui->graphicsViewSkeleton->scale(1/1.05,1/1.05);
	}
}

void SS_GUI::on_pushButtonContinue_pressed()
{
	m_draw = true;
}
