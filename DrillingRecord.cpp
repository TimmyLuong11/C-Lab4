#include "DrillingRecord.h"
#include <iomanip>

//Puts num in array, increments counter
void DrillingRecord::addNum(double num)
{
	nums[numCtr] = num;
	++numCtr;
}

//Puts string in array, increments counter
void DrillingRecord::addString(std::string string)
{
	strings[strCtr] = string;
	++strCtr;
}

//Returns (copy of) num at index in num array
double DrillingRecord::getNum(unsigned int index) const
{
	return nums[index];
}

//Returns (copy of) string at index in string array
std::string DrillingRecord::getString(unsigned int index) const
{
	return strings[index];
}

//Overloaded output operator that sends one formatted record to ostream
std::ostream& operator<<(std::ostream& os, const DrillingRecord& record)
{
	os << record.getString(0) << ';' << record.getString(1) << ';';
	for (int index = 0; index < static_cast<int> (MAX_NUMS); ++index)
	{
		os << std::fixed << std::setprecision(2) << record.getNum(index);
		if (index < static_cast<int> (MAX_NUMS) - 1)
		{
			os << ';';
		}
	}
	return os;
}
