#pragma once

#include <SFML/Graphics.hpp>

#include "Observer.h"

class Item
{
public:
    virtual ~Item() = default;

    virtual void pickup() = 0;                          //virual void - become picked up
    virtual sf::Vector2f getPosition() const = 0;

    void addObserver(Observer* t_observer);

    bool isActive() const;

protected:
    void notify(EventType t_event, int t_value = 0);

    sf::Vector2f m_position;

    bool m_isActive{ true };

private:
    std::vector<Observer*> m_observers;
};