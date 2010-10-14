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

PsthPlot::PsthPlot(double *xd, double *yd, QWidget *parent, const char *name)
  : QwtPlot( parent, name )
{
  x = xd;
  y = yd;

  // Assign a title
  setTitle("PSTH");

  cPsthData = insertCurve("PSTH");

  setCurvePen(cPsthData, QPen(blue, 2));
  setCurveStyle(cPsthData, QwtCurve::Steps);
  setCurveRawData(cPsthData, xd, yd, 50);

  long mY = insertLineMarker("", QwtPlot::yLeft);
  setMarkerYPos(mY, 0.0);

  setAxisTitle(QwtPlot::xBottom, "Time/ms");
  setAxisTitle(QwtPlot::yLeft, "Spikes/s");

  setAutoReplot(FALSE);
}

void PsthPlot::setPsthData(double *xd, double *yd, int l)
{
  x = xd;
  y = yd;
  setCurveRawData(cPsthData, x, y, l);
}

void PsthPlot::startDisplay()
{
  (void)startTimer(150);
}

void PsthPlot::stopDisplay()
{
  (void)killTimers();
}

void PsthPlot::timerEvent(QTimerEvent *)
{
  replot();
}
