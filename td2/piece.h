#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <QMainWindow>
#include <QWidget>
#include <QDateTime>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QTimerEvent>
#include <QTimer>
#include <ctime>
#include <iostream>

#include "lum.h"
#include "chauf.h"
#include "alarm.h"

using namespace std;


class Piece //: public QWidget
{
   //Q_OBJECT

public:
    Piece();
    Piece(alarm a);
    void restartAlarm();
    void stopAutoCheck();
    ~Piece();
    alarm a;
    //lum l;
    //chauf c;

private:
    //vector<Device> listOfDevice;
};


#endif // PIECE_H
