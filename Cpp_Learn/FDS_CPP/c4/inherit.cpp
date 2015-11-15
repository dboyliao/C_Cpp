#include <iostream.h>
enum Boolean{FALSE, TRUE};

class Polygon
{
public:
    int GetId(); // non-virtual member function
    virtual Boolean Concave(); // virtual member function
    virtual int Perimeter() = 0; // pure virtual member function
protected:
    int id;
};

class Rectangle : public Polygon // Rectangle publicly inherits from Polygon
{
public:
    Rectangle(int a, int b, int c, int d, int e) {
	x1 = a; y1 = b; id = c; h = d; w = e;
    }
    Boolean Concave(); // redefined in Rectangle
    int Perimeter(); // defined in Rectangle
    // GetId() and id are inherited from Polygon
    // They, respectively, become public and protected members of Rectangle
private:
    // additional data members required to specialize Rectangle
    int x1, y1, h, w;
};


// GetId must never be redefined in a derived class
int Polygon::GetId() {
    return id;
}

// Default implementation of Concave() in Polygon.
Boolean Polygon::Concave() {
    return TRUE;
}

// Rectangle must define Perimeter() because it is a pure virtual function
int Rectangle::Perimeter() {
    return 2*(h+w);
}

// The default implementtaion of Concave() does not apply to rectangles.
// So, it has to be redefined
Boolean Rectangle::Concave() {
    return FALSE;
}

void main()
{
   Rectangle r(1,1,1,3,4);
   Polygon *s = &r;
   cout << r.GetId() << "\t" << s->GetId() << endl;
   cout << r.Perimeter() << "\t" << s->Perimeter() << endl;
   cout << r.Concave() << "\t" << s->Concave() <<  endl;

}