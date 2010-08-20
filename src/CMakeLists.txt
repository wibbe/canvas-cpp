
SET(SOURCE 
  Canvas.cpp
  ColorParser.cpp
  Context.cpp
  Painter.cpp
  Script.cpp
  State.cpp
  ImageData.cpp
  util/Mutex.cpp
  util/ScopedLock.cpp
  util/Thread.cpp
  binding/Object.cpp
)

SET(LIBRARIES
  skia
  v8
)

IF(APPLE)
  LIST(APPEND SOURCE util/Timer.mm)
ELSE()
  LIST(APPEND SOURCE util/Timer.cpp)
ENDIF()

ADD_LIBRARY(canvas ${SOURCE})
TARGET_LINK_LIBRARIES(canvas ${LIBRARIES})

