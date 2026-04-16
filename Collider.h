#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp>
#include "GameEssentials.h"
#include "SpriteRendererComponent.h"
#include "Gameobject.h"

enum ColliderType
{
    Box,
    Circle
};

class Collider : public Component
{

private:
    ColliderType typeOfCollider;
    size_t id;


public:
    Collider(ColliderType CT = ColliderType::Box, bool isTrigger = false);

    ~Collider();
    

    size_t GetID() 
    {
        return id;
    }
    
    void OnUpdate(float dt) override;
    
    
    bool CheckCollision(Collider* OtherCollider)
    {
        if (OtherCollider->typeOfCollider == ColliderType::Box && typeOfCollider == ColliderType::Box)
        {
            return CheckBoxCollision(OtherCollider);
        }
        if ((OtherCollider->typeOfCollider == ColliderType::Box && typeOfCollider == ColliderType::Circle) || (OtherCollider->typeOfCollider == ColliderType::Circle && typeOfCollider == ColliderType::Box))
        {
            return CheckCombinedCollision(OtherCollider);
        }
        if (OtherCollider->typeOfCollider == ColliderType::Circle && typeOfCollider == ColliderType::Circle)
        {
            return CheckCircleCollision(OtherCollider);
        }
   

        return false;
    }

    bool CheckBoxCollision(Collider* OtherCollider)
    {
       
        if (BoxRect.findIntersection(OtherCollider->BoxRect));
    }
    bool CheckCircleCollision(Collider* OtherCollider)
    {

    }
    bool CheckCombinedCollision(Collider* OtherCollider)
    {

    }


    bool IsTrigger = false;
    float Radius;
    sf::Vector2f RectOffset;
    sf::FloatRect BoxRect;

};

