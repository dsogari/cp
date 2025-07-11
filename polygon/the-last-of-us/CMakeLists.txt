get_filename_component(DIR ${CMAKE_CURRENT_SOURCE_DIR} NAME)
foreach(file main ok1 ok2 mle tle wa generator validator)
  add_executable(polygon_${DIR}_${file} ${file}.cc)
endforeach(file)
