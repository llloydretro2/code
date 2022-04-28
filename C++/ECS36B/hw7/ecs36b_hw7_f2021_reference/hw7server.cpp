
// for Json::value
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>
#include <string>
#include <ctype.h>

// for JsonRPCCPP
#include <iostream>
#include "hw7server.h"
#include <jsonrpccpp/server/connectors/httpserver.h>
#include <stdio.h>

// ecs36b_hw7
#include "Post.h"

std::map<std::string, Post *> Post_Map;
std::map<std::string, JvTime *> RT_Map;

extern const char *hw5error[];

using namespace jsonrpc;
using namespace std;

class Myhw7Server : public hw7Server
{
public:
  Myhw7Server(AbstractServerConnector &connector, serverVersion_t type);
  virtual Json::Value update(const std::string& updating_json);
  virtual Json::Value search(const std::string& search_clause);
};

Myhw7Server::Myhw7Server(AbstractServerConnector &connector, serverVersion_t type)
  : hw7Server(connector, type)
{
  std::cout << "Myhw7Server Object created" << std::endl;
}

// member functions

int
checkTimeInterval
(std::string arg_id)
{
  time_t ticks; 
  ticks = time(NULL);
  struct std::tm * my_tm_ptr = gmtime(&ticks);
  JvTime * now_time_ptr = new JvTime();
  int rc = now_time_ptr->setStdTM(my_tm_ptr);
  if (rc != HW5_ERROR_NORMAL)
    {
      std::cout << "error: failed to set time!" << std::endl;
      delete now_time_ptr;
      return HW5_ERROR_SET_STD_TM;
    }
  
  if (RT_Map.find(arg_id) == RT_Map.end())
    {
      RT_Map[arg_id] = now_time_ptr;
      return HW5_ERROR_NORMAL;
    }

  double time_diff = 0.0;
	  
  // Now we should check the timestamp
  JvTime *old_time_ptr = RT_Map[arg_id];

  time_diff = (*now_time_ptr) - (*old_time_ptr);
  delete old_time_ptr;
  RT_Map[arg_id] = now_time_ptr;

  std::cout << "Time_Diff = " << time_diff << std::endl;
  if (time_diff < 5.0)
    {
      return HW5_ERROR_SMACK_STACK_DETECTED;
    }
  return HW5_ERROR_NORMAL;
}

