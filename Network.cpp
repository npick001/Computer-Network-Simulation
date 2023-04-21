#include "Network.h"

Computer* Network::_computerNetwork = 0;

Network::Network()
{

}

void Network::ReadFile(std::string filename)
{
}

int Network::GetEdgeWeight(Computer* computer)
{
    return computer->GetQueueSize();
}
