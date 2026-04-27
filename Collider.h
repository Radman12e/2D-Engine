#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp>
#include "GameEssentials.h"
#include "SpriteRendererComponent.h"
#include "Gameobject.h"
#include <iostream>

struct AABB
{
    float minX, maxX;
    float minY, maxY;
};


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

    AABB GetAABB()
    {
        return axisAllignedBox = { BoxRect.position.x - BoxRect.size.x, BoxRect.position.x + BoxRect.size.x ,BoxRect.position.y - BoxRect.size.y, BoxRect.position.y + BoxRect.size.y };

    }
    AABB axisAllignedBox;
    void OnUpdate(float dt) override;

    void OnAlive() override;

    void SetupCollider(ColliderType CT = ColliderType::Box, bool isTrigger = false);

    void SetupFromClone();
   
    void OnDestroy() override;
    
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

            sf::Vector2f c1 = { BoxRect.position.x + BoxRect.size.x * 0.5f,  BoxRect.position.y + BoxRect.size.y * 0.5f };
            sf::Vector2f c2 = { OtherCollider->BoxRect.position.x + OtherCollider->BoxRect.size.x * 0.5f,  OtherCollider->BoxRect.position.y + OtherCollider->BoxRect.size.y * 0.5f };

            if (overlap.size.x < overlap.size.y)
            {
                if (c1.x < c2.x) {
                    
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
                if (c1.y < c2.y)
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

    std::unique_ptr<Component> CloneComponent() override
    {
        auto c = std::make_unique<Collider>(*this);
        c->SetupFromClone();

        return c;
    }

    void Enable() override 
    {
        if (this->Enabled) return;
        this->Enabled = true;
        SetupFromClone();
    }
    void Disable() override;

};

