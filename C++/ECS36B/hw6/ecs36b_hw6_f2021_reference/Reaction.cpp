
#include "Reaction.h"

Reaction::Reaction
(void)
{
  this->type = "";
  this->author = (Person *) NULL;
  this->created = (JvTime *) NULL;
}

Json::Value * Reaction::dumpJ
(void)
{
  Json::Value * result_ptr = new Json::Value();
  (*result_ptr)["from"] = (*(this->author)->dumpJ());
  (*result_ptr)["type"] = this->type;

  std::string * str_ptr =  (this->created)->getTimeString();
  (*result_ptr)["created_time"] = *str_ptr;
  delete str_ptr;

#ifdef _ECS36B_DEBUG_
  std::cout << result_ptr->toStyledString() << std::endl;
#endif /* _ECS36B_DEBUG_ */

  std::cout << "dumpJ of Reaction ==> end" << std::endl;
  return result_ptr;
}

bool 
Reaction::Jdump
(Json::Value *input_json_ptr)
{
  if ((input_json_ptr == NULL) ||
      ((*input_json_ptr).isNull() == true) ||
      ((*input_json_ptr).isObject() != true))
    {
      return false;
    }

  if ((((*input_json_ptr)["type"]).isNull() == true) ||
      (((*input_json_ptr)["from"]).isNull() == true) ||
      (((*input_json_ptr)["created_time"]).isNull() == true) ||
      (((*input_json_ptr)["type"]).isString() != true) ||
      (((*input_json_ptr)["from"]).isObject() != true) ||
      (((*input_json_ptr)["created_time"]).isString() != true))
    {
      return false;
    }

  if (this->author == NULL)
    {
      // ************************************************
      // to be completed by ecs36b_f2021 students for hw6
      // ************************************************
      this->author = new Person();
      bool rc = (this->author)->Jdump(&((*input_json_ptr)["from"]));
      if (rc == false)
      {
        delete this->author;
        this->author = NULL;
        return false;
      }



    }

  if (this->created == NULL)
    {
      // ************************************************
      // to be completed by ecs36b_f2021 students for hw6
      // ************************************************
      this->created = new JvTime((((*input_json_ptr)["created_time"]).asString()).c_str());





    }

  // we allow reaction type to be changed
  this->type = ((*input_json_ptr)["type"]).asString();

#ifdef _ECS36B_DEBUG_
  std::cout << (this->dumpJ())->toStyledString() << std::endl;
#endif /* _ECS36B_DEBUG_ */

  return true; // if successful
}

