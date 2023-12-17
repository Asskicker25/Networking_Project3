#include <iostream>

#include "CubicBezierCurve.h"
#include "../RendererInstance.h"
#include "../Lerp.h"

CubicBezierCurve::CubicBezierCurve(float spacing)
{
	this->renderer = renderer;
	this->spacing = spacing;

	renderer = RendererInstance::GetInstance().GetRenderer();
}

void CubicBezierCurve::CalculateCurve()
{
	listOfPointsOnCurve.clear();

	int count = 1 / spacing;

	for (int i = 0; i <= count; i++)
	{
		listOfPointsOnCurve.push_back(GetPointOnCurve(i * spacing));
	}
}

void CubicBezierCurve::DrawCurve()
{
	if (!visualize) return;

	for (PointOnCurve point : listOfPointsOnCurve)
	{
		renderer->DrawSphere(point.point, 0.1f, glm::vec4(1, 0, 0, 1));
	}

	for (CubicBezierPoint point : listOfPoints)
	{
		renderer->DrawSphere(point.point, 0.1f, glm::vec4(0, 1, 0, 1));
		renderer->DrawSphere(point.point, 0.1f, glm::vec4(00, 0, 1, 1));
	}
}

int CubicBezierCurve::GetCurveCount()
{
	return listOfPointsOnCurve.size();
}

void CubicBezierCurve::AddPoint(CubicBezierPoint point)
{
	listOfPoints.push_back(point);
}

PointOnCurve CubicBezierCurve::GetCachedPointOnCurve(int index)
{
	return listOfPointsOnCurve[index];
}

PointOnCurve CubicBezierCurve::GetPointOnCurve(float time) const
{
	int startIndex;
	int endIndex;

	if (time == 1)
	{
		return PointOnCurve(listOfPoints[listOfPoints.size() - 1].point, glm::vec3(0), glm::vec3(0));
	}

	float segment = 1.0f / (listOfPoints.size() - 1);


	startIndex = std::floor(time / segment);
	endIndex = startIndex + 1;

	float t = (time - startIndex * segment) / segment;


	/*Debugger::Print("StartIndex :", startIndex);
	Debugger::Print("EndIndex :", endIndex);
	Debugger::Print("Time :", time);
	Debugger::Print("T :", t);*/

	CubicBezierPoint point1 = listOfPoints[startIndex];
	CubicBezierPoint point2 = listOfPoints[endIndex];

	glm::vec3 rotation = Lerp(point1.rotationOffset, point2.rotationOffset, t);

	glm::vec3 point1Control = point1.controlPoint;

	if (startIndex != 0)
	{
		glm::vec3 diff = point1.point - point1.controlPoint;


		point1Control = point1.point + diff;
	}

	float x, y, z;

	x = std::pow((1 - t), 3) * point1.point.x + 3 * std::pow((1 - t), 2) * t * point1Control.x +
		3 * (1 - t) * std::pow(t, 2) * point2.controlPoint.x + std::pow(t, 3) * point2.point.x;

	y = std::pow((1 - t), 3) * point1.point.y + 3 * std::pow((1 - t), 2) * t * point1Control.y +
		3 * (1 - t) * std::pow(t, 2) * point2.controlPoint.y + std::pow(t, 3) * point2.point.y;

	z = std::pow((1 - t), 3) * point1.point.z + 3 * std::pow((1 - t), 2) * t * point1Control.z +
		3 * (1 - t) * std::pow(t, 2) * point2.controlPoint.z + std::pow(t, 3) * point2.point.z;

	return PointOnCurve(glm::vec3(x, y, z), glm::vec3(0), rotation);
}
//
//PointOnCurve CubicBezierCurve::GetPointOnCurve(float t) const {
//    int numPoints = static_cast<int>(listOfPoints.size());
//
//    if (numPoints < 2) {
//        std::cout << "Insufficient points to create a Bezier curve." << std::endl;
//        return PointOnCurve(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f));
//    }
//
//    std::vector<glm::vec3> points;
//    std::vector<glm::vec3> controlPoints;
//
//    for (const CubicBezierPoint& bezierPoint : listOfPoints) {
//        points.push_back(bezierPoint.point);
//        controlPoints.push_back(bezierPoint.controlPoint);
//    }
//
//    glm::vec3 tangent = glm::vec3(0.0f);
//
//    while (points.size() > 1) {
//        std::vector<glm::vec3> nextPoints;
//        std::vector<glm::vec3> nextControlPoints;
//
//        for (size_t i = 0; i < points.size() - 1; ++i) {
//            glm::vec3 p0 = points[i];
//            glm::vec3 p1 = points[i + 1];
//            glm::vec3 controlPoint = controlPoints[i];
//            glm::vec3 q0 = p0 + t * (controlPoint - p0);
//            glm::vec3 q1 = controlPoint + t * (p1 - controlPoint);
//            glm::vec3 q2 = q0 + t * (q1 - q0);
//
//            nextPoints.push_back(q2);
//            nextControlPoints.push_back(controlPoint);
//        }
//
//        // Calculate the tangent at the last point
//        tangent = (nextPoints.back() - points.back());
//
//        points = nextPoints;
//        controlPoints = nextControlPoints;
//    }
//
//    // Normalize the tangent to get the right vector
//    glm::vec3 rightVector = (glm::length(tangent) > 0.0f) ? glm::normalize(tangent) :
//        listOfPointsOnCurve[listOfPointsOnCurve.size() - 1].tangent;
//
//    return PointOnCurve(points.back(), rightVector, glm::vec3(0));
//}
