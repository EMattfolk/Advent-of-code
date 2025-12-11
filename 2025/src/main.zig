const std = @import("std");
const lib = @import("lib.zig");

const day01 = @import("day01.zig");
const day02 = @import("day02.zig");
const day03 = @import("day03.zig");
const day04 = @import("day04.zig");
const day05 = @import("day05.zig");

pub fn main() !void {
    var buf: []const u8 = "";
    var ans1: []const u8 = "";
    var ans2: []const u8 = "";
    buf = try lib.readFile("input/day01.txt");
    ans1, ans2 = try day01.solve(buf);
    std.debug.print("Day  1: {s}, {s}\n", .{ ans1, ans2 });

    buf = try lib.readFile("input/day02.txt");
    ans1, ans2 = try day02.solve(buf);
    std.debug.print("Day  2: {s}, {s}\n", .{ ans1, ans2 });

    buf = try lib.readFile("input/day03.txt");
    ans1, ans2 = try day03.solve(buf);
    std.debug.print("Day  3: {s}, {s}\n", .{ ans1, ans2 });

    buf = try lib.readFile("input/day04.txt");
    ans1, ans2 = try day04.solve(buf);
    std.debug.print("Day  4: {s}, {s}\n", .{ ans1, ans2 });

    buf = try lib.readFile("input/day05.txt");
    ans1, ans2 = try day05.solve(buf);
    std.debug.print("Day  5: {s}, {s}\n", .{ ans1, ans2 });
}
