import { type TestCase, run } from "../../utils";

export class Prefiquence implements TestCase {
  a: string;
  b: string;

  constructor(lines: Array<string>) {
    const [x, y] = lines.shift()!.split(' ').map(Number);
    this.a = lines.shift()!.slice(0, x);
    this.b = lines.shift()!.slice(0, y);
  }

  run(): number {
    return prefiquence(this.a, this.b);
  }
}

export function prefiquence(a: string, b: string): number {
  let k = 0;
  for (let j = 0; k < a.length && j < b.length; ++j) {
    if (a[k] == b[j]) {
      ++k;
    }
  }
  return k;
}

run(Prefiquence);