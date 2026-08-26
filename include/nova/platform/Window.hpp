#pragma once
#include <memory>
#include <string>
namespace nova::platform { class Window { struct Impl; std::unique_ptr<Impl> p_; public: Window(int width,int height,std::string title); ~Window(); Window(const Window&)=delete; bool open()const; bool shouldClose()const; void pollEvents(); void swapBuffers(); void requestClose(); int width()const; int height()const; }; }
