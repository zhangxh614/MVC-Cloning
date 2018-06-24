#include "MVCCloner.h"
#include <algorithm>
#include <cmath>

inline double distance(const Point& a, const Point& b) {
    return sqrt(CGAL::squared_distance(a, b));
}

inline double tan1_2(double a, double b, double c) {
    double cosine = (a * a + b * b - c * c) / (2 * a * b);
    cosine = fmax(-1.0, fmin(cosine, 1.0));
    double t = acos(cosine);
    return tan(t / 2);
}

MVCCloner::MVCCloner() {
    adaptiveMesh = new DelaunayTriangulation();
}

void MVCCloner::preprocess(const std::vector<Point>& curve) {
    std::cout << "MVCCloner: Working on " << curve.size() << " boundary vertices" << std::endl;

    // create the adaptive mesh using CGAL

    std::cout << "MVCCloner: Creating adaptive mesh ";
    std::cout << "...";

    adaptiveMesh->clear();
    adaptiveMesh->insert(curve.begin(), curve.end());
    for (unsigned int i = 0 ; i < curve.size() ; ++i) {
        Point curr = curve[i];
        Point next = curve[(i + 1) % curve.size()];
        adaptiveMesh->insert_constraint(curr, next);
    }
    Mesher mesher(*adaptiveMesh);
    mesher.set_criteria(Criteria(0.125, 0));
    mesher.refine_mesh();
    std::cout << " Done with " << adaptiveMesh->number_of_vertices()
              << " vertices and " << adaptiveMesh->number_of_faces()
              << " triangles." << std::endl;
}

void MVCCloner::calMVC(const Point& p, double* lambda, const std::vector<Point>& curve) {
    int cagesize = curve.size();

    double* len = new double[cagesize];
    for(int i = 0; i < cagesize; i++) {
        len[i] = distance(curve[i], p);
        if(len[i] < 1) {
            for(int j = 0; j < cagesize; j++) {
                lambda[j] = 0;
            }
            lambda[i] = 1;
            return;
        }
    }

    double* tana = new double[cagesize];
    for(int i = 0; i < cagesize - 1; i++) {
        tana[i] = tan1_2(len[i], len[i + 1], distance(curve[i], curve[i + 1]));
    }
    tana[cagesize - 1] = tan1_2(len[cagesize - 1], len[0], distance(curve[0], curve[cagesize - 1]));

    double sum = 0.0;
    double* w = new double[cagesize];
    for(int i = 1; i < cagesize; i++) {
        sum += w[i] = (tana[i - 1] + tana[i]) / len[i];
    }
    sum += w[0] = (tana[cagesize - 1] + tana[0]) / len[0];

    double nor = 1.0 /  sum;
    for(int i = 0; i < cagesize; i++) {
        lambda[i] = w[i] * nor;
    }

    delete[] len;
    delete[] tana;
    delete[] w;
}

void MVCCloner::fh2fp(const FaceHandle& fh, std::vector<Point>& fp) {
    fp.clear();
    for(int i = 0; i < 3; i ++) {
        Point p = fh -> vertex(i) -> point();
        fp.push_back(p);
    }
}

void MVCCloner::MVCClonerSolver(Image& target, Image& source, const std::vector<Point>& curve) {
    int cagesize = curve.size();
    int w = source.width();
    int h = source.height();

    std::vector<Point> vertics;
    for (FiniteVerticesIterator iter = adaptiveMesh->finite_vertices_begin(); iter != adaptiveMesh->finite_vertices_end() ; ++iter) {
        Point p = iter->point();
        vertics.push_back(p);
    }

    Color* diff = new Color[cagesize];
    for(int i = 0; i < cagesize; i ++) {
        diff[i] = Color(target.getPixel(curve[i]) - source.getPixel(curve[i]));
    }
    double*** lambda = new double**[w];
    Color** r = new Color*[w];
    for(int i = 0; i < w; i ++) {
        lambda[i] = new double*[h];
        r[i] = new Color[h];
        for(int j = 0; j < h; j ++) {
            lambda[i][j] = new double[cagesize];
        }
    }
    for(auto p : vertics) {
        int x = p.x();
        int y = p.y();
        calMVC(p, lambda[x][y], curve);
        Color c(0.0, 0.0, 0.0);
        for(int k = 0; k < cagesize; k ++) {
            c += diff[k] * lambda[x][y][k];
        }
        r[x][y] = c;
        target.paint(x, y, source.getPixel(p) + c);
    }
    for(int i = 0; i < w; i ++) {
        for(int j = 0; j < h; j ++) {

            Point p(i, j);
            Side side = CGAL::bounded_side_2(curve.begin(), curve.end(), p, K());
            if(side == CGAL::ON_BOUNDED_SIDE) {
                FaceHandle fh = adaptiveMesh->locate(p);
                std::vector<Point> fp;
                fh2fp(fh, fp);
                Color c = (r[(int)fp[0].x()][(int)fp[0].y()] + r[(int)fp[1].x()][(int)fp[1].y()] + r[(int)fp[2].x()][(int)fp[2].y()]) * 0.3333333;
                target.paint(i, j, source.getPixel(p) + c);
            }
        }
    }

    delete[] diff;
    for(int i = 0; i < w; i ++) {
        for(int j = 0; j < h; j ++)
            delete[] lambda[i][j];
        delete[] lambda[i];
        delete[] r[i];
    }
    delete[] lambda;
    delete[] r;
}

void MVCCloner::paintMesh(Image& img) {
    for (FiniteFacesIterator iter = adaptiveMesh->finite_faces_begin() ; iter != adaptiveMesh->finite_faces_end() ; ++iter) {
        Triangle triangle = adaptiveMesh->triangle(iter);
        Point v1 = triangle.vertex(0);
        Point v2 = triangle.vertex(1);
        Point v3 = triangle.vertex(2);

        img.drawLine(v1, v2);
        img.drawLine(v1, v3);
        img.drawLine(v2, v3);
    }
}
