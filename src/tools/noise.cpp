#include "noise.h"
#include <algorithm>
#include <random>

PerlinNoise::PerlinNoise(int seed) {
	for (int i = 0; i < 256; i++) {
		p[i] = i;
	}
	std::shuffle(p, p + 256, std::default_random_engine(seed));

	for (int i = 0; i < 256; i++) {
		p[i + 256] = p[i];
	}
}
float PerlinNoise::noise(float x, float y) const {
	int X = (int)floor(x) & 255;
	int Y = (int)floor(y) & 255;
	x -= floor(x);
	y -= floor(y);
	float u = fade(x);
	float v = fade(y);
	int aa = p[p[X] + Y];
	int ab = p[p[X] + Y + 1];
	int ba = p[p[X + 1] + Y];
	int bb = p[p[X + 1] + Y + 1];
	return (1 - u) * (1 - v) * grad(aa, x, y) +
		u * (1 - v) * grad(ba, x - 1, y) +
		(1 - u) * v * grad(ab, x, y - 1) +
		u * v * grad(bb, x - 1, y - 1);
}
float PerlinNoise::fade(float t) const {
	return t * t * t * (t * (t * 6 - 15) + 10);
}
float PerlinNoise::grad(int hash, float x, float y) const {
	int h = hash & 3;
	float u = h < 2 ? x : y;
	float v = h < 2 ? y : x;
	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}