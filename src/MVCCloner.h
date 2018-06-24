#ifndef __MVC_CLONER__H
#define __MVC_CLONER__H

#include "common.h"
#include "image.h"

class MVCCloner {
  private:
    DelaunayTriangulation* adaptiveMesh;

    void calMVC(const Point& p, double* lambda, const std::vector<Point>& curve);
    void fh2fp(const FaceHandle& fh, std::vector<Point>& fp);
  public:
    MVCCloner();

    void preprocess(const std::vector<Point>& curve);
    void MVCClonerSolver(Image& target, Image& source, const std::vector<Point>& curve);
    void paintMesh(Image& img);

    virtual ~MVCCloner() {};
};

#endif
