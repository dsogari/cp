get_filename_component(DIR ${CMAKE_CURRENT_SOURCE_DIR} NAME)
foreach(problem a b c d e f g)
  add_executable(codeforces_${DIR}_${problem} ${problem}/main.cc)
endforeach(problem)

add_executable(codeforces_${DIR}_g_alt1 g/alt1.cc)
add_executable(codeforces_${DIR}_g_alt2 g/alt2.cc)
add_executable(codeforces_${DIR}_g_alt3 g/alt3.cc)