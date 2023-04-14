#pragma once
#include "Computer.h"

class Network
{
public:
	Network();
	void ReadFile(std::string filename);
	int GetEdgeWeight(Computer* computer);
private:
	// need to be static so only one network can exist.
	static Computer* _computerNetwork;
};

