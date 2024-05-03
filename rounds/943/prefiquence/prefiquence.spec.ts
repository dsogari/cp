import { describe, expect, it } from "vitest";
import { prefiquence } from "./prefiquence";

describe("prefiquence", () => {
  it("should pass", () => {
    expect(prefiquence('10011', '1110')).toEqual(2);
  });
});
