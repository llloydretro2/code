#include "netflow.hpp"

#define TOO_FEW_VERTICES "Too few vertices."
#define TOO_FEW_EDGES "Too few edges."
#define EDGE_WEIGHT_ZERO "Detected edge weight of 0."
#define EDGE_BAD_ENDPOINT "Edge interacts with nonexistent vertex."
#define SELF_LOOP "At least one self-loop."
#define MULTI_EDGES "Detected multi-edges."
#define NOT_ONE_SRC "Zero or more than one source."
#define NOT_ONE_SINK "Zero or more than one sink."

#include <algorithm>
#include <iostream>
#include <queue>


bool BFS(std::vector<std::vector<unsigned>> &resMatrix,
         unsigned &source,
         unsigned &sink,
         std::vector<int> &parentList) {

    //Get size
    unsigned size = resMatrix.size();

    //Created a visited list for BFS
    std::vector<bool> visited;
    for (unsigned i = 0; i < size; ++i) {
        visited.push_back(false);
    }

    //Create a queue for BFS
    std::queue<unsigned> q;

    //Make the source node visited, update its parent vertice to NA
    q.push(source);
    visited[source] = true;
    parentList[source] = -1;

    //Starting BFS
    while (!q.empty()) {

        //Pop vertice out and find its neighbor
        unsigned currentVertice = q.front();
        q.pop();

        for (unsigned i = 0; i < size; ++i) {

            //Get capacity
            unsigned capacity = resMatrix[currentVertice][i];

            //Checking if vertice is already visited
            if ((visited[i] == false) && (capacity > 0)) {

                //Update queue, parent, and visited
                q.push(i);
                parentList[i] = currentVertice;
                visited[i] = true;
            }
        }
    }

    //If sink is reached, return true
    if (visited[sink] == true) {
        return true;
    }

    return false;

}

