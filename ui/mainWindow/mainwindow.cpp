#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    world = new WorldMap(nullptr, new QGraphicsScene, new CustomQGraphicsView, new WorldCollide);
    initializeInterface();
}

void MainWindow::initializeInterface()
{
    //ui
    QString relativePath = QApplication::applicationDirPath();
    relativeIconPaths =
        {
            relativePath + "/images/button_empty.png",
            relativePath + "/images/button_changedir.png",
            relativePath + "/images/button_load.png",
            relativePath + "/images/button_move.png",
            relativePath + "/images/button_path.png",
            relativePath + "/images/button_portal.png",
            relativePath + "/images/button_rail.png",
            relativePath + "/images/button_signals.png",
            relativePath + "/images/button_train.png",
            relativePath + "/images/button_uncouple.png",
            relativePath + "/images/button_unload.png",
            relativePath + "/images/button_via.png",
            relativePath + "/images/button_exit.png",
            relativePath + "/images/button_bin.png",
            relativePath + "/images/button_motor.png",
        };
    setEditAddInterface();
    //Map
    ui->MapViewLayout->addWidget(world->getWorldView(),1);

    //button icon size
    ui->MultiFuncBut1->setIconSize(ui->MultiFuncBut1->size());
    ui->MultiFuncBut2->setIconSize(ui->MultiFuncBut2->size());
    ui->MultiFuncBut3->setIconSize(ui->MultiFuncBut3->size());
    ui->MultiFuncBut4->setIconSize(ui->MultiFuncBut4->size());
    ui->MultiFuncBut5->setIconSize(ui->MultiFuncBut5->size());
    ui->MultiFuncBut6->setIconSize(ui->MultiFuncBut6->size());
    ui->MultiFuncBut7->setIconSize(ui->MultiFuncBut7->size());
    ui->MultiFuncBut8->setIconSize(ui->MultiFuncBut8->size());
    ui->MultiFuncBut9->setIconSize(ui->MultiFuncBut9->size());
    ui->MultiFuncBut10->setIconSize(ui->MultiFuncBut10->size());
    ui->MultiFuncBut11->setIconSize(ui->MultiFuncBut11->size());
    ui->MultiFuncBut12->setIconSize(ui->MultiFuncBut12->size());
    ui->MultiFuncBut13->setIconSize(ui->MultiFuncBut13->size());
    ui->MultiFuncBut14->setIconSize(ui->MultiFuncBut14->size());
    ui->MultiFuncBut15->setIconSize(ui->MultiFuncBut15->size());
    ui->MultiFuncBut16->setIconSize(ui->MultiFuncBut16->size());
    ui->MultiFuncBut17->setIconSize(ui->MultiFuncBut17->size());
    ui->MultiFuncBut18->setIconSize(ui->MultiFuncBut18->size());
    ui->MultiFuncBut19->setIconSize(ui->MultiFuncBut19->size());
    ui->MultiFuncBut20->setIconSize(ui->MultiFuncBut20->size());
    ui->MultiFuncBut21->setIconSize(ui->MultiFuncBut21->size());
    ui->MultiFuncBut22->setIconSize(ui->MultiFuncBut22->size());
    ui->MultiFuncBut23->setIconSize(ui->MultiFuncBut23->size());
    ui->MultiFuncBut24->setIconSize(ui->MultiFuncBut24->size());

    /*
    ui->MultiFuncBut4->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->MultiFuncBut5->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->MultiFuncBut6->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->MultiFuncBut7->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->MultiFuncBut8->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->MultiFuncBut9->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->MultiFuncBut10->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->MultiFuncBut11->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->MultiFuncBut12->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->MultiFuncBut13->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->MultiFuncBut14->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->MultiFuncBut15->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->MultiFuncBut16->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->MultiFuncBut17->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->MultiFuncBut18->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->MultiFuncBut19->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->MultiFuncBut20->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->MultiFuncBut21->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->MultiFuncBut22->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    ui->MultiFuncBut23->setStyleSheet("background-color: rgba(20, 20, 20, 8);"); //unused button
    */

    //console
    managerConsole = new ManagerConsole(this); //add custom manager console

    //ZOOM IN MAP (BUTTONS)
    //Cannot be used - a KNOWN BUG
    //Reason: ZOOM buttons are placed under a console (label) covering the entire area.
    //This is an alternative solution because the RMB event does not work on the map. WHY?!!
    //However, RMB does work on the label = console.
    mapZoomLayout = new QHBoxLayout();
    ZoomWidget = new QWidget(this);

    ZoomWidget->setLayout(mapZoomLayout);
    mapZoomLayout->addWidget(ui->ZoomAddBut);
    mapZoomLayout->addWidget(ui->ZoomSubBut);
    ZoomWidget->setGeometry(QRect(155,5,70,70)); //pos x, pos y, size x, size y

    //BASIC STATS
    ui->BasicStats->setVisible(true);

    //SPECIAL STATS
    ui->SpecialStats->setVisible(true);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QSize sizeView = world->getWorldView()->size();
    managerConsole->setConsolePos({160, 0},sizeView.width()-160,sizeView.height());
    managerConsole->printToConsole("bugged console (you have to resize window), affects response to mouse events", RED_BOLD_COLOR, MIDDLE_DURATION);
}

