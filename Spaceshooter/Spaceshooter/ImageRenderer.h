// ImageRenderer.h
// Krystof Hruby
// 2023

#pragma once

#include <vector>

#include "Component_SpriteRenderer.h"

// Holds values of the iamge to be rendered.
struct Image {
	PictureIndex picture_index;
	int layer;
	Vector2D position;
	float scale;
	float rotation;
	float transparency;
};

// Used to separate images into their render layers and draw them in correct order.
class ImageRenderer final {
public:
	// Returns singleton instance.
	static ImageRenderer& GetInstance();

	// Schedule image to be rendered at the end of the frame.
	void ScheduleImage(PictureIndex picture_index, int layer, Vector2D position, float scale, float rotation, float transparency);

private:
	// For RenderScheduledImages.
	friend class Gameloop;

	// Singleton
	ImageRenderer();
	ImageRenderer(ImageRenderer const& copy) = delete;
	ImageRenderer operator = (ImageRenderer const& copy) = delete;

	std::vector<std::vector<Image>> scheduled_images;

	// Renders all images scheduled for rendering.
	void RenderScheduledImages();
};

