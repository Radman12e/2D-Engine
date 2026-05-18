#pragma once
class Renderable
{

public:

	virtual void Render() = 0;
	virtual ~Renderable();
	int GetLayer()
	{
		return Layer;
	}
	int Layer = 0;

	void UpdateLayer(int Layer);
};

