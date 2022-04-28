#include "netflow.hpp"

#include <iostream>

#define appendPref(course) \
    instructors.back().addPreference((course))

int main()
{
    /**
     * I use real instructors' names for fun, but do note that the
     * preference lists are not necessarily accurate.
     * I picked them in a way that leads to an interesting result
     * in which one of Butner or Posnett cannot be assigned
     * as many courses as he desires. (That is, if Posnett is
     * assigned ECS 154A, then Butner cannot be assigned two courses.)
     */
    std::vector<Instructor> instructors;
    instructors.emplace_back("Kaloti", 2);
    appendPref("ECS 50");
    appendPref("ECS 36C");
    appendPref("ECS 34");
    instructors.emplace_back("Nitta", 1);
    appendPref("ECS 150");
    appendPref("ECS 34");
    appendPref("ECS 154A");
    instructors.emplace_back("Porquet", 1);
    appendPref("ECS 150");
    appendPref("ECS 36C");
    instructors.emplace_back("Butner", 2);
    appendPref("ECS 36A");
    appendPref("ECS 154A");
    instructors.emplace_back("Posnett", 1);
    appendPref("ECS 154A");
    std::vector<std::string> courses{"ECS 34", "ECS 36A",
        "ECS 36C", "ECS 50", "ECS 150", "ECS 154A"};
    assignCourses(instructors, courses);
    for (const Instructor& instructor : instructors)
    {
        std::cout << "Prof. " << instructor.lastName
                  << " is assigned to teach:";
        for (const std::string& course : instructor.assignedCourses)
            std::cout << ' ' << course;
        std::cout << std::endl;
    }
}
