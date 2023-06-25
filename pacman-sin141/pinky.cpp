#include "pinky.h"
Pinky::Pinky(int x, int y) : Ghost() {
	entityX = x;
	entityY = y;
	ghostType = 3;
}
Pinky::~Pinky(){}
void Pinky::chasePacman(std::vector<std::vector<char>> map, int pacX, int pacY)
{
	// TODO: implement Pinky's unique chase method
}
void Pinky::renderGhost(ALLEGRO_BITMAP* imgPinky, int sprite) {
	al_draw_bitmap_region(imgPinky, direction * entityWidth, sprite * entityHeight, entityWidth, entityHeight, getEntityX(), getEntityY(), 0);
}
