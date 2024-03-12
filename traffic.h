#pragma once
#include "planning_base.h"
#include "car.h"

/******************************************障碍物******************************************/
class Cone//锥桶
{
public:
	Cone() = default;
	Cone(const double& pos_x, const double& pos_y, const double& R = 20.0);
	void showCone();

public:
	unique_ptr<Point> p_center;//中心点
	double r = 20.0;//半径
};

class Person//行人
{
public:
	Person() = default;
	Person(const double& pos_x, const double& pos_y);
	void personMove();//行人移动
	void showPerson();

public:
	unique_ptr<Point> p_center;//中心点
	double r = 20.0;//半径
	double speed = 0.0;//速度
};

class CarObsStatic : public CarBase//静态障碍车
{
public:
	CarObsStatic() = default;
	CarObsStatic(const double& pos_x, const double& pos_y, const double& heading = 0.0, const double& width = 80.0, const double& length = 160.0);//静态障碍车

public:
	//4条边位置
	double topPos = 0.0;
	double rightPos = 0.0;
	double leftPos = 0.0;
	double bottomPos = 0.0;
};