#include "PCB.h"

PCB::PCB()
{
    int _id = 0;
    int _state = NEW;
    int _priority = 0;
}

PCB::~PCB()
{

}

void PCB::setId(int id)
{
    _id = id;
}

void PCB::setState(int state)
{
    _state = state;
}

void PCB::setPriority(int priority)
{
    _priority = priority;
}

int PCB::getId()
{
    return _id;
}

int PCB::getState()
{
    return _state;
}

int PCB::getPriority()
{
    return _priority;
}
