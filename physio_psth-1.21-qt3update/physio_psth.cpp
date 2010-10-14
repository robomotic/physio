/***************************************************************************
 *   Copyright (C) 2003 by Matthias H. Hennig                              *
 *   hennig@cn.stir.ac.uk                                                  *
 *   Copyright (C) 2005 by Bernd Porr                                      *
 *   BerndPorr@f2s.com                                                     *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include "physio_psth.h"

class PrintFilter: public QwtPlotPrintFilter
{
public:
  PrintFilter() {};

  virtual QFont font(const QFont &f, Item, int) const
  {
    QFont f2 = f;
    f2.setPointSize(f.pointSize() * 0.75);
    return f2;
  }
};

MainWindow::MainWindow( QWidget *parent, const char *name )
  : QWidget( parent, name )
{
  // initialize comedi
  char filename[] = "/dev/comedi0";
  subdevice = 0;
  int rangeid = 0; // +/- 4V
  int aref = AREF_GROUND;
  int n_chan = MAX_CHANNELS;

  /* open the device */
  dev = comedi_open(filename);
  if(!dev){
    comedi_perror(filename);
    exit(1);
  }

  chanlist=new unsigned int[n_chan];
  /* Set up channel list */
  for(int i=0;i<n_chan;i++){
    chanlist[i]=CR_PACK(i,rangeid,aref);
  }

  cmd=new comedi_cmd;
  //[FIX]: i think this one is expressed in nanoseconds 1e9
  int r = comedi_get_cmd_generic_timed(dev,
                                       subdevice,
                                       cmd,
                                       n_chan,
                                       (int)(1e9/(SAMPLING_RATE/n_chan)));
  if(r<0){
    printf("comedi_get_cmd_generic_timed failed\n");
    exit(-1);
  }

  /* Modify parts of the command */
  cmd->chanlist           = chanlist;
  cmd->chanlist_len       = n_chan;

  cmd->scan_end_arg = n_chan;

  cmd->stop_src=TRIG_NONE;
  cmd->stop_arg=0;

  /* comedi_command_test() tests a command to see if the
   * trigger sources and arguments are valid for the subdevice.
   * If a trigger source is invalid, it will be logically ANDed
   * with valid values (trigger sources are actually bitmasks),
   * which may or may not result in a valid trigger source.
   * If an argument is invalid, it will be adjusted to the
   * nearest valid value.  In this way, for many commands, you
   * can test it multiple times until it passes.  Typically,
   * if you can't get a valid command in two tests, the original
   * command wasn't specified very well. */
  int ret = comedi_command_test(dev,cmd);
  if(ret<0){
    comedi_perror("comedi_command_test");
    exit(-1);
  }
  fprintf(stderr,"first test returned %d\n",ret);

  ret = comedi_command_test(dev,cmd);
  if(ret<0){
    comedi_perror("comedi_command_test");
    exit(-1);
  }
  fprintf(stderr,"second test returned %d\n",ret);
  if(ret!=0){
    fprintf(stderr,"Error preparing command\n");
    exit(-1);
  }

  /* start the command */
  ret=comedi_command(dev,cmd);
  if(ret<0){
    comedi_perror("comedi_command");
    exit(1);
  }


  // defaults
  adChannel = 4;
  psthLength = 1000;
  psthBinw = 20;
  spikeThres = 2500;
  time = 0;
  psthOn = 0;

  psthNumTrials = 10;
  psthRecordMode = 0;

  spikeDetected = 0;
  spikec = 0;

  beep=255;
  quiet=0;
  playSound = 0;

  //  Initialize data for plots
  for (int i = 0; i< MAX_PSTH_LENGTH; i++)
    {
      x[i] = double(i);     // time axis
      y[i] = 0;
      t[i] = double(i)*psthBinw; // psth time axis
      p[i] = 0;
      psth[i] = 0;
      spikes[i] = 0;
    }

  // the gui, straight forward QT/Qwt
  printer = new QPrinter;

  resize(640,420);
  QHBoxLayout *mainLayout = new QHBoxLayout( this, 2, 2 );
  QVBoxLayout *controlLayout = new QVBoxLayout( mainLayout);
  QVBoxLayout *plotLayout = new QVBoxLayout( mainLayout);

  // two plots
  RawDataPlot = new DataPlot(psthLength, &x[0], &y[0], this);
  plotLayout->addWidget(RawDataPlot);
  RawDataPlot->show();
  RawDataPlot->setPsthLength(psthLength);
  //RawDataPlot->setSpikeThres(spikeThres);

  MyPsthPlot = new PsthPlot(&t[0], &psth[0], this);
  plotLayout->addWidget(MyPsthPlot);
  MyPsthPlot->show();

  // all buttons
  // AD group
  QGroupBox *ADcounterGroup = new QButtonGroup( 1, QGroupBox::Horizontal, "A/D Channel", this );
  controlLayout->addWidget( ADcounterGroup );
  ADcounterGroup->setAlignment(Qt::AlignJustify);
  ADcounterGroup->setSizePolicy (QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

  QwtCounter *cntChannel = new QwtCounter(ADcounterGroup);
  cntChannel->setRange(0, MAX_CHANNELS-1, 1);
  cntChannel->setValue(adChannel);
  connect(cntChannel, SIGNAL(valueChanged(double)), SLOT(slotSetChannel(double)));

  QPushButton *toggleSound = new QPushButton(ADcounterGroup);
  toggleSound->setText("Sound on");
  toggleSound->setToggleButton ( TRUE );
  connect(toggleSound, SIGNAL(clicked()), SLOT(slotSoundToggle()));

  // psth functions
  QGroupBox *PSTHfunGroup = new QButtonGroup( 1, QGroupBox::Horizontal, "PSTH functions", this );
  controlLayout->addWidget( PSTHfunGroup );
  PSTHfunGroup->setSizePolicy (QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

  averagePsth = new QPushButton(PSTHfunGroup);
  averagePsth->setText("linear average");
  averagePsth->setToggleButton ( TRUE );
  connect(averagePsth, SIGNAL(clicked()), SLOT(slotAveragePsth()));

  triggerPsth = new QPushButton(PSTHfunGroup);
  triggerPsth->setText("PSTH on");
  triggerPsth->setToggleButton ( TRUE );
  connect(triggerPsth, SIGNAL(clicked()), SLOT(slotTriggerPsth()));

  QPushButton *clearPsth = new QPushButton(PSTHfunGroup);
  clearPsth->setText("clear PSTH");
  connect(clearPsth, SIGNAL(clicked()), SLOT(slotClearPsth()));

  QPushButton *savePsth = new QPushButton(PSTHfunGroup);
  savePsth->setText("save PSTH");
  connect(savePsth, SIGNAL(clicked()), SLOT(slotSavePsth()));

  QPushButton *printPsth = new QPushButton(PSTHfunGroup);
  printPsth->setText("print PSTH");
  connect(printPsth, SIGNAL(clicked()), SLOT(slotPrint()));

  // psth params
  QGroupBox *PSTHcounterGroup = new QButtonGroup( 1, QGroupBox::Horizontal, "PSTH parameters", this );
  controlLayout->addWidget( PSTHcounterGroup );
  PSTHcounterGroup->setSizePolicy (QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

  (void *) new QLabel("PSTH Length", PSTHcounterGroup);
  QwtCounter *cntSLength = new QwtCounter(PSTHcounterGroup);
  cntSLength->setNumButtons(2);
  cntSLength->setIncSteps(QwtCounter::Button1, 10);
  cntSLength->setIncSteps(QwtCounter::Button2, 100);
  cntSLength->setRange(1, MAX_PSTH_LENGTH, 1);
  cntSLength->setValue(psthLength);
  connect(cntSLength, SIGNAL(valueChanged(double)), SLOT(slotSetPsthLength(double)));

  (void *) new QLabel("PSTH Binwidth", PSTHcounterGroup);
  cntBinw = new QwtCounter(PSTHcounterGroup);
  cntBinw->setNumButtons(2);
  cntBinw->setIncSteps(QwtCounter::Button1, 1);
  cntBinw->setIncSteps(QwtCounter::Button2, 10);
  cntBinw->setRange(1, 100, 1);
  cntBinw->setValue(psthBinw);
  connect(cntBinw, SIGNAL(valueChanged(double)), SLOT(slotSetPsthBinw(double)));

  (void *) new QLabel("Spike Threshold", PSTHcounterGroup);
  cntSpikeT = new QwtCounter(PSTHcounterGroup);
  cntSpikeT->setNumButtons(3);
  cntSpikeT->setIncSteps(QwtCounter::Button1, 1);
  cntSpikeT->setIncSteps(QwtCounter::Button2, 10);
  cntSpikeT->setIncSteps(QwtCounter::Button3, 100);
  cntSpikeT->setRange(0, 4095, 1);
  cntSpikeT->setValue(spikeThres);
  connect(cntSpikeT, SIGNAL(valueChanged(double)), SLOT(slotSetSpikeThres(double)));

  // psth recording
  QGroupBox *PSTHrecGroup = new QButtonGroup( 1, QGroupBox::Horizontal, "PSTH recording", this );
  controlLayout->addWidget( PSTHrecGroup );
  PSTHrecGroup->setSizePolicy (QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

  (void *) new QLabel("Number of Trials", PSTHrecGroup);
  QwtCounter *cntTrials = new QwtCounter(PSTHrecGroup);
  cntTrials->setNumButtons(3);
  cntTrials->setIncSteps(QwtCounter::Button1, 1);
  cntTrials->setIncSteps(QwtCounter::Button2, 10);
  cntTrials->setIncSteps(QwtCounter::Button3, 100);
  cntTrials->setRange(0, 9000, 1);
  cntTrials->setValue(psthNumTrials);
  connect(cntTrials, SIGNAL(valueChanged(double)), SLOT(slotSetNumTrials(double)));

  QPushButton *startRecPsthb = new QPushButton(PSTHrecGroup);
  startRecPsthb->setText("start Recording");
  connect(startRecPsthb, SIGNAL(clicked()), SLOT(slotStartPsthRec()));

  // Generate timer event every 50ms
  (void)startTimer(50);

}

MainWindow::~MainWindow()
{
}

void MainWindow::slotPrint()
{
  // print the PSTH plot
  QPrinter printer;

  QString docName = MyPsthPlot->title();
  if ( docName.isEmpty() )
    {
      docName.replace (QRegExp (QString::fromLatin1 ("\n")), tr (" -- "));
      printer.setDocName (docName);
    }

  printer.setOrientation(QPrinter::Landscape);

  if (printer.setup())
    MyPsthPlot->print(printer, PrintFilter());
}

void MainWindow::slotSoundToggle()
{
  if(playSound == 0)
    playSound = 1;
  else
    playSound = 0;
}

void MainWindow::slotStartPsthRec()
{
  for(int i=0; i<psthLength/psthBinw; i++) {
    psth[i] = 0;
    p[i] = 0;
  }
  psthRecordMode = 1;
  psthActTrial = 0;
  psthOn = 1;
  time = 0;
  MyPsthPlot->startDisplay();
}

void MainWindow::slotSetNumTrials(double n)
{
  psthNumTrials = (int) n;
}

void MainWindow::slotSavePsth()
{
  QFileDialog fd(this, "file dialog", TRUE );
  fd.setMode( QFileDialog::AnyFile );
  fd.setFilter( "PSTH Data (*.psth)" );
  fd.setViewMode( QFileDialog::Detail );
  if ( fd.exec() == QDialog::Accepted )
    {
      QString fileName = fd.selectedFile();
      QFile file(fileName);
      file.open(IO_WriteOnly);
      QTextStream ts(&file);
      for(int i=0; i<psthLength/psthBinw; i++) {
	ts << t[i] << "\t" << psth[i] << "\n";
      }
      file.close();
    }
}

void MainWindow::slotClearPsth()
{
  time = 0;
  for(int i=0; i<psthLength/psthBinw; i++) {
    psth[i] = 0;
    p[i] = 0;
  }
  spikeDetected = 0;
  psthActTrial = 0;
  MyPsthPlot->replot();
}

void MainWindow::slotTriggerPsth()
{
  if(psthOn == 0)
    {
      MyPsthPlot->startDisplay();
      psthOn = 1;
      psthActTrial = 0;
      time = 0;
    }
  else
    {
      MyPsthPlot->stopDisplay();
      psthOn = 0;
      psthActTrial = 0;
      spikeDetected = 0;
    }
}

void MainWindow::slotSetChannel(double c)
{
  adChannel = (int)c;
  //RawDataPlot->setChannel(adChannel);
  spikeDetected = 0;
}

void MainWindow::slotSetPsthLength(double l)
{
  psthLength = (int)l;
  RawDataPlot->setPsthLength((int) l);
  time = 1;
  for(int i=0; i<psthLength/psthBinw; i++) {
    psth[i] = 0;
    p[i] = 0;
    t[i] = double(i)*psthBinw;
  }
  spikeDetected = 0;
  psthActTrial = 0;
  time = 0;
  MyPsthPlot->setPsthData(&t[0], &psth[0], (int)(psthLength/psthBinw));
}

void MainWindow::slotSetPsthBinw(double b)
{
  psthBinw = (int)b;
  //RawDataPlot->setPsthBinw((int)b);
  time = 1;
  for(int i=0; i<psthLength/psthBinw; i++) {
    psth[i] = 0;
    p[i] = 0;
    t[i] = double(i)*psthBinw;
  }
  spikeDetected = 0;
  psthActTrial = 0;
  time = 0;
  MyPsthPlot->setPsthData(&t[0], &psth[0], (int)(psthLength/psthBinw));
}

void MainWindow::slotSetSpikeThres(double t)
{
  spikeThres = (int)t;
  //RawDataPlot->setSpikeThres(spikeThres);
  spikeDetected = 0;
}

void MainWindow::slotAveragePsth() {
	if (averagePsth->state()==QButton::On) {
		cntBinw->setEnabled( FALSE );
		cntSpikeT->setEnabled( FALSE );
		MyPsthPlot->setYaxisLabel("Averaged Data");
		triggerPsth->setText("Averaging on");
		psthBinw=1;
		cntBinw->setValue(psthBinw);
	} else {
		cntBinw->setEnabled( TRUE );
		cntSpikeT->setEnabled( TRUE );
		MyPsthPlot->setYaxisLabel("Spikes/s");
		triggerPsth->setText("PSTH on");
	}
}

void MainWindow::timerEvent(QTimerEvent *)
{
  //unsigned char buffer[32];

  while (comedi_get_buffer_contents(dev,subdevice)) {
    if (read(comedi_fileno(dev),buffer,16)==0) {
      printf("Error: end of Aquisition\n");
      exit(1);
    }

    qwtShiftArray(y, MAX_PSTH_LENGTH, 1);
    y[0] = ((sampl_t *)buffer)[adChannel];
    if (averagePsth->state()==QButton::On) {
	    if(psthOn)
		    {
			    p[(int)floor(time%psthLength)] += y[0];
			    if (time) {
				    psth[(int)floor(time%psthLength)] =
					    p[(int)floor(time%psthLength)]/ceil((double)time/psthLength);
			    }
		    }
    } else {
	    if(y[0] > spikeThres && spikeDetected == 0) {
		    if(playSound != 0) {
			    // click once
			    // crashes when artsd is running
			    sounddev = fopen("/dev/dsp","w");
			    fwrite(&beep, 1, 1, sounddev);
			    fwrite(&quiet, 1, 1, sounddev);
			    fclose(sounddev);
		    }
		    if(psthOn) {
			    spikes[spikec%MAX_PSTH_LENGTH] = time;
			    p[(int)floor((time%psthLength)/psthBinw)] += 1;
			    if (time) {
				    psth[(int)floor((time%psthLength)/psthBinw)] = \
					    p[(int)floor((time%psthLength)/psthBinw)]*1000/psthBinw/ceil((double)time/psthLength);
			    }
			    spikeDetected = 1;
			    spikec += 1;
		    }
	    }
	    else if(spikeDetected != 0 && y[0]<spikeThres)
		    spikeDetected = 0;
    }
    
    time++;
    
    if(time%psthLength == 0)
	    psthActTrial += 1;
    
    if(psthRecordMode && psthActTrial == psthNumTrials) {
	    psthRecordMode = 0;
	    psthOn = 0;
	    MyPsthPlot->stopDisplay();
    }
  }
  
  RawDataPlot->replot();
}


