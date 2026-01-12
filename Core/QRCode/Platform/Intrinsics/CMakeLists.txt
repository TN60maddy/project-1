add_library(QRCodeIntrinsics SHARED)

# Preprocessor defines
target_compile_definitions(QRCodeIntrinsics PUBLIC -D_CRT_SECURE_NO_WARNINGS -D_CRT_NONSTDC_NO_DEPRECATE)

target_include_directories(QRCodeIntrinsics PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Source")
target_include_directories(QRCodeIntrinsics PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Include")

if(${EW_VERSION} LESS 12)
  set(PPSOURCES "${EMWIPATH}/Chora/Sdk/ewrte.c")
  target_sources(QRCodeIntrinsics PRIVATE ${PPSOURCES})
  source_group("PlatformPackage" FILES ${PPSOURCES}) 
else()
  set(PPSOURCES "${EMWIPATH}/SDK/Intrinsics/ewrte.c"
    "${EMWIPATH}/SDK/Intrinsics/ewgfx.c")
  target_sources(QRCodeIntrinsics PRIVATE ${PPSOURCES})
  source_group("PlatformPackage" FILES ${PPSOURCES})
endif()

file(GLOB SOURCE CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.c")
target_sources(QRCodeIntrinsics PRIVATE "${SOURCE}")
source_group("Source" FILES ${SOURCE})

# Set the name of the output shared library
set_target_properties(QRCodeIntrinsics PROPERTIES PREFIX "" OUTPUT_NAME "QRCode" SUFFIX ".ewi")

# Set the output path for the output shared library
set_target_properties(QRCodeIntrinsics
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/EmWiGui"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/EmWiGui"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/EmWiGui"
)

target_link_libraries(QRCodeIntrinsics PRIVATE QRCode)