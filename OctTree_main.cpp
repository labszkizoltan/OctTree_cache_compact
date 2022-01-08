
#include <iostream>
#include <stdlib.h> //rand
#include <chrono>

#include "OctTree.h"

// naive neighbourhood search
std::vector<Vec3D> GetNeighborhood(Vec3D point, float radius, const std::vector<Vec3D>& points)
{
	std::vector<Vec3D> result;
	float r2 = radius * radius;
	for (int i = 0; i < points.size(); i++)
	{
		float length2 = (point - points[i]).lengthSquare();
		if (length2 < r2)
			result.push_back(points[i]);
	}

	return result;
}


/*
int main()
{
	std::cout << "sizeof(Node<short int>): " << sizeof(Node<short int>) << "\n";
	std::cout << "sizeof(Node<int>): " << sizeof(Node<int>) << "\n";
	std::cout << "sizeof(Node<char>): " << sizeof(Node<char>) << "\n";
	std::cout << "sizeof(Node<void*>): " << sizeof(Node<void*>) << "\n";
	std::cout << "sizeof(Node<Vec3D>): " << sizeof(Node<Vec3D>) << "\n";

	OctTree<int> tree(Box3D({ Vec3D(0,0,0), Vec3D(10,10,10) }));

	int point_count = 10000;
	std::vector<Vec3D> all_points;
	for (int i = 0; i < point_count; i++)
	{
		Vec3D v(
			(float)(rand() % 1000) / 50.0f - 10.0f,
			(float)(rand() % 1000) / 50.0f - 10.0f,
			(float)(rand() % 1000) / 50.0f - 10.0f
		);
		all_points.push_back(v);
	}

	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < point_count; i++)
		tree.Insert(all_points[i], i);

	auto finish = std::chrono::high_resolution_clock::now();
	std::cout << "Building the OctTree took (microsec):" << std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count() << "\n";

	//----- Searching the tree -----//

	float radius = 1.0f;
	Box3D box; box.center = Vec3D(5.0, 5.0, -5.0); box.radius = Vec3D(radius, radius, radius);

	long long int time_sum = 0;
	int measurement_count = std::min(point_count, 1000);
	std::vector<int> query_result; query_result.reserve(10);

	for (int i = 0; i < measurement_count; i++)
	{
		box.center = all_points[i];

		auto start = std::chrono::high_resolution_clock::now();
//		std::vector<int> something = tree.QueryRange(box);
		query_result.clear();
		tree.QueryRange(box, query_result, 0);
		auto finish = std::chrono::high_resolution_clock::now();

		time_sum += std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
	}
	std::cout << "avg time searching the OctTree: " << (double)time_sum / measurement_count << "\n";

	// with OCTREE_NODE_CAPACITY = 32, point_count = 100000, tree.QueryRange(box)
//	Building the OctTree took(microsec) :33871
//	avg time searching the OctTree : 11.87
//	Building the OctTree took(microsec) :34541
//	avg time searching the OctTree : 11.929

	// with OCTREE_NODE_CAPACITY = 32, point_count = 100000, tree.QueryRange(box, query_result, 0) <- this doesnt reallocate memory for the results
//	Building the OctTree took(microsec) :34145
//	avg time searching the OctTree : 8.517
//	Building the OctTree took(microsec) :34559
//	avg time searching the OctTree : 8.505

	// with OCTREE_NODE_CAPACITY = 32, point_count = 10000, tree.QueryRange(box)
//	Building the OctTree took(microsec) :3169
//	avg time searching the OctTree : 3.928
//	Building the OctTree took(microsec) :2719
//	avg time searching the OctTree : 3.723

	// with OCTREE_NODE_CAPACITY = 32, point_count = 10000, tree.QueryRange(box, query_result, 0) <- this doesnt reallocate memory for the results
//	Building the OctTree took(microsec) :2740
//	avg time searching the OctTree : 2.542
//	Building the OctTree took(microsec) :2810
//	avg time searching the OctTree : 2.488


	std::cout << "program finished\n";
	return 0;
}
*/



int main()
{
	OctTree<Vec3D> tree(Box3D({ Vec3D(0,0,0), Vec3D(10,10,10) }));

	int point_count = 10000;
	std::vector<Vec3D> all_points;
	for (int i = 0; i < point_count; i++)
	{
		Vec3D v(
			(float)(rand() % 1000) / 50.0f - 10.0f,
			(float)(rand() % 1000) / 50.0f - 10.0f,
			(float)(rand() % 1000) / 50.0f - 10.0f
		);
		all_points.push_back(v);
	}

	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < point_count; i++)
		tree.Insert(all_points[i], all_points[i]);

	auto finish = std::chrono::high_resolution_clock::now();
	std::cout << "Building the OctTree took (microsec):" << std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count() << "\n";

	//----- Searching the tree -----//

	float radius = 1.0f;
	Box3D box; box.center = Vec3D(5.0, 5.0, -5.0); box.radius = Vec3D(radius, radius, radius);

	long long int time_sum = 0;
	int measurement_count = std::min(point_count, 1000);
	std::vector<Vec3D> query_result; query_result.reserve(10);

	for (int i = 0; i < measurement_count; i++)
	{
		box.center = all_points[i];

		auto start = std::chrono::high_resolution_clock::now();
		std::vector<Vec3D> something = tree.QueryRange(box);
//		query_result.clear();
//		tree.QueryRange(box, query_result, 0);
		auto finish = std::chrono::high_resolution_clock::now();

		time_sum += std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
	}
	std::cout << "avg time searching the OctTree: " << (double)time_sum / measurement_count << "\n";

	// with OCTREE_NODE_CAPACITY = 32, point_count = 100000
//	Building the OctTree took(microsec) :37928
//	avg time searching the OctTree : 13.403
//	Building the OctTree took(microsec) :41863
//	avg time searching the OctTree : 13.866

	// with OCTREE_NODE_CAPACITY = 32, point_count = 100000, no mem realloc for result querying
//	Building the OctTree took(microsec) :36768
//	avg time searching the OctTree : 8.802
//	Building the OctTree took (microsec):37280
//	avg time searching the OctTree : 9.001


	// with OCTREE_NODE_CAPACITY = 32, point_count = 10000
//	Building the OctTree took(microsec) :3502
//	avg time searching the OctTree : 4.084
//	Building the OctTree took(microsec) :3293
//	avg time searching the OctTree : 4.38

	// with OCTREE_NODE_CAPACITY = 32, point_count = 10000, no mem realloc for result querying
//	Building the OctTree took(microsec) :3370
//	avg time searching the OctTree : 2.571
//	Building the OctTree took(microsec) :3097
//	avg time searching the OctTree : 2.631

	std::cout << "program finished\n";
	return 0;
}

















