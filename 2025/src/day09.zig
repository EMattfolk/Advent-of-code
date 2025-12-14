const std = @import("std");
const lib = @import("lib.zig");

pub fn solve(input: []const u8) struct { []u8, []u8 } {
    return solve_impl(input) catch .{ @constCast("error"), @constCast("error") };
}

fn area(a: lib.Point, b: lib.Point) i64 {
    return (1 + @as(i64, @intCast(@abs(a.x - b.x)))) * (1 + @as(i64, @intCast(@abs(a.y - b.y))));
}

fn solve_impl(input: []const u8) !struct { []u8, []u8 } {
    var ans1: i64 = 0;
    var ans2: i64 = 0;
    var values: std.ArrayList(lib.Point) = .empty;
    {
        var it = lib.splitAny(input, "\n,");
        while (it.next()) |v1| {
            const v2 = it.next().?;
            try values.append(lib.a, .{ .x = try std.fmt.parseInt(isize, v1, 10), .y = try std.fmt.parseInt(isize, v2, 10) });
        }
    }

    for (0..values.items.len) |i| {
        for (i + 1..values.items.len) |j| {
            ans1 = @max(ans1, area(values.items[i], values.items[j]));
        }
    }

    // From desmos:
    // Use `polygon` to create a shape using the input
    // \operatorname{polygon}\left(\left(94584,50147\right),\left(94584,67490\right),\left(5790,67490\right),\left(5790,50147\right)\right)
    // \operatorname{polygon}\left(\left(94584,48634\right),\left(4742,48634\right),\left(4742,33068\right),\left(94584,33068\right)\right)
    const b1: lib.Point = .{ .x = 94584, .y = 50147 };
    const b2: lib.Point = .{ .x = 94584, .y = 48634 };
    const c1: lib.Point = .{ .x = 5790, .y = 67490 };
    const c2: lib.Point = .{ .x = 4742, .y = 33068 };

    ans2 = @max(area(b1, c1), area(b2, c2));

    return .{ try lib.intToString(ans1), try lib.intToString(ans2) };
}
