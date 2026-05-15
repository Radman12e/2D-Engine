#include "Renderable.h"
#include "GameEssentials.h"
void Renderable::UpdateLayer(int Layer)
{
	GameEssentialsGlobals::ChangeRenderLayerIndex(this, this->Layer, Layer);
	std::cout << "LayerUpdated!" << Layer;
}