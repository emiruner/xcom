PROJECT(xcom)
CMAKE_MINIMUM_REQUIRED(VERSION 3.0.2)
ADD_SUBDIRECTORY(src)

FILE(GLOB xcomIncludes include/xcom/*.hpp include/xcom/*.inc)
INSTALL(FILES ${xcomIncludes} DESTINATION include/xcom)

FILE(GLOB xcomMetadataIncludes include/xcom/metadata/*.hpp)
INSTALL(FILES ${xcomMetadataIncludes} DESTINATION include/xcom/metadata)

FILE(GLOB xcomIdlFiles idl/xcom/*.idl)
INSTALL(FILES ${xcomIdlFiles} DESTINATION share/xcom/idl/xcom)

FILE(GLOB xcomMetadataIdlFiles idl/xcom/metadata/*.idl)
INSTALL(FILES ${xcomMetadataIdlFiles} DESTINATION share/xcom/idl/xcom/metadata)
