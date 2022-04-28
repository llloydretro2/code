
// f2021 version of HW2 part2

#include "Person.h"

unsigned int Person::person_count {0};

GPS_DD::GPS_DD()
{
  // finished
  this->latitude = 0.0;
  this->longitude = 0.0;
}

GPS_DD::GPS_DD(double arg_latitude, double arg_longitude)
{
  // finished
  this->latitude = arg_latitude;
  this->longitude = arg_longitude;
}

double 
GPS_DD::getLatitude()
{
  // finished
  return this->latitude;
}
 
double
GPS_DD::getLongitude
()
{
  // finished
  return this->longitude;
}

// DD distance calculation
#include <math.h>
#define pi 3.14159265358979323846

double deg2rad(double);
double rad2deg(double);

double GeoDataSource_distance(double lat1, double lon1, double lat2, double lon2, char unit) 
{
  double theta, dist;
  if ((lat1 == lat2) && (lon1 == lon2)) {
    return 0;
  }
  else {
    theta = lon1 - lon2;
    dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2)) + cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * cos(deg2rad(theta));
    dist = acos(dist);
    dist = rad2deg(dist);
    dist = dist * 60 * 1.1515;
    switch(unit) {
      case 'M':
        break;
      case 'K':
        dist = dist * 1.609344;
        break;
      case 'N':
        dist = dist * 0.8684;
        break;
    }
    return (dist);
  }
  // to be implemented by the student
  // for this homework, please use the source code shared by GeoDataSource under --
  // https://www.geodatasource.com/developers/c (you can copy and paste here)
}

double deg2rad(double deg)
{
  // finished
  return (deg * pi / 180);
}

double rad2deg(double rad)
{
  // finished
  return (rad * 180 / pi);
}

double
GPS_DD::distance
(GPS_DD& another)
{
  return GeoDataSource_distance(this->getLatitude(), this->getLongitude(), another.getLatitude(), another.getLongitude(), 'M');
  // to be implemented by the student
  // something like: return GeoDataSource_distance(,,,,);
}

IP_Address::IP_Address()
{
  // do nothing here for now
}

IP_Address::IP_Address
(unsigned int arg_ip)
{
  // do nothing here for now
}

std::string SDefault {"Default"};

std::string&
IP_Address::getIPaddressString()
{  
  // do nothing here for now
  // std::string s {"0.0.0.0"};
  // return s;
}

unsigned int
IP_Address::getIPaddressValue()
{
  // do nothing here for now
  return 0;
}

Person::Person()
{
  this->name = "a";
  this->vsID = 1;
  Person::person_count++;
  
  // to be implemented by the student
}

Person::Person
(std::string arg_name, std::string arg_id)
{
  this->name = arg_name;
  this->vsID = arg_id;
  Person::person_count++;
  
  // to be implemented by the student
}

void
Person::setHome
(std::string arg_home)
{
  this->hometown = arg_home;
  // to be implemented by the student
}

void
Person::setHome
(GPS_DD arg_home)
{
  this->home = arg_home;
  // to be implemented by the student
}

std::string
Person::getVsID()
{
  return this->vsID;
  // to be implemented by the student
}

std::string
Person::getName()
{
  return this->name;
  // to be implemented by the student
}

bool
Person::operator==
(Person& aPerson)
{
  if (this->getVsID() == aPerson.getVsID())
  {
    return true;
  }
  return false;
  // to be implemented by the student
}
