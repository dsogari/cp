import { type TestCase, run } from "../../utils";
import { prefiquence } from "./prefiquence";

class Prefiquence implements TestCase<number> {
  private readonly a: string;
  private readonly b: string;

  constructor(lines: Array<string>) {
    const [x, y] = lines.shift()!.split(' ').map(Number);
    this.a = lines.shift()!.slice(0, x);
    this.b = lines.shift()!.slice(0, y);
  }

  run(): number {
    return prefiquence(this.a, this.b);
  }
}

run(Prefiquence, (val) => console.log(val));