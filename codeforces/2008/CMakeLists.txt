get_filename_component(DIR ${CMAKE_CURRENT_SOURCE_DIR} NAME)
foreach(problem a b c d e f g h)
  add_executable(codeforces_${DIR}_${problem} ${problem}/main.cc)
endforeach(problem)
