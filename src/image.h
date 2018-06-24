#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "common.h"

class Color {
  public:
    double r, g, b;
    Color();
    Color(const double tr, const double rb, const double rg);
    Color(const cv::Vec3b& t);

    void set(const double tr, const double tb, const double tg);
    void operator +=(const Color& c);
    friend Color operator *(const Color& t, const double d);
    friend Color operator +(const Color& a, const Color& t);
    friend Color operator -(const Color& a, const Color& t);
};

class Image {
  private:
    cv::Mat img;
    int offsetx, offsety;

    double normalize(const double c);
  public:
    Image();
    Image(const std::string& filename, const int ox, const int oy);

    void loadImg(const std::string& filename);
    void exportImg(const std::string& filename);
    void drawLine(const Point& p1, const Point& p2);
    void paint(const int x, const int y, const Color& c);
    int width() const;
    int height() const;
    Color getPixel(const Point& p);
};
#endif
