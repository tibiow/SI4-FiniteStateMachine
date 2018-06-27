#ifndef DOMO_H
#define DOMO_H

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
#include <vector>
#include <sstream>
#include <string>
//#include "qscxmlcppdatamodel.h"


#include "piece.h"
#include "secu.h"
#include "lum.h"
#include "alarm.h"
#include "LumManager.h"
#include "chaufManager.h"
#include "chauf.h"
#include "fenetre.h"

using namespace std;



class Domo : public QWidget
{
    Q_OBJECT
    //Q_SCXML_DATAMODEL

public:
    QGridLayout gridLayout;
    QTime* time = nullptr;
    QTimer *updateTimer = nullptr;

    /******************************************sécu**********************************************/
    secu s;
    alarm a_C1;
    alarm a_C2;
    alarm a_L1;
    alarm a_B1;

    /******************************************lumière**********************************************/
    LumManager lumManager_C1;
    LumManager lumManager_C2;
    LumManager lumManager_L1;
    LumManager lumManager_B1;
    lum l_C1;
    lum l_C2;
    lum l_L1;
    lum l_B1;

    /******************************************chauffage**********************************************/

    chaufManager chaufManager_C1;
    chaufManager chaufManager_C2;
    chaufManager chaufManager_L1;
    chaufManager chaufManager_B1;
    chauf c_C1;
    chauf c_C2;
    chauf c_L1;
    chauf c_B1;

    /******************************************window**********************************************/

    fenetre f_C1;
    fenetre f_C2;
    fenetre f_L1;
    fenetre f_B1;



    explicit Domo(QWidget *parent = 0);
    ~Domo();
public slots:
    void updateModel();
    void refreshDisplay();
    int  getConsigne(int startTime, int endTime, int startConsigne, int endConsigne);
    std::string tostr (int x);
private:
    int NB_PIECE =4;
    int TIMEINCREMENT = 1;
    int currentTime = 0;
    int MAX_CHAUFF = 255;
    int MIN_CHAUFF = 0;
    int MAX_LIGHT = 255;
    int MIN_LIGHT = 0;
    bool alarmEnabled =false;


    //Variable Pièce 1
    int currentSegmentLum_C1 = 0;
    int currentSegmentChauff_C1 = 0;
    bool lumAutomatic_C1 = true;
    bool chauffAutomatic_C1 = true;
    bool windowClosed_C1 = true;

    //valeur gestion chauffage
    int chauffageConsigne_C1 = 0;
    int chauffage_C1 = 0;
    int chauffConsigneAuto_C1[5]= {0,15,45,15,0};
    int chauffTimeAuto_C1[5]= {0,15,30,45,60};

    //valeur gestion lumière
    int luminosity_C1 = 0;
    int luminosityConsigne_C1 = 0;
    int lumConsigneAuto_C1[5] = {0,15,45,15,0};
    int lumTimeAuto_C1[5]= {0,15,30,45,60};

    //Variable Pièce 2
    int currentSegmentLum_C2 = 0;
    int currentSegmentChauff_C2 = 0;
    bool lumAutomatic_C2 = true;
    bool chauffAutomatic_C2 = true;
    bool windowClosed_C2 = true;

    //valeur gestion chauffage
    int chauffageConsigne_C2 = 0;
    int chauffage_C2 = 0;
    int chauffConsigneAuto_C2[5]= {0,15,45,15,0};
    int chauffTimeAuto_C2[5]= {0,15,30,45,60};

    //valeur gestion lumière
    int luminosity_C2 = 0;
    int luminosityConsigne_C2 = 0;
    int lumConsigneAuto_C2[5] = {0,15,45,15,0};
    int lumTimeAuto_C2[5]= {0,15,30,45,60};


    //Variable Pièce 3
    int currentSegmentLum_L1 = 0;
    int currentSegmentChauff_L1 = 0;
    bool lumAutomatic_L1 = true;
    bool chauffAutomatic_L1 = true;
    bool windowClosed_L1 = true;

