/***************************************************************************
 *   Copyright (C) 2003 by Matthias H. Hennig                              *
 *   hennig@cn.stir.ac.uk                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include "psthplot.h"
//Added by qt3to4:
#include <QTimerEvent>

//[TO DO] the name of window must be like QwtText("title")
PsthPlot::PsthPlot(double *xd, double *yd, QWidget *parent, const char *name)
  : QwtPlot( parent )
{
  x = xd;
  y = yd;

  dataCurve = new QwtPlotCurve("PSTH");

  // Assign a title
  setTitle("PSTH");
  dataCurve->setRawData(x,y,50);
  dataCurve->attach(this);
  //cPsthData = insertCurve("PSTH");
  dataCurve->setPen(QPen(Qt::blue,2));

  dataCurve->setStyle(QwtPlotCurve::Steps);

  //long mY = insertLineMarker("", QwtPlot::yLeft);
  //setMarkerYPos(mY, 0.0);

  setAxisTitle(QwtPlot::xBottom, "Time/ms");
  setAxisTitle(QwtPlot::yLeft, "Spikes/s");

  setAutoReplot(FALSE);
}

void PsthPlot::setPsthData(double *xd, double *yd, int l)
{
  x = xd;
  y = yd;
  dataCurve->setRawData(x, y, l);

}

void PsthPlot::startDisplay()
{
  currtimer=startTimer(150);
}

void PsthPlot::stopDisplay()
{
       killTimer(currtimer);

}

void PsthPlot::timerEvent(QTimerEvent *)
{
  replot();
}
