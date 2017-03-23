#include "joystickwindow.h"
#include "ui_joystickwindow.h"
#include <QTimer>
#include <string>
#include <QDebug>


JoystickWindow::JoystickWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::JoystickWindow)
{
    ui->setupUi(this);

   // odomsub = nh.subscribe("/odom", 1000, odomCallback);
    velpub = nh.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/teleop",1);

    ui->leJs->setText("/dev/input/js0");
    timer = new QTimer(this);
    joystick = new Joystick();
    connect(ui->btConnect, SIGNAL(clicked()), this, SLOT(joystickConnect()));
    connect(timer, SIGNAL(timeout() ), this ,SLOT(updateFrom()));
    fillDisplay();

}

JoystickWindow::~JoystickWindow()
{
    delete ui;
}



void JoystickWindow::odomCallback(const nav_msgs::Odometry::ConstPtr& o)
{
    std::cerr << "X: " << o->pose.pose.position.x << std::endl;
    std::cerr << "Y: " << o->pose.pose.position.y << std::endl;
}

void JoystickWindow::publish_vel(ros::Publisher& velpub, double linear, double angular)
{
    geometry_msgs::Twist vel;
    vel.angular.z = angular;
    vel.linear.x = linear;
    velpub.publish(vel);
}


void JoystickWindow::fillDisplay()
{
    ui->lbFront->setText("↑");
    ui->lbBack->setText("↓");
    ui->lbRigth->setText("→");
    ui->lbLeft->setText("←");
}

void JoystickWindow::cleanDisplay()
{
    ui->lbFront->setText("");
    ui->lbBack->setText("");
    ui->lbRigth->setText("");
    ui->lbLeft->setText("");
}

void JoystickWindow::updateFrom()
{
    cleanDisplay();
    qDebug() << joystick->getAxis(0)<< joystick->getAxis(1)<< joystick->getAxis(2)<< joystick->getAxis(3)<< joystick->getAxis(4)<< joystick->getAxis(5);

    //para cima
     if( ( joystick->getAxis(1) < -1) || (joystick->getAxis(5) < -1) )
     {
             ui->lbFront->setText("↑");
              publish_vel(velpub, 0.15, 0);
     }
     //para baixo
     if( ( joystick->getAxis(1) > 0) || (joystick->getAxis(5) > 0) )
     {
          ui->lbBack->setText("↓");
           publish_vel(velpub, -0.15, 0);

     }
     //para lado direito
     if((joystick->getAxis(0)>0) || (joystick->getAxis(4)>0))
     {
         ui->lbRigth->setText("→");
          publish_vel(velpub, 0, -1.2);
     }
     //para lado esquerdo
     if((joystick->getAxis(0) < -1) || (joystick->getAxis(4) < -1 ))
     {
         ui->lbLeft->setText("←");
         publish_vel(velpub, 0, 1.2);

     }

}






void JoystickWindow::joystickConnect()
{


    if( joystick->init(ui->leJs->text().toStdString().c_str())  > -1)
    {
        ui->btConnect->setText("Connect!");
        timer->start();
    }
}
