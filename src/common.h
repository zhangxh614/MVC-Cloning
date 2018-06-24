#ifndef COMMON_H
#define COMMON_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

// CGAL includes for triangulation
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_conformer_2.h>
#include <CGAL/Triangulation_vertex_base_2.h>
#include <CGAL/Delaunay_mesh_face_base_2.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/Polygon_2_algorithms.h>
#include <CGAL/Delaunay_mesher_2.h>
#include <CGAL/Delaunay_mesh_size_criteria_2.h>

// CGAL typedefs and definitions
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Delaunay_mesh_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Constrained_Delaunay_triangulation_2<K, Tds> DelaunayTriangulation;

typedef CGAL::Delaunay_mesh_size_criteria_2<DelaunayTriangulation> Criteria;

typedef DelaunayTriangulation::Finite_vertices_iterator FiniteVerticesIterator;
typedef DelaunayTriangulation::Finite_faces_iterator FiniteFacesIterator;
typedef DelaunayTriangulation::Finite_edges_iterator FiniteEdgesIterator;
typedef DelaunayTriangulation::Face_circulator FacesCirculator;
typedef DelaunayTriangulation::Point_iterator PointIterator;
typedef DelaunayTriangulation::Vertex Vertex;
typedef DelaunayTriangulation::Vertex_handle VertexHandle;
typedef DelaunayTriangulation::Edge Edge;
typedef DelaunayTriangulation::Face Face;
typedef DelaunayTriangulation::Face_handle FaceHandle;
typedef DelaunayTriangulation::Triangle Triangle;

typedef CGAL::Cartesian<double> Metric;
typedef DelaunayTriangulation::Point Point;
typedef CGAL::Polygon_2<Metric> Polygon2D;
typedef CGAL::Bbox_2 BBox2D;

typedef CGAL::Bounded_side Side;

typedef CGAL::Delaunay_mesher_2<DelaunayTriangulation, Criteria> Mesher;

#endif
