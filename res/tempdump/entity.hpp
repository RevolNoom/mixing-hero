/*
    <<I N T E R F A C E>>  ENTITY
    Defines the common operations in all the game object
*/

#ifndef ENTITY_H
#define ENTITY_H

namespace Effect
{
    class Effect;
}

class Entity
{
public:
    // An Effect might be modified by a Passive effect
    // So it's a good idea to pass by value
    virtual void AffectedBy(Effect::Effect e);
};


#endif

