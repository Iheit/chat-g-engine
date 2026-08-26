#pragma once
#include "nova/core/Math.hpp"
#include "nova/platform/Window.hpp"
#include <vector>
#include <cstdint>
namespace nova::render {
struct Vertex{math::Vec3 position;math::Vec3 normal;};
class Renderer{public:virtual~Renderer()=default;virtual bool initialize(platform::Window&)=0;virtual void beginFrame(float,float,float)=0;virtual void drawCube(const math::Mat4&,const math::Mat4&,const math::Mat4&)=0;virtual void endFrame()=0;};
class OpenGLRenderer final:public Renderer{public:bool initialize(platform::Window&)override;void beginFrame(float,float,float)override;void drawCube(const math::Mat4&,const math::Mat4&,const math::Mat4&)override;void endFrame()override;};
}
