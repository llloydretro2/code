
#include "Reaction.h"

Reaction::Reaction
(std::string arg_type, Person * arg_author, JvTime * arg_created)
{
  this->type = arg_type;
  this->author = arg_author;
  this->created = arg_created;
}

Json::Value * Reaction::dumpJ(void)
{
  Json::Value * result_ptr = (this->author)->dumpJ();
  (*result_ptr)["type"] = this->type;
  (*result_ptr)["created_time"] = *(this->created)->getTimeString();
  //std::cout << result_ptr->toStyledString() << std::endl;
  
  // to be implemented for hw4 part3
  return result_ptr; // this line is incorrect, just to avoid a g++ warning
}
