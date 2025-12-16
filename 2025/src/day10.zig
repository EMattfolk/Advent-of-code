const std = @import("std");
const lib = @import("lib.zig");

pub fn solve(input: []const u8) struct { []u8, []u8 } {
    return solve_impl(input) catch .{ @constCast("error"), @constCast("error") };
}

//     x
//     y
// 0 1        20
// 1 1      = 28
// 0 1        20
// 1 0         8
//
//   y = 20
// x+y = 28
//   y = 20
// x   = 8

//         x
//         y
//         z
//         w
// 1 1 1 1        63
//   1   1      = 34
// 1              18
//   1 1          31
fn solve_impl(input: []const u8) !struct { []u8, []u8 } {
    var ans1: i64 = 0;
    var lines: std.ArrayList(struct { lights: []const u8, buttons: [][]const u8, other: []const u8 }) = .empty;
    var it = lib.lines(input);
    while (it.next()) |line| {
        var it2 = lib.splitAny(line, "[] (){}");
        const lights = it2.next().?;
        var buttons: std.ArrayList([]const u8) = .empty;
        var other: []const u8 = undefined;
        while (it2.next()) |button| {
            if (it2.peek()) |_| {
                try buttons.append(lib.a, button);
            } else {
                other = button;
            }
        }
        try lines.append(lib.a, .{ .lights = lights, .buttons = buttons.items, .other = other });
    }

    for (lines.items) |line| {
        var visited = std.AutoHashMap([10]u8, void).init(lib.a);
        try visited.put(@constCast("..........").*, {});
        defer visited.deinit();
        var toVisit: std.ArrayList([10]u8) = .empty;
        defer toVisit.deinit(lib.a);
        var newToVisit: std.ArrayList([10]u8) = .empty;
        defer newToVisit.deinit(lib.a);
        try toVisit.append(lib.a, @constCast("..........").*);
        var steps: i64 = 0;
        lbl: while (toVisit.items.len > 0) : (steps += 1) {
            for (toVisit.items) |lights| {
                if (std.mem.eql(u8, lights[0..line.lights.len], line.lights)) {
                    break :lbl;
                }
                for (line.buttons) |button| {
                    var newLights: [10]u8 = lights;
                    var i: usize = 0;
                    while (i < button.len) : (i += 2) {
                        // std.debug.print("{s}\n", .{button});
                        const lightIndex: usize = button[i] - '0';
                        newLights[lightIndex] = if (newLights[lightIndex] == '.') '#' else '.';
                    }

                    if (!visited.contains(newLights)) {
                        try newToVisit.append(lib.a, newLights);
                        try visited.put(newLights, {});
                    }
                }
            }
            std.mem.swap(std.ArrayList([10]u8), &toVisit, &newToVisit);
            newToVisit.shrinkRetainingCapacity(0);
        }
        ans1 += steps;
    }

    const ans2 = (try std.process.Child.run(.{ .allocator = lib.a, .argv = &[_][]const u8{ "python", "src/day10.py" } })).stdout;

    return .{ try lib.intToString(ans1), ans2[0 .. ans2.len - 1] };
}
