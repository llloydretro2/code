#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>

#include "netflow.hpp"

#define EXIT_TEST_MISUSE -1

#define NO_CATCH_EXPECTED_EXCEPTION \
    std::cout << "Expected an exception, but did not catch any.\n";

#define CATCH_EXPECTED_EXCEPTION \
    catch (const std::runtime_error& e) \
    { \
        std::cout << e.what() << '\n'; \
    } \
    catch (...) \
    { \
        std::cout << "Wrong type of exception.\n"; \
    }

static bool verifyStructure(const std::vector<Edge>& flowNetwork,
                            const std::vector<Edge>& flow)
{
    // Quick heuristic: no reason the flow network should
    // have less edges than the flow.
    if (flowNetwork.size() < flow.size())
        return false;

    // Check if the flow uses an edge that does not exist
    // in the flow network.
    for (const Edge& flowEdge : flow)
    {
        // Verify that the endpoints of @flowEdge appear in @flowNetwork.
        bool found = false;
        for (const Edge& capacityEdge : flowNetwork)
            if (capacityEdge.from == flowEdge.from
                && capacityEdge.to == flowEdge.to)
            {
                found = true;
                break;
            }
        if (!found)
            return false;
    }

    // Check if the flow repeats any edge.
    for (unsigned i = 0; i < flow.size(); ++i)
    {
        const Edge& edge1 = flow[i];
        for (unsigned j = i + 1; j < flow.size(); ++j)
        {
            const Edge& edge2 = flow[j];
            // Check if found duplicate edge.
            if (edge1.from == edge2.from
                && edge1.to == edge2.to)
                return false;
        }
    }

    return true;
}

static bool verifyCapacityCondition(const std::vector<Edge>& flowNetwork,
                                    const std::vector<Edge>& flow)
{
    for (const Edge& flowEdge : flow)
    {
        // Find the corresponding edge in the flow network.
        const Edge* capacityEdge = nullptr;
        for (const Edge& e : flowNetwork)
            if (flowEdge.from == e.from && flowEdge.to == e.to)
            {
                capacityEdge = &e;
                break;
            }
        assert(capacityEdge);

        // Check if capacity condition is violated on this specific edge.
        if (flowEdge.weight > capacityEdge->weight)
            return false;
    }

    return true;
}

static bool verifyConservationCondition(const std::vector<Edge>& flow,
                                        unsigned numVertices,
                                        unsigned source,
                                        unsigned sink)
{
    // Incoming flow for each vertex.
    std::vector<unsigned > incomingFlow;
    std::vector<unsigned > outgoingFlow;
    for (unsigned i = 0; i < numVertices; ++i) {
        incomingFlow.push_back(0);
        outgoingFlow.push_back(0);
    }
    // Outgoing flow for each vertex.
//    unsigned outgoingFlow[numVertices] = {0};

    // Determine incoming and outgoing flow for each vertex.
    for (const Edge& edge : flow)
    {
        outgoingFlow[edge.from] += edge.weight;
        incomingFlow[edge.to] += edge.weight;
    }

    // Check if the conservation condition was violated.
    for (unsigned i = 0; i < numVertices; ++i)
    {
        if (i == source || i == sink)
            continue;
        if (incomingFlow[i] != outgoingFlow[i])
            return false;
    }

    return true;
}

/**
 * Verify that the alleged max flow returned by the student's
 * solveNetworkFlow() is indeed a flow.
 */
static bool verifyFlow(const std::vector<Edge>& flowNetwork,
                       const std::vector<Edge>& flow,
                       unsigned numVertices,
                       unsigned source,
                       unsigned sink)
{
    bool result = verifyStructure(flowNetwork, flow);
    if (!result)
    {
        std::cout << "Returned flow does not have same vertices/edges as the flow network.\n";
        return false;
    }
    result = verifyCapacityCondition(flowNetwork, flow);
    if (!result)
    {
        std::cout << "Returned flow violates capacity condition.\n";
        return false;
    }
    result = verifyConservationCondition(flow, numVertices, source, sink);
    if (!result)
    {
        std::cout << "Returned flow violates conservation condition.\n";
        return false;
    }
    return true;
}

