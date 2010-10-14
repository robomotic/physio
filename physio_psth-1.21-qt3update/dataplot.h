/***************************************************************************
 *   Copyright (C) 2003 by Matthias H. Hennig                              *
 *   hennig@cn.stir.ac.uk                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef DATAPLOT_H
#define DATAPLOT_H

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <math.h>

#include <qwt_plot.h>
#include <qwt_math.h>
#include <qwt_counter.h>

/// this plot shows the raw input data (spikes or membrane potential)
class DataPlot : public QwtPlot
{

public:

  DataPlot(int initP, double *x, double *y, QWidget *parent = 0, const char *name=0);
  void setPsthLength(int l);
  
protected:

private:

  double *x, *y;

  // number of data points
  int psthLength;
  // curve handle
  long cRawData;

};

#endif
