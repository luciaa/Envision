/***********************************************************************************************************************
 * MainView.cpp
 *
 *  Created on: Jan 10, 2011
 *      Author: Dimitar Asenov
 **********************************************************************************************************************/

#include "views/MainView.h"
#include "Scene.h"

#include "Core/headers/global.h"

#include <QtGui/QWheelEvent>
#include <QtGui/QPrinter>
#include <QtSvg/QSvgGenerator>

namespace Visualization {

MainView::MainView(Scene *scene) :
	View(scene, NULL), miniMap(new MiniMap(scene, this)), scaleLevel(SCALING_FACTOR)
{
	setRenderHint(QPainter::Antialiasing);
	setRenderHint(QPainter::TextAntialiasing);

	setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

	setMiniMapSize(MINIMAP_DEFAULT_WIDTH, MINIMAP_DEFAULT_HEIGHT);
}

MainView::~MainView()
{
	SAFE_DELETE(miniMap);
}

void MainView::setMiniMapSize(int width, int height)
{
	if ( miniMap )
	{
		miniMap->resize(width, height);
		miniMap->sceneRectChanged(scene()->sceneRect());
	}
}

bool MainView::event( QEvent *event )
{
	switch (event->type())
	{
		case QEvent::KeyPress :
		{
			QKeyEvent *k = (QKeyEvent *)event;
			keyPressEvent(k);
			if (k->key() == Qt::Key_Backtab || k->key() == Qt::Key_Tab ) event->accept();
			return true;
		}
		break;
		case QEvent::KeyRelease :
		{
			QKeyEvent *k = (QKeyEvent *)event;
			keyReleaseEvent(k);
			if (k->key() == Qt::Key_Backtab || k->key() == Qt::Key_Tab ) event->accept();
			return true;
		}
		break;
		default: return View::event( event );
	}
}

void MainView::resizeEvent(QResizeEvent *event)
{
	View::resizeEvent(event);
	if ( miniMap )
	{
		miniMap->updatePosition();
		miniMap->visibleRectChanged();
	}
}

void MainView::wheelEvent(QWheelEvent *event)
{
	if ( event->delta() > 0 ) scaleLevel--;
	else scaleLevel++;

	if ( scaleLevel <= 0 ) scaleLevel = 1;
	qreal scaleFactor = SCALING_FACTOR / (qreal) scaleLevel;
	setTransform(QTransform::fromScale(scaleFactor, scaleFactor));

	if ( miniMap ) miniMap->visibleRectChanged();
}

void MainView::scrollContentsBy(int dx, int dy)
{
	View::scrollContentsBy(dx, dy);
	if ( miniMap ) miniMap->visibleRectChanged();
}

void MainView::keyPressEvent(QKeyEvent *event)
{
	if ( (event->modifiers() & Qt::ControlModifier || event->modifiers() & Qt::ShiftModifier) && event->key() == Qt::Key_Print)
	{
		event->accept();

		QPrinter printer;
		printer.setOutputFormat(QPrinter::PdfFormat);
		printer.setFullPage(true);
		printer.setResolution(300);

		QSvgGenerator svggen;
		svggen.setResolution(90);

		if (event->modifiers() & Qt::ShiftModifier)
		{
			// Print scene
			printer.setOutputFileName("screenshot-scene.pdf");
			printer.setPaperSize(QSize(scene()->sceneRect().width(), scene()->sceneRect().height()), QPrinter::Point);
			QPainter painter(&printer);
			scene()->render( &painter );

			svggen.setFileName("screenshot-scene.svg");
			svggen.setSize(QSize(scene()->sceneRect().width(), scene()->sceneRect().height()));
			QPainter svgPainter(&svggen);
			scene()->render(&svgPainter);
		}
		else
		{
			// Print view
			printer.setOutputFileName("screenshot-view.pdf");
			printer.setPaperSize(QSize(viewport()->rect().width(), viewport()->rect().height()), QPrinter::Point);
			QPainter painter(&printer);
			render(&painter);

			svggen.setFileName("screenshot-view.svg");
			svggen.setSize(QSize(viewport()->rect().width(), viewport()->rect().height()));
			QPainter svgPainter(&svggen);
			render(&svgPainter);
		}
	}
	else View::keyPressEvent(event);
}

}
