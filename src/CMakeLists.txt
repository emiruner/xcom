FILE(GLOB xcomSources *.cpp platform/linux/*.cpp)
LINK_LIBRARIES(dl)
INCLUDE_DIRECTORIES(${xcom_SOURCE_DIR}/include)
ADD_LIBRARY(xcom SHARED ${xcomSources})
INSTALL(TARGETS xcom LIBRARY DESTINATION lib)
