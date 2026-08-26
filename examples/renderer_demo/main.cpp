#include "nova/platform/Window.hpp"
#include "nova/render/Renderer.hpp"
#include "nova/core/Math.hpp"
#include <chrono>
#include <cmath>
int main(){nova::platform::Window w(1280,720,"Nova3D");if(!w.open())return 2;nova::render::OpenGLRenderer r;if(!r.initialize(w))return 3;auto t0=std::chrono::steady_clock::now();while(!w.shouldClose()){w.pollEvents();float t=std::chrono::duration<float>(std::chrono::steady_clock::now()-t0).count();r.beginFrame(.02f,.03f,.05f);auto p=nova::math::Mat4::perspective(1.0472f,1280.f/720.f,.1f,100.f);auto v=nova::math::Mat4::lookAt({0,0,5},{0,0,0},{0,1,0});auto m=nova::math::Mat4::identity();m.at(0,0)=std::cos(t);m.at(0,2)=std::sin(t);m.at(2,0)=-std::sin(t);m.at(2,2)=std::cos(t);r.drawCube(m,v,p);r.endFrame();w.swapBuffers();}return 0;}
