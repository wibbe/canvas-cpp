
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
  LIST(APPEND LIBRARIES ${Carbon_FRAMEWORK})
ENDIF()

ADD_LIBRARY(canvas ${SOURCE})
TARGET_LINK_LIBRARIES(canvas ${LIBRARIES})

