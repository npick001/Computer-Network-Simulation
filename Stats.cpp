#include "Stats.h"
#include <fstream>
#include <iostream>

void StatsHolder::ReportStats()
{
	MSGItr = MSGList.begin();
	PCItr = PCList.begin();
	for (int i = 0; i < PCList.size() - 1; i++)
	{
		std::cout
			<< "Computer Statistics:\n"
			<< "Computer " << PCList.front()->getId() << ":"
			<< "\n	Average Processing Time:" << (*PCItr)->getAvgTime()
			<< "\n  Utilization:" << (*PCItr)->getUsage()
			<< "\n		Queue Stats:"
			<< "\n			Average Queue Time: " << (*PCItr)->_serviceQueue->getAvgTime()
			<< "\n			Average Queue Size: " << (*PCItr)->_serviceQueue->getAvgSize() << std::endl;
			//<< "\n			Max Queue Size: " << (*PCItr)->_serviceQueue->getMax();
		PCItr++;
	}
}