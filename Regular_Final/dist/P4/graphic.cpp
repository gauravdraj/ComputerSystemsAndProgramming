#include  <iostream>
#include "graphic.hpp"

// constructor 
// default set (_x, _y, _z) = (0, 0, 0)
Vec3::Vec3(){
  _x = 0;
  _y = 0;
  _z = 0;
};
// constructor
Vec3::Vec3(const double & _x1, const double & _y1, const double & _z1){
  // your code here
  _x = _x1;
  _y = _y1;
  _z = _z1;
};
// copy constructor 
Vec3::Vec3(const Vec3 & _p){
  _x = _p.x();
  _y = _p.y();
  _z = _p.z();
};

// return value of _x
const double Vec3::x() const{
  return _x;
};

//return value of _y
const double Vec3::y() const{
  return _y;
};

// return value of _z
const double Vec3::z() const{
  return _z;
}
// modify _x
void Vec3::set_x(const double& _t){
  // your code here
  _x = _t;
};
// modify _y
void Vec3::set_y(const double& _t){
  // your code here
  _y = _t;
};
// modify _z
void Vec3::set_z(const double& _t){
  // your code here
  _z = _t;
};
// operator overloading +
Vec3 Vec3::operator + (const Vec3 &b){
  // your code here
  return Vec3(_x + b.x(), _y + b.y(), _z + b.z());
}

Vec3 Vec3::operator - (const Vec3 &b){
  // your code here
  return Vec3(_x - b.x(), _y - b.y(), _z - b.z());
}


Vec3 Vec3::operator ^ (const Vec3 &b){
  // your code here
  return Vec3((_y * b.z()) - (_z * b.y()), (_z * b.x()) - (_x * b.z()), (_x * b.y()) - (_y * b.x()));
};

