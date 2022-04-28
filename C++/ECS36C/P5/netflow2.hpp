#ifndef NETFLOW_HPP
#define NETFLOW_HPP

/////////////////////////////////////////////////////////////////////
/// As a reminder, you are NOT allowed to modify this file.
/// The autograder will use its own version of netflow.hpp.
/////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>
#include <iostream>
#include <queue>

/**
 * Each vertex is represented by a unique unsigned ID.
 */
struct Edge
{
public:
    Edge() = default;
    Edge(unsigned f, unsigned t, unsigned w)
        : from{f}, to{t}, weight{w} { }

    unsigned from;  // ID of vertex this edge is coming out of
    unsigned to;    // ID of vertex this edge is going into
    unsigned weight;
};

/**
 * Takes as argument a list of edges representing a flow network.
 *
 * Returns a list of edges representing a max flow.
 * Does not include any edge whose weight is zero.
 *
 * Throws std::runtime_error if any of the following is true
 * (if multiple of the below error conditions are true, the first
 * error condition's message should be used):
 * - @numVertices < 2.
 *      - Runtime error message: "Too few vertices."
 * - Zero edges.
 *      - Runtime error message: "Too few edges."
 * - There is at least one edge with weight 0.
 *      - Runtime error message: "Detected edge weight of 0."
 * - There is at least one Edge with a @from or @to member
 *    that is >= @numVertices. (Each vertex is supposed to have
 *    a unique ID from 0 to (@numVertices - 1).)
 *      - Runtime error message: "Edge interacts with nonexistent vertex."
 * - There is at least one self-loop.
 *      - Runtime error message: "At least one self-loop."
 * - There is at least one occurrence of multi-edges.
 *      - Runtime error message: "Detected multi-edges."
 * - The flow network does not contain only one source.
 *      - Runtime error message: "Zero or more than one source."
 * - The flow network does not contain only one sink.
 *      - Runtime error message: "Zero or more than one sink."
 */



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

    //If number of vertices is less than 2, runtime_error
    if (numVertices < 2) {
        throw std::runtime_error("Too few vertices.");
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
        adjacentMatrix[flowNetwork[i].from][flowNetwork[i].to] = flowNetwork[i].weight;
//        std::cout << i << "---------------------" << std::endl;
//        for (int i = 0; i < numVertices; ++i) {
//            for (int j = 0; j < numVertices; ++j) {
//                std::cout << adjacentMatrix[i][j] << " ";
//            }
//            std::cout<< std::endl;
//        }
//        std::cout << i << "---------------------" << std::endl;
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
    unsigned source = flowNetwork[0].from;
    unsigned sink = flowNetwork[numVertices].to;

    while (BFS(resMatrix, source, sink, parentList) == true) {

        //initializing a temp flow in each iteration
        unsigned currentMaxFlow = 114514;

        //Find paths
        int currentVertice = sink;

        while (currentVertice != source) {

            //get parent from current vertice
            int tempParent = parentList[currentVertice];
            for (int i = 0; i < parentList.size(); ++i) {
                std::cout << parentList[i] << std::endl;
            }
            std::cout << " " << currentVertice << " " << tempParent << std::endl;

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

            //Update current vertice to its parent
            currentVertice = tempParent;
        }

        maxFlow += currentMaxFlow;
    }

    std::cout << "----------" << std::endl << maxFlow << "----------" << std::endl;


    return flowNetwork;
}







/**
 * Contains information about an instructor who needs to be
 * assigned a course or courses to teach.
 */
struct Instructor
{
public:
    Instructor(const std::string& ln,
               unsigned mc)
            : lastName{ln}
            , preferences{}
            , maxCourses{mc}
            , assignedCourses{}
    {
    }
    void addPreference(const std::string& course)
    {
        preferences.push_back(course);
    }
    std::string lastName;
    // Names of the courses this instructor is willing to teach.
    std::vector<std::string> preferences;
    // Maximum number of courses this instructor is willing to teach.
    unsigned maxCourses;
    // The courses that this instructor is assigned to teach.
    std::vector<std::string> assignedCourses;
};
/**
 * Creates a valid assignment of instructors to courses that maximizes the
 * number of courses assigned. This assignment is stored in the assignedCourses
 * members of the various Instructor instances in @instructors.
 */
void assignCourses(
        std::vector<Instructor>& instructors,
        const std::vector<std::string>& courses);

#endif  // NETFLOW_HPP
