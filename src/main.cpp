#include "MVCCloner.h"
#include "image.h"
#include "common.h"

#include <cmath>
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

void ReadVertex(const string& filename, vector<Point>& v) {
    ifstream in;
    in.open(filename, ios::in);
    int cnt;
    in >> cnt;
    int x, y;
    for(int i = 0; i < cnt; i ++) {
        in >> x >> y;
        v.push_back(Point(x, y));
    }
    in.close();
}


int main() {
    MVCCloner cloner;
    string name;
    cout << "Please input name: " << endl;
    cin >> name;
    int offsetx, offsety;
    cout << "Please input offset x and y (int): " << endl;
    cin >> offsetx >> offsety;
    Image sImg("../images/" + name + "_source.jpg", 0, 0);
    Image tImg("../images/" + name + "_target.jpg", offsetx, offsety);
    vector<Point> curve;
    ReadVertex("../edge/" + name + ".txt", curve);


    cloner.preprocess(curve);
    cloner.MVCClonerSolver(tImg, sImg, curve);
    // DelaunayTriangulation *adaptiveMesh = cmesh->mesh;
    // cloner.tagFaces(adaptiveMesh);

    cloner.paintMesh(sImg);
    tImg.exportImg("../result/" + name + "_result.png");
    sImg.exportImg("../result/" + name + "_mesh.png");

    return 0;
}
