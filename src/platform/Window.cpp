#include "nova/platform/Window.hpp"
#if defined(_WIN32)
#define NOMINMAX
#include <windows.h>
#include <GL/gl.h>
#else
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#endif
namespace nova::platform {
struct Window::Impl {
#if defined(_WIN32)
 HWND h{}; HDC dc{}; HGLRC rc{}; bool close{}; int w{},hgt{};
#else
 Display* d{}; ::Window w{}; GLXContext rc{}; Atom wm{}; bool close{}; int ww{},hh{};
#endif
};
#if defined(_WIN32)
static LRESULT CALLBACK proc(HWND h,UINT m,WPARAM,LPARAM){if(m==WM_CLOSE||m==WM_DESTROY){PostQuitMessage(0);return 0;}return DefWindowProcA(h,m,0,0);}
Window::Window(int w,int h,std::string title):p_(new Impl{}){p_->w=w;p_->hgt=h;auto hi=GetModuleHandleA(nullptr);WNDCLASSA c{};c.lpfnWndProc=proc;c.hInstance=hi;c.lpszClassName="Nova3D";RegisterClassA(&c);p_->h=CreateWindowA(c.lpszClassName,title.c_str(),WS_OVERLAPPEDWINDOW|WS_VISIBLE,CW_USEDEFAULT,CW_USEDEFAULT,w,h,nullptr,nullptr,hi,nullptr);p_->dc=GetDC(p_->h);PIXELFORMATDESCRIPTOR f{};f.nSize=sizeof(f);f.nVersion=1;f.dwFlags=PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER;f.iPixelType=PFD_TYPE_RGBA;f.cColorBits=32;f.cDepthBits=24;SetPixelFormat(p_->dc,ChoosePixelFormat(p_->dc,&f),&f);p_->rc=wglCreateContext(p_->dc);wglMakeCurrent(p_->dc,p_->rc);}
Window::~Window(){if(!p_)return;wglMakeCurrent(nullptr,nullptr);if(p_->rc)wglDeleteContext(p_->rc);if(p_->h)DestroyWindow(p_->h);delete p_.release();}
bool Window::open()const{return p_&&p_->h;}bool Window::shouldClose()const{return p_->close;}void Window::pollEvents(){MSG m{};while(PeekMessageA(&m,nullptr,0,0,PM_REMOVE)){if(m.message==WM_QUIT)p_->close=true;TranslateMessage(&m);DispatchMessageA(&m);}}void Window::swapBuffers(){SwapBuffers(p_->dc);}void Window::requestClose(){p_->close=true;}int Window::width()const{return p_->w;}int Window::height()const{return p_->hgt;}
#else
Window::Window(int w,int h,std::string title):p_(new Impl{}){p_->ww=w;p_->hh=h;p_->d=XOpenDisplay(nullptr);if(!p_->d)return;int a[]={GLX_RGBA,GLX_DOUBLEBUFFER,GLX_DEPTH_SIZE,24,None};auto v=glXChooseVisual(p_->d,DefaultScreen(p_->d),a);if(!v)return;p_->w=XCreateSimpleWindow(p_->d,RootWindow(p_->d,v->screen),0,0,w,h,0,0,0);XStoreName(p_->d,p_->w,title.c_str());XSelectInput(p_->d,p_->w,KeyPressMask|StructureNotifyMask);p_->wm=XInternAtom(p_->d,"WM_DELETE_WINDOW",False);XSetWMProtocols(p_->d,p_->w,&p_->wm,1);p_->rc=glXCreateContext(p_->d,v,nullptr,True);XFree(v);glXMakeCurrent(p_->d,p_->w,p_->rc);XMapWindow(p_->d,p_->w);}
Window::~Window(){if(p_&&p_->d){glXMakeCurrent(p_->d,None,nullptr);if(p_->rc)glXDestroyContext(p_->d,p_->rc);if(p_->w)XDestroyWindow(p_->d,p_->w);XCloseDisplay(p_->d);}delete p_.release();}bool Window::open()const{return p_&&p_->d&&p_->rc;}bool Window::shouldClose()const{return p_->close;}void Window::pollEvents(){if(!p_->d)return;while(XPending(p_->d)){XEvent e;XNextEvent(p_->d,&e);if(e.type==ClientMessage)p_->close=true;if(e.type==KeyPress&&XLookupKeysym(&e.xkey,0)==XK_Escape)p_->close=true;}}void Window::swapBuffers(){glXSwapBuffers(p_->d,p_->w);}void Window::requestClose(){p_->close=true;}int Window::width()const{return p_->ww;}int Window::height()const{return p_->hh;}
#endif
}
