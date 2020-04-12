#pragma once
#include<math.h>
struct Seller
{
	char Name[20];
	char Surname[20];
	double Rating = 0;

	void AddBuyer(int weight, int piece, double time)
	{
		Rating = (Rating * count + Rate((weight * 3 + piece) / time)) / (count + 1);
		count++;
		
	}
private:
	int count = 0;
	double Rate(double x)
	{
		if ((5 * x) / (x + 0.125) + 0.5 > 5)
			return 5;
		else
			return ((5 * x) / (x + 0.125)) + 0.5;
	}
};

