set(PROBLEMS
982_E
bookcase
mos
pairsum
palindrobabilty
segtree
)
foreach(problem ${PROBLEMS})
  add_executable(playground_${problem} ${problem}/main.cc)
endforeach(problem)
