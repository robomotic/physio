/***************************************************************************
 *   Copyright (C) 2003 by Matthias H. Hennig                              *
 *   hennig@cn.stir.ac.uk                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#include "physio_psth.h"

int main(int argc, char **argv)
{
  QApplication a(argc, argv);

  MainWindow m;
  m.show();
  a.setMainWidget(&m);
  
  return a.exec();
}