    //valeur gestion chauffage
    int chauffageConsigne_L1 = 0;
    int chauffage_L1 = 0;
    int chauffConsigneAuto_L1[5]= {0,15,45,15,0};
    int chauffTimeAuto_L1[5]= {0,15,30,45,60};

    //valeur gestion lumière
    int luminosity_L1 = 0;
    int luminosityConsigne_L1 = 0;
    int lumConsigneAuto_L1[5] = {0,15,45,15,0};
    int lumTimeAuto_L1[5]= {0,15,30,45,60};


    //Variable Pièce 4
    int currentSegmentLum_B1 = 0;
    int currentSegmentChauff_B1 = 0;
    bool lumAutomatic_B1 = true;
    bool chauffAutomatic_B1 = true;
    bool windowClosed_B1 = true;

    //valeur gestion chauffage
    int chauffageConsigne_B1 = 0;
    int chauffage_B1 = 0;
    int chauffConsigneAuto_B1[5]= {0,15,45,15,0};
    int chauffTimeAuto_B1[5]= {0,15,30,45,60};

    //valeur gestion lumière
    int luminosity_B1 = 0;
    int luminosityConsigne_B1 = 0;
    int lumConsigneAuto_B1[5] = {0,15,45,15,0};
    int lumTimeAuto_B1[5]= {0,15,30,45,60};
    //************************************************IHM Global*******************************************************//
    QLabel timer;
    QPushButton mButton_All;
    QPushButton m_reset_alarm;
    QPushButton onOff_security_Button;

    //IHM Piece 1
    QPushButton onOff_lumiere_Button_C1;
    QPushButton automatic_lumiere_Button_C1;
    QLabel Lum_C1;

    QPushButton onOff_chauff_Button_C1;
    QPushButton automatic_chauf_Button_C1;
    QPushButton increase_chauff_power_C1;
    QPushButton decrease_chauff_power_C1;
    QLabel Chauff_C1;

    QPushButton enable_alarm_C1;
    QPushButton set_Presence_C1;
    QLabel presence_C1;

    QPushButton openClose_window_C1;
    QLabel window_C1;

    //IHM Piece 2
    QPushButton onOff_lumiere_Button_C2;
    QPushButton automatic_lumiere_Button_C2;
    QLabel Lum_C2;

    QPushButton onOff_chauff_Button_C2;
    QPushButton automatic_chauf_Button_C2;
    QPushButton increase_chauff_power_C2;
    QPushButton decrease_chauff_power_C2;
    QLabel Chauff_C2;

    QPushButton enable_alarm_C2;
    QPushButton set_Presence_C2;
    QLabel presence_C2;

    QPushButton openClose_window_C2;
    QLabel window_C2;

    //IHM Piece 3
    QPushButton onOff_lumiere_Button_L1;
    QPushButton automatic_lumiere_Button_L1;
    QLabel Lum_L1;

    QPushButton onOff_chauff_Button_L1;
    QPushButton automatic_chauf_Button_L1;
    QPushButton increase_chauff_power_L1;
    QPushButton decrease_chauff_power_L1;
    QLabel Chauff_L1;

    QPushButton enable_alarm_L1;
    QPushButton set_Presence_L1;
    QLabel presence_L1;

    QPushButton openClose_window_L1;
    QLabel window_L1;

    //IHM Piece 4
    QPushButton onOff_lumiere_Button_B1;
    QPushButton automatic_lumiere_Button_B1;
    QLabel Lum_B1;

    QPushButton onOff_chauff_Button_B1;
    QPushButton automatic_chauf_Button_B1;
    QPushButton increase_chauff_power_B1;
    QPushButton decrease_chauff_power_B1;
    QLabel Chauff_B1;

    QPushButton enable_alarm_B1;
    QPushButton set_Presence_B1;
    QLabel presence_B1;

    QPushButton openClose_window_B1;
    QLabel window_B1;

};

#endif // DOMO_H
