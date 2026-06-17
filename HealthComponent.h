#pragma once
#include "Component.h"
#include "GameEssentials.h"
#include "AnimatorComponent.h"
#include <cmath>
#include "SoundClass.h"
#include "SoundComponent.h"


class HealthComponent :
    public Component
{
public:
    float Health = 1;
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
                Explosion->GetComponent<SoundComponent>()->PlaySound("default");
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
    Sound* ShootSound = nullptr;
    

    void FireGun(sf::Vector2f Dir, std::string ShootSound2 = "")
    {
        if (c > 0) return;
        c = bcd;

        if (ShootSound2 != "" && ShootSound == nullptr)
        {
            ShootSound = new Sound(ShootSound2);
            ShootSound->GetSound()->setVolume(50);
            std::cout << "PlaySound!";


        }
        ShootSound->GetSound()->setPitch(((std::rand() % 50) + 50) / 100.f);
        if (ShootSound != nullptr) ShootSound->playSound();

        Gameobject* Explosion = GameEssentialsGlobals::LocalRh->InstansiatePrefab(BulletPrefab);
        if (Explosion != nullptr)
        {
            Explosion->MoveTo(GameObject->getWorldPos());
            Explosion->GetComponent<Rigidbody>()->Velocity = Dir.normalized() * Explosion->GetComponent<BulletComponent>()->Speed;

        }

    }
    ~GunComponent() 
    {
        delete ShootSound;
    }

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


class BeamUIRelay : public Component
{
public:
    bool Setup1 = false;
    float MaxSize = 80;
    float CurrentProgress = 0;
    float TimeForBigBeam = 1;
    float TimeForMediumBeam = 0.5;

    bool FullLastFrame = false;
    bool Held = false;

    void OnUpdate(float dt) override 
    {
        if (!Setup1) 
        {
            Setup();
        }
        if (Held) 
        {
            CurrentProgress += dt;
        }
        if (CurrentProgress >= TimeForBigBeam) 
        {
            CurrentProgress = TimeForBigBeam;
        }
        if (FullLastFrame == false && CurrentProgress >= TimeForBigBeam)
        {
            GameObject->GetComponent<AnimatorComponent>()->PlayAnim("ChargedFull");
            FullLastFrame = true;
        }
        int s1 = (CurrentProgress / TimeForBigBeam) * MaxSize;
        int s = MaxSize - ((MaxSize - (s1) / 2));
        GameObject->GetChildren()[0]->GetComponent<SpriteRendererComponent>()->SetRect({ {s,0},{s1,15} });

        //posx = (maxsize - x) / 2mah
    }

    void Setup() 
    {
        Setup1 = true;
        std::function<void(EventArgs)> OnBeamChargeStart = [this](EventArgs)
            {
                this->Held = true;
                //std::cout << "HELD!!!";
            };
        std::function<void(EventArgs)> OnBeamChargeEnd = [this](EventArgs)
            {
                this->Held = false;
                FullLastFrame = false;
                GameObject->GetComponent<AnimatorComponent>()->PlayAnim("idle");
                CurrentProgress = 0;
            };
        this->bindEvent("ShootStart", OnBeamChargeStart);
        this->bindEvent("ShootEnd", OnBeamChargeEnd);
        //std::cout << "\n\n\nSETUP!!!!\n\n\n";
    }

    std::unique_ptr<Component> CloneComponent() override
    {
        return std::make_unique<BeamUIRelay>(*this);
    }
    ~BeamUIRelay() = default;


};