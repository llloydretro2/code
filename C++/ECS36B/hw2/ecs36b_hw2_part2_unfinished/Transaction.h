
// Transaction.h for f2021 ecs36b hw2 part2, not to be modified

#ifndef _TRANSACTION_H_
#define _TRANSACTION_H_

// Transaction.h
#include <iostream>
#include "Person.h"

#define TR_TYPE_FLIGHT 1

class Transaction
{
 private:
  unsigned int tr_type;
  unsigned int tr_status;

  Person tr_sender;
  Person tr_receiver;
  GPS_DD tr_src_where;
  GPS_DD tr_dst_where;
  time_t tr_when;
  IP_Address tr_srcIP;
  IP_Address tr_dstIP;

  void *tr_data;
 public:
  Transaction(unsigned int);
  Transaction(unsigned int, Person&, Person&, GPS_DD&, GPS_DD&, IP_Address&, IP_Address&, time_t);

  static unsigned int transaction_count;

  void setData(void *);
  void *getData();
  double getDistance();
  std::string description();
};

#endif  /* _TRANSACTION_H_ */
