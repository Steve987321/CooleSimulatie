#include "pch.h"
#include "Simulator/Sim.h"
#include "Grid.h"

float sim::Grid::MapToRange(float value, float minIn, float maxIn, float minOut, float maxOut)
{
    float x = (value - minIn) / (maxIn - minIn);
    float result = minOut + (maxOut - minOut) * x;
    return (result < minOut) ? minOut : (result > maxOut) ? maxOut : result;
}

void sim::Grid::apply_physics()
{
	p_Physics->Diffuse(1, this->px, this->x, this->visc, this->dt, 16, this->size);
	p_Physics->Diffuse(2, this->py, this->y, this->visc, this->dt, 16, this->size);

	p_Physics->Project(this->px, this->py, this->x, this->y, 16, this->size);

	p_Physics->Advect(1, this->x, this->px, this->px, this->py, this->dt, this->size);
	p_Physics->Advect(2, this->y, this->py, this->px, this->py, this->dt, this->size);

	p_Physics->Project(this->x, this->y, this->px, this->py, 16, this->size);

	p_Physics->Diffuse(0, this->previousDensity, this->density, this->diff, this->dt, 16, this->size);
	p_Physics->Advect(0, this->density, this->previousDensity, this->x, this->y, this->dt, this->size);
}
void sim::Grid::FadeDensity(int size)
{
    for (int i = 0; i < size; i++) {
        float d = this->density[i];
        density[i] = (d - 0.05f < 0) ? 0 : d - 0.05f;
    }
}

void sim::Grid::AddDensity(float x, float y, float amount)
{
	this->density[IX(x, y, this->size)] += amount;
}

void sim::Grid::AddVelocity(float x, float y, float px, float py)
{
	int index = IX(x, y, this->size);

	this->x[index] += px;
	this->y[index] += py;
}

void sim::Grid::Update(sf::RenderWindow& win)
{
	apply_physics();
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size; j++) {
			sf::RectangleShape rect;
			rect.setSize(sf::Vector2f(grid::scale, grid::scale));
			rect.setPosition(j * grid::scale, i * grid::scale);
			//rect.setFillColor(sf::Color(255, 255, 255, (this->density[IX(i, j, this->size)] > 255) ? 255 : this->density[IX(i, j, this->size)]));
            rect.setFillColor(this->Hsv((this->density[IX(i, j, this->size)]), 1, 1, 255));
			win.draw(rect);
		}
	}
	FadeDensity(size*size);
}

sf::Color sim::Grid::Hsv(int hue, float sat, float val, float d)
{
    hue %= 360;
    while (hue < 0) hue += 360;

    if (sat < 0.f) sat = 0.f;
    if (sat > 1.f) sat = 1.f;

    if (val < 0.f) val = 0.f;
    if (val > 1.f) val = 1.f;

    int h = hue / 60;
    float f = float(hue) / 60 - h;
    float p = val * (1.f - sat);
    float q = val * (1.f - sat * f);
    float t = val * (1.f - sat * (1 - f));

    switch (h) {
    default:
    case 0:
    case 6: return sf::Color(val * 255, t * 255, p * 255, d);
    case 1: return sf::Color(q * 255, val * 255, p * 255, d);
    case 2: return sf::Color(p * 255, val * 255, t * 255, d);
    case 3: return sf::Color(p * 255, q * 255, val * 255, d);
    case 4: return sf::Color(t * 255, p * 255, val * 255, d);
    case 5: return sf::Color(val * 255, p * 255, q * 255, d);
    }
}