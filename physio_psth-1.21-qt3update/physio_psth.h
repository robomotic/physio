/***************************************************************************
 *   Copyright (C) 2003 by Matthias H. Hennig                              *
 *   hennig@cn.stir.ac.uk                                                  *
 *   Copyright (C) 2005 by Bernd Porr                                      *
 *   BerndPorr@f2s.com                                                     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef PHYSIO_PSTH_H
#define PHYSIO_PSTH_H

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <math.h>

#include <qapplication.h>
#include <qmainwindow.h>
#include <qlayout.h> 
#include <qframe.h>
#include <qwidget.h>
#include <qlabel.h>
#include <qgroupbox.h>
#include <qbuttongroup.h>
#include <qlayout.h> 
#include <qsize.h>
#include <qpushbutton.h>
#include <qtextstream.h>
#include <qfile.h>
#include <qfiledialog.h>
#include <qpainter.h>
#include <qprinter.h>
#include <qregexp.h>
#include <qpen.h>

#include <comedilib.h>
#include <fcntl.h>

#include "psthplot.h"
#include "dataplot.h"

// maximal length of the PSTH (for memory alloctaion)
#define MAX_PSTH_LENGTH 5000

// Number of channels. The MAX186 has 8 channels
#define MAX_CHANNELS 8

#define SAMPLING_RATE 8000 // 8kHz

#define FILTER_FREQU 50 // filter out 50Hz noise


class MainWindow : public QWidget
{
  Q_OBJECT
    
  // show the raw serai data here
  DataPlot *RawDataPlot;
  // here the PSTH will be shown
  PsthPlot *MyPsthPlot;
  
  // channel number for the seari device
  int adChannel;
  // length of the PSTH, this is the length on one trial
  int psthLength;
  // bin width for the PSTH
  int psthBinw;
  // treshold for a spike
  int spikeThres;

  // boo, activate/deactivate the psth plot
  int psthOn;

  // for the PSTH 'record mode':
  // numer of repetitions
  int psthNumTrials;
  // bool, indicates active recording mode
  int psthRecordMode;
  // count trials while recording
  int psthActTrial;
  
  // bool, set when a spike is detected and the activity has not
  // gone back to resting potential
  int spikeDetected;
  // spikecounter
  int spikec;
  
  // data, x is time and y is value
  double x[MAX_PSTH_LENGTH], y[MAX_PSTH_LENGTH];
  // PSTH, t is time, p is spike count, psth is spikes/sec
  double t[MAX_PSTH_LENGTH], p[MAX_PSTH_LENGTH], psth[MAX_PSTH_LENGTH];
  // contains all spikes of a trial
  long int spikes[MAX_PSTH_LENGTH];
  
  // serai file desc
  int usbFd;
  // buffer for the serai data
  //short int buffer[16];
  unsigned char buffer[32];
  
  // time counter
  long int time;
  
  // click
  FILE *sounddev;
  char beep;
  char quiet;
  int playSound;
  
  // print the psths
  QPrinter     *printer;
  
  
  int subdevice;
  comedi_cmd *cmd;
  
  /**
   * file descriptor for /dev/comedi0
   **/
  comedi_t *dev;
  unsigned int *chanlist;

  QPushButton *averagePsth;
  QwtCounter *cntBinw;
  QwtCounter *cntSpikeT;
  QPushButton *triggerPsth;

private slots:

  // actions:
  void slotPrint();
  void slotClearPsth();
  void slotTriggerPsth();
  void slotSetChannel(double c);
  void slotSetPsthLength(double l);
  void slotSetPsthBinw(double b);
  void slotSetSpikeThres(double t);
  void slotSavePsth();
  void slotSetNumTrials(double);
  void slotStartPsthRec();
  void slotSoundToggle();
  void slotAveragePsth();

protected:

  /// timer to read out the data
  virtual void timerEvent(QTimerEvent *e);

public:

  MainWindow( QWidget *parent=0, const char *name=0 );
  ~MainWindow();

};

#endif
