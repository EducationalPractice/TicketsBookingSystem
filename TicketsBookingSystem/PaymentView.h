#pragma once
#include "Views.h"
class PaymentView : public View
{
	RailCarInformation railCar;
public:
	PaymentView();

	void draw();
};
