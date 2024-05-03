export function prefiquence(a: string, b: string): number {
  let k = 0;
  for (let j = 0; k < a.length && j < b.length; ++j) {
    if (a[k] == b[j]) {
      ++k;
    }
  }
  return k;
}
