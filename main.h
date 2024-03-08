#pragma once
#include "scene_straight.h"
#include "scene_obs_pass.h"
#include "scene_park.h"
#include "scene_drift.h"

enum PlanType//类型
{
	//直行
	StraightStopObsType,//停障
	StraightStationType,//停靠站点
	StraightFollowType,//跟车
	StraightCrosswalkType,//通过斑马线

	//绕障
	ObsPassStaticType,//静态绕障
	ObsPassOvertakeType,//超车
	ObsPassMeetingType,//会车

	//泊车
	ParkReverse1Type,//倒库1
	ParkReverse2Type,//倒库2
	ParkParallelType,//侧方位

	//漂移
	DriftPointType,//定点漂移
	DriftparkType,//漂移泊车
};