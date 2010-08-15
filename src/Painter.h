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

#ifndef CANVAS_PAINTER_HEADER
#define CANVAS_PAINTER_HEADER

#include <string>
#include <list>
#include <map>
#include <v8.h>
#include "Script.h"
#include "Context.h"
#include "Callback.h"
#include "Canvas.h"
#include "util/Mutex.h"
#include "binding/Object.h"

namespace canvas
{
   class Painter
   {
         typedef std::map<int, Callback> CallbackMap;
         
      public:
         Painter(int width, int height, Canvas::Format format, std::string const& fileOrCode, bool isFile = true);
         ~Painter();
         
         void start();
         
         void draw();
         
         void copyImageTo(void * target);
         
         int setInterval(v8::Handle<v8::Function> const& function);
         void clearInterval(int index);
         
         v8::Handle<v8::Value> getContext(std::string const& type);
         
         int width() const { return m_width; }
         /// Only here because binding system must have a get/set pair.
         void setWidth(int);
         
         int height() const { return m_height; }
         /// Only here because binding system must have a get/set pair.
         void setHeight(int);
         
         /// Store a string in the log history.
         void log(std::string const& log);
         
         /// Returns the oldest entry in the history, 
         /// while also poping it from the list.
         std::string lastLogEntry();
         
      private:
         Mutex m_painterMutex;
         Mutex m_logMutex;
         
         int m_width;
         int m_height;
         Canvas::Format m_format;
         std::string m_fileOrCode;
         bool m_isFile;
         
         Script * m_script;
         Context * m_context;
         
         /// Stores the log history
         std::list<std::string> m_history;
         
         CallbackMap m_callbacks;
         int m_callbackIndex;
         
         binding::Object<Painter> * m_windowBinding;
         binding::Object<Context> * m_contextBinding;
         
         v8::Persistent<v8::ObjectTemplate> m_scriptTemplate;
   };
}

#endif

