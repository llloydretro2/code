
// Person.h for ecs36b_hw2_part2, not to be modified

#ifndef _PERSON_H_
#define _PERSON_H_

// Person.h
#include <iostream>

class GPS_DD
{
 private:
  double latitude;
  double longitude;
 public:
  GPS_DD();
  GPS_DD(double, double);
  double getLatitude();
  double getLongitude();
  double distance(GPS_DD&);
};

class IP_Address
{
 private:
  unsigned int addr;
 public:
  IP_Address();
  IP_Address(unsigned int);
  std::string& getIPaddressString();
  unsigned int getIPaddressValue();
};

class Person
{
 private:
  static unsigned int person_count;
  std::string vsID;
  std::string name;
  std::string hometown;
  GPS_DD home;
 public:
  Person();
  Person(std::string, std::string);
  void setHome(std::string);
  void setHome(GPS_DD);
  bool operator==(Person& aPerson);
  std::string getVsID();
  std::string getName();
};

#endif  /* _PERSON_H_ */
