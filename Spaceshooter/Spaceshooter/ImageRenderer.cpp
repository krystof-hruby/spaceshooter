// ImageRenderer.cpp
// Krystof Hruby
// 2023

#include "ImageRenderer.h"

#include "GameObject.h"
#include "mydrawengine.h"

ImageRenderer::ImageRenderer() {
	// Add layer 0.
	this->scheduled_images.push_back(std::vector<Image>());
}

ImageRenderer& ImageRenderer::GetInstance() {
	static ImageRenderer instance;
	return instance;
}

void ImageRenderer::ScheduleImage(PictureIndex picture_index, int layer, Vector2D position, float scale, float rotation, float transparency) {
	// Add layer if not already in.
	for (size_t i = (this->scheduled_images.size() - 1); i < layer; i++)
		this->scheduled_images.push_back(std::vector<Image>());

	Image image;
	image.picture_index = picture_index;
	image.layer = layer;
	image.position = position;
	image.scale = scale;
	image.rotation = rotation;
	image.transparency = transparency;

	this->scheduled_images[layer].push_back(image);
}

void ImageRenderer::RenderScheduledImages() {
	for (auto& render_layer : this->scheduled_images) {
		for (auto& image : render_layer)
			MyDrawEngine::GetInstance()->DrawAt(image.position, image.picture_index, image.scale, image.rotation, image.transparency);

		render_layer.clear(); // Remove all scheduled images from the layer.
	}
}
