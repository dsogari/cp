get_filename_component(DIR ${CMAKE_CURRENT_SOURCE_DIR} NAME)
foreach(file main generator interactor validator)
  add_executable(polygon_${DIR}_${file} ${file}.cc)
endforeach(file)