Json::Value
Myhw7Server::update(const std::string& updating_json)
{

Json::Value result_json;
char fname_buf[1024];
FILE * post_f_ptr;
int rc = HW5_ERROR_NORMAL;
Post * post_ptr = NULL;
#ifdef _ECS36B_DEBUG_
std:: cout<<"update"<<<< updating_json << std::endl;
#endif/*ECS36B DEBUG*/


//print the log

myPrintLog("(\"location\":\"p0\"}", "hw7server_update.log");
    try{

      if ((updating_json.c_str())[0] != '{')
        throw HW5_ERROR_JSON_PARSING;
        
     

  myPrintLog(updating_json, "hw7server_update.log");

    Json::Value myv_message;
    rc= checkBigID(updating_json);  
  if (rc != HW5_ERROR_NORMAL) throw rc;
  rc = myParseJSON(updating_json, &myv_message);
  if (rc != HW5_ERROR_NORMAL) throw rc;
  //set the json_post file name
  if (((myv_message["id" ]).isNull()== true) &&
  ((myv_message["id" ]).isString() == false) && (checkPostID((myv_message["id"]) .asString()) != 0))
  {
    throw HW5_ERROR_JSON_POST_NO_ID;
  }
//1 checking for timestamp
rc= checkTimeInterval ( (myv_message["id"]).asString());
if (rc != HW5_ERROR_NORMAL) throw rc;
#ifdef _SUSPICIOUS_
 //these were suspicious requests (now we will do it differently
if ((strcmp(112638136365359860811666331781839957994_262650593813279*
((myv_message["id" ]) . asString()) .c str()) == 0) ||
(strcmp("13138632993542341544767636272106082590_2626505938132791",
((myv_message["id" ]).asString() ) .c_str())==0) ||
(strcmp("818825745475509662924811371419165400_100098",
((myv_message["id"]).asString() ).c_str())==0))
{
throw HW5_ERROR_SUSPICIOUS;
}
#endif /*_SUSPICIOUS_ */

    bzero(fname_buf, 1024) ;
    sprintf (fname_buf, "./posts/post_%s.ison" ,((myv_message[ "id"]).asString()) .c_str());
    std::cout << " name: "<< fname_buf << std::endl;

    //check vsID portion of id
  {
    char idstr[1024];
    bzero(idstr, 1024);
    sprintf(idstr,"%s", ((myv_message["id"]).asString()).c_str());
    char c_prof_buf[256];
    char c_post_buf[256];
    bzero(c_prof_buf, 256) ;
    bzero(c_post_buf, 256) ;
    sscanf(idstr,c_prof_buf, c_post_buf);
    std::string s_vsID { c_prof_buf};
    #ifdef _REAL_SERVER_
    if (vsID_Map.find (s_VsID) == vsID_Map. end ())
    {
    // invalid vsID
    throw HW5_ERROR_VSID_POST_ID;
    }
 # endif/* REAL_SERVER_ */
}
      myPrintLog("{\"location\":\"entering 3 cases\"}", "hw7server update.log");
      if (Post_Map.find((myv_message["id"]).asString()) != Post_Map. end())
    {
    // case (1)
    // we need to merge
    myPrintLog ("{\"location\":\"case 1\"}", "hw7server_update.log");
    post_ptr = Post_Map[ (myv_message["id"]).asString()];
    myPrintLog("{\"location\":\"before Json Post Merging\"}","hw7server_update.log");

    // was (s2020)-=> IC = Json Post_Mêrging(myv_message, post_ptr);
    bool result_flag = post_ptr->Jdump(&myv_message);
    if (result_flag == false){
        throw HW5_ERROR_JSON_POST_MERGING;
}
    myPrintLog("{\"location\":\" after Json Post Merging\"}","hw7server_update.log");
    
}
else{
  Json::Value pjf_v;
  rc = myFile2JSON(fname_buf, &pjf_v);
  if(rc == HW5_ERROR_NORMAL){
    //case 2
    myPrintLog("{\"location\":\"case 2\"}", "hw7server_update.log");
    post_ptr = new Post((Person *) NULL, (Message *) NULL);
    myPrintLog("{\"location\":\"before Json2 Post Merging\"}","hw7server_update.log");
    bool result_flag = post_ptr -> Jdump(&pjf_v);
    myPrintLog("{\"location\":\"after Json2 Post Merging\"}","hw7server_update.log");
    if(result_flag == false){
      delete post_ptr;
      throw HW5_ERROR_JSON_2_POST;
    }
    else
{
    std::cout <<"update p2 case 2s\n";
    Post_Map[ (myv_message["id" ]).asString()] = post_ptr;
    myPrintLog("(\"location\":\"before Json Post Merging\"}", "hw7server_update.");
    // was (s2020) ==> rc = Json_Post_Merging (myv_message, post_ptr);
      bool result_flag = post_ptr->Jdump(&myv_message);
      myPrintLog ("(\"location)\":\"after Json Post Merging\"}", "hw7server_update.");
      if(result_flag == false)
{
      throw HW5_ERROR_JSON_POST_MERGING;
      }
    }
  }
else
{

      myPrintLog("[\"location\": \"case 3\"}", "hw6server update.log");
    // case (3)
    // create a new Post
      post_ptr = new Post ((Person *) NULL, (Message *) NULL);
      myPrintLog("(\"location\":\"before Json_2_post\"}", "hw7server_update.");
      bool result_flag = post_ptr->Jdump(&myv_message);
      myPrintLog("(\"location\": \"after Json 2 Post\"}","hw7server_update.log") ;
    if (result_flag== false)
    {
    delete post_ptr;
    throw HW5_ERROR_JSON_2_POST;
    }
    else 
        Post_Map[(myv_message["id"]).asString()] = post_ptr;


          }
        }     
      } 
  
catch (int error_code)
{
myPrintLog("(\"location\": \"catch\"}","hw7server_update.log");
int erc = produceErrorJSON(error_code, "hw7server_update.log", &result_json, 0);
if (erc != HW5_ERROR_NORMAL)
  myPrintLog("(\"location\": \"catch\"}","hw7server_update.log");
return result_json;
}
  
myPrintLog("(\"location\": \"before write back\"}","hw7server_update.log");
if (post_ptr == NULL)
{
    myPrintLog("(\"location\":\"before write back POST PTR null\")", "hw7server_update.log");
}
      Json::Value * jj= post_ptr->dumpJ();
      myPrintLog("{\"location\":\"after dumbj\"}","hw7server_update.log");
      rc = myJSON2File(fname_buf, jj);
      myPrintLog("(\"location\": \"after Json2File\"}","hw7server_update.log");
      if (rc != HW5_ERROR_NORMAL)
      {
      int erc= produceErrorJSON(rc, "hwöserver update. log" , &result_json, 0);
      if (erc != HW5_ERROR_NORMAL )
          myPrintLog("(\"location\": \"Write back double errors\"}","hw7server_update.log");
      return result_json;

      }
      myPrintLog("(\"location\":\"after write back\")", "hw7server_update.log");
      std::cout << Post_Map.size() << "\n";
      Json::Value *rj_ptr = post_ptr->dumpJ();
      myPrintLog("(\"location\": \"after dumbJ\"}","hw7server_update.log");
      produceErrorJSON(HW5_ERROR_NORMAL, "hw7server_update.log", &result_json, 0);
        
        return *rj_ptr;
}