void MainWindow::playButSwitch(bool editMode)
{
    if (editMode) ui->PlayBut->setText("PlayMode");
    else ui->PlayBut->setText("EditMode");
    selectMenuSwitch(false); //switch mode -> always set "ADD MENU"
}

void MainWindow::selectMenuSwitch(bool selectMode)
{
    (selectMode) ? ui->MenuName->setText("EDIT MENU") : ui->MenuName->setText("ADD MENU");
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    QPoint globalPos = QCursor::pos();
    int delta = event->angleDelta().y();
    if (delta > 0)
    {
        world->getWorldView()->zoomIn(true);
    }
    else if (delta < 0)
    {
        world->getWorldView()->zoomOut();
    }
    QWidget::wheelEvent(event);
}

void MainWindow::on_TestButton1_clicked()
{
    for (auto actor : world->tickedActorsList)
    {
        if (dynamic_cast<Train*>(actor))
        {
            qDebug() << "direction changed";
            dynamic_cast<Train*>(actor)->changeMoveDirection();
        }
    }
}

void MainWindow::on_PlayBut_clicked() {}//overrided
void MainWindow::on_ZoomSubBut_clicked() {}//overrided
void MainWindow::on_ZoomAddBut_clicked() {}//overrided
void MainWindow::on_AddMenuBut_clicked(){}//overrided
void MainWindow::on_EditMenuBut_clicked(){}//overrided

void MainWindow::on_MultiFuncBut1_clicked() {}//overrided
void MainWindow::on_MultiFuncBut2_clicked() {}//overrided
void MainWindow::on_MultiFuncBut3_clicked() {} //overrided;
void MainWindow::on_MultiFuncBut4_clicked() {} //overrided;
void MainWindow::on_MultiFuncBut5_clicked() {} //overrided;
void MainWindow::on_MultiFuncBut6_clicked() {} //overrided;
void MainWindow::on_MultiFuncBut7_clicked() {} //overrided;
void MainWindow::on_MultiFuncBut8_clicked() {} //overrided;
void MainWindow::on_MultiFuncBut9_clicked() {} //overrided;
void MainWindow::on_MultiFuncBut10_clicked() {} //overrided;
void MainWindow::on_MultiFuncBut11_clicked() {} //overrided;
void MainWindow::on_MultiFuncBut12_clicked() {} //overrided;
void MainWindow::on_MultiFuncBut13_clicked() {} //overrided;
void MainWindow::on_MultiFuncBut14_clicked() {} //overrided;
void MainWindow::on_MultiFuncBut15_clicked() {} //overrided;
void MainWindow::on_MultiFuncBut16_clicked() {} //overrided;
void MainWindow::on_MultiFuncBut17_clicked() {} //overrided;
void MainWindow::on_MultiFuncBut18_clicked() {} //overrided;
void MainWindow::on_MultiFuncBut19_clicked() {} //overrided;
void MainWindow::on_MultiFuncBut20_clicked() {} //overrided;
void MainWindow::on_MultiFuncBut21_clicked() {} //overrided;
void MainWindow::on_MultiFuncBut22_clicked() {} //overrided;
void MainWindow::on_MultiFuncBut23_clicked() {} //overrided;
void MainWindow::on_MultiFuncBut24_clicked() {}//overrided

void MainWindow::InterfaceSet(int menuSelected)
{
    if (menuSelected >= OPTION_MODE_START && menuSelected <= OPTION_MODE_END) setBasicMenuInterface();
    else if (menuSelected >= EDIT_MODE_START && menuSelected <= EDIT_ADD_END) setEditAddInterface();
    else if (menuSelected >= EDIT_SELECT_START && menuSelected <= EDIT_MODE_END) setEditSelectInterface();
    else if (menuSelected >= PLAY_MODE_START && menuSelected <= PLAY_ADD_END) setPlayAddInterface();
    else if (menuSelected >= PLAY_SELECT_START && menuSelected <= PLAY_MODE_END) setPlaySelectInterface();
}

