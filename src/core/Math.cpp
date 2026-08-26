#include "nova/core/Math.hpp"
namespace nova::math {
float dot(Vec3 a,Vec3 b){return a.x*b.x+a.y*b.y+a.z*b.z;} Vec3 cross(Vec3 a,Vec3 b){return{a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x};} Vec3 normalize(Vec3 v){float l=std::sqrt(dot(v,v));return l>1e-6f?v*(1.f/l):Vec3{};}
Mat4 Mat4::identity(){Mat4 r{};r.at(0,0)=r.at(1,1)=r.at(2,2)=r.at(3,3)=1;return r;}
Mat4 Mat4::perspective(float f,float a,float n,float z){Mat4 r{};float t=std::tan(f*.5f);r.at(0,0)=1/(a*t);r.at(1,1)=1/t;r.at(2,2)=-(z+n)/(z-n);r.at(2,3)=-(2*z*n)/(z-n);r.at(3,2)=-1;return r;}
Mat4 Mat4::lookAt(Vec3 e,Vec3 c,Vec3 up){Vec3 f=normalize(c-e),s=normalize(cross(f,up)),u=cross(s,f);Mat4 r=identity();r.at(0,0)=s.x;r.at(0,1)=s.y;r.at(0,2)=s.z;r.at(1,0)=u.x;r.at(1,1)=u.y;r.at(1,2)=u.z;r.at(2,0)=-f.x;r.at(2,1)=-f.y;r.at(2,2)=-f.z;r.at(0,3)=-dot(s,e);r.at(1,3)=-dot(u,e);r.at(2,3)=dot(f,e);return r;}
Mat4 operator*(const Mat4&a,const Mat4&b){Mat4 r{};for(int c=0;c<4;c++)for(int row=0;row<4;row++)for(int k=0;k<4;k++)r.at(row,c)+=a.m[c*4+k]*b.m[k*4+row];return r;}
}
