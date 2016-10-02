#pragma once
#include "Views.h"
class PaymentView : public View
{
	string creditCard;
	string dateOfExpire;
	string CVV;
	int counter = 0;

	bool creditcard_entered = false;
	bool dateOfExpire_entered = false;
	bool cvv_entered = false;

	void enterLine(string&, bool &, int, int&);
public:
	PaymentView();
	void setCreditCard(string);
	void setDateOfExpire(string);
	void setCVV(string);

	void draw();
	
	View* handle();
};
