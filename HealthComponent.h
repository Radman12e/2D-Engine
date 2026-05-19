#pragma once
#include "Component.h"
#include "GameEssentials.h"



class HealthComponent :
    public Component
{
public:
    float Health = 10;
    std::vector<sf::Vector2f> ExplosionPoints = { {0,0} };
    float PlayHitEffect = 0;
   
    HealthComponent() {};
    ~HealthComponent() = default;
    std::unique_ptr<Component> CloneComponent() override
    {
        return std::make_unique<HealthComponent>(*this);
    }

    void takeDamage(float Dmg) 
    {
        Health -= Dmg;
        if (Health <= 0) 
        {
            Death();
        }
        PlayHitEffect = 10;
    }
    void Death() 
    {
        for (auto& a : ExplosionPoints) {

            Gameobject* Explosion = GameEssentialsGlobals::LocalRh->InstansiatePrefab("Explosion");
            if (Explosion != nullptr)
            {
                Explosion->SetParent(GameObject);
                Explosion->SetlocalPosition(a);
                Explosion->SetParent(GameEssentialsGlobals::WorldRoot);
            }
        }
        GameObject->Destroy();
    }

    void OnUpdate(float dt) override 
    {
        if (PlayHitEffect) 
        {
            SpriteRendererComponent* src = GameObject->GetComponent<SpriteRendererComponent>();
            if (src == nullptr) return;
            PlayHitEffect --;
            src->Sprite.setColor(sf::Color(255, 0, 0, 255));
        }
        else
        {
            SpriteRendererComponent* src = GameObject->GetComponent<SpriteRendererComponent>();
            if (src == nullptr) return;
            src->Sprite.setColor(sf::Color(255, 255, 255, 255));
        }
    }

};

class BulletComponent :
    public Component
{
public:
    float Damage = 1;
    float Speed = 100* 6;
    //std::vector<sf::Vector2f> ExplosionPoints;


    std::string Explosionstr = "miniExplosion";
    BulletComponent() {};
    ~BulletComponent() = default;
    std::unique_ptr<Component> CloneComponent() override
    {
        return std::make_unique<BulletComponent>(*this);
    }

    void OnTriggerEntered(collision& CollisionObject) override
    {
        auto c = CollisionObject.rb->GetGameObject()->GetComponent<HealthComponent>();
        if (c != nullptr)
        {
            float chealth = c->Health;
            c->takeDamage(Damage);
            Damage -= chealth;

        }
        else
        {
            Damage = 0;
        }
        if (Damage <= 0)
        {
            
            Gameobject* Explosion = GameEssentialsGlobals::LocalRh->InstansiatePrefab(Explosionstr);
            if (Explosion != nullptr)
            {
                Explosion->MoveTo(GameObject->getWorldPos());
            }
            //GameObject->Disable();
            GameObject->Destroy();
        }
        
    }



};


class GunComponent : public Component
{
public:
    std::string BulletPrefab;
    float bcd = 0.f;
    float c = 0;

    void FireGun(sf::Vector2f Dir) 
    {
        if (c > 0) return;
        c = bcd;

        Gameobject* Explosion = GameEssentialsGlobals::LocalRh->InstansiatePrefab(BulletPrefab);
        if (Explosion != nullptr)
        {
            Explosion->MoveTo(GameObject->getWorldPos());
            Explosion->GetComponent<Rigidbody>()->Velocity = Dir.normalized() * Explosion->GetComponent<BulletComponent>()->Speed;

        }

    }
    ~GunComponent() = default;

    std::unique_ptr<Component> CloneComponent() override
    {
        return std::make_unique<GunComponent>(*this);
    }

    void OnUpdate(float dt) override 
    {
        c -= dt;
    }
};

class BasicGunComponent : public GunComponent 
{
public:
    //BasicGunComponent();
    std::unique_ptr<Component> CloneComponent() override
    {
        return std::make_unique<BasicGunComponent>(*this);
    }
    ~BasicGunComponent() = default;
};