
#include "Transaction.h"

// this line is important -- try to remove it and see what happens.
unsigned int Transaction::transaction_count {0};

Transaction::Transaction(unsigned int arg_type)
{
  this->tr_type = arg_type;
  Transaction::transaction_count++;

  // to be implemented by the student
}

Transaction::Transaction
(unsigned int arg_type, Person& arg_sender, Person& arg_receiver,
 GPS_DD& arg_src_where, GPS_DD& arg_dst_where,
 IP_Address& arg_srcIP, IP_Address& arg_dstIP, time_t arg_when)
{
  this->tr_sender = arg_sender;
  this->tr_receiver = arg_receiver;
  this->tr_src_where = arg_src_where;
  this->tr_dst_where = arg_dst_where;
  this->tr_srcIP = arg_srcIP;
  this->tr_dstIP = arg_dstIP;
  this->tr_when = arg_when;
  Transaction::transaction_count++;

  // to be implemented by the student
}

void
Transaction::setData(void *arg_data)
{
  this->tr_data = arg_data;
  // to be implemented by the student
}

void *
Transaction::getData(void)
{
  return this->tr_data;
  // to be implemented by the student
}

double
Transaction::getDistance()
{
  return this->tr_src_where.distance(this->tr_dst_where);
  // to be implemented by the student
}

std::string
Transaction::description()
{
  // finished
  std::string res;

  if (this->tr_sender == this->tr_receiver)
    {
      res += ("One-person Transaction for " + this->tr_sender.getName());
    }
  else
    {
      res += ("Two-persons Transaction for " + this->tr_sender.getName() + " and " + this->tr_receiver.getName());
    }

  res += (", Distance = " + std::to_string(this->getDistance()) + " miles.");
  return res;
}
