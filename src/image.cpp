#include "image.h"

Color::Color(): r(0), g(0), b(0) { }

Color::Color(const double tr, const double tg, const double tb) {
    r = tr;
    g = tg;
    b = tb;
}

Color::Color(const cv::Vec3b& t) {
    r = t[2];
    g = t[1];
    b = t[0];
}

void Color::set(const double tr, const double tb, const double tg) {
    r = tr;
    g = tg;
    b = tb;
}

void Color::operator+=(const Color& c) {
    r += c.r;
    g += c.g;
    b += c.b;
}

Color operator*(const Color& t, const double d) {
    return Color(t.r * d, t.g * d, t.b * d);
}

Color operator +(const Color& a, const Color& t) {
    return Color(a.r + t.r, a.g + t.g, a.b + t.b);
}

Color operator -(const Color& a, const Color& t) {
    return Color(a.r - t.r, a.g - t.g, a.b - t.b);
}

double Image::normalize(const double c) {
    if(c > 255) return 255;
    if(c < 0) return 0;
    return c;
}

Image::Image() { }

Image::Image(const std::string& filename, const int ox, const int oy):
    offsetx(ox), offsety(oy) {
    img = cv::imread(filename);
}

void Image::loadImg(const std::string& filename) {
    img = cv::imread(filename);
}

void Image::exportImg(const std::string& filename) {
    cv::imwrite(filename, img);
}

void Image::drawLine(const Point& p1, const Point& p2) {
    cv::Point start = cv::Point(p1.x() + offsetx, p1.y() + offsety);
    cv::Point end = cv::Point(p2.x() + offsetx, p2.y() + offsety);
    cv::line(img, start, end, cv::Scalar(0, 255, 255));
}

void Image::paint(const int x, const int y, const Color& c) {
    int tx = x + offsetx;
    int ty = y + offsety;
    img.at<cv::Vec3b>(ty, tx)[0] = normalize(c.b);
    img.at<cv::Vec3b>(ty, tx)[1] = normalize(c.g);
    img.at<cv::Vec3b>(ty, tx)[2] = normalize(c.r);
}

int Image::width() const {
    return img.cols;
}

int Image::height() const {
    return img.rows;
}

Color Image::getPixel(const Point& p) {
    return Color(img.at<cv::Vec3b>(p.y() + offsety, p.x() + offsetx));
}
