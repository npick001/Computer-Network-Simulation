#include "Stats.h"
#include <fstream>
#include <iostream>

void StatsHolder::ReportStats()
{
	char input;
	std::cout << "Wouuld you like a detailed Description? (Y/N): ";
	std::cin >> input;
	MSGItr = MSGList.begin();
	PCItr = PCList.begin();
	if (input == 'Y' || input == 'y') 
	{
		std::cout << "Message Statistics:\n";
		for (int i = 0; i < MSGList.size(); i++)
			{
				std::cout << "STATS FOR MESSAGE: " << (*MSGItr)->getID() << " - Total Time in Queues: " << (*MSGItr)->getWaitTime() << ", Total Communication Time: " << (*MSGItr)->getCommTime() << std::endl;
				MSGItr++;
			}
		std::cout << "Computer Statistics:\n";
		for (int j = 0; j < PCList.size(); j++)
		{
			std::cout << "STATS FOR COMPUTER: " << (*PCItr)->getId() << " - Average Processing Time: " << (*PCItr)->getAvgTime() << ", Utilization %: " << (*PCItr)->getUsage() << std::endl;
			std::cout << "\tStats for the Queue - Average Size:" << (*PCItr)->_serviceQueue->getAvgSize() << " Maximum Size: " << (*PCItr)->_serviceQueue->getMax() << " Average Wait Time:" << (*PCItr)->_serviceQueue->getAvgTime() << std::endl;
			PCItr++;
		}
		
	}
	MSGItr = MSGList.begin();
	PCItr = PCList.begin();
}