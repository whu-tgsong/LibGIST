set(SRC_LIST
  gist.cpp
  libgist.cpp
  standalone_image.cpp
  main.cpp  
)
set(HEADER_LIST
  ${PROJ_INCLUDE_DIR}/gist.h
  ${PROJ_INCLUDE_DIR}/libgist.h
  ${PROJ_INCLUDE_DIR}/standalone_image.h
)

add_executable(LibGIST ${SRC_LIST} ${HEADER_LIST})
target_link_libraries(LibGIST ${FFTWF_LIB} ${OpenCV_LIBS})