#include "main.h"

bool process(const int& type)
{
	switch (type)
	{
	case PlanType::StraightStopObsType:
	{
		unique_ptr<SceneBase> plan_obj = make_unique<StraightStopObs>();
		return plan_obj->planning_process();
	}
	case PlanType::StraightStationType:
	{
		unique_ptr<SceneBase> plan_obj = make_unique<StraightStation>();
		return plan_obj->planning_process();
	}
	case PlanType::StraightFollowType:
	{
		unique_ptr<SceneBase> plan_obj = make_unique<StraightFollow>();
		return plan_obj->planning_process();
	}
	case PlanType::StraightCrosswalkType:
	{
		unique_ptr<SceneBase> plan_obj = make_unique<StraightCrosswalk>();
		return plan_obj->planning_process();
	}
	case PlanType::ObsPassStaticType:
	{
		unique_ptr<SceneBase> plan_obj = make_unique<StaticObs>();
		return plan_obj->planning_process();
	}
	case PlanType::ObsPassOvertakeType:
	{
		unique_ptr<SceneBase> plan_obj = make_unique<OvertakeObs>();
		return plan_obj->planning_process();
	}
	case PlanType::ObsPassMeetingType:
	{
		unique_ptr<SceneBase> plan_obj = make_unique<MeetingObs>();
		return plan_obj->planning_process();
	}
	case PlanType::ParkReverse1Type:
	{
		unique_ptr<SceneBase> plan_obj = make_unique<ReverseParking1>();
		return plan_obj->planning_process();
	}
	case PlanType::ParkReverse2Type:
	{
		unique_ptr<SceneBase> plan_obj = make_unique<ReverseParking2>();
		return plan_obj->planning_process();
	}
	case PlanType::ParkParallelType:
	{
		unique_ptr<SceneBase> plan_obj = make_unique<ParallelParking>();
		return plan_obj->planning_process();
	}
	case PlanType::DriftPointType:
	{
		unique_ptr<SceneBase> plan_obj = make_unique<DriftPoint>();
		return plan_obj->planning_process();
	}
	case PlanType::DriftparkType:
	{
		unique_ptr<SceneBase> plan_obj = make_unique<DriftParking>();
		return plan_obj->planning_process();
	}
	default:
		break;
	}
	cout << "plan type is not right" << endl;
	return false;
}

int main(int argc, _TCHAR* argv[])
{
	initgraph(SWIDTH, SHEIGHT, EW_SHOWCONSOLE);//Í¼ÐÎ´°¿Ú
	setbkcolor(WHITE);

	if (process(PlanType::StraightStopObsType))
	{
		cout << "finish" << endl;
	}
	system("pause");

	if (process(PlanType::StraightStationType))
	{
		cout << "finish" << endl;
	}
	system("pause");

	if (process(PlanType::StraightFollowType))
	{
		cout << "finish" << endl;
	}
	system("pause");


	if (process(PlanType::StraightCrosswalkType))
	{
		cout << "finish" << endl;
	}
	system("pause");

	if (process(PlanType::ObsPassStaticType))
	{
		cout << "finish" << endl;
	}
	system("pause");

	if (process(PlanType::ObsPassOvertakeType))
	{
		cout << "finish" << endl;
	}
	system("pause");

	if (process(PlanType::ObsPassMeetingType))
	{
		cout << "finish" << endl;
	}
	system("pause");

	if (process(PlanType::ParkReverse1Type))
	{
		cout << "finish" << endl;
	}
	system("pause");

	if (process(PlanType::ParkReverse2Type))
	{
		cout << "finish" << endl;
	}
	system("pause");

	if (process(PlanType::ParkParallelType))
	{
		cout << "finish" << endl;
	}
	system("pause");

	if (process(PlanType::DriftPointType))
	{
		cout << "finish" << endl;
	}
	system("pause");

	if (process(PlanType::DriftparkType))
	{
		cout << "finish" << endl;
	}
	system("pause");

	closegraph();
	return 0;
}