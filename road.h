#pragma once
#include "traffic.h"

/******************************************道路基类******************************************/
class RoadBase//一般道路
{
public:
	virtual ~RoadBase() = default;
	virtual void showRoad() = 0;

	virtual double getUpLine() { return 0.0; }
	virtual double getMidLine() { return 0.0; }
	virtual double getDownLine() { return 0.0; }

public:
	double Rwidth = 200.0;//车道宽，或半宽
	//边界
	double up_boundary = 0.0;//上
	double down_boundary = 0.0;//下
	double left_boundary = 0.0;//左
	double right_boundary = 0.0;//右
};

class RoadNormal : public RoadBase
{
public:
	RoadNormal(const double& r_width = 200.0);
	void showRoad() override;
};

class RoadDoubleLane : public RoadBase//双车道线道路
{
public:
	RoadDoubleLane(const double& r_width = 200.0);
	void showRoad() override;
};

class RoadCrosswalk : public RoadBase//斑马线道路
{
public:
	RoadCrosswalk(const double& r_width = 200.0);
	void showRoad() override;
	double getUpLine() { return this->up_line; }//获取斑马线上边界
	double getMidLine() { return this->mid_line; }//获取斑马线中心线
	double getDownLine() { return this->down_line; }//获取斑马线下边界

public:
	double up_line = 0.0;//斑马线上边界
	double mid_line = 0.0;//斑马线中心线
	double down_line = 0.0;//斑马线下边界
	double disRec = 20.0;//间距
};