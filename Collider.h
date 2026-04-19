#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp>
#include "GameEssentials.h"
#include "SpriteRendererComponent.h"
#include "Gameobject.h"
#include <iostream>

enum ColliderType
{
    Box,
    Circle
};

class Collider : public Component
{

private:
    ColliderType typeOfCollider = ColliderType::Box;
    size_t id = 0;


public:
    Collider() {}

    ~Collider();
    

    size_t GetID() 
    {
        return id;
    }
    
    void OnUpdate(float dt) override;

    void OnAlive() override;

    void SetupCollider(ColliderType CT = ColliderType::Box, bool isTrigger = false);
   
    
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
       
      
        //std::cout << "\n\nCheckingCollision!";
        auto intersection = BoxRect.findIntersection(OtherCollider->BoxRect);

        if (intersection)
        {
            const sf::FloatRect& overlap = *intersection;

            //std::cout << "\n\n collision found!!";

            if (overlap.size.x < overlap.size.y)
            {
                if (BoxRect.position.x < OtherCollider->BoxRect.position.x) {
                    //std::cout << "\n\n YEET OVER HERE!! " << -overlap.size.x;
                    return { -overlap.size.x, 0 };
                }
                else 
                {
                    //std::cout << "\n\n YEET OVER HERE Y!! " << -overlap.size.y;
                    return { overlap.size.x, 0 };
                }
            }
            else
            {
                if (BoxRect.position.y < OtherCollider->BoxRect.position.y)
                    return { 0, -overlap.size.y };
                else
                    return { 0, overlap.size.y };
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

    void UpdateColliderPos();

    bool IsTrigger = false;
    float Radius = 0;
    sf::Vector2f RectOffset = {0,0};
    sf::FloatRect BoxRect = sf::FloatRect();

};

