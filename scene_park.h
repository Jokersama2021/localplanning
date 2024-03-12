#pragma once
#include "scene_base.h"

class ReverseParking1 : public SceneBase //倒车方式1
{
public:
	ReverseParking1();
	void showScene();
	bool planning_process() override;

public:
	unique_ptr<CarObsStatic> ob1;
	unique_ptr<CarObsStatic> ob2;
	double dis_in = 0.0;//倒车直行的距离
	double park_width = 0.0;//库的宽度	
	double dis_obs_L = 120.0;//与障碍车左方的横向距离
	double safedis = 10.0;//与道路右边界的安全距离
};

class ReverseParking2 : public SceneBase //倒车方式2
{
public:
	ReverseParking2();
	void showScene();
	bool planning_process() override;

public:
	unique_ptr<CarObsStatic> ob1;
	unique_ptr<CarObsStatic> ob2;
	double dis_in = 0.0;//倒车直行的距离
	double park_width = 0.0;//库的宽度
	double dis_obs_L = 80.0;//与障碍车左方的横向距离
	double safedis = 10.0;//与道路右边界的安全距离
};

class ParallelParking : public SceneBase //侧方位倒车
{
public:
	ParallelParking();
	void showScene();
	bool planning_process() override;

public:
	unique_ptr<CarObsStatic> ob1;
	unique_ptr<CarObsStatic> ob2;
	double safedis = 10.0;//与后方安全距离
	double park_length = 0.0;//库的长度
	double dis_obs_L = 80.0;//与障碍车左方的横向距离
};
