#pragma once
#include <array>
#include <cmath>
#include <cstddef>
namespace nova::math {
struct Vec3 { float x{},y{},z{}; Vec3 operator+(Vec3 r)const{return{x+r.x,y+r.y,z+r.z};} Vec3 operator-(Vec3 r)const{return{x-r.x,y-r.y,z-r.z};} Vec3 operator*(float s)const{return{x*s,y*s,z*s};} };
float dot(Vec3 a,Vec3 b); Vec3 cross(Vec3 a,Vec3 b); Vec3 normalize(Vec3 v);
struct Mat4 { std::array<float,16> m{}; static Mat4 identity(); static Mat4 perspective(float f,float aspect,float zn,float zf); static Mat4 lookAt(Vec3 eye,Vec3 center,Vec3 up); float* data(){return m.data();} const float* data()const{return m.data();} float& at(std::size_t r,std::size_t c){return m[c*4+r];} };
Mat4 operator*(const Mat4&a,const Mat4&b);
}
