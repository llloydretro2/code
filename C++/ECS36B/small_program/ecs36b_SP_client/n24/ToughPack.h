// ToughPack.h
#ifndef TOUGHPACK_H
#define  TOUGHPACK_H

#include  "Box.h"

class  ToughPack : public Box
{
public:
  // Constructor
  ToughPack(double lv, double wv, double hv) : Box {lv, wv, hv} {}

  // Function  to  calculate volume of  a ToughPack  allowing 15%  for  packing
  double volume()  const { return 0.85*length*width*height; }
};
#endif