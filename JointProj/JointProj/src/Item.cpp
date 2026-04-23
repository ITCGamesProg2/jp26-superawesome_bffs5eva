#include "../include/Item.h"

void Item::addObserver(Observer* t_observer)
{
    m_observers.push_back(t_observer);
}

void Item::notify(EventType t_event, int t_value)
{
    for (auto obserever : m_observers)
    {
        obserever->onNotify(t_event, t_value);
    }
}

bool Item::isActive() const
{
    return m_isActive;
}