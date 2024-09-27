set(PROBLEMS 
1700
)
foreach(problem ${PROBLEMS})
  add_executable(cses_${problem} ${problem}/main.cc)
endforeach(problem)
