get_filename_component(DIR ${CMAKE_CURRENT_SOURCE_DIR} NAME)
foreach(problem a b c d e f g)
  add_executable(codeforces_${DIR}_${problem} ${problem}/main.cc)
endforeach(problem)

add_executable(codeforces_${DIR}_d_alt1 d/main_alt1.cc)
add_executable(codeforces_${DIR}_d_alt2 d/main_alt2.cc)