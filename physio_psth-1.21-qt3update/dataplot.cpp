/***************************************************************************
 *   Copyright (C) 2003 by Matthias H. Hennig                              *
 *   hennig@cn.stir.ac.uk                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include "dataplot.h"

DataPlot::DataPlot(int initP, 
		   double *xd, double *yd, 
		   QWidget *parent, const char *name)
  : QwtPlot( parent, name )
{
  // Assign a title
  setTitle("Raw Data");

  x = xd;
  y = yd;

  // Insert new curve for raw data
  cRawData = insertCurve("Raw Data");

  setCurvePen(cRawData, QPen(red));
  setCurveRawData(cRawData, x, y, initP);

  long mY = insertLineMarker("", QwtPlot::yLeft);
  setMarkerYPos(mY, 0.0);

  setAxisTitle(QwtPlot::xBottom, "Time/ms");
  setAxisTitle(QwtPlot::yLeft, "A/D Value");
  setAxisScale(QwtPlot::yLeft,0, 3000);

}

void DataPlot::setPsthLength(int l)
{
  psthLength = l;
  setCurveRawData(cRawData, x, y, psthLength);
  replot();
}

