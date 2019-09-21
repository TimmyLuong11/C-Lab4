#include <iostream>
#include <string> 
#include <vector> 
#include <sstream>
#include <fstream> 
#include <iomanip>
#include "DrillingRecord.h"
#include "ResizableArray.h"
#include "Exceptions.h"
using namespace std;

int main()
{
	//Variables for the program
	int index1 = 0;
	int index2 = 0;
	string line1;
	string line2;
	string date;
	vector<int> lineArray;
	vector<string> skipLineArray;
	vector<string> dataArray;
	vector<string> dateArray;
	vector<string> timeArray;
	vector<string> valueArray;
	vector<string> resultLine2;
	vector<string> errorMessage;
	vector<string> resultLine;

	getline(cin, line1);

	//Read in the file and add to array
	while (getline(cin, line1))
	{
		string str;
		istringstream inside(line1);
		while (getline(inside, str, ','))
		{
			dataArray.push_back(str);
		}
		dateArray.push_back(dataArray[index1]);
		timeArray.push_back(dataArray[index1 + 1]);
		date = dateArray[0];
		index1 += 18;
	}

	//Code for checking date if it is matching
	long arraySize = dataArray.size();
	long dateSize = dateArray.size();
	for (int index = 2; index < arraySize; ++index)
	{
		for (int cont = 0; cont < 16; ++cont)
		{
			valueArray.push_back(dataArray[cont + index]);
		}
		index += 17;
	}

	for (int index = 0; index < dateSize; ++index)
	{
		line2 = "";
		if (date == dateArray[index])
		{
			for (int counter = 0; counter <= 17; ++counter)
			{
				line2.append(dataArray[counter + index2]);
				if (counter < 17)
				{
					line2.append(";");
				}
			}
			skipLineArray.push_back(line2);
			index2 += 18;
		}
		else
		{
			int lineCounter = 16 * index;
			skipLineArray.push_back("Dates are not matching " + dateArray[index] + " at line " + to_string(index + 1) + ".");
			timeArray[index] = to_string(index);

			for (int count = 0; count < 16; ++count)
			{
				valueArray[(lineCounter + count)] = to_string(1);
			}
			index2 += 18;
			lineArray.push_back(index + 1);
		}
	}

	//Code for checking time if it is matching
	long timeSize = timeArray.size();
	for (int index1 = 0; index1 < timeSize; ++index1)
	{
		string str = timeArray[index1];
		for (int perCol = 1; perCol < timeSize; ++perCol)
		{
			if ((index1 + perCol) < timeSize)
			{
				if (str == timeArray[perCol + index1])
				{
					skipLineArray[index1 + perCol] = "Duplicate timestamp " + timeArray[index1 + perCol] + " at line " + to_string(index1 + perCol + 1) + ".";

					int lineCounter = 16 * (perCol + index1);

					for (int count = 0; count < 16; ++count)
					{
						valueArray[(lineCounter + count)] = to_string(1);
					}
					lineArray.push_back(index1 + perCol + 1);
				}
			}
		}
	}

	//Code for checking value if it is matching
	long valueSize = valueArray.size();
	int value = 0;
	int lineCounter = 1;
	for (int index = 0; index < valueSize; ++index)
	{
		if ((index - 16) == value)
		{
			++lineCounter;
			value = index;
		}

		double first = stof(valueArray[index].c_str());
		if (first <= 0)
		{
			skipLineArray[lineCounter - 1] = "Invalid floating-point data at line " + to_string(lineCounter) + ".";
			lineArray.push_back(lineCounter);
		}
	}

	//Code for adding it to the lineArray
	long lineArraySize = lineArray.size();
	long resultLineSize = skipLineArray.size();
	for (int index1 = 0; index1 < lineArraySize; ++index1)
	{
		for (int index2 = 1 + index1; index2 < lineArraySize; ++index2)
		{
			if (lineArray[index1] > lineArray[index2])
			{
				int temp = 0;
				temp = lineArray[index1];
				lineArray[index1] = lineArray[index2];
				lineArray[index2] = temp;
			}
		}
	}

	//Code for error message 
	for (int index = 0; index < lineArraySize; ++index)
	{
		string temp = skipLineArray[lineArray[index] - 1];
		errorMessage.push_back(temp);
		skipLineArray[lineArray[index] - 1].erase();
	}

	//Code for reading in the line
	for (int index = 0; index < resultLineSize; ++index)
	{
		string subString;
		istringstream line(skipLineArray[index]);

		while (getline(line, subString, ';'))
		{
			resultLine.push_back(subString);
		}
	}

	//Code for error message
	long errorMessageSize = errorMessage.size();
	for (int index = 0; index < errorMessageSize; ++index)
	{
		if (errorMessage[index] != "")
		{
			cout << errorMessage[index] << endl;
		}
	}

	
	//Access the class and adding the data to the class to be printed out or double capacity
	ResizableArray<DrillingRecord> drillArray = ResizableArray<DrillingRecord>();
	unsigned int countSize = 0;
	for (long count = resultLine.size() - 1; count > 0; count -= 18)
	{
		DrillingRecord* tempDr = new DrillingRecord;
		tempDr->addString(resultLine[count - 17]);
		tempDr->addString(resultLine[(count - 16)]);
		for (int index = 0; index < 16; ++index)
		{
			double temp = stof(resultLine[(count - 15 + index)].c_str());
			tempDr->addNum(temp);
		}
		drillArray.add(*tempDr);
		++countSize;
	}
	

	//For loop for gettting the drilling record array and printing it out
	for (unsigned index = 0; index < countSize; ++index)
	{
		cout << drillArray.get(index) << endl;
	}
	
	return 0;
}