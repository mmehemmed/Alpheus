#pragma once

#include "rawmodel.h"
#include "texture.h"

class TexturedModel {
public:
	TexturedModel(const RawModel& rawModel, const Texture& texture) : rawModel(rawModel), texture(texture) {}
	const RawModel& getRawModel() const { return rawModel; }
	const Texture& getTexture() const { return texture; }
	float getShininess() const { return shininess; }
	void setShininess(float value) { shininess = value; }
	float getGlossiness() const { return glossiness; }
	void setGlossiness(float value) { glossiness = value; }
private:
	RawModel rawModel;
	Texture texture;
	float shininess = 0.5f; // Default shininess value for specular highlights
	float glossiness = 32.0f; // Default glossiness value for specular highlights
};