static void printFlowValue(unsigned flowValue)
{
    std::cout << "Flow value: " << flowValue << '\n';
}

static void printNumAssignedCourses(unsigned numAssigned)
{
    std::cout << "Number of assigned courses: " << numAssigned << '\n';
}

static unsigned getFlowValue(const std::vector<Edge>& flow,
                             unsigned source)
{
    // Compute the flow exiting the source.
    // (This is equivalent to calculating the flow entering the sink.)
    unsigned flowValue = 0;
    for (const Edge& edge : flow)
        if (edge.from == source)
            flowValue += edge.weight;
    return flowValue;
}

static void case1()
{
    try
    {
        solveNetworkFlow({{0, 0, 3}}, 1);
        NO_CATCH_EXPECTED_EXCEPTION
    }
    CATCH_EXPECTED_EXCEPTION
}

static void case2()
{
    try
    {
        solveNetworkFlow({}, 2);
        NO_CATCH_EXPECTED_EXCEPTION
    }
    CATCH_EXPECTED_EXCEPTION
}

static void case3()
{
    try
    {
        solveNetworkFlow({
            {0, 1, 3},
            {0, 2, 0},
            {1, 2, 4}
        },
        3);
        NO_CATCH_EXPECTED_EXCEPTION
    }
    CATCH_EXPECTED_EXCEPTION
}

static void case5()
{
    try
    {
        solveNetworkFlow({
            {0, 1, 3},
            {0, 2, 1},
            {1, 2, 4},
            {2, 3, 1}
        },
        3);
        NO_CATCH_EXPECTED_EXCEPTION
    }
    CATCH_EXPECTED_EXCEPTION
}

static void case7()
{
    try
    {
        solveNetworkFlow({
            {0, 1, 3},
            {0, 2, 1},
            {1, 2, 4},
            {0, 0, 1}
        },
        3);
        NO_CATCH_EXPECTED_EXCEPTION
    }
    CATCH_EXPECTED_EXCEPTION
}

static void case9()
{
    try
    {
        solveNetworkFlow({
            {0, 1, 3},
            {0, 2, 1},
            {1, 2, 4},
            {0, 2, 2}
        },
        3);
        NO_CATCH_EXPECTED_EXCEPTION
    }
    CATCH_EXPECTED_EXCEPTION
}

static void case11()
{
    try
    {
        solveNetworkFlow({
            {1, 0, 3},
            {2, 0, 4},
            {0, 3, 5}
        },
        4);
        NO_CATCH_EXPECTED_EXCEPTION
    }
    CATCH_EXPECTED_EXCEPTION
}

static void case13()
{
    try
    {
        solveNetworkFlow({
            {1, 0, 3},
            {1, 2, 4},
            {1, 3, 5}
        },
        4);
        NO_CATCH_EXPECTED_EXCEPTION
    }
    CATCH_EXPECTED_EXCEPTION
}

static void case15()
{
    std::vector<Edge> flowNetwork{
        {2, 4, 1},
        {1, 2, 2},
        {1, 3, 100},
        {3, 4, 5},
        {1, 0, 6},
        {0, 4, 3}
    };
    unsigned numVertices = 5;
    std::vector<Edge> flow = solveNetworkFlow(flowNetwork, numVertices);
    unsigned source = 1;
    unsigned sink = 4;
    if (verifyFlow(flowNetwork, flow, numVertices, source, sink))
    {
        unsigned flowValue = getFlowValue(flow, source);
        printFlowValue(flowValue);
    }
}

#define appendPref(course) \
    instructors.back().addPreference((course))

