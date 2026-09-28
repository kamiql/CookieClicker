#pragma once

#include "Renderer.hpp"

class Triangle {
public:
    Triangle(Point a, Point b, Point c, Color color)
        : a_(a), b_(b), c_(c), color_(color) {}

    void draw(Renderer& renderer) const {
        renderer.drawTriangle(a_, b_, c_, color_);
    }

private:
    Point a_;
    Point b_;
    Point c_;
    Color color_;
};

class Rectangle {
public:
    Rectangle(float x, float y, float width, float height, Color color)
        : x_(x), y_(y), width_(width), height_(height), color_(color) {}

    void draw(Renderer& renderer) const {
        renderer.drawRectangle(x_, y_, width_, height_, color_);
    }

private:
    float x_;
    float y_;
    float width_;
    float height_;
    Color color_;
};

class Circle {
public:
    Circle(Point center, float radius, Color color)
        : center_(center), radius_(radius), color_(color) {}

    void draw(Renderer& renderer) const {
        renderer.drawCircle(center_, radius_, color_);
    }

    bool contains(Point point) const {
        float dx = point.x - center_.x;
        float dy = point.y - center_.y;
        return dx * dx + dy * dy <= radius_ * radius_;
    }

private:
    Point center_;
    float radius_;
    Color color_;
};