const std = @import("std");
const lib = @import("lib.zig");
const day01 = @import("day01.zig");

pub fn main() !void {
    const buf = try lib.readFile("input/day01.txt");
    const ans1, const ans2 = try day01.solve(buf);
    std.debug.print("{s}, {s}\n", .{ ans1, ans2 });
}
