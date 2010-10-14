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

//[TO DO] fix name to QwtText
DataPlot::DataPlot(int initP, 
		   double *xd, double *yd, 
		   QWidget *parent, const char *name)
  : QwtPlot( parent)
{

  // Insert new curve for raw data
  dataCurve = new QwtPlotCurve("Raw Data");
  // Assign a title
  setTitle("Raw Data");
  x = xd;
  y = yd;
  //at the beginning they are empty
  for(int i=0;i<initP/2;i++) {
          x[i]=0.0;
          y[i]=0.0;
  }
  dataCurve->setPen(QPen(Qt::red,2));
  dataCurve->setRawData(x,y,initP);

  //long mY = insertLineMarker("", QwtPlot::yLeft);
  //setMarkerYPos(mY, 0.0);

  setAxisTitle(QwtPlot::xBottom, "Time/ms");
  setAxisTitle(QwtPlot::yLeft, "A/D Value");
  setAxisScale(QwtPlot::yLeft,0, 3000);
  dataCurve->attach(this);

}

void DataPlot::setPsthLength(int l)
{
  psthLength = l;
  dataCurve->setRawData(x,y,psthLength);
  replot();
}

