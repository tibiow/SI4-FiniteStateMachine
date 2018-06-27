#include "domo.h"
#include "ui_domo.h"
//#include <vector>


Domo::Domo(QWidget *parent) :
    QWidget(parent),
    gridLayout(this) ,
    timer("00:00:00,000") ,
    mButton_All("switchOffAllLum"),
    m_reset_alarm("reset_Alarm"),
    onOff_security_Button("enable_alarm"),
    Lum_C1("0"),
    onOff_lumiere_Button_C1("put_lumiere_On"),
    automatic_lumiere_Button_C1("put_lumiere_automatic_Off"),
    onOff_chauff_Button_C1("put_chauff_Off"),
    automatic_chauf_Button_C1("put_chauff_automatic_Off"),
    set_Presence_C1("trigger_presence"),
    openClose_window_C1("open_window"),
    increase_chauff_power_C1("chauff++"),
    decrease_chauff_power_C1("chauff--"),
    Lum_C2("0"),
    onOff_lumiere_Button_C2("put_lumiere_On"),
    automatic_lumiere_Button_C2("put_lumiere_automatic_Off"),
    onOff_chauff_Button_C2("put_chauff_Off"),
    automatic_chauf_Button_C2("put_chauff_automatic_Off"),
    set_Presence_C2("trigger_presence"),
    openClose_window_C2("open_window"),
    increase_chauff_power_C2("chauff++"),
    decrease_chauff_power_C2("chauff--"),
    Lum_L1("0"),
    onOff_lumiere_Button_L1("put_lumiere_On"),
    automatic_lumiere_Button_L1("put_lumiere_automatic_Off"),
    onOff_chauff_Button_L1("put_chauff_Off"),
    automatic_chauf_Button_L1("put_chauff_automatic_Off"),
    set_Presence_L1("trigger_presence"),
    openClose_window_L1("open_window"),
    increase_chauff_power_L1("chauff++"),
    decrease_chauff_power_L1("chauff--"),
    Lum_B1("0"),
    onOff_lumiere_Button_B1("put_lumiere_On"),
    automatic_lumiere_Button_B1("put_lumiere_automatic_Off"),
    onOff_chauff_Button_B1("put_chauff_Off"),
    automatic_chauf_Button_B1("put_chauff_automatic_Off"),
    set_Presence_B1("trigger_presence"),
    openClose_window_B1("open_window"),
    increase_chauff_power_B1("chauff++"),
    decrease_chauff_power_B1("chauff--"),
    Chauff_B1("0")
{

    //**********************************Timer ********************************//
    QFont font("Arial", 24, QFont::Bold);
    QPalette palette = timer.palette();
    palette.setColor(QPalette::WindowText, Qt::blue);
    timer.setPalette(palette);
    timer.setFont(font);
    gridLayout.setAlignment(&timer, Qt::AlignCenter);

    gridLayout.addWidget(&timer, 1, 0 , 1,1);

    time = new QTime();
    updateTimer = new QTimer(this);

    time->start();
    updateTimer->start(1000);
    //connect an event (here the timer timeout) to a handler fonction
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(refreshDisplay()));
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(updateModel()));

    //****************************************Bouton test**************************//
    gridLayout.addWidget(&mButton_All,   6, 4, 1, 1);



    //****************************label global********************************//

    gridLayout.addWidget(&m_reset_alarm,   6, 5, 1, 1);
    gridLayout.addWidget(&onOff_security_Button,   6, 6, 1, 1);

    gridLayout.setAlignment(&m_reset_alarm, Qt::AlignCenter);
    gridLayout.setAlignment(&onOff_security_Button, Qt::AlignCenter);

    connect(&m_reset_alarm, &QAbstractButton::clicked, [this] {
        if(windowClosed_B1 && windowClosed_L1 && windowClosed_C2 && windowClosed_C1){
            s.submitEvent("stopAlarm");
            a_C1.submitEvent("restartAutoCheck");
            a_C2.submitEvent("restartAutoCheck");
            a_L1.submitEvent("restartAutoCheck");
            a_B1.submitEvent("restartAutoCheck");

        }
    } );
    connect(&onOff_security_Button, &QAbstractButton::clicked, [this] {
        if(alarmEnabled){
            s.submitEvent("disableAlarm");
            alarmEnabled=false;
            onOff_security_Button.setText("enable_alarm");
        }
        else{
            s.submitEvent("enableAlarm");
            alarmEnabled=true;
            onOff_security_Button.setText("disable_alarm");
        }

    } );
    //****************************label piece1********************************//

    gridLayout.addWidget(new QLabel("lumière"),   9, 1, 1, 1);
    gridLayout.addWidget(&Lum_C1,   9, 2, 1, 1);
    gridLayout.addWidget(new QLabel("chauffage"),   9, 3, 1, 1);
    gridLayout.addWidget(&Chauff_C1,   9, 4, 1, 1);
    gridLayout.addWidget(&onOff_lumiere_Button_C1,   8, 2, 1, 1);
    gridLayout.addWidget(&automatic_lumiere_Button_C1,   8, 3, 1, 1);
    gridLayout.addWidget(&onOff_chauff_Button_C1,   8, 4, 1, 1);
    gridLayout.addWidget(&automatic_chauf_Button_C1,   8, 5, 1, 1);
    gridLayout.addWidget(&set_Presence_C1,   8, 6, 1, 1);
    gridLayout.addWidget(&presence_C1,   9, 6, 1, 1);
    gridLayout.addWidget(&increase_chauff_power_C1,   8, 9, 1, 1);
    gridLayout.addWidget(&decrease_chauff_power_C1,   8, 10, 1, 1);
    gridLayout.addWidget(&openClose_window_C1,   8, 8, 1, 1);
    gridLayout.addWidget(&window_C1,   9, 8, 1, 1);

    gridLayout.setAlignment(&onOff_lumiere_Button_C1, Qt::AlignCenter);
    gridLayout.setAlignment(&automatic_lumiere_Button_C1, Qt::AlignCenter);
    gridLayout.setAlignment(&onOff_chauff_Button_C1, Qt::AlignCenter);
    gridLayout.setAlignment(&automatic_chauf_Button_C1, Qt::AlignCenter);
    gridLayout.setAlignment(&set_Presence_C1, Qt::AlignCenter);
    gridLayout.setAlignment(&presence_C1, Qt::AlignCenter);
    gridLayout.setAlignment(&increase_chauff_power_C1, Qt::AlignCenter);
    gridLayout.setAlignment(&decrease_chauff_power_C1, Qt::AlignCenter);
    gridLayout.setAlignment(&openClose_window_C1, Qt::AlignCenter);
    gridLayout.setAlignment(&window_C1, Qt::AlignCenter);
    gridLayout.setAlignment(&Lum_C1, Qt::AlignCenter);

    //****************************label piece2********************************//

    gridLayout.addWidget(new QLabel("lumière"),   11, 1, 1, 1);
    gridLayout.addWidget(&Lum_C2,   11, 2, 1, 1);
    gridLayout.addWidget(new QLabel("chauffage"),   11, 3, 1, 1);
    gridLayout.addWidget(&Chauff_C2,   11, 4, 1, 1);
    gridLayout.addWidget(&onOff_lumiere_Button_C2,   10, 2, 1, 1);
    gridLayout.addWidget(&automatic_lumiere_Button_C2,   10, 3, 1, 1);
    gridLayout.addWidget(&onOff_chauff_Button_C2,   10, 4, 1, 1);
    gridLayout.addWidget(&automatic_chauf_Button_C2,   10, 5, 1, 1);
    gridLayout.addWidget(&set_Presence_C2,   10, 6, 1, 1);
    gridLayout.addWidget(&presence_C2,   11, 6, 1, 1);
    gridLayout.addWidget(&increase_chauff_power_C2,   10, 9, 1, 1);
    gridLayout.addWidget(&decrease_chauff_power_C2,   10, 10, 1, 1);
    gridLayout.addWidget(&openClose_window_C2,   10, 8, 1, 1);
    gridLayout.addWidget(&window_C2,   11, 10, 1, 1);

    gridLayout.setAlignment(&onOff_lumiere_Button_C2, Qt::AlignCenter);
    gridLayout.setAlignment(&automatic_lumiere_Button_C2, Qt::AlignCenter);
    gridLayout.setAlignment(&onOff_chauff_Button_C2, Qt::AlignCenter);
    gridLayout.setAlignment(&automatic_chauf_Button_C2, Qt::AlignCenter);
    gridLayout.setAlignment(&set_Presence_C2, Qt::AlignCenter);
    gridLayout.setAlignment(&presence_C2, Qt::AlignCenter);
    gridLayout.setAlignment(&increase_chauff_power_C2, Qt::AlignCenter);
    gridLayout.setAlignment(&decrease_chauff_power_C2, Qt::AlignCenter);
    gridLayout.setAlignment(&openClose_window_C2, Qt::AlignCenter);
    gridLayout.setAlignment(&window_C2, Qt::AlignCenter);
    gridLayout.setAlignment(&Lum_C2, Qt::AlignCenter);

    //****************************label piece3********************************//

    gridLayout.addWidget(new QLabel("lumière"),   13, 1, 1, 1);
    gridLayout.addWidget(&Lum_L1,   13, 2, 1, 1);
    gridLayout.addWidget(new QLabel("chauffage"),   13, 3, 1, 1);
    gridLayout.addWidget(&Chauff_L1,   13, 4, 1, 1);
    gridLayout.addWidget(&onOff_lumiere_Button_L1,   12, 2, 1, 1);
    gridLayout.addWidget(&automatic_lumiere_Button_L1,   12, 3, 1, 1);
    gridLayout.addWidget(&onOff_chauff_Button_L1,   12, 4, 1, 1);
    gridLayout.addWidget(&automatic_chauf_Button_L1,   12, 5, 1, 1);
    gridLayout.addWidget(&set_Presence_L1,   12, 6, 1, 1);
    gridLayout.addWidget(&presence_L1,   13, 6, 1, 1);
    gridLayout.addWidget(&increase_chauff_power_L1,   12, 9, 1, 1);
    gridLayout.addWidget(&decrease_chauff_power_L1,   12, 10, 1, 1);
    gridLayout.addWidget(&openClose_window_L1,   12, 8, 1, 1);
    gridLayout.addWidget(&window_L1,   13, 12, 1, 1);

    gridLayout.setAlignment(&onOff_lumiere_Button_L1, Qt::AlignCenter);
    gridLayout.setAlignment(&automatic_lumiere_Button_L1, Qt::AlignCenter);
    gridLayout.setAlignment(&onOff_chauff_Button_L1, Qt::AlignCenter);
    gridLayout.setAlignment(&automatic_chauf_Button_L1, Qt::AlignCenter);
    gridLayout.setAlignment(&set_Presence_L1, Qt::AlignCenter);
    gridLayout.setAlignment(&presence_L1, Qt::AlignCenter);
    gridLayout.setAlignment(&increase_chauff_power_L1, Qt::AlignCenter);
    gridLayout.setAlignment(&decrease_chauff_power_L1, Qt::AlignCenter);
    gridLayout.setAlignment(&openClose_window_L1, Qt::AlignCenter);
    gridLayout.setAlignment(&window_L1, Qt::AlignCenter);
    gridLayout.setAlignment(&Lum_L1, Qt::AlignCenter);

    //****************************label piece4********************************//

    gridLayout.addWidget(new QLabel("lumière"),   15, 1, 1, 1);
    gridLayout.addWidget(&Lum_B1,   15, 2, 1, 1);
    gridLayout.addWidget(new QLabel("chauffage"),   15, 3, 1, 1);
    gridLayout.addWidget(&Chauff_B1,   15, 4, 1, 1);
    gridLayout.addWidget(&onOff_lumiere_Button_B1,   14, 2, 1, 1);
    gridLayout.addWidget(&automatic_lumiere_Button_B1,   14, 3, 1, 1);
    gridLayout.addWidget(&onOff_chauff_Button_B1,   14, 4, 1, 1);
    gridLayout.addWidget(&automatic_chauf_Button_B1,   14, 5, 1, 1);
    gridLayout.addWidget(&set_Presence_B1,   14, 6, 1, 1);
    gridLayout.addWidget(&presence_B1,   15, 6, 1, 1);
    gridLayout.addWidget(&increase_chauff_power_B1,   14, 9, 1, 1);
    gridLayout.addWidget(&decrease_chauff_power_B1,   14, 10, 1, 1);
    gridLayout.addWidget(&openClose_window_B1,   14, 8, 1, 1);
    gridLayout.addWidget(&window_B1,   15, 5, 1, 1);

    gridLayout.setAlignment(&onOff_lumiere_Button_B1, Qt::AlignCenter);
    gridLayout.setAlignment(&automatic_lumiere_Button_B1, Qt::AlignCenter);
    gridLayout.setAlignment(&onOff_chauff_Button_B1, Qt::AlignCenter);
    gridLayout.setAlignment(&automatic_chauf_Button_B1, Qt::AlignCenter);
    gridLayout.setAlignment(&set_Presence_B1, Qt::AlignCenter);
    gridLayout.setAlignment(&presence_B1, Qt::AlignCenter);
    gridLayout.setAlignment(&increase_chauff_power_B1, Qt::AlignCenter);
    gridLayout.setAlignment(&decrease_chauff_power_B1, Qt::AlignCenter);
    gridLayout.setAlignment(&openClose_window_B1, Qt::AlignCenter);
    gridLayout.setAlignment(&window_B1, Qt::AlignCenter);
    gridLayout.setAlignment(&Lum_B1, Qt::AlignCenter);

    //Connect Button Pièce 1

    connect(&automatic_lumiere_Button_C1, &QAbstractButton::clicked, [this] {
        if(lumAutomatic_C1){
            lumManager_C1.submitEvent("stopAutomaticLum");
            lumAutomatic_C1 = false;
            automatic_lumiere_Button_C1.setText("put_lumiere_automatic_On");
        }
        else{
            lumManager_C1.submitEvent("startAutomaticLum");
            lumAutomatic_C1 = true;
            automatic_lumiere_Button_C1.setText("put_lumiere_automatic_Off");
        }
    } );
    connect(&onOff_lumiere_Button_C1, &QAbstractButton::clicked, [this] {lumManager_C1.submitEvent("toggleLight");}) ;
    connect(&onOff_chauff_Button_C1, &QAbstractButton::clicked, [this] {chaufManager_C1.submitEvent("toggleChauff");} );
    connect(&automatic_chauf_Button_C1, &QAbstractButton::clicked, [this] {
        if(chauffAutomatic_C1){
            chaufManager_C1.submitEvent("stopAutomaticChauff");
            chauffAutomatic_C1 = false;
            automatic_chauf_Button_C1.setText("put_chauff_automatic_On");
        }
        else{
            chaufManager_C1.submitEvent("startAutomaticChauff");
            chauffAutomatic_C1 = true;
            automatic_chauf_Button_C1.setText("put_chauff_automatic_Off");
        }

    } );
    connect(&increase_chauff_power_C1, &QAbstractButton::clicked, [this] {chauffageConsigne_C1++;} );
    connect(&decrease_chauff_power_C1, &QAbstractButton::clicked, [this] {chauffageConsigne_C1--;} );

    connect(&set_Presence_C1, &QAbstractButton::clicked, [this] {if(alarmEnabled)a_C1.submitEvent("stopAutoCheck");} );
    connect(&openClose_window_C1, &QAbstractButton::clicked, [this] {
        if(windowClosed_C1){
            f_C1.submitEvent("openWindow");
            openClose_window_C1.setText("close_window");
            windowClosed_C1=false;
        }
        else{
            f_C1.submitEvent("closeWindow");
            openClose_window_C1.setText("open_window");
            windowClosed_C1=true;
        }
    } );

    //Connect Button Pièce 2

    connect(&automatic_lumiere_Button_C2, &QAbstractButton::clicked, [this] {
        if(lumAutomatic_C2){
            lumManager_C2.submitEvent("stopAutomaticLum");
            lumAutomatic_C2 = false;
            automatic_lumiere_Button_C2.setText("put_lumiere_automatic_On");
        }
        else{
            lumManager_C2.submitEvent("startAutomaticLum");
            lumAutomatic_C2 = true;
            automatic_lumiere_Button_C2.setText("put_lumiere_automatic_Off");
        }
    } );
    connect(&onOff_lumiere_Button_C2, &QAbstractButton::clicked, [this] {lumManager_C2.submitEvent("toggleLight");}) ;
    connect(&onOff_chauff_Button_C2, &QAbstractButton::clicked, [this] {chaufManager_C2.submitEvent("toggleChauff");} );
    connect(&automatic_chauf_Button_C2, &QAbstractButton::clicked, [this] {
        if(chauffAutomatic_C2){
            chaufManager_C2.submitEvent("stopAutomaticChauff");
            chauffAutomatic_C2 = false;
            automatic_chauf_Button_C2.setText("put_chauff_automatic_On");
        }
        else{
            chaufManager_C2.submitEvent("startAutomaticChauff");
            chauffAutomatic_C2 = true;
            automatic_chauf_Button_C2.setText("put_chauff_automatic_Off");
        }

    } );
    connect(&increase_chauff_power_C2, &QAbstractButton::clicked, [this] {chauffageConsigne_C2++;} );
    connect(&decrease_chauff_power_C2, &QAbstractButton::clicked, [this] {chauffageConsigne_C2--;} );

    connect(&set_Presence_C2, &QAbstractButton::clicked, [this] {if(alarmEnabled)a_C2.submitEvent("stopAutoCheck");} );
    connect(&openClose_window_C2, &QAbstractButton::clicked, [this] {
        if(windowClosed_C2){
            f_C2.submitEvent("openWindow");
            openClose_window_C2.setText("close_window");
            windowClosed_C2=false;
        }
        else{
            f_C2.submitEvent("closeWindow");
            openClose_window_C2.setText("open_window");
            windowClosed_C2=true;
        }
    } );

   //Connect Button Pièce 3

    connect(&automatic_lumiere_Button_L1, &QAbstractButton::clicked, [this] {
        if(lumAutomatic_L1){
            lumManager_L1.submitEvent("stopAutomaticLum");
            lumAutomatic_L1 = false;
            automatic_lumiere_Button_L1.setText("put_lumiere_automatic_On");
        }
        else{
            lumManager_L1.submitEvent("startAutomaticLum");
            lumAutomatic_L1 = true;
            automatic_lumiere_Button_L1.setText("put_lumiere_automatic_Off");
        }
    } );
    connect(&onOff_lumiere_Button_L1, &QAbstractButton::clicked, [this] {lumManager_L1.submitEvent("toggleLight");}) ;
    connect(&onOff_chauff_Button_L1, &QAbstractButton::clicked, [this] {chaufManager_L1.submitEvent("toggleChauff");} );
    connect(&automatic_chauf_Button_L1, &QAbstractButton::clicked, [this] {
        if(chauffAutomatic_L1){
            chaufManager_L1.submitEvent("stopAutomaticChauff");
            chauffAutomatic_L1 = false;
            automatic_chauf_Button_L1.setText("put_chauff_automatic_On");
        }
        else{
            chaufManager_L1.submitEvent("startAutomaticChauff");
            chauffAutomatic_L1 = true;
            automatic_chauf_Button_L1.setText("put_chauff_automatic_Off");
        }

    } );
    connect(&increase_chauff_power_L1, &QAbstractButton::clicked, [this] {chauffageConsigne_L1++;} );
    connect(&decrease_chauff_power_L1, &QAbstractButton::clicked, [this] {chauffageConsigne_L1--;} );

    connect(&set_Presence_L1, &QAbstractButton::clicked, [this] {if(alarmEnabled)a_L1.submitEvent("stopAutoCheck");} );
    connect(&openClose_window_L1, &QAbstractButton::clicked, [this] {
        if(windowClosed_L1){
            f_L1.submitEvent("openWindow");
            openClose_window_L1.setText("close_window");
            windowClosed_L1=false;
        }
        else{
            f_L1.submitEvent("closeWindow");
            openClose_window_L1.setText("open_window");
            windowClosed_L1=true;
        }
    } );

   //Connect Button Pièce 4

    connect(&automatic_lumiere_Button_B1, &QAbstractButton::clicked, [this] {
        if(lumAutomatic_B1){
            lumManager_B1.submitEvent("stopAutomaticLum");
            lumAutomatic_B1 = false;
            automatic_lumiere_Button_B1.setText("put_lumiere_automatic_On");
        }
        else{
            lumManager_B1.submitEvent("startAutomaticLum");
            lumAutomatic_B1 = true;
            automatic_lumiere_Button_B1.setText("put_lumiere_automatic_Off");
        }
    } );
    connect(&onOff_lumiere_Button_B1, &QAbstractButton::clicked, [this] {lumManager_B1.submitEvent("toggleLight");}) ;
    connect(&onOff_chauff_Button_B1, &QAbstractButton::clicked, [this] {chaufManager_B1.submitEvent("toggleChauff");} );
    connect(&automatic_chauf_Button_B1, &QAbstractButton::clicked, [this] {
        if(chauffAutomatic_B1){
            chaufManager_B1.submitEvent("stopAutomaticChauff");
            chauffAutomatic_B1 = false;
            automatic_chauf_Button_B1.setText("put_chauff_automatic_On");
        }
        else{
            chaufManager_B1.submitEvent("startAutomaticChauff");
            chauffAutomatic_B1 = true;
            automatic_chauf_Button_B1.setText("put_chauff_automatic_Off");
        }

    } );
    connect(&increase_chauff_power_B1, &QAbstractButton::clicked, [this] {chauffageConsigne_B1++;} );
    connect(&decrease_chauff_power_B1, &QAbstractButton::clicked, [this] {chauffageConsigne_B1--;} );

    connect(&set_Presence_B1, &QAbstractButton::clicked, [this] {if(alarmEnabled)a_B1.submitEvent("stopAutoCheck");} );
    connect(&openClose_window_B1, &QAbstractButton::clicked, [this] {
        if(windowClosed_B1){
            f_B1.submitEvent("openWindow");
            openClose_window_B1.setText("close_window");
            windowClosed_B1=false;
        }
        else{
            f_B1.submitEvent("closeWindow");
            openClose_window_B1.setText("open_window");
            windowClosed_B1=true;
        }
    } );


    //********************************************Piece1_domotique*******************************************************//

    //********************************************Lumiere*******************************************************//

    //******************Pièce_C1
    l_C1.start();
    lumManager_C1.start();

    lumManager_C1.connectToEvent(QStringLiteral("refreshLumValue"), this,[this](const QScxmlEvent &event){
        //cout<<"refreshLumValue"<<endl;
        if(luminosity_C1<luminosityConsigne_C1){
            l_C1.submitEvent("LumIsUpper");
        }
        else if(luminosity_C1>luminosityConsigne_C1){
            l_C1.submitEvent("LumIsLower");
        }
    });

    lumManager_C1.connectToEvent(QStringLiteral("updateLumConsigne"), this,[this](const QScxmlEvent &event){
        luminosityConsigne_C1=getConsigne(lumTimeAuto_C1[currentSegmentLum_C1],lumTimeAuto_C1[currentSegmentLum_C1+1],lumConsigneAuto_C1[currentSegmentLum_C1],lumConsigneAuto_C1[currentSegmentLum_C1+1]);
    });

    lumManager_C1.connectToEvent(QStringLiteral("maxPowerLight"), this,[this](const QScxmlEvent &event){
        luminosityConsigne_C1 = MAX_LIGHT;
    });

    lumManager_C1.connectToEvent(QStringLiteral("minPowerLight"), this,[this](const QScxmlEvent &event){
        luminosityConsigne_C1 = MIN_LIGHT;
        //cout<<luminosityConsigne_C1<<endl;
    });


    l_C1.connectToEvent(QStringLiteral("lightDown"), this,[this](const QScxmlEvent &event){
        //cout<<"lightDown"<<endl;
        if(luminosity_C1>MIN_LIGHT){
            luminosity_C1--;
            lumManager_C1.submitEvent("refreshLumValue");
        }
    });

    l_C1.connectToEvent(QStringLiteral("lightUp"), this,[this](const QScxmlEvent &event){
        //cout<<"lightUp"<<endl;
        if(luminosity_C1<MAX_LIGHT){
            luminosity_C1++;
            lumManager_C1.submitEvent("refreshLumValue");
        }
    });

    //******************Pièce_C2

    l_C2.start();
    lumManager_C2.start();

    lumManager_C2.connectToEvent(QStringLiteral("refreshLumValue"), this,[this](const QScxmlEvent &event){
        //cout<<"refreshLumValue"<<endl;
        if(luminosity_C2<luminosityConsigne_C2){
            l_C2.submitEvent("LumIsUpper");
        }
        else if(luminosity_C2>luminosityConsigne_C2){
            l_C2.submitEvent("LumIsLower");
        }
    });

    lumManager_C2.connectToEvent(QStringLiteral("updateLumConsigne"), this,[this](const QScxmlEvent &event){
        luminosityConsigne_C2=getConsigne(lumTimeAuto_C2[currentSegmentLum_C2],lumTimeAuto_C2[currentSegmentLum_C2+1],lumConsigneAuto_C2[currentSegmentLum_C2],lumConsigneAuto_C2[currentSegmentLum_C2+1]);
    });

    lumManager_C2.connectToEvent(QStringLiteral("maxPowerLight"), this,[this](const QScxmlEvent &event){
        luminosityConsigne_C2 = MAX_LIGHT;
    });

    lumManager_C2.connectToEvent(QStringLiteral("minPowerLight"), this,[this](const QScxmlEvent &event){
        luminosityConsigne_C2 = MIN_LIGHT;
        //cout<<luminosityConsigne_C2<<endl;
    });


    l_C2.connectToEvent(QStringLiteral("lightDown"), this,[this](const QScxmlEvent &event){
        //cout<<"lightDown"<<endl;
        if(luminosity_C2>MIN_LIGHT){
            luminosity_C2--;
            lumManager_C2.submitEvent("refreshLumValue");
        }
    });

    l_C2.connectToEvent(QStringLiteral("lightUp"), this,[this](const QScxmlEvent &event){
        //cout<<"lightUp"<<endl;
        if(luminosity_C2<MAX_LIGHT){
            luminosity_C2++;
            lumManager_C2.submitEvent("refreshLumValue");
        }
    });

    //******************Pièce_L1

    l_L1.start();
    lumManager_L1.start();

    lumManager_L1.connectToEvent(QStringLiteral("refreshLumValue"), this,[this](const QScxmlEvent &event){
        //cout<<"refreshLumValue"<<endl;
        if(luminosity_L1<luminosityConsigne_L1){
            l_L1.submitEvent("LumIsUpper");
        }
        else if(luminosity_L1>luminosityConsigne_L1){
            l_L1.submitEvent("LumIsLower");
        }
    });

    lumManager_L1.connectToEvent(QStringLiteral("updateLumConsigne"), this,[this](const QScxmlEvent &event){
        luminosityConsigne_L1=getConsigne(lumTimeAuto_L1[currentSegmentLum_L1],lumTimeAuto_L1[currentSegmentLum_L1+1],lumConsigneAuto_L1[currentSegmentLum_L1],lumConsigneAuto_L1[currentSegmentLum_L1+1]);
    });

    lumManager_L1.connectToEvent(QStringLiteral("maxPowerLight"), this,[this](const QScxmlEvent &event){
        luminosityConsigne_L1 = MAX_LIGHT;
    });

    lumManager_L1.connectToEvent(QStringLiteral("minPowerLight"), this,[this](const QScxmlEvent &event){
        luminosityConsigne_L1 = MIN_LIGHT;
        //cout<<luminosityConsigne_L1<<endl;
    });


    l_L1.connectToEvent(QStringLiteral("lightDown"), this,[this](const QScxmlEvent &event){
        //cout<<"lightDown"<<endl;
        if(luminosity_L1>MIN_LIGHT){
            luminosity_L1--;
            lumManager_L1.submitEvent("refreshLumValue");
        }
    });

    l_L1.connectToEvent(QStringLiteral("lightUp"), this,[this](const QScxmlEvent &event){
        //cout<<"lightUp"<<endl;
        if(luminosity_L1<MAX_LIGHT){
            luminosity_L1++;
            lumManager_L1.submitEvent("refreshLumValue");
        }
    });

    //******************Pièce_B1

    l_B1.start();
    lumManager_B1.start();

    lumManager_B1.connectToEvent(QStringLiteral("refreshLumValue"), this,[this](const QScxmlEvent &event){
        //cout<<"refreshLumValue"<<endl;
        if(luminosity_B1<luminosityConsigne_B1){
            l_B1.submitEvent("LumIsUpper");
        }
        else if(luminosity_B1>luminosityConsigne_B1){
            l_B1.submitEvent("LumIsLower");
        }
    });

    lumManager_B1.connectToEvent(QStringLiteral("updateLumConsigne"), this,[this](const QScxmlEvent &event){
        luminosityConsigne_B1=getConsigne(lumTimeAuto_B1[currentSegmentLum_B1],lumTimeAuto_B1[currentSegmentLum_B1+1],lumConsigneAuto_B1[currentSegmentLum_B1],lumConsigneAuto_B1[currentSegmentLum_B1+1]);
    });

    lumManager_B1.connectToEvent(QStringLiteral("maxPowerLight"), this,[this](const QScxmlEvent &event){
        luminosityConsigne_B1 = MAX_LIGHT;
    });

    lumManager_B1.connectToEvent(QStringLiteral("minPowerLight"), this,[this](const QScxmlEvent &event){
        luminosityConsigne_B1 = MIN_LIGHT;
        //cout<<luminosityConsigne_B1<<endl;
    });


    l_B1.connectToEvent(QStringLiteral("lightDown"), this,[this](const QScxmlEvent &event){
        //cout<<"lightDown"<<endl;
        if(luminosity_B1>MIN_LIGHT){
            luminosity_B1--;
            lumManager_B1.submitEvent("refreshLumValue");
        }
    });

    l_B1.connectToEvent(QStringLiteral("lightUp"), this,[this](const QScxmlEvent &event){
        //cout<<"lightUp"<<endl;
        if(luminosity_B1<MAX_LIGHT){
            luminosity_B1++;
            lumManager_B1.submitEvent("refreshLumValue");
        }
    });

    connect(&mButton_All, &QAbstractButton::clicked, [this] {
        lumManager_C1.submitEvent("stopAutomaticLum"); lumManager_C1.submitEvent("toggleLight");
        lumManager_C2.submitEvent("stopAutomaticLum"); lumManager_C2.submitEvent("toggleLight");
        lumManager_L1.submitEvent("stopAutomaticLum"); lumManager_L1.submitEvent("toggleLight");
        lumManager_B1.submitEvent("stopAutomaticLum"); lumManager_B1.submitEvent("toggleLight");
    });

    //********************************************Chauffage*******************************************************//


    //****************** Pièce_C1

    c_C1.start();
    chaufManager_C1.start();

    chaufManager_C1.connectToEvent(QStringLiteral("refreshChauffValue"), this,[this](const QScxmlEvent &event){
        if(chauffage_C1<chauffageConsigne_C1){
            c_C1.submitEvent("chauffIsUpper");
        }
        else if(chauffage_C1>chauffageConsigne_C1){
            c_C1.submitEvent("chauffIsLower");
        }

    });

    chaufManager_C1.connectToEvent(QStringLiteral("stopChauffModel"), this,[this](const QScxmlEvent &event){
        chauffAutomatic_C1 = false;
    });

    chaufManager_C1.connectToEvent(QStringLiteral("updateChauffConsigne"), this,[this](const QScxmlEvent &event){
        chauffageConsigne_C1=getConsigne(chauffTimeAuto_C1[currentSegmentChauff_C1],chauffTimeAuto_C1[currentSegmentChauff_C1+1],chauffConsigneAuto_C1[currentSegmentChauff_C1],chauffConsigneAuto_C1[currentSegmentChauff_C1+1]);
        chauffAutomatic_C1 = true;
    });


    chaufManager_C1.connectToEvent(QStringLiteral("minPowerChauff"), this,[this](const QScxmlEvent &event){
        chauffageConsigne_C1 = MIN_CHAUFF;
        //cout<<chauffageConsigne_C1<<endl;
    });


    c_C1.connectToEvent(QStringLiteral("chauffDown"), this,[this](const QScxmlEvent &event){
        //cout<<"lightDown"<<endl;
        if(chauffage_C1>MIN_CHAUFF){
            chauffage_C1--;
            chaufManager_C1.submitEvent("refreshChauffValue");
        }
    });

    c_C1.connectToEvent(QStringLiteral("chauffUp"), this,[this](const QScxmlEvent &event){
        //cout<<"lightUp"<<endl;
        if(chauffage_C1<MAX_CHAUFF){
            chauffage_C1++;
            chaufManager_C1.submitEvent("refreshChauffValue");
        }
    });

    //****************** Pièce_C2

    c_C2.start();
    chaufManager_C2.start();

    chaufManager_C2.connectToEvent(QStringLiteral("refreshChauffValue"), this,[this](const QScxmlEvent &event){
        if(chauffage_C2<chauffageConsigne_C2){
            c_C2.submitEvent("chauffIsUpper");
        }
        else if(chauffage_C2>chauffageConsigne_C2){
            c_C2.submitEvent("chauffIsLower");
        }

    });

    chaufManager_C2.connectToEvent(QStringLiteral("stopChauffModel"), this,[this](const QScxmlEvent &event){
        chauffAutomatic_C2 = false;
    });

    chaufManager_C2.connectToEvent(QStringLiteral("updateChauffConsigne"), this,[this](const QScxmlEvent &event){
        chauffageConsigne_C2=getConsigne(chauffTimeAuto_C2[currentSegmentChauff_C2],chauffTimeAuto_C2[currentSegmentChauff_C2+1],chauffConsigneAuto_C2[currentSegmentChauff_C2],chauffConsigneAuto_C2[currentSegmentChauff_C2+1]);
        chauffAutomatic_C2 = true;
    });

    chaufManager_C2.connectToEvent(QStringLiteral("maxPowerChauff"), this,[this](const QScxmlEvent &event){
        chauffageConsigne_C2 = MAX_CHAUFF;
    });

    chaufManager_C2.connectToEvent(QStringLiteral("minPowerChauff"), this,[this](const QScxmlEvent &event){
        chauffageConsigne_C2 = MIN_CHAUFF;
        //cout<<chauffageConsigne_C2<<endl;
    });


    c_C2.connectToEvent(QStringLiteral("chauffDown"), this,[this](const QScxmlEvent &event){
        //cout<<"lightDown"<<endl;
        if(chauffage_C2>MIN_CHAUFF){
            chauffage_C2--;
            chaufManager_C2.submitEvent("refreshChauffValue");
        }
    });

    c_C2.connectToEvent(QStringLiteral("chauffUp"), this,[this](const QScxmlEvent &event){
        //cout<<"lightUp"<<endl;
        if(chauffage_C2<MAX_CHAUFF){
            chauffage_C2++;
            chaufManager_C2.submitEvent("refreshChauffValue");
        }
    });

    //****************** Pièce_L1

    c_L1.start();
    chaufManager_L1.start();

    chaufManager_L1.connectToEvent(QStringLiteral("refreshChauffValue"), this,[this](const QScxmlEvent &event){
        if(chauffage_L1<chauffageConsigne_L1){
            c_L1.submitEvent("chauffIsUpper");
        }
        else if(chauffage_L1>chauffageConsigne_L1){
            c_L1.submitEvent("chauffIsLower");
        }

    });

    chaufManager_L1.connectToEvent(QStringLiteral("stopChauffModel"), this,[this](const QScxmlEvent &event){
        chauffAutomatic_L1 = false;
    });

    chaufManager_L1.connectToEvent(QStringLiteral("updateChauffConsigne"), this,[this](const QScxmlEvent &event){
        chauffageConsigne_L1=getConsigne(chauffTimeAuto_L1[currentSegmentChauff_L1],chauffTimeAuto_L1[currentSegmentChauff_L1+1],chauffConsigneAuto_L1[currentSegmentChauff_L1],chauffConsigneAuto_L1[currentSegmentChauff_L1+1]);
        chauffAutomatic_L1 = true;
    });

    chaufManager_L1.connectToEvent(QStringLiteral("maxPowerChauff"), this,[this](const QScxmlEvent &event){
        chauffageConsigne_L1 = MAX_CHAUFF;
    });

    chaufManager_L1.connectToEvent(QStringLiteral("minPowerChauff"), this,[this](const QScxmlEvent &event){
        chauffageConsigne_L1 = MIN_CHAUFF;
        //cout<<chauffageConsigne_L1<<endl;
    });


    c_L1.connectToEvent(QStringLiteral("chauffDown"), this,[this](const QScxmlEvent &event){
        //cout<<"lightDown"<<endl;
        if(chauffage_L1>MIN_CHAUFF){
            chauffage_L1--;
            chaufManager_L1.submitEvent("refreshChauffValue");
        }
    });

    c_L1.connectToEvent(QStringLiteral("chauffUp"), this,[this](const QScxmlEvent &event){
        //cout<<"lightUp"<<endl;
        if(chauffage_L1<MAX_CHAUFF){
            chauffage_L1++;
            chaufManager_L1.submitEvent("refreshChauffValue");
        }
    });

    //****************** Pièce_B1

    c_B1.start();
    chaufManager_B1.start();

    chaufManager_B1.connectToEvent(QStringLiteral("refreshChauffValue"), this,[this](const QScxmlEvent &event){
        if(chauffage_B1<chauffageConsigne_B1){
            c_B1.submitEvent("chauffIsUpper");
        }
        else if(chauffage_B1>chauffageConsigne_B1){
            c_B1.submitEvent("chauffIsLower");
        }

    });

    chaufManager_B1.connectToEvent(QStringLiteral("stopChauffModel"), this,[this](const QScxmlEvent &event){
        chauffAutomatic_B1 = false;
    });

    chaufManager_B1.connectToEvent(QStringLiteral("updateChauffConsigne"), this,[this](const QScxmlEvent &event){
        chauffageConsigne_B1=getConsigne(chauffTimeAuto_B1[currentSegmentChauff_B1],chauffTimeAuto_B1[currentSegmentChauff_B1+1],chauffConsigneAuto_B1[currentSegmentChauff_B1],chauffConsigneAuto_B1[currentSegmentChauff_B1+1]);
        chauffAutomatic_B1 = true;
    });

    chaufManager_B1.connectToEvent(QStringLiteral("maxPowerChauff"), this,[this](const QScxmlEvent &event){
        chauffageConsigne_B1 = MAX_CHAUFF;
    });

    chaufManager_B1.connectToEvent(QStringLiteral("minPowerChauff"), this,[this](const QScxmlEvent &event){
        chauffageConsigne_B1 = MIN_CHAUFF;
        //cout<<chauffageConsigne_B1<<endl;
    });


    c_B1.connectToEvent(QStringLiteral("chauffDown"), this,[this](const QScxmlEvent &event){
        //cout<<"lightDown"<<endl;
        if(chauffage_B1>MIN_CHAUFF){
            chauffage_B1--;
            chaufManager_B1.submitEvent("refreshChauffValue");
        }
    });

    c_B1.connectToEvent(QStringLiteral("chauffUp"), this,[this](const QScxmlEvent &event){
        //cout<<"lightUp"<<endl;
        if(chauffage_B1<MAX_CHAUFF){
            chauffage_B1++;
            chaufManager_B1.submitEvent("refreshChauffValue");
        }
    });


    //************************************************Alarm*******************************************************//

    //connect to Button

    s.start();
    a_C1.start();
    a_C2.start();
    a_L1.start();
    a_B1.start();

    s.connectToEvent(QStringLiteral("presenceDetected"), this,[this](const QScxmlEvent &event){
        a_C1.submitEvent("stopAutoCheck");
        a_C2.submitEvent("stopAutoCheck");
        a_L1.submitEvent("stopAutoCheck");
        a_B1.submitEvent("stopAutoCheck");
    });

    s.connectToEvent(QStringLiteral("stopAlarm"), this,[this](const QScxmlEvent &event){
        a_C1.submitEvent("restartAutoCheck");
        a_C2.submitEvent("restartAutoCheck");
        a_L1.submitEvent("restartAutoCheck");
        a_B1.submitEvent("restartAutoCheck");
    });

    a_C1.connectToEvent(QStringLiteral("stopDetection"), this,[this](const QScxmlEvent &event){
        if(alarmEnabled)
        s.submitEvent("presenceDetected");
    });

    a_C2.connectToEvent(QStringLiteral("stopDetection"), this,[this](const QScxmlEvent &event){
        if(alarmEnabled)
        s.submitEvent("presenceDetected");
    });

    a_L1.connectToEvent(QStringLiteral("stopDetection"), this,[this](const QScxmlEvent &event){
        if(alarmEnabled)
        s.submitEvent("presenceDetected");
    });

    a_B1.connectToEvent(QStringLiteral("stopDetection"), this,[this](const QScxmlEvent &event){
        if(alarmEnabled)
        s.submitEvent("presenceDetected");
    });

    //************************************************window*******************************************************//

    f_C1.start();
    f_C2.start();
    f_L1.start();
    f_B1.start();

    f_C1.connectToEvent(QStringLiteral("windowIsOpen"), this,[this](const QScxmlEvent &event){
        if(alarmEnabled){
            a_C1.submitEvent("stopAutoCheck");
        }
        else{
            s.submitEvent("windowOpen");
        }
    });

    f_C1.connectToEvent(QStringLiteral("windowIsClose"), this,[this](const QScxmlEvent &event){
        if(!alarmEnabled){
            s.submitEvent("windowClose");
        }
    });

    f_C2.connectToEvent(QStringLiteral("windowIsOpen"), this,[this](const QScxmlEvent &event){
        if(alarmEnabled){
            a_C2.submitEvent("stopAutoCheck");
        }
        else{
            s.submitEvent("windowOpen");
        }
    });

    f_C2.connectToEvent(QStringLiteral("windowIsClose"), this,[this](const QScxmlEvent &event){
        if(!alarmEnabled){
            s.submitEvent("windowClose");
        }
    });
}

