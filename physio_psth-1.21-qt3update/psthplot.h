/***************************************************************************
 *   Copyright (C) 2003 by Matthias H. Hennig                              *
 *   hennig@cn.stir.ac.uk                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef PSTHPLOT_H
#define PSTHPLOT_H

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <math.h>

#include <qwt_plot.h>
#include <qwt_math.h>
#include <qwt_counter.h>


/** The PSTH plot widget
*/
class PsthPlot : public QwtPlot
{

  /// pointer to the x and y data
  double *x, *y;
  
  /// PSTH curve
  long cPsthData;

protected:

  /// replot the data regularly
  virtual void timerEvent(QTimerEvent *e);
	
public:
    
  PsthPlot(double *xd, double *yd, QWidget *parent = 0, const char *name=0);
  void setPsthData(double *xd, double *yd, int l);
  void startDisplay();
  void stopDisplay();
  
  void setYaxisLabel(char * l) {
	  setAxisTitle(QwtPlot::yLeft,l);
  }

};

#endif