std::vector<Edge> solveNetworkFlow(
        const std::vector<Edge>& flowNetwork,
        unsigned numVertices) {

    //If number of vertices is less than 2, throw TOO_FEW_VERTICES
    if (numVertices < 2) {
        throw std::runtime_error{TOO_FEW_VERTICES};
    }

    //Testing TOO_FEW_EDGES
    if (flowNetwork.size() == 0){
        throw std::runtime_error{TOO_FEW_EDGES};
    }

    //Test EDGE_BAD_ENDPOINT
    std::vector<unsigned> VertList;
    for (unsigned i = 0; i < flowNetwork.size(); ++i) {
        if (std::count(VertList.begin(), VertList.end(), flowNetwork[i].from) == 0){
            VertList.push_back(flowNetwork[i].from);
        }
        if (std::count(VertList.begin(), VertList.end(), flowNetwork[i].to) == 0){
            VertList.push_back(flowNetwork[i].to);
        }
    }

    if (numVertices < VertList.size()){
        throw std::runtime_error{EDGE_BAD_ENDPOINT};
    }

    //Self loop
    for (unsigned i = 0; i < flowNetwork.size(); ++i) {
        if (flowNetwork[i].from == flowNetwork[i].to){
            throw std::runtime_error{SELF_LOOP};
        }
    }

    //Create an Adjacent matrix by using @numVertices
    std::vector<std::vector<unsigned>> adjacentMatrix;
    for (unsigned i = 0; i < numVertices; ++i) {
        std::vector<unsigned> newRow;
        adjacentMatrix.push_back(newRow);
        for (unsigned j = 0; j < numVertices; ++j) {
            adjacentMatrix[i].push_back(0);
        }
    }

    //Giving value to the adjacent matrix using @flowNetwork
    for (unsigned i = 0; i < flowNetwork.size(); ++i) {
        if (adjacentMatrix[flowNetwork[i].from][flowNetwork[i].to] != 0 && flowNetwork[i].weight != 0) {
            throw std::runtime_error{MULTI_EDGES};
        }
        adjacentMatrix[flowNetwork[i].from][flowNetwork[i].to] = flowNetwork[i].weight;
        //Check if the edge is 0
        if (flowNetwork[i].weight == 0){
            throw std::runtime_error{EDGE_WEIGHT_ZERO};
        }
    }

    unsigned maxFlow = 0;

    //Create residual adjacent matrix
    std::vector<std::vector<unsigned>> resMatrix;
    for (unsigned i = 0; i < numVertices; ++i) {
        std::vector<unsigned> newRow;
        resMatrix.push_back(newRow);
        for (unsigned j = 0; j < numVertices; ++j) {
            resMatrix[i].push_back(adjacentMatrix[i][j]);
        }
    }

    //Create a parent list for redo
    std::vector<int> parentList;
    for (unsigned i = 0; i < numVertices; ++i) {
        parentList.push_back(-1);
    }

    //Get source and sink
    std::vector<unsigned> sources;
    std::vector<unsigned> sinks;
    unsigned source;
    unsigned sink;
    bool sourceStatus;
    bool sinkStatus;
    unsigned currentV;
    for (unsigned i = 0; i < numVertices; ++i) {
        currentV = i;
        sourceStatus = true;
        sinkStatus = true;
        for (unsigned j = 0; j < numVertices; ++j) {
            if (adjacentMatrix[j][i] > 0){
                sourceStatus = false;
            }
            if (adjacentMatrix[i][j] > 0){
                sinkStatus = false;
            }
        }
        if (sourceStatus) {
            sources.push_back(currentV);
        }
        if (sinkStatus){
            sinks.push_back(currentV);
        }
    }
    if (sources.size() > 1 || sources.size() == 0){
        throw std::runtime_error{NOT_ONE_SRC};
    }
    else{
        source = sources[0];
    }

    if (sinks.size() > 1 || sinks.size() == 0) {
        throw std::runtime_error{NOT_ONE_SINK};
    }
    else{
        sink = sinks[0];
    }


    //returning matrix
    std::vector<std::vector<int>> returnMatrix;
    for (unsigned i = 0; i < numVertices; ++i) {
        std::vector<int> newRow;
        returnMatrix.push_back(newRow);
        for (unsigned j = 0; j < numVertices; ++j) {
            returnMatrix[i].push_back(0);
        }
    }

    while (BFS(resMatrix, source, sink, parentList) == true) {

        //initializing a temp flow in each iteration
        unsigned currentMaxFlow = 114514;

        //Find paths
        unsigned currentVertice = sink;

        while (currentVertice != source) {

            //get parent from current vertice
            int tempParent = parentList[currentVertice];
            for (unsigned i = 0; i < parentList.size(); ++i) {
//                std::cout << parentList[i] << std::endl;
            }
//            std::cout << " " << currentVertice << " " << tempParent << std::endl;

            //Update max flow in the path
            unsigned currentCapacity = resMatrix[tempParent][currentVertice];
            currentMaxFlow = std::min(currentCapacity, currentMaxFlow);

            //Update current vertice to its parent
            currentVertice = tempParent;
        }

        //Update residual matrix
        currentVertice = sink;
        while (currentVertice != source) {
            //get parent from current vertice
            int tempParent = parentList[currentVertice];

            //Update capacity
            resMatrix[tempParent][currentVertice] -= currentMaxFlow;
            resMatrix[currentVertice][tempParent] += currentMaxFlow;
            //Update return matrix
            returnMatrix[tempParent][currentVertice] += currentMaxFlow;
            returnMatrix[currentVertice][tempParent] -= currentMaxFlow;

            //Update current vertice to its parent
            currentVertice = tempParent;
        }

        maxFlow += currentMaxFlow;
    }

    //Giving value to the return net flow
    std::vector<Edge> returnFlow;
    for (unsigned i = 0; i < flowNetwork.size(); ++i) {
        returnFlow.push_back(flowNetwork[i]);
    }

    for (unsigned i = 0; i < flowNetwork.size(); ++i) {
        returnFlow[i].weight = returnMatrix[flowNetwork[i].from][flowNetwork[i].to];
    }
    return returnFlow;
}

