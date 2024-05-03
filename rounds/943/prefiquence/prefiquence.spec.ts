import { describe, expect, it } from "vitest";
import { prefiquence } from "./main";

describe("prefiquence", () => {
  it("case 1", () => {
    const input: Array<[string, string]> = [
      ["10011", "1110"],
      ["100", "110"],
      ["1", "111"],
      ["1011", "1111"],
      ["100", "11010"],
      ["100", "0"],
    ];
    const expected = [2, 2, 1, 1, 3, 0];
    expect(input.map((item) => prefiquence(...item))).toEqual(expected);
  });
});
