#pragma once
#include "planning_base.h"

/******************************************状态机******************************************/
enum Shift//档位
{
	m_D,//前进档
	m_N,//空档
	m_R,//倒档
	m_P//驻车档
};

enum TurnDirection//转向状态机
{
	TurnRight,
	TurnLeft,
};

/******************************************车基类******************************************/
class CarBase//车基类
{
public:
	virtual ~CarBase() = default;
	void initCar(const double& pos_x, const double& pos_y, const double& heading, const double& width, const double& length);
	void updatePmidf();//前中点
	void updatePmidr();//中点
	void updatePmid();//几何中点
	void showCar(const COLORREF& color);
	void showCircle();
	void coutInfo();

	void moveStraightStep();//单帧直行	
	void carTurnStep();//单帧转向
	void carRotationStep();//单帧自转

	void updateRinRout(const double& R);//更新4个半径
	void updateTurnInfo(const int& turn_state, const double& R);//更新转向信息
	void updateXYva();//更新x和y方向的速度和加速度
	void updateStraightInfo();//更新直行信息
	void updateDriftRotInfo();//更新漂移自转信息
	void updateDriftRotRevInfo(const Point& center);//更新漂移自转+公转信息

public:
	double car_width = 80.0;//车宽
	double car_length = 160.0;//车长

	unique_ptr<Point> plf;//左前点
	unique_ptr<Point> plr;//左后点
	unique_ptr<Point> prf;//右前点
	unique_ptr<Point> prr; //右后点
	unique_ptr<Point> p_center;//转向中心点

	unique_ptr<Point> pmidf;//前轴中点
	unique_ptr<Point> pmidr;//后轴中点
	unique_ptr<Point> pmid;//几何中点

	double Rmin = 100.0;//最小转弯半径
	double Rof = 0.0;//外前半径
	double Ror = 0.0;//外后半径
	double Rif = 0.0;//内前半径
	double Rir = 0.0;//内后半径

	double R0;//半斜长，自转半径
	double theta0;//atan(car_length / car_width)

	double speed = 0.0;//合速度，负前进，正倒车
	double speed_x = 0.0;//x方向分速度，负左，正右
	double speed_y = 0.0;//y方向分速度，负上，正下

	double a = 0.0;//合加速度，负加，正减
	double a_x = 0.0;//x方向分加速度，负左，正右
	double a_y = 0.0;//y方向分加速度，负上，正下

	double delta_theta = 0.0;//角速度，负顺，正逆
	double delta_theta_rot = 0.0;//自转角速度，负顺，正逆
	double heading_theta = 0.0;//航向角，为0时车辆竖直向上，负代表向左偏航，正代表向右偏航

	int Gear = m_P;//档位
};

/******************************************一般车******************************************/
class CarNormal : public CarBase
{
public:
	CarNormal(const double& pos_x, const double& pos_y, const double& heading = 0.0, const double& width = 80.0, const double& length = 160.0);
};