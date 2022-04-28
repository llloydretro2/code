
// for Json::value
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>
#include <string>

// for JsonRPCCPP
#include <iostream>
#include "hw3server.h"
#include <jsonrpccpp/server/connectors/httpserver.h>
#include <stdio.h>

// ecs36b
#include "Core.h"
#include "Person.h"
#include "Transaction.h"
#include "Shadow_Flight.h"
#include "Shadow_Person.h"
#include <time.h>

using namespace jsonrpc;
using namespace std;

class Myhw3Server : public hw3Server
{
public:
  Myhw3Server(AbstractServerConnector &connector, serverVersion_t type);
  virtual Json::Value ecs36b_hw3(const std::string& action, const std::string& arguments, const std::string& class_id, const std::string& host_url, const std::string& object_id, const std::string& owner_vsID);
  virtual Json::Value GetDistance(const std::string& action, const std::string& arguments, const std::string& class_id, const std::string& host_url, const std::string& object_id, const std::string& owner_vsID);
  virtual Json::Value Conflict_of_Interest(const std::string& action, const std::string& arguments, const std::string& class_id, const std::string& host_url, const std::string& object_id, const std::string& owner_vsID);
  virtual Json::Value OperatorEqEq(const std::string& aPerson_class_id, const std::string& aPerson_host_url, const std::string& aPerson_object_id, const std::string& aPerson_owner_vsID, const std::string& action, const std::string& arguments, const std::string& class_id, const std::string& host_url, const std::string& object_id, const std::string& owner_vsID);
  virtual Json::Value GetVsID(const std::string& action, const std::string& arguments, const std::string& class_id, const std::string& host_url, const std::string& object_id, const std::string& owner_vsID);
};

Myhw3Server::Myhw3Server(AbstractServerConnector &connector, serverVersion_t type)
  : hw3Server(connector, type)
{
  std::cout << "Myhw3Server Object created" << std::endl;
}

Flight *f2;
Flight *f3;
Person *p3;
Person *p4;

// member function
Json::Value
Myhw3Server::ecs36b_hw3
(const std::string& action, const std::string& arguments,
 const std::string& class_id, const std::string& host_url,
 const std::string& object_id, const std::string& owner_vsID)
{
  Json::Value result;
  std::cout << action << " " << arguments << " " << owner_vsID << std::endl;
  std::string strJson;

  double d;
  if ((class_id != "Flight") || ((object_id != "00000002") && (object_id != "00000003")))
    {
      strJson += "{\"status\" : \"failed\", ";
      if (class_id != "Flight")
	strJson += ("\"reason\": \"class " + class_id + " unknown\"}");
      else
	strJson += ("\"reason\": \"object " + object_id + " unknown\"}");
    }
  else
    {
      if (object_id == "00000002")
	d = f2->getDistance();
      else
	d = f3->getDistance();

      strJson += "{\"status\" : \"successful\", ";
      strJson += ("\"distance\": " + to_string(d) + "}");
    }

  Json::CharReaderBuilder builder;
  Json::CharReader* reader = builder.newCharReader();
  std::string errors;
  bool parsingSuccessful = reader->parse
    (strJson.c_str(), strJson.c_str() + strJson.size(), &result, &errors);
  delete reader;

  if (!parsingSuccessful) {
    std::cout << "Failed to parse the JSON, errors:" << std::endl;
    std::cout << errors << std::endl;
  }

  return result;
}




Json::Value
Myhw3Server::GetDistance
(const std::string& action, const std::string& arguments,
 const std::string& class_id, const std::string& host_url,
 const std::string& object_id, const std::string& owner_vsID)
{
  Json::Value result;
  std::cout << action << " " << arguments << " " << owner_vsID << std::endl;
  std::string strJson;

  double d;
  if ((class_id != "Flight") || ((object_id != "00000002") && (object_id != "00000003")))
    {
      strJson += "{\"status\" : \"failed\", ";
      if (class_id != "Flight")
	strJson += ("\"reason\": \"class " + class_id + " unknown\"}");
      else
	strJson += ("\"reason\": \"object " + object_id + " unknown\"}");
    }
  else
    {
      if (object_id == "00000002")
	d = f2->getDistance();
      else
	d = f3->getDistance();

      strJson += "{\"status\" : \"successful\", ";
      strJson += ("\"distance\": " + to_string(d) + "}");
    }

  Json::CharReaderBuilder builder;
  Json::CharReader* reader = builder.newCharReader();
  std::string errors;
  bool parsingSuccessful = reader->parse
    (strJson.c_str(), strJson.c_str() + strJson.size(), &result, &errors);
  delete reader;

  if (!parsingSuccessful) {
    std::cout << "Failed to parse the JSON, errors:" << std::endl;
    std::cout << errors << std::endl;
  }
  std::cout<<"GetDistance called in hw3server"<<std::endl;
  return result;
}

// all the function


