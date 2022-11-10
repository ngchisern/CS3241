//============================================================
// STUDENT NAME:
// NUS User ID.:
// COMMENTS TO GRADER:
//
// ============================================================

#include <cmath>
#include "Sphere.h"

using namespace std;



bool Sphere::hit( const Ray &r, double tmin, double tmax, SurfaceHitRecord &rec ) const
{
    //***********************************************
    //*********** WRITE YOUR CODE HERE **************
    //***********************************************
    Vector3d origin = r.origin() - center;

    double a = dot(r.direction(), r.direction());
    double b = 2 * dot(r.direction(), origin);
    double c = dot(origin,origin) - pow(radius, 2);

    double d = pow(b, 2) - 4 * a * c;
    if (d < 0) {
        return false;
    }

    double t = (- b - sqrt(d)) / (2 * a);
    if (t < 0) {
        t = (- b + sqrt(d)) / (2 * a);
    }

    if (t < 0) {
        return false;
    }

    if ( t < tmin || t > tmax ) return false;

    Vector3d normal = origin + t * r.direction();

    rec.t = t;
    rec.p = r.pointAtParam(t);
    rec.normal = normal / dot(normal, normal);
    rec.material = material;
    return true;
}



bool Sphere::shadowHit( const Ray &r, double tmin, double tmax ) const
{
    //***********************************************
    //*********** WRITE YOUR CODE HERE **************
    //***********************************************
    Vector3d origin = r.origin() - center;

    double a = dot(r.direction(), r.direction());
    double b = 2 * dot(r.direction(), origin);
    double c = dot(origin,origin) - pow(radius, 2);

    double d = pow(b, 2) - 4 * a * c;
    if (d < 0) {
        return false;
    }

    double t = (- b - sqrt(d)) / (2 * a);
    if (t < 0) {
        t = (- b + sqrt(d)) / (2 * a);
    }

    if (t < 0) {
        return false;
    }

    return ( t >= tmin && t <= tmax );
}
