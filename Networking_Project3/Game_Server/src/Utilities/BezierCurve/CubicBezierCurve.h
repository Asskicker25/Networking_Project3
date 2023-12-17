#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <Graphics/Renderer.h>

struct CubicBezierPoint
{
	glm::vec3 point;
	glm::vec3 controlPoint;
	glm::vec3 rotationOffset;

	CubicBezierPoint(const glm::vec3& point, const glm::vec3& controlPoint, glm::vec3 rotationOffset)
	{
		this->point = point;
		this->controlPoint = controlPoint;
		this->rotationOffset = rotationOffset;
	}

};

struct PointOnCurve
{
	glm::vec3 point;
	glm::vec3 tangent;
	glm::vec3 rotationOffset;

	PointOnCurve(const glm::vec3& point, const glm::vec3& tangent, glm::vec3 rotationOffset)
	{
		this->point = point;
		this->tangent = tangent;
		this->rotationOffset = rotationOffset;
	}
};

class CubicBezierCurve
{
public:
	
	float spacing = 0;

	CubicBezierCurve(float spacing = 0.01f);

	void CalculateCurve();
	void DrawCurve();

	int GetCurveCount();

	void AddPoint(CubicBezierPoint point);

	PointOnCurve GetCachedPointOnCurve(int index);

private:

	Renderer* renderer;

	bool visualize = true;

	std::vector<CubicBezierPoint> listOfPoints;
	std::vector<PointOnCurve> listOfPointsOnCurve;

	PointOnCurve GetPointOnCurve(float t) const;

};

