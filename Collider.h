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
    
    //returns collision correction for x,y
    sf::Vector2f CheckCollision(Collider* OtherCollider)
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
   

        return {0,0};
    }

    sf::Vector2f CheckBoxCollision(Collider* OtherCollider)
    {
       
      
       
        if (BoxRect.findIntersection(OtherCollider->BoxRect)) 
        {
            float OverlapL = (BoxRect.position.x + BoxRect.size.x) - OtherCollider->BoxRect.position.x;
            float OverlapR = (OtherCollider->BoxRect.position.x + OtherCollider->BoxRect.size.x) - BoxRect.position.x;
            float OverlapT = (BoxRect.position.y + BoxRect.size.y) - OtherCollider->BoxRect.position.y;
            float OverlapB = (OtherCollider->BoxRect.position.y + OtherCollider->BoxRect.size.y) - BoxRect.position.y;

            bool fromLeft = std::abs(OverlapL) < std::abs(OverlapR);
            bool fromTop = std::abs(OverlapT) < std::abs(OverlapB);

            float minX = fromLeft ? OverlapL : -OverlapR;
            float minY = fromTop ? OverlapT : -OverlapB;

            if (std::abs(minX) < std::abs(minY)) 
            {
                return { -minX,0 };
            }
            else
            {
                return { 0, -minY };
            }

        }
        return { 0,0 };

    }
    sf::Vector2f CheckCircleCollision(Collider* OtherCollider)
    {
        return { 0,0 };
    }
    sf::Vector2f CheckCombinedCollision(Collider* OtherCollider)
    {
        return { 0,0 };
    }


    bool IsTrigger = false;
    float Radius;
    sf::Vector2f RectOffset;
    sf::FloatRect BoxRect;

};