Json::Value
Myhw7Server::search
(const std::string& search_clause)
{
  Json::Value result_json;

  int rc = HW5_ERROR_NORMAL;
  #ifdef _ECS36B_DEBUG_
      std::cout << "serach" << " "<< search_clause << std::endl;
    #endif /*_ECS36B_DEBUG_ */

    myPrintLog("(\"location\": \"p0\"}","hw7server_search.log");
    try{
    if((search_clause.c_str())[0] != '{')
      throw HW5_ERROR_JSON_PARSING;
    myPrintLog( search_clause,"hw7server_search.log");
    Json::Value myv_message;
    rc = myParseJSON(search_clause, &myv_message);
    if(rc != HW5_ERROR_NORMAL) throw rc;
    if(myv_message.isObject() != true){
      throw HW5_ERROR_BAD_KEYWORD_FORMAT;
    }
    Json::Value json_data;
    if((myv_message["keyword"]).isNull()== true){
      throw HW5_ERROR_NO_SEARCH_KEYWORD;
    }
    if((myv_message["keyword"]).isString()== true){
      throw HW5_ERROR_BAD_KEYWORD_FORMAT;
    }
    myPrintLog("(\"location\": \"p1\"}","hw7server_search.log");

    char fn_buf[256];
    bzero (fn_buf,256);
    char test_str [256];
    bzero(test_str,256);
    sprintf(test_str, "%s", ((myv_message["keyword"]).asString()).c_str());

    char cbuf[1024];
    bzero(cbuf,1024);
    
    

    int ii;
    for (ii=0; ii <strlen(test_str); ii++){
      if((test_str[ii]>= 'A')&& (test_str[ii] <='Z'))
      cbuf[ii]= tolower(test_str[ii]);
      else
        cbuf[ii] = test_str[ii];
    }
    sprintf(fn_buf, "./okeys/okey_%s.list", cbuf);
    std:: string s= fn_buf;
    myPrintLog(s, "hw7server_search.log");
    FILE * okey_f = fopen(fn_buf, "r");
    if(okey_f == NULL){
      throw HW5_ERROR_NO_OKEY;
    }
    char post_id_buf[1024];
    int okey_flag = 1;
    int post_count = 0;
    int i =0;
    Json::Value *dumbjv_ptr;

    myPrintLog("(\"location\": \"p2\"}","hw7server_search.log");
    while(okey_flag){
      bzero(post_id_buf, 1024);
      int f_rc = fscanf(okey_f, "%[^\n]", post_id_buf);
      std::cout<< post_id_buf << std::endl;
      std::string post_id_string = post_id_buf;
      if(f_rc == EOF){
        okey_flag = 0;
      }
      else{
            if(checkPostID(post_id_string)==0){
              char pfn_buf [1024];
              bzero (pfn_buf, 1024);
              sprintf(pfn_buf, "./post/post_%s.json", post_id_buf);
              std::cout<< pfn_buf<< std::endl;

              myPrintLog("(\"location\": \"p3\"}","hw7server_search.log");
              Json::Value pjf_v;
              rc = myFile2JSON(pfn_buf, &pjf_v);
              if(rc!= HW5_ERROR_NORMAL){
                std::string s {  "{\"id 113\"}:{"};
                s+= "\"}";
                myPrintLog(s,"hw7server_search.log");
              }
              else {
                Post *post_ptr = new Post((Person*) NULL , (Message *) NULL);
                myPrintLog("(\"location\": \"before Json_2_post\"}","hw7server_search.log");

                bool result_flag = post_ptr -> Jdump(& pjf_v);
                myPrintLog("(\"location\": \"after Json_2_post\"}","hw7server_search.log");
                if (result_flag == false){
                  std::string s {  "{\"id 114\"}:{" };
                    s+= "\"}";
                  myPrintLog(s,"hw7server_search.log");
                }
                else {
                  dumbjv_ptr = post_ptr-> dumpJ();
                  json_data[i]= (*dumbjv_ptr);
                  i++;
                  delete dumbjv_ptr;
                }
              }
            }
      }
      fgetc(okey_f);
    }
    fclose (okey_f);
    result_json["data"] = json_data;
    result_json["count"] = ((int)i);
    }
   catch(int error_code){
      myPrintLog("(\"location\": \"catch\"}","hw7server_search.log");
      int erc = produceErrorJSON(error_code, "hw7server_search.log", &result_json, 0);
      if(erc != HW5_ERROR_NORMAL)
        myPrintLog("(\"location\": \"catch more\"}","hw7server_search.log");
      return result_json;
   }   
  myPrintLog("(\"location\": \"before the end\"}","hw7server_search.log");
  Json::Value r2;
  produceErrorJSON (HW5_ERROR_NORMAL, "hw7server_search.log", &r2, 0);
  return result_json;
}



int
main(int argc, char *argv[])
{
  if (argc != 1) exit(-1);

  char buf[1024];
  int flag1;

  HttpServer httpserver(55407);
  Myhw7Server s(httpserver,
		JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)
  s.StartListening();
  std::cout << "Hit enter to stop the server" << endl;
  getchar();

  s.StopListening();
  return 0;
}