std::vector<std::vector<int>> solveNetworkFlowForInstructor(
        std::vector<std::vector<unsigned >>& adjMatrix,
        unsigned numVertices){

    //Create an Adjacent matrix by using @numVertices
    std::vector<std::vector<unsigned>> adjacentMatrix;
    for (unsigned i = 0; i < numVertices; ++i) {
        std::vector<unsigned> newRow;
        adjacentMatrix.push_back(newRow);
        for (unsigned j = 0; j < numVertices; ++j) {
            adjacentMatrix[i].push_back(adjMatrix[i][j]);
        }
    }

    unsigned maxFlow = 0;

    //Create residual adjacent matrix
    std::vector<std::vector<unsigned>> resMatrix;
    for (unsigned i = 0; i < numVertices; ++i) {
        std::vector<unsigned> newRow;
        resMatrix.push_back(newRow);
        for (unsigned j = 0; j < numVertices; ++j) {
            resMatrix[i].push_back(adjacentMatrix[i][j]);
        }
    }

    //Create a parent list for redo
    std::vector<int> parentList;
    for (unsigned i = 0; i < numVertices; ++i) {
        parentList.push_back(-1);
    }

    //Get source and sink
    unsigned source = 0;
    unsigned sink = numVertices - 1;

    //returning matrix
    std::vector<std::vector<int>> returnMatrix;
    for (unsigned i = 0; i < numVertices; ++i) {
        std::vector<int> newRow;
        returnMatrix.push_back(newRow);
        for (unsigned j = 0; j < numVertices; ++j) {
            returnMatrix[i].push_back(0);
        }
    }

    while (BFS(resMatrix, source, sink, parentList) == true) {

        //initializing a temp flow in each iteration
        unsigned currentMaxFlow = 114514;

        //Find paths
        unsigned currentVertice = sink;

        while (currentVertice != source) {

            //get parent from current vertice
            int tempParent = parentList[currentVertice];
            for (unsigned i = 0; i < parentList.size(); ++i) {
//                std::cout << parentList[i] << std::endl;
            }
//            std::cout << " " << currentVertice << " " << tempParent << std::endl;

            //Update max flow in the path
            unsigned currentCapacity = resMatrix[tempParent][currentVertice];
            currentMaxFlow = std::min(currentCapacity, currentMaxFlow);

            //Update current vertice to its parent
            currentVertice = tempParent;
        }

        //Update residual matrix
        currentVertice = sink;
        while (currentVertice != source) {
            //get parent from current vertice
            int tempParent = parentList[currentVertice];

            //Update capacity
            resMatrix[tempParent][currentVertice] -= currentMaxFlow;
            resMatrix[currentVertice][tempParent] += currentMaxFlow;
            //Update return matrix
            returnMatrix[tempParent][currentVertice] += currentMaxFlow;
            returnMatrix[currentVertice][tempParent] -= currentMaxFlow;

            //Update current vertice to its parent
            currentVertice = tempParent;
        }

        maxFlow += currentMaxFlow;
    }

    return returnMatrix;
}

void assignCourses(
        std::vector<Instructor>& instructors,
        const std::vector<std::string>& courses){

    //Create list of Vertices that contains source + instructors + courses + sink
    std::vector<std::string> VertList;
    VertList.push_back("s");
    for (unsigned i = 0; i < instructors.size(); ++i) {
        VertList.push_back(instructors[i].lastName);
    }
    for (unsigned i = 0; i < courses.size(); ++i) {
        VertList.push_back(courses[i]);
    }
    VertList.push_back("t");

    //Create a Adjacency list
    std::vector<std::vector<unsigned >> adjMatrix;
    for (unsigned i= 0; i < VertList.size(); ++i) {
        std::vector<unsigned> newRow;
        adjMatrix.push_back(newRow);
        for (unsigned j = 0; j < VertList.size(); ++j) {
            adjMatrix[i].push_back(0);
        }
    }

    //Giving value to source
    for (unsigned i = 0; i < instructors.size(); ++i) {
        adjMatrix[0][i+1] = instructors[i].maxCourses;
    }

    //Connecting instructors to preferred courses
    std::string tempCourse;
    int tempLocation;
    for (unsigned i = 0; i < instructors.size(); ++i) {
//        std::cout << "Current Instructor: " << instructors[i].lastName << std::endl;
        for (unsigned j = 0; j < instructors[i].preferences.size(); ++j) {

            tempCourse = instructors[i].preferences[j];
//            std::cout << tempCourse << "-> ";
            for (unsigned k = 0; k < VertList.size(); ++k) {
                if (VertList[k] == tempCourse){
                    tempLocation = k;
//                    std::cout << tempLocation << std::endl;
                    break;
                }
            }

            adjMatrix[i+1][tempLocation] = 1;
        }
    }

//    for (unsigned i = 0; i < VertList.size(); ++i) {
//        std::cout << VertList[i] << " ";
//    }
//    std::cout << std::endl;
//    for (unsigned i = 0; i < VertList.size(); ++i) {
//        for (unsigned j = 0; j < VertList.size(); ++j) {
//            std::cout << adjMatrix[i][j]<< " ";
//        }
//        std::cout << std::endl;
//    }

    //Connecting courses to sink
    for (unsigned i = 1+ instructors.size(); i < VertList.size()-1; ++i) {
        adjMatrix[i][VertList.size()-1] = 1;
    }

    //Using flow net work to get max flow table
    std::vector<std::vector<int>> resMatrix = solveNetworkFlowForInstructor(adjMatrix, VertList.size());

    //Assigning to instructors
    for (unsigned i = 0; i < instructors.size(); ++i) {
        for (unsigned j = 1 + instructors.size(); j < VertList.size()-1; ++j) {
            if (resMatrix[i+1][j] == 1){
                instructors[i].assignedCourses.push_back(VertList[j]);
            }
        }
    }

}