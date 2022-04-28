
#ifndef _PERSON_H_
#define _PERSON_H_

#include "Core.h"

// Person.h
#include <iostream>

class GPS_DD
{
 private:
  double latitude;
  double longtitude;
 public:
  GPS_DD();
  GPS_DD(double, double);
  double getLatitude();
  double getLongtitude();
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

class Person : public Core
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
  Person(std::string core_arg_host_url, std::string core_arg_owner_vsID,
                std::string core_arg_class_id, std::string core_arg_object_id);
  Person(std::string core_arg_host_url, std::string core_arg_owner_vsID,
                std::string core_arg_class_id, std::string core_arg_object_id,
                std::string arg_name, std::string arg_id);
  void setHome(std::string);
  void setHome(GPS_DD);
  virtual bool operator==(Person& aPerson);
  virtual std::string getVsID();
  std::string getName();
};

#endif  /* _PERSON_H_ */
