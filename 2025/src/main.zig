const std = @import("std");
const lib = @import("lib.zig");

const day01 = @import("day01.zig");
const day02 = @import("day02.zig");
const day03 = @import("day03.zig");
const day04 = @import("day04.zig");
const day05 = @import("day05.zig");
const day06 = @import("day06.zig");

var res: [12]struct { []const u8, []const u8 } = undefined;

fn runDay(day: usize, f: anytype, input: []const u8) !void {
    res[day - 1] = try f(input);
}

pub fn main() !void {
    var buf: []const u8 = "";

    buf = try lib.readFile("input/day01.txt");
    var t1 = try std.Thread.spawn(.{}, runDay, .{ 1, day01.solve, buf });
    buf = try lib.readFile("input/day02.txt");
    var t2 = try std.Thread.spawn(.{}, runDay, .{ 2, day02.solve, buf });
    buf = try lib.readFile("input/day03.txt");
    var t3 = try std.Thread.spawn(.{}, runDay, .{ 3, day03.solve, buf });
    buf = try lib.readFile("input/day04.txt");
    var t4 = try std.Thread.spawn(.{}, runDay, .{ 4, day04.solve, buf });
    buf = try lib.readFile("input/day05.txt");
    var t5 = try std.Thread.spawn(.{}, runDay, .{ 5, day05.solve, buf });
    buf = try lib.readFile("input/day06.txt");
    var t6 = try std.Thread.spawn(.{}, runDay, .{ 6, day06.solve, buf });

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();

    std.debug.print("Day  1: {s}, {s}\n", res[1 - 1]);
    std.debug.print("Day  2: {s}, {s}\n", res[2 - 1]);
    std.debug.print("Day  3: {s}, {s}\n", res[3 - 1]);
    std.debug.print("Day  4: {s}, {s}\n", res[4 - 1]);
    std.debug.print("Day  5: {s}, {s}\n", res[5 - 1]);
    std.debug.print("Day  6: {s}, {s}\n", res[6 - 1]);
}
