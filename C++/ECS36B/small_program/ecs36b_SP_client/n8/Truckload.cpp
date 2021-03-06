#include <memory>                                             // For smart pointers
#include <vector>                                             // For vector<T>
#include "Box.h"
#include "Package.h"
#include "Truckload.h"

// Constructor
Truckload::Truckload(const std::vector< ptr<Box> >& boxes)	   
{
  for (auto pBox : boxes)
  {
    addBox(pBox);
  }
}

// Add a Box to the list
void Truckload::addBox(ptr<Box> pBox)
{
  auto pPackage = std::make_shared<Package>(pBox);  // Create a Package

  if (pHead)                                        // Check  list is not  empty
    pTail->setNext(pPackage);                       // Add the  new  object  to  the  tail
  else                                              // List is empty
    pHead = pPackage;                               // so new  object  is the  head

  pTail = pPackage;                                 // Store  its address as tail
}

// Find the Package containing pBox and delete it from the list
bool Truckload::deleteBox(ptr<Box> pBox)
{
  pCurrent = pHead;                                 // Start at the first box
  ptr<Package> pPrevious;                           // There's no previous box to the 1st
  while (pCurrent)
  {
    if (pCurrent->getBox() == pBox)                  // Check for identical Box pointers
    { // We found the box!
      if (pPrevious)                                 // If there's a previous box...
      {
        pPrevious->setNext(pCurrent->getNext());      // ...set its next to be the box after current
      }
      else                                            // It is the first box...
      {
        pHead = pHead->getNext();                     // ..so make the next the first box
      }
      pCurrent = nullptr;
      return true;
    }
    pPrevious = pCurrent;                             // Make current the previous box...
    pCurrent = pCurrent->getNext();                   // ... and the next one current
  }
  return false;
}

// Output all Box objects in the list
void Truckload::listBoxes()
{
  pCurrent = pHead;
  size_t count {};
  while (pCurrent)
  {
    pCurrent->getBox()->listBox();
    pCurrent = pCurrent->getNext();
    if(! (++count % 5)) std::cout << std::endl;
  }
  if (count % 5) std::cout << std::endl;
}

// Get the first Box
ptr<Box> Truckload::getFirstBox()				                   
{
  pCurrent = pHead->getNext();
  return pHead->getBox();
}

// Get the next Box
ptr<Box> Truckload::getNextBox()               
{
  if (!pCurrent)                                     // If there's no current...
    return getFirstBox();                            // ...return the 1st

  auto pPackage = pCurrent->getNext();               // Save the next package
  if (pPackage)                                      // If there is one...
  {
    pCurrent = pPackage;                             // Update current to the next                                  
    return pPackage->getBox();
  }
  pCurrent = nullptr;                                // If we get to here...
  return nullptr;                                    // ...there was no next
}
