#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp>
#include "GameEssentials.h"
#include "SpriteRendererComponent.h"

enum ColliderType
{
    Box,
    Circle
};

class Collider : public Component
{

private:
    ColliderType typeOfCollider;
    


public:
    Collider(ColliderType CT = ColliderType::Box, bool isTrigger = false)
    {
        IsTrigger = true;
        SpriteRendererComponent* Temp = GameObject->GetComponent<SpriteRendererComponent>();
        if (Temp != nullptr) 
        {
            BoxRect = (sf::FloatRect)Temp->getRect();
            RectOffset = sf::Vector2f((Temp->getRect().size) / 2);
            Radius = (Temp->getRect().size / 2).x;
        }
        
    }
    
    void OnUpdate(float dt) override
    {
        BoxRect.position = GameObject->getWorldPos() + RectOffset;
    }
    
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