/*************************utilitaire************************************/

void Domo::refreshDisplay()
{
    unsigned int h = (time->elapsed()/3600000)%24;
    unsigned int m = (time->elapsed()/60000)%60;
    unsigned int s = (time->elapsed()/1000)%60;
    unsigned int ms = time->elapsed()%1000;
    const QString diff =  QString("%1:%2:%3,%4")
                               .arg(h,  2, 10, QChar('0'))
                               .arg(m,  2, 10, QChar('0'))
                               .arg(s,  2, 10, QChar('0'))
                               .arg(ms, 3, 10, QChar('0'));
    timer.setText(diff);

    const QString diffChauffage_B1 =  QString("%1").arg(chauffage_B1,  2, 10, QChar('0'));
    Chauff_B1.setText(diffChauffage_B1);
    const QString diffChauffage_L1 =  QString("%1").arg(chauffage_L1,  2, 10, QChar('0'));
    Chauff_L1.setText(diffChauffage_L1);
    const QString diffChauffage_C1 =  QString("%1").arg(chauffage_C1,  2, 10, QChar('0'));
    Chauff_C1.setText(diffChauffage_C1);
    const QString diffChauffage_C2 =  QString("%1").arg(chauffage_C2,  2, 10, QChar('0'));
    Chauff_C2.setText(diffChauffage_C2);
    const QString diffLumage_B1 =  QString("%1").arg(luminosity_B1,  2, 10, QChar('0'));
    Lum_B1.setText(diffLumage_B1);
    const QString diffLumage_L1 =  QString("%1").arg(luminosity_L1,  2, 10, QChar('0'));
    Lum_L1.setText(diffLumage_L1);
    const QString diffLumage_C1 =  QString("%1").arg(luminosity_C1,  2, 10, QChar('0'));
    Lum_C1.setText(diffLumage_C1);
    const QString diffLumage_C2 =  QString("%1").arg(luminosity_C2,  2, 10, QChar('0'));
    Lum_C2.setText(diffLumage_C2);




}

