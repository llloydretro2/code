#include "cursor_list.hpp"

#include <iostream>

#define NUM_SLOTS 30

struct Slot
{
    int data;
    unsigned next;  // index of next slot
};

static struct Slot SLOTS[NUM_SLOTS];

unsigned slotAlloc()
{
    // TODO: Implement.
    if(SLOTS[0].next == 0)
    {
        throw std::runtime_error("no more slots");
    }
    unsigned s = SLOTS[0].next;
    SLOTS[0].next = SLOTS[s].next;
    return s;

}

void slotFree(unsigned index)
{
    // TODO: Implement.
    SLOTS[index].next = SLOTS[0].next;
    SLOTS[0].next = index;
}

void printSlots(unsigned start, unsigned end)
{
    for (unsigned i = start; i < end; ++i)
        std::cout << "SLOTS[" << i << "]: " << SLOTS[i].data
            << ' ' << SLOTS[i].next << '\n';
}

unsigned clCreate()
{
    if (SLOTS[0].next == 0)
    {
        for (int i = 0; i < NUM_SLOTS-1; ++i)
        {
            SLOTS[i].next = i+1;
        }
        SLOTS[0].data = 0;
        SLOTS[NUM_SLOTS-1].next = 0;

    }

    unsigned newHead = slotAlloc();
    SLOTS[newHead].next = 0;
    // TODO: Implement.
    return newHead;
}

void clDestroy(unsigned head)
{
    // TODO: Implement.
    unsigned s = head;
    unsigned temp;
    while(s != 0)
    {
        temp = s;
        s = SLOTS[s].next;
        slotFree(temp);
    }

}

void clAppend(unsigned node, int val)
{
    // TODO: Implement.
    unsigned s = node;
    while(SLOTS[s].next != 0)
    {
        s = SLOTS[s].next;
    }
    unsigned newSlot = slotAlloc();
    SLOTS[s].next = newSlot;
    SLOTS[newSlot].data = val;
    SLOTS[newSlot].next = 0;
    
}

void clInsert(unsigned node, int val)
{
    // TODO: Implement.
    unsigned s = slotAlloc();
    if (!s)
    {
        throw std::runtime_error("out of space");
    }

    SLOTS[s].data = val;
    SLOTS[s].next = SLOTS[node].next;
    SLOTS[node].next = s;
}

unsigned clFind(unsigned head, int val)
{
    // TODO: Implement.
    unsigned s = SLOTS[head].next;
    while(s && (SLOTS[s].data != val))
    {
        s = SLOTS[s].next;
    }
    return s;
}

void clPrint(unsigned head)
{
    // TODO: Implement.

    std::cout << "SLOTS[" << head << "]: (header)" << std::endl;
    unsigned s = SLOTS[head].next;
    while(s != 0)
    {
        std::cout << "SLOTS[" << s << "]: " << SLOTS[s].data << std::endl;
        s = SLOTS[s].next;
    }
}

bool clDelete(unsigned head, int val)
{
    if (clFind(head, val) == 0)
    {
        return 0;
    }
    // TODO: Implement.
    unsigned previous = head;
    unsigned s = SLOTS[head].next;

    while(s && (SLOTS[s].data != val))
    {
        previous = s;
        s = SLOTS[s].next;
    }

    SLOTS[previous].next = SLOTS[s].next;
    slotFree(s);

    return true;
    
}

bool clIsEmpty(unsigned head)
{
    // TODO: Implement.
    return SLOTS[head].next == 0;
}

unsigned clLength(unsigned head)
{
    // TODO: Implement.
    unsigned s = head;
    int length = 0;
    while(SLOTS[s].next != 0)
    {
        length += 1;
        s = SLOTS[s].next;
    }
    return length;
    
}

unsigned clDeleteAll(unsigned head, int val)
{
    // TODO: Implement.
    int count = 0;
    while (clDelete(head, val))
    {
        count+=1;
    }
    return count;
}

unsigned clCopy(unsigned head)
{
    // TODO: Implement.
    int length = clLength(head);
    int remainSlot = 0;
    for (int i = 1; i <= NUM_SLOTS-1; ++i)
    {
        if (SLOTS[i].next != 0)
        {
            remainSlot++;
        }
    }
    if (remainSlot < length)
    {
        throw std::runtime_error("out of range");
    }

    unsigned current = slotAlloc();
    unsigned newHeader = current;
    //SLOTS[current].data = SLOTS[head].data;
    unsigned tempSlot;
    unsigned s = SLOTS[head].next;
    while (s != 0)
    {
        tempSlot = slotAlloc();
        SLOTS[current].next = tempSlot;
        SLOTS[tempSlot].data = SLOTS[s].data;
        s = SLOTS[s].next;
        current = tempSlot;
    }
    SLOTS[current].next = 0;

    return newHeader;

}

void clReverse(unsigned head)
{
    // TODO: Implement.
    int length = clLength(head);
    int pointerList[length];
    unsigned s = head;
    for (int i = 0; i <= length; ++i)
    {
        pointerList[i] = s;
        s = SLOTS[s].next;
    }
    SLOTS[pointerList[0]].next = pointerList[length];
    for (int i = 0; i < length; ++i)
    {
        SLOTS[pointerList[length - i]].next = pointerList[length-i-1];
    }
    SLOTS[pointerList[1]].next = 0;
}
