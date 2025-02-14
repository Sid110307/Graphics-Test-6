#include "include/shape.h"

Shape::Shape(const ShapeType type, const std::vector<Gdiplus::PointF>& points, const Gdiplus::Color color,
             const bool fill) : type(type), points(points), color(color), fill(fill)
{
}

void Shape::Draw(Gdiplus::Graphics& graphics) const
{
	const Gdiplus::Pen pen(color);
	const Gdiplus::SolidBrush brush(color);

	switch (type)
	{
		case ShapeType::Circle:
		{
			const auto& point = points.front();
			const auto& radius = points.back().X;

			if (fill) graphics.FillEllipse(&brush, point.X - radius, point.Y - radius, 2 * radius, 2 * radius);
			else graphics.DrawEllipse(&pen, point.X - radius, point.Y - radius, 2 * radius, 2 * radius);

			break;
		}
		case ShapeType::Rectangle:
		{
			const auto& topLeft = points.front();
			const auto& bottomRight = points.back();

			if (fill)
				graphics.FillRectangle(&brush, topLeft.X, topLeft.Y, bottomRight.X - topLeft.X,
				                       bottomRight.Y - topLeft.Y);
			else
				graphics.DrawRectangle(&pen, topLeft.X, topLeft.Y, bottomRight.X - topLeft.X,
				                       bottomRight.Y - topLeft.Y);

			break;
		}
		case ShapeType::Polygon:
		{
			if (fill) graphics.FillPolygon(&brush, points.data(), static_cast<INT>(points.size()));
			else graphics.DrawPolygon(&pen, points.data(), static_cast<INT>(points.size()));

			break;
		}
		default:
			throw std::runtime_error("Invalid shape type");
	}
}