void Domo::updateModel(){
    //Check si on recommence une journée. Dans ce cas on reset les compteurs pour en commencer une nouvelle
    currentTime += TIMEINCREMENT;

    luminosityConsigne_C1=getConsigne(lumTimeAuto_C1[currentSegmentLum_C1],lumTimeAuto_C1[currentSegmentLum_C1+1],lumConsigneAuto_C1[currentSegmentLum_C1],lumConsigneAuto_C1[currentSegmentLum_C1+1]);
    luminosityConsigne_C2=getConsigne(lumTimeAuto_C2[currentSegmentLum_C2],lumTimeAuto_C2[currentSegmentLum_C2+1],lumConsigneAuto_C2[currentSegmentLum_C2],lumConsigneAuto_C2[currentSegmentLum_C2+1]);
    luminosityConsigne_L1=getConsigne(lumTimeAuto_L1[currentSegmentLum_L1],lumTimeAuto_L1[currentSegmentLum_L1+1],lumConsigneAuto_L1[currentSegmentLum_L1],lumConsigneAuto_L1[currentSegmentLum_L1+1]);
    luminosityConsigne_B1=getConsigne(lumTimeAuto_B1[currentSegmentLum_B1],lumTimeAuto_B1[currentSegmentLum_B1+1],lumConsigneAuto_B1[currentSegmentLum_B1],lumConsigneAuto_B1[currentSegmentLum_B1+1]);
    if(chauffAutomatic_L1){
        chauffageConsigne_L1=getConsigne(chauffTimeAuto_L1[currentSegmentChauff_L1],chauffTimeAuto_L1[currentSegmentChauff_L1+1],chauffConsigneAuto_L1[currentSegmentChauff_L1],chauffConsigneAuto_L1[currentSegmentChauff_L1+1]);
    }
    if(chauffAutomatic_C1){
        chauffageConsigne_C1=getConsigne(chauffTimeAuto_C1[currentSegmentChauff_C1],chauffTimeAuto_C1[currentSegmentChauff_C1+1],chauffConsigneAuto_C1[currentSegmentChauff_C1],chauffConsigneAuto_C1[currentSegmentChauff_C1+1]);
    }
    if(chauffAutomatic_C2){
        chauffageConsigne_C2=getConsigne(chauffTimeAuto_C2[currentSegmentChauff_C2],chauffTimeAuto_C2[currentSegmentChauff_C2+1],chauffConsigneAuto_C2[currentSegmentChauff_C2],chauffConsigneAuto_C2[currentSegmentChauff_C2+1]);
    }
    if(chauffAutomatic_B1){
        chauffageConsigne_B1=getConsigne(chauffTimeAuto_B1[currentSegmentChauff_B1],chauffTimeAuto_B1[currentSegmentChauff_B1+1],chauffConsigneAuto_B1[currentSegmentChauff_B1],chauffConsigneAuto_B1[currentSegmentChauff_B1+1]);
    }



    lumManager_C1.submitEvent(("updateLum"));
    chaufManager_C1.submitEvent("updateChauff");
    lumManager_C2.submitEvent(("updateLum"));
    chaufManager_C2.submitEvent("updateChauff");
    lumManager_B1.submitEvent(("updateLum"));
    chaufManager_B1.submitEvent("updateChauff");
    lumManager_L1.submitEvent(("updateLum"));
    chaufManager_L1.submitEvent("updateChauff");




    if(currentTime==lumTimeAuto_C1[currentSegmentLum_C1+1]&&(sizeof(lumTimeAuto_C1)/sizeof(int)==currentSegmentLum_C1+2)&&(currentTime==chauffTimeAuto_C1[currentSegmentChauff_C1+1]&&(sizeof(chauffTimeAuto_C1)/sizeof(int)==currentSegmentChauff_C1+2))
       &&(currentTime==lumTimeAuto_C2[currentSegmentLum_C2+1]&&(sizeof(lumTimeAuto_C2)/sizeof(int)==currentSegmentLum_C2+2)&&(currentTime==chauffTimeAuto_C2[currentSegmentChauff_C2+1]&&(sizeof(chauffTimeAuto_C2)/sizeof(int)==currentSegmentChauff_C2+2)))
       &&(currentTime==lumTimeAuto_L1[currentSegmentLum_L1+1]&&(sizeof(lumTimeAuto_L1)/sizeof(int)==currentSegmentLum_L1+2)&&(currentTime==chauffTimeAuto_L1[currentSegmentChauff_L1+1]&&(sizeof(chauffTimeAuto_L1)/sizeof(int)==currentSegmentChauff_L1+2)))
       &&(currentTime==lumTimeAuto_B1[currentSegmentLum_B1+1]&&(sizeof(lumTimeAuto_B1)/sizeof(int)==currentSegmentLum_B1+2)&&(currentTime==chauffTimeAuto_B1[currentSegmentChauff_B1+1]&&(sizeof(chauffTimeAuto_B1)/sizeof(int)==currentSegmentChauff_B1+2)))
            ){
        currentSegmentLum_C1=0;
        currentSegmentLum_C2=0;
        currentSegmentLum_L1=0;
        currentSegmentLum_B1=0;
        currentSegmentChauff_C1=0;
        currentSegmentChauff_C2=0;
        currentSegmentChauff_L1=0;
        currentSegmentChauff_B1=0;
        currentTime=0;
    }
    if(currentTime==lumTimeAuto_C1[currentSegmentLum_C1+1]){
        currentSegmentLum_C1++;
    }
    if(currentTime==chauffTimeAuto_C1[currentSegmentChauff_C1+1]){
        currentSegmentChauff_C1++;
    }
    if(currentTime==lumTimeAuto_C2[currentSegmentLum_C2+1]){
        currentSegmentLum_C2++;
    }
    if(currentTime==chauffTimeAuto_C2[currentSegmentChauff_C2+1]){
        currentSegmentChauff_C2++;
    }
    if(currentTime==lumTimeAuto_B1[currentSegmentLum_B1+1]){
        currentSegmentLum_B1++;
    }
    if(currentTime==chauffTimeAuto_B1[currentSegmentChauff_B1+1]){
        currentSegmentChauff_B1++;
    }
    if(currentTime==lumTimeAuto_L1[currentSegmentLum_L1+1]){
        currentSegmentLum_L1++;
    }
    if(currentTime==chauffTimeAuto_L1[currentSegmentChauff_L1+1]){
        currentSegmentChauff_L1++;
    }
}

int Domo::getConsigne(int startTime, int endTime, int startConsigne, int endConsigne){
    return startConsigne + ((((float)endConsigne - (float)startConsigne )/ ((float)endTime - (float)startTime)) * ((float)currentTime - (float)startTime ));
}

std::string Domo::tostr (int x)
{
    std::stringstream str;
    str << x;
    return str.str();
}

Domo::~Domo()
{
    delete time;
    delete updateTimer;
}
