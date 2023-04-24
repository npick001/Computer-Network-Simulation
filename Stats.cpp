#include "Stats.h"
#include <fstream>
#include <iostream>

void StatsHolder::ReportStats()
{
	MSGList.sort();
	MSGItr = MSGList.begin();
	PCList.sort();
	PCItr = PCList.begin();
	for (int i = 0; i < PCList.size(); i++)
	{
		std::cout
			<< "Computer Statistics:\n"
			<< "Computer " << (*PCItr)->getId() << ":"
			<< "\n	Average Processing Time:" << (*PCItr)->getAvgTime()
			<< "\n  Utilization:" << (*PCItr)->getUsage() 
			<< "\n		Queue Stats:"
			<< "\n			Average Queue Time: " << (*PCItr)->GetFIFO()->getAvgTime()
			<< "\n			Average Queue Size: " << (*PCItr)->GetFIFO()->getAvgSize()
			<< "\n			Max Queue Size: " << (*PCItr)->GetFIFO()->getMax();
	}
}