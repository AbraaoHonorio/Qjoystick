#ifndef JOYSTICKWINDOW_H
#define JOYSTICKWINDOW_H
#include <joystick.h>

#include <QMainWindow>
#include <ros/ros.h> //ros::init ...
#include <iostream> //std::cout, std::cerr

#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>


namespace Ui {
class JoystickWindow;
}

class JoystickWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit JoystickWindow(QWidget *parent = 0);
    ~JoystickWindow();
    void getButtons();
    void publish_vel(ros::Publisher& velpub, double linear, double angular);
    void odomCallback(const nav_msgs::Odometry::ConstPtr& o);
    // funções para tela
    void cleanDisplay();
    void fillDisplay();

private slots:
    void updateFrom();
    void joystickConnect();



private:
    Ui::JoystickWindow *ui;
    QTimer *timer;
    Joystick *joystick;
    ros::NodeHandle nh;
    ros::Subscriber odomsub;
    ros::Publisher velpub;
};

#endif // JOYSTICKWINDOW_H
