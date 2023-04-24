#include "Stats.h"
#include <fstream>
#include <iostream>

void StatsHolder::ReportStats()
{
	char input;
	Time MSGQT=0, MSGCt = 0;
	Time PCAVGPT=0, QWait = 0;
	double Usage=0, QAvgS=0, QAvgM = 0;
	std::cout << "Would you like a detailed Description? (Y/N): ";
	std::cin >> input;
	MSGItr = MSGList.begin();
	PCItr = PCList.begin();

		std::cout << "Message Statistics:\n";
		for (int i = 0; i < MSGList.size(); i++)
			{
			MSGQT += (*MSGItr)->getWaitTime();
			MSGCt += (*MSGItr)->getCommTime();
			if (input == 'Y' || input == 'y')
			{
				std::cout << "STATS FOR MESSAGE: " << (*MSGItr)->getID() << " - Total Time in Queues: " << (*MSGItr)->getWaitTime() << ", Total Communication Time: " << (*MSGItr)->getCommTime() << std::endl;
			}
				MSGItr++;
			}
		std::cout << "Computer Statistics:\n";
		for (int j = 0; j < PCList.size(); j++)
		{
			PCAVGPT += (*PCItr)->getAvgTime();
			Usage += (*PCItr)->getUsage();
			QAvgS += (*PCItr)->_serviceQueue->getAvgSize();
			QWait += (*PCItr)->_serviceQueue->getAvgTime();
			if ((*PCItr)->_serviceQueue->getMax() > QAvgM) { QAvgM = (*PCItr)->_serviceQueue->getMax(); }
			if (input == 'Y' || input == 'y')
			{
				std::cout << "STATS FOR COMPUTER: " << (*PCItr)->getId() << " - Average Processing Time: " << (*PCItr)->getAvgTime() << ", Utilization %: " << (*PCItr)->getUsage() << std::endl;
				std::cout << "\tStats for the Queue - Average Size:" << (*PCItr)->_serviceQueue->getAvgSize() << " Maximum Size: " << (*PCItr)->_serviceQueue->getMax() << " Average Wait Time:" << (*PCItr)->_serviceQueue->getAvgTime() << std::endl;
			}
			
			PCItr++;
		}
		MSGQT /= MSGList.size();
		MSGCt /= MSGList.size();
		Usage /= PCList.size();
		QAvgS /= PCList.size();
		QWait /= PCList.size();
		PCAVGPT /= PCList.size();
		std::cout
			<< "\nFor all in the network:\n"
			<< " Computer:"
			<< "\n\t Computer Average Processing Time: " << PCAVGPT
			<< "\n\t Computer Utilization: " << Usage << "%"
			<< "\n Queues:"
			<< "\n\t Average Queue Size: " << QAvgS
			<< "\n\t Maximum Queue Size: " << QAvgM
			<< "\n\t Average Queue Time: " << QWait
			<< "\n Messages:"
			<< "\n\t Average Communication Time: " << MSGCt
			<< "\n\t Average Wait Time: " << MSGQT;
}