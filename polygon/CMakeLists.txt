include_directories(testlib)
set(PROBLEMS 
absecutive
unnamed-easy
unnamed-hard
bookcase-easy
bookcase-hard
inc-match-2
tarzan
)
foreach(problem ${PROBLEMS})
  add_executable(polygon_${problem} ${problem}/main.cc)
endforeach(problem)
