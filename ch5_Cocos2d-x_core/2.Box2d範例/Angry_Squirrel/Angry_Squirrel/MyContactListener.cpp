//
//  MyContactListener.cpp
//  Angry_Squirrel
//
//  Created by Ljj on 13-11-5.
//
//

#include "MyContactListener.h"
void MyContactListener::BenginContact(b2Contact *contact){
    
    
}

void MyContactListener::EndContact(b2Contact *contact)
{
    
}
 void MyContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{

}
 void MyContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
    bool isAEnemy =contact->GetFixtureA()->GetUserData() != NULL;
    bool isBEnemy = contact->GetFixtureB()->GetUserData() != NULL;
    if(isAEnemy || isBEnemy)
    {
        
        //should the body break?
        int32 count = contact->GetManifold()->pointCount;
        
        float32 maxImpulse = 0.0f;
        for (int32 i= 0;i <count; ++i)
        {
            
            maxImpulse = b2Max(maxImpulse, impulse->normalImpulses[i]);
            
        }
        if(maxImpulse>1.0f)
        {
            if(isAEnemy)
                contacts.insert(contact->GetFixtureA()->GetBody());
            if(isBEnemy)
                contacts.insert(contact->GetFixtureB()->GetBody());
        }
    }
    
}