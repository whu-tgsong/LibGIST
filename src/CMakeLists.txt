set(SRC_LIST
  gist.cpp
  libgist.cpp
  standalone_image.cpp
  main.cpp  
)
set(HEADER_LIST
  ${INCLUDE_DIR}/gist.h
  ${INCLUDE_DIR}/libgist.h
  ${INCLUDE_DIR}/standalone_image.h
)

add_executable(LibGIST ${SRC_LIST} ${HEADER_LIST})
target_link_libraries(LibGIST ${FFTWF_LIB} ${OpenCV_LIBS})