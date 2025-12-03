const std = @import("std");
const lib = @import("lib.zig");
const day01 = @import("day01.zig");
const day02 = @import("day02.zig");

pub fn main() !void {
    var buf = try lib.readFile("input/day01.txt");
    var ans1, var ans2 = try day01.solve(buf);
    std.debug.print("Day  1: {s}, {s}\n", .{ ans1, ans2 });
    buf = try lib.readFile("input/day02.txt");
    ans1, ans2 = try day02.solve(buf);
    std.debug.print("Day  2: {s}, {s}\n", .{ ans1, ans2 });
}
