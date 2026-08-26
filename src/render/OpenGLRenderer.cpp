#include "nova/render/Renderer.hpp"
#if defined(_WIN32)
#include <windows.h>
#include <GL/gl.h>
#else
#include <GL/gl.h>
#endif
namespace nova::render {
bool OpenGLRenderer::initialize(platform::Window&){glEnable(GL_DEPTH_TEST);glEnable(GL_CULL_FACE);glCullFace(GL_BACK);return true;}
void OpenGLRenderer::beginFrame(float r,float g,float b){glViewport(0,0,1280,720);glClearColor(r,g,b,1.f);glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);}
void OpenGLRenderer::drawCube(const math::Mat4& model,const math::Mat4& view,const math::Mat4& proj){glMatrixMode(GL_PROJECTION);glLoadMatrixf(proj.data());glMatrixMode(GL_MODELVIEW);math::Mat4 mv=view*model;glLoadMatrixf(mv.data());static const float v[][3]={{-1,-1,1},{1,-1,1},{1,1,1},{-1,1,1},{-1,-1,-1},{1,-1,-1},{1,1,-1},{-1,1,-1}};static const unsigned q[][4]={{0,1,2,3},{1,5,6,2},{3,2,6,7},{5,4,7,6},{4,0,3,7},{4,5,1,0}};static const float n[][3]={{0,0,1},{1,0,0},{0,1,0},{0,0,-1},{-1,0,0},{0,-1,0}};glBegin(GL_QUADS);for(int f=0;f<6;f++){glNormal3fv(n[f]);for(int k=0;k<4;k++)glVertex3fv(v[q[f][k]]);}glEnd();}
void OpenGLRenderer::endFrame(){}
}
