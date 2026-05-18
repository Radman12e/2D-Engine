#include "Renderable.h"
#include "GameEssentials.h"
void Renderable::UpdateLayer(int Layer)
{
	
	GameEssentialsGlobals::ChangeRenderLayerIndex(this, this->Layer, Layer);
	this->Layer = Layer;
}

Renderable::~Renderable()
{
	GameEssentialsGlobals::RemoveSprite(this, Layer);
}