
// ecs36b first program

#include <iostream>
#include "Shadow_Flight.h"
#include "Shadow_Person.h"

using namespace std;

int main() {
  Shadow_Flight f3 { "http://localhost:8384", "123456789", "Flight", "00000003" };
  std::cout << std::to_string(f3.getDistance()) << std::endl;
  
  Shadow_Flight f2 { "http://localhost:8384", "123456789", "Flight", "00000002" };
  std::cout << std::to_string(f2.getDistance()) << std::endl;
  std::cout << std::to_string(f2.Conflict_of_Interest()) << std::endl;

  Shadow_Person p3 {"http://localhost:8384", "1145141919810", "Person", "00000005"};
  std::cout << ((Person&)p3).getVsID() << std::endl;
  Shadow_Person p4 {"http://localhost:8384", "11111111111111", "Person", "00000006"};
  std::cout << std::to_string(p3.operator==(p4)) << std::endl;
  
}
 