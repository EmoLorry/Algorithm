#include<iostream>
using namespace std;
class Circle
{
private:
	double radius;
public:
	Circle(double r):radius(r)
	{
		cout <<"Ô²µÄ°ë¾¶" << radius << endl;
	}
	Circle() {
		radius = 33;
		cout << "Ô²µÄ°ë¾¶£¨£©" << radius << endl;
	}
	double GetR() { return radius; }

};
class Cylinder :public Circle {
private:
	Circle c;
	const double height;
	double text1;
	Circle c1, c2;
	double& textref;
	double text2;
public:
	Cylinder(double r, double h) :text1(h), Circle(r = 20), c2(r + 5), c1(r = 18), height(h = 25), text2(r), textref(text2)
	{
		cout<<"Ô²ÖùµÄ°ë¾¶" << GetR() << endl;

	}

};
int main()
{
	Cylinder cy(3, 5);
	return 0;
}
