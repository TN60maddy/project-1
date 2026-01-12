add_library(QRCode)

target_include_directories(QRCode PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Source")
target_include_directories(QRCode PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Include")

file(GLOB SOURCE CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.c")
target_sources(QRCode PRIVATE "${SOURCE}")
source_group("Source" FILES ${SOURCE})

if ( "${PLATFORM}" MATCHES "Intrinsics" )
  target_compile_definitions(QRCode PUBLIC -DEW_INTRINSIC_DLL)
  set(EWPATH "C:/Program Files (x86)/Embedded Wizard ${EW_VERSION}")
  if(${EW_VERSION} LESS 12)
    # PUBLIC to let the library consumer get those include directories as well
    target_include_directories(QRCode PUBLIC "${EWPATH}/Chora/Sdk")
    target_include_directories(QRCode PUBLIC "${EWPATH}/Platforms/Tara/Win32/RGBA8888/GFX")
    target_include_directories(QRCode PUBLIC "${EWPATH}/Platforms/Tara/Win32/RTE")
  else()    
    target_include_directories(QRCode PUBLIC "${EWPATH}/SDK")
    target_include_directories(QRCode PUBLIC "${EWPATH}/SDK/Intrinsics")
  endif()
else()
  target_link_libraries(QRCode PRIVATE Bsp)
endif()

if( EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/Platform/${PLATFORM}" )
  add_subdirectory("Platform/${PLATFORM}")
endif()