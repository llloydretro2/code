
#include <iostream>

// JSON RPC part
#include <stdlib.h>
#include "hw7client.h"
#include <jsonrpccpp/client/connectors/httpclient.h>

#include "Post.h"

using namespace jsonrpc;
using namespace std;

int
main(int argc, char *argv[])
{
  if (argc != 2)
    {
      char arg_string[] = " <update_json>";
      std::cout << "usage: " << argv[0] << arg_string << std::endl; 
      return -1;
    }

  // [update]
  // assume that you have a Post JSON file that you like to update
  // (1) read the file in, make it a String, s
  // (2) result_json = myClient.update(s);
  // (3) print out result_json, and see if there is any error status
  
  // [search]
  // assume that you have a Search Clause JSON file that you like to search
  // {"keyword":"happy"}
  // (1) read the file in, make it a String, s
  // (2) result_json = myClient.search(s);
  // (3) print out result_json, and see if there is any error status
  //     result_json {"count": <number of posts>,
  //                  "data": [{.post..},{...},...{...}]}
  // (4) save each of Post, into a separate file so you can append your history
  //     record, and validate/update
  
  Json::Value jv;
  int rc = myFile2JSON(argv[1], &jv);

  Post * my_post_ptr = new Post((Person *) NULL, (Message *) NULL);
  bool result_flag = my_post_ptr->Jdump(&jv);

  if (result_flag == false)
    {
      exit(-1);
    }

  HttpClient httpclient("http://127.0.0.1:55407");
  hw7Client myClient(httpclient, JSONRPC_CLIENT_V2);

  Json::Value result_json;

  // f2021 ecs36b hw7
  // update ==> Jdump, dumpJ in Post.cpp related to OKeys
  // hw7server.cpp

  try {
    std::cout << (my_post_ptr->dumpJ())->toStyledString() << std::endl;
    result_json = myClient.update((my_post_ptr->dumpJ())->toStyledString());
    std::cout << result_json.toStyledString() << endl;
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }

  return 0;
}
