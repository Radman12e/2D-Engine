#pragma once
class Renderable
{

public:

	virtual void Render() = 0;
	virtual ~Renderable() = default;
	int GetLayer()
	{
		return Layer;
	}
	size_t Layer = 0;

	void UpdateLayer(int Layer);
};

