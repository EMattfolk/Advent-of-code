const std = @import("std");
const lib = @import("lib.zig");

pub fn solve(input: []const u8) struct { []u8, []u8 } {
    return solve_impl(input) catch |err| blk: {
        std.debug.print("{}\n", .{err});
        break :blk .{ @constCast("error"), @constCast("error") };
    };
}

fn solve_impl(input: []const u8) !struct { []u8, []u8 } {
    var ans1: i64 = 0;
    var sections: std.ArrayList([]const u8) = .empty;
    {
        var it = lib.sections(input);
        while (it.next()) |section| {
            try sections.append(lib.a, section);
        }
    }

    var counts = [6]i64{ 0, 0, 0, 0, 0, 0 };
    for (0..sections.items.len - 1) |i| {
        for (sections.items[i]) |c| {
            if (c == '#') {
                counts[i] += 1;
            }
        }
    }

    // std.debug.print("{any}\n", .{counts});

    var no: i64 = 0;
    var unknown: i64 = 0;
    var yes: i64 = 0;

    var it = lib.lines(sections.items[sections.items.len - 1]);
    while (it.next()) |line| {
        var it2 = lib.splitAny(line, "x: ");
        const w = try std.fmt.parseInt(i64, it2.next().?, 10);
        const h = try std.fmt.parseInt(i64, it2.next().?, 10);
        _ = it2.next();
        var lower: i64 = 0;
        var upper: i64 = 0;
        for (0..6) |i| {
            const count = try std.fmt.parseInt(i64, it2.next().?, 10);
            lower += counts[i] * count;
            upper += 9 * count;
        }
        if (upper <= w * h) {
            yes += 1;
        } else if (lower <= w * h and w * h < upper) {
            unknown += 1;
        } else if (w * h < lower) {
            no += 1;
        } else {
            unreachable;
        }
    }

    ans1 = yes;

    return .{ try lib.intToString(ans1), "" };
}
