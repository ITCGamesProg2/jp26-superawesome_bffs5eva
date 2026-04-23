#pragma once

enum class EventType
{
    KEY_ACQUIRED,
    COLLECTIBLE_ACQUIRED,
    DAMAGE_PLAYER
};

class Observer
{
public:
    virtual void onNotify(EventType t_event, int t_value = 0) = 0;
};