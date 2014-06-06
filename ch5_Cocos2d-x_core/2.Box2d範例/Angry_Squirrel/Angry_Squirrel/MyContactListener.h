//
//  MyContactListener.h
//  Angry_Squirrel
//
//  Created by Ljj on 13-11-5.
//
//

#ifndef __Angry_Squirrel__MyContactListener__
#define __Angry_Squirrel__MyContactListener__

#include <iostream>
#include "Box2D.h"
#include <set>
#include <algorithm>
class MyContactListener: public b2ContactListener
{
public:
    std::set<b2Body*>contacts;
    MyContactListener *contactListener;
    virtual void BenginContact(b2Contact * contact);
    virtual void EndContact(b2Contact* contact);
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
};
#endif /* defined(__Angry_Squirrel__MyContactListener__) */
