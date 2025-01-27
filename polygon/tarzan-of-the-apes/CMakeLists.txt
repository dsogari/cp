get_filename_component(DIR ${CMAKE_CURRENT_SOURCE_DIR} NAME)
foreach(file main mle checker generator validator)
  add_executable(polygon_${DIR}_${file} ${file}.cc)
endforeach(file)
