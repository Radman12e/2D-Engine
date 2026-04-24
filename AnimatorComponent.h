#pragma once
#include "Component.h"
#include "SpriteRendererComponent.h"
#include <SFML/Graphics.hpp>


struct AnimationFrame
{
    sf::IntRect Frame;
    float FramesDelay = 0;
};

struct Animationstrip
{
    std::vector<AnimationFrame> Frames;
    bool Looping = false;
};


class AnimatorComponent :
    public Component
{
    float FramesUntilNextFrame = 0;
    int CurrentFrameIndex = 0;

    SpriteRendererComponent* SpriteRenderer = nullptr;

    std::unordered_map<std::string, Animationstrip> Anims;

    Animationstrip* CurrentAnimation = nullptr;
public:
    void OnUpdate(float dt) override 
    {
        if (!Enabled) return;
        if (SpriteRenderer == nullptr) 
        {
            SpriteRenderer = GameObject->GetComponent<SpriteRendererComponent>();
        }
        if (CurrentAnimation != nullptr && SpriteRenderer != nullptr)
        {
            if (FramesUntilNextFrame <= 0)
            {
                CurrentFrameIndex++;
                size_t vectorSize = CurrentAnimation->Frames.size();
                if (vectorSize - 1 < CurrentFrameIndex)
                {
                    if (CurrentAnimation->Looping) CurrentFrameIndex = 0;
                    else CurrentAnimation = nullptr;
                    
                }
                
                if (CurrentAnimation != nullptr) SpriteRenderer->SetRect(CurrentAnimation->Frames[CurrentFrameIndex].Frame);
                
                
            }
        }
        FramesUntilNextFrame--;
    }

    void AddAnimation(Animationstrip strip, std::string AnimName) 
    {
        Anims[AnimName] = strip;
    }
    
    void PlayAnim(std::string AnimName)
    {
        CurrentAnimation = &Anims[AnimName];
        FramesUntilNextFrame = CurrentAnimation->Frames[0].FramesDelay;
        CurrentFrameIndex = 0;
        SpriteRenderer->SetRect(CurrentAnimation->Frames[0].Frame);
    }
    
};