void MainWindow::setBasicMenuInterface()
{
    ui->MultiFuncBut1->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut2->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut3->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut4->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut5->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut6->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut7->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut8->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut9->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut10->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut11->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut12->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut13->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut14->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut15->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut16->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut17->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut18->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut19->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut20->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut21->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut22->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut23->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut24->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
}

void MainWindow::setEditSelectInterface()
{
    ui->MultiFuncBut1->setIcon(QIcon(relativeIconPaths[RAIL_ICON]));
    ui->MultiFuncBut2->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut3->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut4->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut5->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut6->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut7->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut8->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut9->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut10->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut11->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut12->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut13->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut14->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut15->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut16->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut17->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut18->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut19->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut20->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut21->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut22->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut23->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut24->setIcon(QIcon(relativeIconPaths[BIN_ICON]));
}

void MainWindow::setEditAddInterface()
{
    ui->MultiFuncBut1->setIcon(QIcon(relativeIconPaths[RAIL_ICON]));
    ui->MultiFuncBut2->setIcon(QIcon(relativeIconPaths[SIGNAL_ICON]));
    ui->MultiFuncBut3->setIcon(QIcon(relativeIconPaths[PORTAL_ICON]));
    ui->MultiFuncBut4->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut5->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut6->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut7->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut8->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut9->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut10->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut11->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut12->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut13->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut14->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut15->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut16->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut17->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut18->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut19->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut20->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut21->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut22->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut23->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut24->setIcon(QIcon(relativeIconPaths[BIN_ICON]));
}

void MainWindow:: setPlaySelectInterface()
{
    ui->MultiFuncBut1->setIcon(QIcon(relativeIconPaths[TRAIN_ICON]));
    ui->MultiFuncBut2->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut3->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut4->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut5->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut6->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut7->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut8->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut9->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut10->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut11->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut12->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut13->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut14->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut15->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut16->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut17->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut18->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut19->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut20->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut21->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut22->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut23->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut24->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
}

void MainWindow::setTrainMenu()
{  
    ui->MultiFuncBut1->setIcon(QIcon(relativeIconPaths[PATH_ICON]));
    ui->MultiFuncBut2->setIcon(QIcon(relativeIconPaths[MOVE_ICON]));
    ui->MultiFuncBut3->setIcon(QIcon(relativeIconPaths[VIA_ICON]));
    ui->MultiFuncBut4->setIcon(QIcon(relativeIconPaths[CHANGEDIR_ICON]));
    ui->MultiFuncBut5->setIcon(QIcon(relativeIconPaths[MOTOR_ICON]));
    ui->MultiFuncBut6->setIcon(QIcon(relativeIconPaths[UNCOUPLE_ICON]));
    ui->MultiFuncBut7->setIcon(QIcon(relativeIconPaths[LOAD_ICON]));
    ui->MultiFuncBut8->setIcon(QIcon(relativeIconPaths[UNLOAD_ICON]));
    ui->MultiFuncBut9->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut10->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut11->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut12->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut13->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut14->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut15->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut16->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut17->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut18->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut19->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut20->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut21->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut22->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut23->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut24->setIcon(QIcon(relativeIconPaths[EXIT_ICON]));
}

void MainWindow::setPlayAddInterface()
{
    ui->MultiFuncBut1->setIcon(QIcon(relativeIconPaths[TRAIN_ICON]));
    ui->MultiFuncBut2->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut3->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut4->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut5->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut6->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut7->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut8->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut9->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut10->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut11->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut12->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut13->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut14->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut15->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut16->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut17->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut18->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut19->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut20->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut21->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut22->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut23->setIcon(QIcon(relativeIconPaths[EMPTY_ICON]));
    ui->MultiFuncBut24->setIcon(QIcon(relativeIconPaths[BIN_ICON]));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete world;
    delete mapZoomLayout;
    delete ZoomWidget;
}
