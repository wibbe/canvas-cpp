
SET(SOURCE 
  CanvasTest.cpp
  ColorParserTest.cpp
  Main.cpp
)

SET(LIBRARIES
  canvas
  skia
  v8
)
              
IF(APPLE)
  LIST(APPEND LIBRARIES ${Carbon_FRAMEWORK})
  LIST(APPEND LIBRARIES ${Cocoa_FRAMEWORK})
ENDIF()

ADD_EXECUTABLE(unit_test ${SOURCE})
TARGET_LINK_LIBRARIES(unit_test ${LIBRARIES})