Json::Value
Myhw3Server::GetVsID
(const std::string& action, const std::string& arguments,
 const std::string& class_id, const std::string& host_url,
 const std::string& object_id, const std::string& owner_vsID)
{
  Json::Value result;
  std::cout << action << " " << arguments << " " << owner_vsID << std::endl;
  std::string strJson;
printf("Hello\n");

  std::string d;
  if ((class_id != "Person") || ((object_id != "00000005") && (object_id != "00000006")))
    {
      strJson += "{\"status\" : \"failed\", ";
      if (class_id != "Person")
	strJson += ("\"reason\": \"class " + class_id + " unknown\"}");
      else
	strJson += ("\"reason\": \"object " + object_id + " unknown\"}");
    }
  else
    {
      if (object_id == "00000005")
	      d = p3->getVsID();
      else
        d = p4->getVsID();
  /*
      else
	std::string d = p2->getVsID();
  */

      strJson += "{\"status\" : \"successful\", ";
      strJson += ("\"getvsID\": " + d + "}");
    }

  Json::CharReaderBuilder builder;
  Json::CharReader* reader = builder.newCharReader();
  std::string errors;
  bool parsingSuccessful = reader->parse
    (strJson.c_str(), strJson.c_str() + strJson.size(), &result, &errors);
  delete reader;

  if (!parsingSuccessful) {
    std::cout << "Failed to parse the JSON, errors:" << std::endl;
    std::cout << errors << std::endl;
  }
  std::cout<<"GetVsID called in hw3server"<<std::endl;

  return result;
}




Json::Value
Myhw3Server::Conflict_of_Interest
(const std::string& action, const std::string& arguments,
 const std::string& class_id, const std::string& host_url,
 const std::string& object_id, const std::string& owner_vsID)
{
  Json::Value result;
  std::cout << action << " " << arguments << " " << owner_vsID << std::endl;
  std::string strJson;

  bool d;
  if ((class_id != "Flight") || ((object_id != "00000002") && (object_id != "00000003")))
    {
      strJson += "{\"status\" : \"failed\", ";
      if (class_id != "Flight")
	strJson += ("\"reason\": \"class " + class_id + " unknown\"}");
      else
	strJson += ("\"reason\": \"object " + object_id + " unknown\"}");
    }
  else
    {
      if (object_id == "00000002")
	d = f2->Conflict_of_Interest();
      else
	d = f3->Conflict_of_Interest();

      strJson += "{\"status\" : \"successful\", ";
      strJson += ("\"conflict_of_interest\": " + to_string(d) + "}");
    }

  Json::CharReaderBuilder builder;
  Json::CharReader* reader = builder.newCharReader();
  std::string errors;
  bool parsingSuccessful = reader->parse
    (strJson.c_str(), strJson.c_str() + strJson.size(), &result, &errors);
  delete reader;

  if (!parsingSuccessful) {
    std::cout << "Failed to parse the JSON, errors:" << std::endl;
    std::cout << errors << std::endl;
  }

  return result;
}






Json::Value
Myhw3Server::OperatorEqEq
(const std::string& aPerson_class_id, const std::string& aPerson_host_url, const std::string& aPerson_object_id, const std::string& aPerson_owner_vsID, const std::string& action, const std::string& arguments,
 const std::string& class_id, const std::string& host_url,
 const std::string& object_id, const std::string& owner_vsID)
{
  Json::Value result;
  std::cout << action << " " << arguments << " " << owner_vsID << std::endl;
  std::string strJson;

  bool d;
  if ((class_id != "Person") || ((object_id != "00000005") && (object_id != "00000006")))
    {
      strJson += "{\"status\" : \"failed\", ";
      if (class_id != "Flight")
	strJson += ("\"reason\": \"class " + class_id + " unknown\"}");
      else
	strJson += ("\"reason\": \"object " + object_id + " unknown\"}");
    }
  else
    {
      if (object_id == "00000005")
	d = p3->operator==(*p4);
  else
  d=p3->operator==(*p4);

      strJson += "{\"status\" : \"successful\", ";
      strJson += ("\"operator==\": " + to_string(d) + "}");
    }

  Json::CharReaderBuilder builder;
  Json::CharReader* reader = builder.newCharReader();
  std::string errors;
  bool parsingSuccessful = reader->parse
    (strJson.c_str(), strJson.c_str() + strJson.size(), &result, &errors);
  delete reader;

  if (!parsingSuccessful) {
    std::cout << "Failed to parse the JSON, errors:" << std::endl;
    std::cout << errors << std::endl;
  }

  return result;
}





int main() {

  Airline United;
  GPS_DD gps_Davis {38.5, -121.7};
  GPS_DD gps_NYC {40.7, -73.95};
  GPS_DD gps_Sydney {-33.87, 151.213};
  IP_Address IP_Davis {12345678};
  IP_Address IP_Sydney {12345678};
  IP_Address IP_NYC {12375678};

  Person p1 {"Lion King", "123456789123456789"};
  Person p2 {"Lion Queen", "223456789123456789"};
  
  Person person_3 {"http://169.237.6.102", "1234567890", "Person", "00000005", "p3", "1145141919810"};
  Person person_4 {"http://169.237.6.102", "1234567890", "Person", "00000006", "p4", "1145141"};
  //  Transaction flight_one {"http://169.237.6.102", "1234567890", "Transaction", "00000001",
  //    TR_TYPE_FLIGHT, "desc", p1, gps_Davis, IP_Davis, time(NULL)};

  Flight flight_two {"http://169.237.6.102", "1234567890", "Flight", "00000002", TR_TYPE_FLIGHT, "desc", p1, gps_Davis, IP_Davis, time(NULL), p2, United, "1234567890", gps_Davis, gps_NYC};
  Shadow_Flight flight_three { "http://localhost:8385", "123456789", "Flight", "00000003" };

  f2 = (&flight_two);
  f3 = (&flight_three);
  
  p3 = (&person_3);
  p4 = (&person_4);

  HttpServer httpserver(8384);
  Myhw3Server s(httpserver, JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)
  s.StartListening();
  std::cout << "Hit enter to stop the server" << endl;
  getchar();

  s.StopListening();
  return 0;
}
