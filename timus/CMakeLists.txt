set(PROBLEMS 
2042
)
foreach(problem ${PROBLEMS})
  add_executable(timus_${problem} ${problem}/main.cc)
endforeach(problem)
