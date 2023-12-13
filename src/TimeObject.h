#pragma once
#include "DisplayableObject.h"
class TimeObject :
    public DisplayableObject
{
public:
    TimeObject(BaseEngine* pEngine)
        :DisplayableObject(pEngine)
    {}

};

