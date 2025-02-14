#pragma once

#include <vector>
#include <memory>

#include <windows.h>
#include <gdiplus.h>

enum class ShapeType
{
	Circle,
	Rectangle,
	Polygon,
};

class Shape
{
public:
	Shape(ShapeType type, const std::vector<Gdiplus::PointF>& points, Gdiplus::Color color, bool fill = true);
	void Draw(Gdiplus::Graphics& graphics) const;

private:
	ShapeType type;
	std::vector<Gdiplus::PointF> points;
	Gdiplus::Color color;
	bool fill;
};
