const std = @import("std");
const lib = @import("lib.zig");

var res: [12]struct { []const u8, []const u8 } = undefined;
var timing: [12]u64 = undefined;
var threads: [12]std.Thread = undefined;

// zig fmt: off
const fns = [_](*const fn ([]const u8) struct { []u8, []u8 })
    { @import("day01.zig").solve
    , @import("day02.zig").solve
    , @import("day03.zig").solve
    , @import("day04.zig").solve
    , @import("day05.zig").solve
    , @import("day06.zig").solve
    , @import("day07.zig").solve
    , @import("day08.zig").solve
    , @import("day09.zig").solve
    , @import("day10.zig").solve
    };
// zig fmt: on

fn runDay(day: usize, input: []const u8) !void {
    const st = try std.time.Instant.now();
    res[day - 1] = fns[day - 1](input);
    const end = try std.time.Instant.now();
    timing[day - 1] = end.since(st);
}

pub fn main() !void {
    const days: usize = fns.len;

    var fileName: []u8 = @constCast("input/day00.txt");

    for (1..days + 1) |day| {
        fileName[9] = '0' + (@as(u8, @intCast(day)) / 10);
        fileName[10] = '0' + @as(u8, @intCast(day)) % 10;
        const buf = try lib.readFile(fileName);
        threads[day - 1] = try std.Thread.spawn(.{}, runDay, .{ day, buf });
    }

    for (1..days + 1) |day| {
        threads[day - 1].join();
        const d1 = @as(u8, @intCast(day)) / 10;
        const d2 = @as(u8, @intCast(day)) % 10;
        const ans1, const ans2 = res[day - 1];
        std.debug.print("Day {c}{}: {} ms - {s}, {s}\n", .{ if (d1 == 0) ' ' else '0' + d1, d2, timing[day - 1] / 1000_000, ans1, ans2 });
    }
}
