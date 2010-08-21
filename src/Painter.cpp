/**
 * Copyright (c) 2010 Daniel Wiberg
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "Painter.h"
#include "util/ScopedLock.h"

#include <iostream>

namespace canvas
{
   
   Painter::Painter(int width, int height, Canvas::Format format)
      : m_painterMutex(),
        m_imageMutex(),
        m_logMutex(),
        m_width(width),
        m_height(height),
        m_format(format),
        m_script(0),
        m_context(0),
        m_callbackIndex(0),
        m_windowBinding(0),
        m_consoleBinding(0),
        m_contextBinding(0),
        m_imageDataBinding(0)
   {
   }
   
   void Painter::start(std::string const& fileOrCode, bool isFile)
   {
      v8::HandleScope scope;
      
      // Create V8 context
      m_scriptTemplate = v8::Persistent<v8::ObjectTemplate>::New(v8::ObjectTemplate::New());
      v8::Local<v8::Context> jsContext = v8::Local<v8::Context>::New(v8::Context::New(0, m_scriptTemplate));

      // Create bindings
      m_windowBinding = new binding::Object<Painter>("Window");
      m_windowBinding->function("setInterval", &Painter::setInterval)
                      .function("clearInterval", &Painter::clearInterval)
                      .function("getContext", &Painter::getContext)
                      .function("getImage", &Painter::getImage)
                      .attribute("width", &Painter::width, &Painter::setWidth)
                      .attribute("height", &Painter::height, &Painter::setHeight);
                      
      m_consoleBinding = new binding::Object<Painter>("Console");
      m_consoleBinding->function("log", &Painter::log);
      
      m_contextBinding = new binding::Object<Context>("Context");
      m_contextBinding->function("scale", &Context::scale)
                       .function("rotate", &Context::rotate)
                       .function("translate", &Context::translate)
                       .functionV8("drawImage", &Context::drawImageCallback)
                       .function("beginPath", &Context::beginPath)
                       .function("closePath", &Context::closePath)
                       .function("moveTo", &Context::moveTo)
                       .function("lineTo", &Context::lineTo)
                       .function("quadraticCurveTo", &Context::quadraticCurveTo)
                       .function("bezierCurveTo", &Context::bezierCurveTo)
                       .function("arcTo", &Context::arcTo)
                       .function("rect", &Context::rect)
                       .function("fillRect", &Context::fillRect)
                       .function("strokeRect", &Context::strokeRect)
                       .function("fill", &Context::fill)
                       .function("stroke", &Context::stroke)
                       .function("clear", &Context::clear)
                       .function("clearRéct", &Context::clearRect)
                       .attribute("lineWidth", &Context::lineWidth, &Context::setLineWidth)
                       .attribute("lineCap", &Context::lineCap, &Context::setLineCap)
                       .attribute("strokeStyle", &Context::strokeStyle, &Context::setStrokeStyle)
                       .attribute("fillStyle", &Context::fillStyle, &Context::setFillStyle)
                       .attribute("globalAlpha", &Context::globalAlpha, &Context::setGlobalAlpha);
                       
      m_imageDataBinding = new binding::Object<ImageData>("ImageData");
      m_imageDataBinding->attribute("width", &ImageData::width, &ImageData::setWidth)
                         .attribute("height", &ImageData::height, &ImageData::setHeight);
      
      v8::Context::Scope contextScope(jsContext);
      
      // Inject the window object
      jsContext->Global()->Set(v8::String::New("window"), m_windowBinding->wrap(this));
      jsContext->Global()->Set(v8::String::New("console"), m_consoleBinding->wrap(this));
                     
      // Create graphics context
      m_context = new Context(m_width, m_height, m_format);
      
      // Create javascript object
      m_script = new Script(jsContext);
      if (isFile)
         m_script->load(fileOrCode);
      else
         m_script->runString(fileOrCode);
         
      m_timer.reset();
   }
   
   Painter::~Painter()
   {
      delete m_script;
      delete m_context;
      delete m_imageDataBinding;
      delete m_contextBinding;
      delete m_consoleBinding;
      delete m_windowBinding;
   }
   
   void Painter::setWidth(int)
   {
      assert(0 && "Invalid operation, not allowed to set width!");
   }
         
   void Painter::setHeight(int)
   {
      assert(0 && "Invalid operation, not allowed to set height!");
   }
   
   void Painter::draw()
   {
      ScopedLock lock(m_painterMutex);
      
      // Call all registered callbacks
      v8::HandleScope scope;
      v8::Context::Scope contextScope(m_script->context());
      v8::TryCatch tryCatch;
   
      CallbackMap::iterator it = m_callbacks.begin();
      CallbackMap::iterator end = m_callbacks.end();
      
      double dt = m_timer.seconds();
      m_timer.reset();
      
      for (; it != end; ++it)
      {
         Callback & callback = it->second;
         
         v8::Handle<v8::Value> result = callback.call(dt);
         if (result.IsEmpty())
         {
            v8::String::Utf8Value error(tryCatch.Exception());
            std::cerr << "Script runtime error: " << *error << std::endl;
         }
      }
   }
   
   void Painter::copyImageTo(void * target)
   {
      ScopedLock lock(m_painterMutex);
      if (target && m_context)
         m_context->copyImageTo(target);
   }
   
   int Painter::setInterval(v8::Handle<v8::Function> const& function, int interval)
   {
      m_callbacks.insert(std::make_pair(++m_callbackIndex, Callback(function, interval)));
      return m_callbackIndex;
   }
   
   void Painter::clearInterval(int index)
   {
      CallbackMap::iterator result = m_callbacks.find(index);
      if (result != m_callbacks.end())
         m_callbacks.erase(result);
   }
   
   v8::Handle<v8::Value> Painter::getContext(std::string const& type)
   {
      v8::HandleScope scope;
      if (type == "2d")
         return scope.Close(m_contextBinding->wrap(m_context));
      
      std::cerr << "Error: Requested wrong context type '" << type << "'" << std::endl;
      return v8::Undefined();
   }
   
   void Painter::registerImage(std::string const& name, ImageData * image)
   {
      assert(image);
      ScopedLock lock(m_imageMutex);
      
      std::map<std::string, ImageData*>::iterator result = m_images.find(name);
      if (result != m_images.end())
      {
         std::cerr << "Failed to register image '" << name << "'. Image with the same name present!" << std::endl;
         return;
      }
      
      m_images.insert(std::make_pair(name, image));
   }
   
   v8::Handle<v8::Value> Painter::getImage(std::string const& name)
   {
      ScopedLock lock(m_imageMutex);
      v8::HandleScope scope;
      
      std::map<std::string, ImageData*>::iterator result = m_images.find(name);
      if (result == m_images.end())
         return v8::Undefined();
         
      return scope.Close(m_imageDataBinding->wrap(result->second));
   }
   
   void Painter::log(std::string const& log)
   {
      ScopedLock lock(m_logMutex);
      
      m_history.push_back(log);
      
      // We only store a 1000 log entries
      if (m_history.size() > 1000)
         m_history.pop_front();
         
      //std::cerr << log << std::endl;
   }
   
   std::string Painter::lastLogEntry()
   {
      ScopedLock lock(m_logMutex);
      
      if (m_history.empty())
         return "";
      
      std::string log = m_history.front();
      m_history.pop_front();
      return log;
   }
   
}

