
#include <iostream>

// JSON RPC part
#include <stdlib.h>
#include <jsonrpccpp/client/connectors/httpclient.h>

#include "Comment.h"
#include "Reaction.h"
#include "Person.h"

using namespace jsonrpc;
using namespace std;

int
main(void)
{
  
  // new comment (preparation)
  std::string s_profile { "1234567" };
  std::string s_post { "123098912" };
  std::string s_comment { "5001234" };

  Person * author_ptr = new Person("Oracle", "1234567890");
  Message * msg_ptr = new Message("Test Message for hw4part3");
  JvTime * created_time_ptr = new JvTime("2020-11-03T17:01:24+0000");

  Comment * comment_ptr = new Comment(s_profile, s_post, s_comment,
				      author_ptr, msg_ptr, created_time_ptr);

  // dumpJ
  Json::Value * myv1_ptr = comment_ptr->dumpJ();
  if (myv1_ptr != NULL)
    std::cout << myv1_ptr->toStyledString() << std::endl;
  else
    std::cout << "null JSON pointer" << std::endl;

  // handling the reactions
  comment_ptr->reactions = new vector<Reaction *>();

  Person *reactor1_ptr = new Person("Trinity", "9876543210");
  JvTime *reacting1_time_ptr = new JvTime("2020-11-03T17:02:01+0000");
  Reaction * reaction1_ptr = new Reaction("Love", reactor1_ptr, reacting1_time_ptr);
  (*(comment_ptr->reactions)).push_back(reaction1_ptr);

  Person *reactor2_ptr = new Person("Neo", "1111111111");
  JvTime *reacting2_time_ptr = new JvTime("2020-11-03T17:04:12+0000");
  Reaction * reaction2_ptr = new Reaction("Happy", reactor2_ptr, reacting2_time_ptr);
  (*(comment_ptr->reactions)).push_back(reaction2_ptr);

  // dumpJ
  Json::Value * myv2_ptr = comment_ptr->dumpJ();
  if (myv2_ptr != NULL)
    std::cout << myv2_ptr->toStyledString() << std::endl;
  else
    std::cout << "null JSON pointer" << std::endl;

}
