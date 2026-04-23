#pragma once

class Observer
{
public:
    virtual void onNotify(int damage) = 0;
};

