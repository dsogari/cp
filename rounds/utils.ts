import { readFileSync } from "fs";

export interface TestCase {
  run(): unknown;
}

export type TestCaseCreator = new (lines: Array<string>) => TestCase;

export function run(creator: TestCaseCreator, path: number | string = 0) {
  const lines = readFileSync(path).toString().split("\n");
  for (let count = Number(lines.shift()); count-- && lines.length; ) {
    console.log(new creator(lines).run());
  }
}
