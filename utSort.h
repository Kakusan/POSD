#ifndef EXP_H
#define EXP_H
#include "include/Shapes.h"
#include "include/Media.h"
#include "include/Sort.h"
#include <vector>
#include <string>

TEST (Sort, sortByIncreasingPerimeter) {
	Rectangle r(0, 0, 3, 4);
	Circle c(0, 0, 3);
	Triangle t(vertex(0, 0), vertex(0, 3), vertex(4, 0));
	
	std::list<Shape*> shapeList;
	shapeList.push_back(&r);
	shapeList.push_back(&c);
	shapeList.push_back(&t);
	Sort::sortByIncreasingPerimeter(&shapeList);
	
	std::vector<Shape*> shapeVector;
	for (Shape* shape : shapeList) {
		shapeVector.push_back(shape);
	}
	
	ASSERT_EQ("t", shapeVector[0]->getShapeName());
	ASSERT_EQ("r", shapeVector[1]->getShapeName());
	ASSERT_EQ("c", shapeVector[2]->getShapeName());
}

TEST (Sort, sortByDecreasingPerimeter) {
	Rectangle r(0, 0, 3, 4);
	Circle c(0, 0, 3);
	Triangle t(vertex(0, 0), vertex(0, 3), vertex(4, 0));
	
	std::list<Shape*> shapeList;
	shapeList.push_back(&r);
	shapeList.push_back(&c);
	shapeList.push_back(&t);
	Sort::sortByDecreasingPerimeter(&shapeList);
	
	std::vector<Shape*> shapeVector;
	for (Shape* shape : shapeList) {
		shapeVector.push_back(shape);
	}
	
	ASSERT_EQ("c", shapeVector[0]->getShapeName());
	ASSERT_EQ("r", shapeVector[1]->getShapeName());
	ASSERT_EQ("t", shapeVector[2]->getShapeName());
}

TEST (Sort, sortByIncreasingArea) {
	Rectangle r(0, 0, 3, 4);
	Circle c(0, 0, 3);
	Triangle t(vertex(0, 0), vertex(0, 3), vertex(4, 0));
	
	std::list<Shape*> shapeList;
	shapeList.push_back(&r);
	shapeList.push_back(&c);
	shapeList.push_back(&t);
	Sort::sortByIncreasingArea(&shapeList);
	
	std::vector<Shape*> shapeVector;
	for (Shape* shape : shapeList) {
		shapeVector.push_back(shape);
	}
	
	ASSERT_EQ("t", shapeVector[0]->getShapeName());
	ASSERT_EQ("r", shapeVector[1]->getShapeName());
	ASSERT_EQ("c", shapeVector[2]->getShapeName());
}

TEST (Sort, sortByDecreasingArea) {
	Rectangle r(0, 0, 3, 4);
	Circle c(0, 0, 3);
	Triangle t(vertex(0, 0), vertex(0, 3), vertex(4, 0));
	
	std::list<Shape*> shapeList;
	shapeList.push_back(&r);
	shapeList.push_back(&c);
	shapeList.push_back(&t);
	Sort::sortByDecreasingArea(&shapeList);
	
	std::vector<Shape*> shapeVector;
	for (Shape* shape : shapeList) {
		shapeVector.push_back(shape);
	}
	
	ASSERT_EQ("c", shapeVector[0]->getShapeName());
	ASSERT_EQ("r", shapeVector[1]->getShapeName());
	ASSERT_EQ("t", shapeVector[2]->getShapeName());
}

TEST (Sort, sortByIncreasingCompactness) {
	Rectangle r(0, 0, 3, 4); // 12/14 = 0.8x  
	Circle c(0, 0, 3); // 9/6 = 1.5
	Triangle t(vertex(0, 0), vertex(0, 3), vertex(4, 0)); // 6/12 = 0.5
	
	std::list<Shape*> shapeList;
	shapeList.push_back(&r);
	shapeList.push_back(&c);
	shapeList.push_back(&t);
	Sort::sortByIncreasingCompactness(&shapeList);
	
	std::vector<Shape*> shapeVector;
	for (Shape* shape : shapeList) {
		shapeVector.push_back(shape);
	}
	
	ASSERT_EQ("t", shapeVector[0]->getShapeName());
	ASSERT_EQ("r", shapeVector[1]->getShapeName());
	ASSERT_EQ("c", shapeVector[2]->getShapeName());
}

#endif
