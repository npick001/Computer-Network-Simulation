#include "Stats.h"
#include <fstream>
#include <iostream>

void StatsHolder::ReportStats()
{
	char input;
	Time MSGQT=0, MSGCt = 0;
	Time PCAVGPT=0, QWait = 0;
	double Usage=0, QAvgS=0, QAvgM = 0;
	std::cout << "Would you like a detailed Description? (Y/N): ";			//This allows the user to decide if they want to print the statistics for every message individually,
	std::cin >> input;														//Even if the user selects no, the average message stats will still be displayed
	MSGItr = MSGList.begin();
	PCItr = PCList.begin();

		std::cout << "\nMessage Statistics:\n";
		for (int i = 0; i < MSGList.size(); i++)			//Iterate through messages.
			{
			MSGQT += (*MSGItr)->getWaitTime();				//Calculate wait times, this is a sum for all messages for averaging later		
			MSGCt += (*MSGItr)->getCommTime();				//Calculate Communication time (EndT-StartT), again a sum of all messages
			if (input == 'Y' || input == 'y')
			{
				std::cout << "STATS FOR MESSAGE " << (*MSGItr)->getID() << ":\n\t- Total Time in Queues: " << (*MSGItr)->getWaitTime() << "\n\t- Total Communication Time: " << (*MSGItr)->getCommTime() << std::endl;
			}
				MSGItr++;
		}
		std::cout << "\nComputer Statistics:\n";			//Iterate Computers
		for (int j = 0; j < PCList.size(); j++)
		{
			PCAVGPT += (*PCItr)->getAvgTime();				//Sum of all computer processing times
			Usage += (*PCItr)->getUsage();					//Sum of all Utilizations for averaging later
			QAvgS += (*PCItr)->_serviceQueue->getAvgSize();	//Sum of average Queue Size for each computer
			QWait += (*PCItr)->_serviceQueue->getAvgTime(); //Sum of average wait time for each computer.
			if ((*PCItr)->_serviceQueue->getMax() > QAvgM) { QAvgM = (*PCItr)->_serviceQueue->getMax(); }		//Instad of outputting an average max queue size, it puts out the larges of all computers.
			std::cout << "COMPUTER " << (*PCItr)->getId() << " STATS:\n\t- Average Processing Time: " << (*PCItr)->getAvgTime() << "\n\t- % Utilization: " << (*PCItr)->getUsage() << std::endl;
			std::cout << "- QUEUE STATS:\n\t- Average Size: " << (*PCItr)->_serviceQueue->getAvgSize() << "\n\t- Maximum Size: " << (*PCItr)->_serviceQueue->getMax() << "\n\t- Average Wait Time: " << (*PCItr)->_serviceQueue->getAvgTime() << std::endl;
			PCItr++;
		}
		MSGQT /= MSGList.size();		// This block averages all the stats collected above.
		MSGCt /= MSGList.size();
		Usage /= PCList.size();
		QAvgS /= PCList.size();
		QWait /= PCList.size();
		PCAVGPT /= PCList.size();
		std::cout												//Formatted Output
			<< "\nFor all in the network:"
			<< "\n Computers:"
			<< "\n\t- Average Processing Time: " << PCAVGPT
			<< "\n\t- Utilization: " << Usage << "%"
			<< "\n Queues:"
			<< "\n\t- Average Size: " << QAvgS
			<< "\n\t- Maximum Size: " << QAvgM
			<< "\n\t- Average Time: " << QWait
			<< "\n Messages:"
			<< "\n\t- Average Communication Time: " << MSGCt
			<< "\n\t- Average Wait Time: " << MSGQT;
}