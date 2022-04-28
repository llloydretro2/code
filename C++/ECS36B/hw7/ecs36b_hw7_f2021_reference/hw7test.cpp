
// hw7test.cpp
// #define _ECS36B_DEBUG_

#ifdef _ECS36B_HW7_

#include "Post.h"

int
main(int argc, char *argv[])
{
  if (argc != 2) return -1;

  Json::Value jv;
  int rc = myFile2JSON(argv[1], &jv);

  // new
  if (rc == HW5_ERROR_NORMAL)
    {
      Post my_post { (Person *) NULL, (Message *) NULL };
      bool result_flag = my_post.Jdump(&jv);

      if (result_flag == true)
	{
	  // now let us print the JSON from C++ objects we just built.
	  std::cout << (*(my_post.dumpJ())).toStyledString() << std::endl;
	}
    }
  else
    {
      Json::Value err_jv;
      produceErrorJSON(rc, "hw7_test.log", &err_jv, 0);
      std::cout << err_jv.toStyledString() << std::endl;
    }

  return 0;
}

#endif /* _ECS36B_HW7_ */

