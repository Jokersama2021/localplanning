#include "scene_park.h"

/******************************************倒车方式1******************************************/
ReverseParking1::ReverseParking1()//倒车方式1
{
	road0 = make_unique<RoadNormal>(250.0);
	ob1 = make_unique<CarObsStatic>(road0->right_boundary - 90.0, SHEIGHT / 2.0, PI / 2.0);
	ob2 = make_unique<CarObsStatic>(road0->right_boundary - 90.0, SHEIGHT / 2.0 + 200.0, PI / 2.0);
	park_width = ob2->topPos - ob1->bottomPos;
	dis_in = ob1->car_length * 0.8;
	cout << "park_width = " << park_width << ", dis_in = " << dis_in << endl;

	car0 = make_unique<CarNormal>(ob1->leftPos - dis_obs_L, SHEIGHT - 80.0);
	car0->speed = -3.0;
	car0->Gear = Shift::m_D;//挂前进挡

	car0->coutInfo();
	ob1->coutInfo();
	ob2->coutInfo();

	showScene();
	system("pause");
}

void ReverseParking1::showScene()//显示
{
	BeginBatchDraw();
	cleardevice();

	road0->showRoad();
	ob1->showCar(RED);
	ob2->showCar(RED);
	car0->showCar(BLACK);

	if (SHOWCIRCLE && car0->p_center)//绘制轨迹线
	{
		car0->showCircle();
	}

	EndBatchDraw();
	delay(DELAYTIME);
}

bool ReverseParking1::planning_process()//整个倒车过程
{
	//判断库的宽度是否足够
	if (park_width <= car0->car_width * 1.2)
	{
		cout << "车库太窄，泊车失败" << endl;
		return false;
	}

	//计算R和stopline
	double R = ob1->car_length + dis_obs_L - dis_in;//转向半径
	double dis_obs_S = R - park_width / 2.0;//与障碍车下方的纵向距离
	double stopline = ob1->bottomPos - dis_obs_S;//直行结束位置
	cout << "R = " << R << ", dis_obs_S = " << dis_obs_S << ", stopline = " << stopline << endl;

	cout << "直行前行" << endl;
	uniformStraight(car0->pmidr->y - stopline);
	car0->Gear = Shift::m_R;
	delay(CHANGETIME);

	cout << "倒车右转" << endl;
	car0->speed = 2.0;//线速度，倒车为正
	car0->delta_theta = car0->speed / R;//角速度=线速度/半径，注意正负号;
	carTurn(TurnDirection::TurnRight, R, PI / 2.0);

	cout << "倒车直行" << endl;
	car0->speed = 2.0;
	uniformStraight(road0->right_boundary - safedis - car0->pmidr->x);
	car0->Gear = Shift::m_P;

	cout << "泊车完成" << endl;
	return true;
}

/******************************************倒车方式2******************************************/
ReverseParking2::ReverseParking2()//倒车方式2
{
	road0 = make_unique<RoadNormal>(250.0);
	ob1 = make_unique<CarObsStatic>(road0->right_boundary - 90.0, SHEIGHT / 2.0, PI / 2.0);
	ob2 = make_unique<CarObsStatic>(road0->right_boundary - 90.0, SHEIGHT / 2.0 + 200.0, PI / 2.0);
	park_width = ob2->topPos - ob1->bottomPos;
	dis_in = ob1->car_length * 0.8;
	cout << "park_width = " << park_width << ", dis_in = " << dis_in << endl;

	car0 = make_unique<CarNormal>(ob1->leftPos - dis_obs_L, SHEIGHT - 80.0);
	car0->speed = -2.0;
	car0->Gear = Shift::m_D;//挂前进挡

	car0->coutInfo();
	ob1->coutInfo();
	ob2->coutInfo();

	showScene();
	system("pause");
}

void ReverseParking2::showScene()//显示
{
	BeginBatchDraw();
	cleardevice();

	road0->showRoad();
	ob1->showCar(RED);
	ob2->showCar(RED);
	car0->showCar(BLACK);

	if (SHOWCIRCLE && car0->p_center)//绘制轨迹线
	{
		car0->showCircle();
	}

	EndBatchDraw();
	delay(DELAYTIME);
}

