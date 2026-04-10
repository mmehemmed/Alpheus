#pragma once

class PerlinNoise {
public:
	PerlinNoise(int seed = 0);
	float noise(float x, float y) const;
private:
	int p[512];
	float fade(float t) const;
	float grad(int hash, float x, float y) const;
};