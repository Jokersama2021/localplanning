#include "scene_drift.h"

/******************************************U型弯漂移、定点漂移******************************************/
DriftPoint::DriftPoint()//U型弯漂移、定点漂移
{
	road0 = make_unique<RoadNormal>(400.0);
	cone = make_unique<Cone>(SWIDTH / 2.0, SHEIGHT / 2.0 + 220.0, 40.0);//放置锥桶

	//计算定位点坐标
	double pos_x = SWIDTH / 2.0 - road0->Rwidth / 2.0;
	double pos_y = 100.0;
	cout << "LocX = " << pos_x << ", LocY = " << pos_y << endl;

	car0 = make_unique<CarNormal>(pos_x, pos_y, PI);
	car0->speed = -5.0;

	car0->coutInfo();
	showScene();
	system("pause");
}

void DriftPoint::showScene()
{
	BeginBatchDraw();
	cleardevice();

	road0->showRoad();
	cone->showCone();
	car0->showCar(BLACK);

	EndBatchDraw();
	delay(DELAYTIME);
}

bool DriftPoint::planning_process()//整个过程
{
	cout << "直行入弯" << endl;
	double drift_start = SHEIGHT / 2.0 - 160.0;//起漂点
	uniformStraight(drift_start - car0->pmidr->y);

	cout << "起漂" << endl;
	car0->delta_theta_rot = PI / 200.0;
	driftStraightByS(cone->p_center->y - car0->pmid->y);

	cout << "过弯" << endl;
	double R = car0->pmid->distanceTo(*cone->p_center);
	car0->delta_theta = -car0->speed / R;//角速度，注意正负号
	car0->delta_theta_rot = car0->delta_theta;//纯公转，让自转角速度和公转相等
	double target_theta = PI * 2.0 - car0->heading_theta;
	driftTurnByRev(target_theta + lap * 2.0 * PI, *cone->p_center);

	cout << "滑移" << endl;
	car0->delta_theta = -car0->speed / R;//角速度，注意正负号
	car0->delta_theta_rot = 0.0;
	driftTurnByRev(PI - target_theta, *cone->p_center);

	cout << "直行出弯" << endl;
	car0->updatePmidr();
	uniformStraight(car0->pmidr->y - 0.0);
	return true;
}

/******************************************漂移泊车******************************************/
DriftParking::DriftParking()//漂移泊车
{
	road0 = make_unique<RoadNormal>(180.0);
	ob1 = make_unique<CarObsStatic>(road0->right_boundary - 50.0, SHEIGHT / 2.0);
	ob2 = make_unique<CarObsStatic>(road0->right_boundary - 50.0, SHEIGHT / 2.0 + 410.0);
	park_length = ob2->topPos - ob1->bottomPos;
	cout << "park_length = " << park_length << endl;

	car0 = make_unique<CarNormal>(SWIDTH / 2.0 - road0->Rwidth / 3.0, 100.0, PI);
	car0->speed = -5.0;

	car0->coutInfo();
	ob1->coutInfo();
	ob2->coutInfo();

	showScene();
	system("pause");
}

void DriftParking::showScene()
{
	BeginBatchDraw();
	cleardevice();



	road0->showRoad();
	ob1->showCar(RED);
	ob2->showCar(RED);
	car0->showCar(BLACK);

	EndBatchDraw();
	delay(DELAYTIME);
}

bool DriftParking::planning_process()
{
	//判断库的长度是否足够
	if (park_length <= car0->car_length * 1.2)
	{
		cout << "车库太短，泊车失败" << endl;
		return false;
	}

	//目标停车点
	double park_x = ob1->pmid->x;
	double park_y = ob1->bottomPos + park_length / 2.0;

	//旋转中心
	double Rturn = park_x - car0->pmid->x;
	Point p_center(park_x, park_y - Rturn);

	cout << "直行入弯" << endl;
	uniformStraight(p_center.y - car0->pmid->y + 5.0);

	cout << "入库" << endl;
	car0->delta_theta = PI / 80.0;
	car0->delta_theta_rot = car0->delta_theta * 2.0;
	driftTurnByRev(PI / 2.0, p_center);
	return true;
}