bool ReverseParking2::planning_process()//整个倒车过程
{
	//判断库的宽度是否足够
	if (park_width <= car0->car_width * 1.2)
	{
		cout << "车库太窄，泊车失败" << endl;
		return false;
	}

	//计算倒车半径，左转目标转角，stopline
	double stopline = ob2->topPos;//直行结束位置
	double Rl = 200.0;//初始化左转转弯半径
	double center_x = car0->pmidr->x - Rl;
	double M = park_width / 2.0;
	double N = road0->right_boundary - dis_in - center_x;
	double Rr = (pow(Rl, 2) - pow(M, 2) - pow(N, 2)) / (M * 2 - Rl * 2);//右转倒车半径	
	double target_theta = atan((Rr + M) / N);//左转目标转角
	cout << "M = " << M << ", N = " << N << ", Rl = " << Rl << ", Rr = " << Rr << ", target_theta = " << target_theta / PI << ", stopline = " << stopline << endl;

	cout << "直行前行" << endl;
	uniformStraight(car0->pmidr->y - stopline);

	cout << "左转前行" << endl;
	car0->delta_theta = -car0->speed / Rl;//角速度=线速度/半径，注意正负号;
	carTurn(TurnDirection::TurnLeft, Rl, target_theta);
	car0->Gear = Shift::m_R;
	delay(CHANGETIME);

	cout << "倒车右转" << endl;
	car0->delta_theta = -car0->speed / Rr;//角速度=线速度/半径，注意正负号;
	carTurn(TurnDirection::TurnRight, Rr, PI / 2.0 - target_theta);

	cout << "倒车直行" << endl;
	car0->speed = 2.0;
	uniformStraight(road0->right_boundary - safedis - car0->pmidr->x);
	car0->Gear = Shift::m_P;

	cout << "泊车完成" << endl;
	return true;
}

/******************************************侧方位倒车******************************************/
ParallelParking::ParallelParking()//侧方位倒车
{
	road0 = make_unique<RoadNormal>(180.0);
	ob1 = make_unique<CarObsStatic>(road0->right_boundary - 50.0, SHEIGHT / 2.0);
	ob2 = make_unique<CarObsStatic>(road0->right_boundary - 50.0, SHEIGHT / 2.0 + 410.0);
	park_length = ob2->topPos - ob1->bottomPos;
	cout << "park_length = " << park_length << endl;

	car0 = make_unique<CarNormal>(ob1->leftPos - dis_obs_L, SHEIGHT - 80.0);
	car0->speed = -3.0;
	car0->Gear = Shift::m_D;//挂前进挡

	car0->coutInfo();
	ob1->coutInfo();
	ob2->coutInfo();

	showScene();
	system("pause");
}

void ParallelParking::showScene()//显示
{
	BeginBatchDraw();
	cleardevice();

	road0->showRoad();
	ob1->showCar(RED);
	ob2->showCar(RED);
	car0->showCar(BLACK);

	if (SHOWCIRCLE && car0->p_center)//绘制轨迹线
	{
		car0->showCircle();
	}

	EndBatchDraw();
	delay(DELAYTIME);
}

bool ParallelParking::planning_process()//整个倒车过程
{
	//判断库的长度是否足够
	if (park_length <= car0->car_length * 1.2)
	{
		cout << "车库太短，泊车失败" << endl;
		return false;
	}

	//计算R，目标转角和stopline
	double stopline = ob1->bottomPos;//直行结束位置
	double L = (dis_obs_L + ob1->car_width / 2.0) / 2.0;
	double h = (park_length - safedis) / 2.0;
	double R = (pow(L, 2) + pow(h, 2)) / L / 2.0;//转向半径
	double target_theta = asin(h / R);//目标转角
	cout << "R = " << R << ", target_theta = " << target_theta / PI << ", stopline = " << stopline << endl;

	cout << "直行前行" << endl;
	uniformStraight(car0->pmidr->y - stopline);
	car0->Gear = Shift::m_R;
	delay(CHANGETIME);

	cout << "倒车右转" << endl;
	car0->speed = 2.0;//线速度，倒车为正
	car0->delta_theta = car0->speed / R;//角速度=线速度/半径，注意正负号;
	carTurn(TurnDirection::TurnRight, R, target_theta);

	cout << "倒车左转" << endl;
	car0->delta_theta = -car0->speed / R;//切换方向
	carTurn(TurnDirection::TurnLeft, R, target_theta);
	car0->Gear = Shift::m_D;
	delay(CHANGETIME);

	cout << "直行前行" << endl;
	car0->speed = -2.0;
	uniformStraight(30.0);
	car0->Gear = Shift::m_P;

	cout << "泊车完成" << endl;
	return true;
}