static bool verifyAssignment(
    const std::vector<Instructor>& instructors,
    const std::vector<Instructor>& instructorsCopy,
    const std::vector<std::string>& courses,
    unsigned* numAssigned)
{
    *numAssigned = 0;

    std::vector<std::string> assignedCourses;

    // Verify that no instructor is assigned to a course he/she did not want.
    for (const Instructor& ins : instructorsCopy)
    {
        // Find the instructor in the student's that matches this one.
        for (const Instructor& ins2 : instructors)
        {
            if (ins.lastName != ins2.lastName)
                continue;

            // Check if any course here is not in the instructor's preferences.
            for (const std::string& assigned : ins2.assignedCourses)
            {
                if (std::find(ins.preferences.begin(),
                              ins.preferences.end(),
                              assigned)
                    == ins.preferences.end())
                {
                    std::cout << "Instructor assigned to course he/she did not want.\n";
                    return false;
                }
                assignedCourses.push_back(assigned);
            }

            break;
        }
    }

    // Verify that no course is assigned twice.
    for (unsigned i = 0; i < assignedCourses.size(); ++i)
        for (unsigned j = i + 1; j < assignedCourses.size(); ++j)
            if (assignedCourses[i] == assignedCourses[j])
            {
                std::cout << "At least one course was assigned twice.\n";
                return false;
            }

    // Calculate the number of courses assigned.
    for (const Instructor& ins : instructors)
        *numAssigned += ins.assignedCourses.size();

    return true;
}

static std::vector<Instructor> copyInstructors(
    const std::vector<Instructor>& instructors)
{
    std::vector<Instructor> copy;
    for (const auto& ins : instructors)
        copy.push_back(ins);
    return copy;
}

static void case20()
{
    std::vector<Instructor> instructors;
    instructors.emplace_back("Frid", 2);
    appendPref("ECS 120");
    appendPref("ECS 122A");
    appendPref("ECS 36C");
    instructors.emplace_back("Franklin", 1);
    appendPref("ECS 120");
    instructors.emplace_back("Porquet", 1);
    appendPref("ECS 158");
    appendPref("ECS 36C");
    instructors.emplace_back("Matloff", 1);
    appendPref("ECS 132");
    appendPref("ECS 158");
    instructors.emplace_back("Eiselt", 1);
    appendPref("ECS 32B");
    instructors.emplace_back("Butner", 1);
    appendPref("ECS 32B");
    std::vector<std::string> courses{
        "ECS 32B",
        "ECS 36C",
        "ECS 120",
        "ECS 122A",
        "ECS 132",
        "ECS 158"
    };
    auto copyIns = copyInstructors(instructors);
    assignCourses(instructors, courses);
    unsigned numAssigned = 0;
    if (verifyAssignment(instructors,
                         copyIns,
                         courses,
                         &numAssigned))
        printNumAssignedCourses(numAssigned);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Need case number as command-line argument.\n";
        return EXIT_TEST_MISUSE;
    }
    unsigned caseNum = atoi(argv[1]);

    /**
     * Run the desired test case.
     *
     * For some reason, it does not seem that there is a way in C++ for
     * me to run the CASE_CALL_TEST() macro on a range of integers,
     * so I had to keep pasting that macro.
     */
    try
    {
        #define CASE_CALL_TEST(caseNum) \
            case (caseNum): case##caseNum(); break;
        switch (caseNum)
        {
        CASE_CALL_TEST(1)
        CASE_CALL_TEST(2)
        CASE_CALL_TEST(3)
        CASE_CALL_TEST(5)
        CASE_CALL_TEST(7)
        CASE_CALL_TEST(9)
        CASE_CALL_TEST(11)
        CASE_CALL_TEST(13)
        CASE_CALL_TEST(15)
        CASE_CALL_TEST(20)
        default:
            std::cerr << "Bad case number.\n";
            return EXIT_TEST_MISUSE;
        }
    }
    catch (...)
    {
        std::cout << "Unexpected exception caught.\n";
    }
}
