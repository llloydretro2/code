
#include "Comment.h"

Comment::Comment
(std::string arg_profile_id, std::string arg_post_id, std::string arg_comment_id,
 Person * arg_author, Message * arg_msg, JvTime * arg_created)
{
  this->profile_id = arg_profile_id;
  this->post_id = arg_post_id;
  this->comment_id = arg_comment_id;
  this->author = arg_author;
  this->msg = arg_msg;
  this->created = arg_created;
  // very critical ==> portable to different platforms
  this->reactions = NULL;
}

Json::Value * Comment::dumpJ
(void)
{
  Json::Value * result_ptr = (this->author)->dumpJ();
  (*result_ptr)["profile_id"] = this->profile_id;
  (*result_ptr)["post_id"] = this->post_id;
  (*result_ptr)["comment_id"] = this->comment_id;
  // (*result_ptr)["author"] = this->author;
  (*result_ptr)["msg"] = (this->msg)->getContent();
  (*result_ptr)["created"] = *(this->created)->getTimeString();



  Json::Value json_reaction;
  Json::Value json_reaction_vector;
  if (this->reactions != NULL && (this->reactions)->size() > 0)
  {
    for (int i = 0; i < (this->reactions)->size(); i++)
    {
      Json::Value * dumpjv_ptr = ((*(this->reactions)).at(i))->dumpJ();
      json_reaction[i] = (*dumpjv_ptr);
      delete dumpjv_ptr;
    }

    json_reaction_vector["data"] = json_reaction;
    json_reaction_vector["count"] = ((int) (*(this->reactions)).size());
    (*result_ptr)["reactions"] = json_reaction_vector;
    
  }
  //std::cout << result_ptr->toStyledString() << std::endl;
  // to be implemented for hw4 part3
  return result_ptr; // this line is incorrect, just to avoid a g++ warning
  // to be implemented for hw4 part3}
}