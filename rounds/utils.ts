import { readFileSync } from "fs";

export interface TestCase<T> {
  run(): T;
}

export function run<T>(
  creator: new (lines: Array<string>) => TestCase<T>,
  output: (val: T) => void,
  path: number | string = 0
) {
  const lines = readFileSync(path).toString().split("\n");
  for (let count = Number(lines.shift()); count-- && lines.length; ) {
    output(new creator(lines).run());
  }
}
