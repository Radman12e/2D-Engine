#include "PrefabHandler.h"

#pragma once
class Scene
{
public:
    
	void Init(std::string data = "");

	virtual void SetupScene(std::string data = "")
	{
	}
    ~Scene();

	
};


class SceneTest : public Scene
{

public:
    


    virtual ~SceneTest() = default;
    
	void SetupScene(std::string data = "") override;
    

};

class SceneStart : public Scene
{

public:



    virtual ~SceneStart() = default;

    void SetupScene(std::string data = "") override;


};





