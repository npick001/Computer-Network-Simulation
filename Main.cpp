#include <vector>
#include <iostream>


std::vector<int> dijkstra(std::vector<std::vector<int>> matrix, int src)
{
    //Suppose have the Suppose use Graph pointer to get the Graph instead and get the Matrix from it?
    //Don't need to call this over and over for the Static but would have to redo the graph and call this every message being sent
    //Used the vector for express purpose of testing
    int nsize = matrix.size();
    //Creates the distance finder,
    std::vector<int> dist(nsize, INT_MAX);
    //Flag for if visited node or not
    std::vector<bool> flagvisited(nsize, false);
    //Creating Route
    std::vector<int>route(nsize);
    //Making sure the Source is taken from the algirthm
    route[src] = -1;
    //Distance to itself is 0 of course
    dist[src] = 0;

    for (int i = 0; i < nsize; i++)
    {
        int closestvertex = -1;
        int shortestDistance = INT_MAX;
        for (int x = 0; x < nsize; x++)
        {
            if (!flagvisited[x] && dist[x] < shortestDistance)
            {
                closestvertex = x;
                shortestDistance = dist[x];
            }
        }
        flagvisited[closestvertex] = true;
        for (int x = 0; x < nsize; x++)
        {
            int distance = matrix[closestvertex][x];
            if (distance > 0 && (shortestDistance + distance < dist[x]))
            {
                route[x] = closestvertex;
                dist[x] = shortestDistance + distance;
            }
        }
    }
    return route;
}
void printPath(int iterator, std::vector<int>path)
{
    if (iterator == -1)
    {
        return;
    }
    printPath(path[iterator], path);
    std::cout << iterator << " ";
};

std::vector<int> PathforN(int srcItr, std::vector<int>path, std::vector<int>NPath)
{

    if (srcItr == -1)
    {
        return NPath;
    }

    PathforN(path[srcItr], path, NPath);
    NPath.insert(NPath.begin(), srcItr);

    return NPath;
}

/*Cameron Checking*/
int main() {
    std::vector<std::vector<int> > adjacencyMatrix
        = { {0,1,1,0,0,0,0},
          {1,0,0,1,0,0,0},
          {1,0,0,0,0,1,0},
          {0,1,1,0,1,1,0},
          {0,0,0,1,0,0,1},
          {0,0,1,1,0,0,1},
          {0,0,0,0,1,1,0} };
    for (int i = 0; i < adjacencyMatrix.size(); i++)
    {
        for (int j = 0; j < adjacencyMatrix[i].size(); j++) {
            std::cout << adjacencyMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::vector<int> routeof7 = dijkstra(adjacencyMatrix, 6);
    int chosenComputer = 6;
    int size = adjacencyMatrix.size();
    /*Unsure if you want to have the datastructure of the path put inside the Message on generation or have each Computer have a list to every node and then send it to the next one based on the destination
    */
    //Proof of Concept for printing out the path
    for (int k = 0; k < size; k++)
    {
        if (k != chosenComputer)
        {
            std::cout << "\n";
            printPath(k, routeof7);
        }
    }
    /*I have not fixed this, it only calls itself twice before putting itself away.*/
    for (int ree = 0; ree < routeof7.size(); ree++)
    {
        std::cout << routeof7[ree] << " ";
    }
    std::cout << std::endl;
    std::vector<int> PathToNode1 = PathforN(0, routeof7, PathToNode1);
    for (int l = 0; l < PathToNode1.size(); l++)
    {
        std::cout << PathToNode1[l] << " ";
    }
    return 0;
}
