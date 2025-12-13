const std = @import("std");
const lib = @import("lib.zig");

const adj = [_](struct { x: i8, y: i8 }){ .{ .x = -1, .y = -1 }, .{ .x = -1, .y = 0 }, .{ .x = -1, .y = 1 }, .{ .x = 0, .y = -1 }, .{ .x = 0, .y = 1 }, .{ .x = 1, .y = -1 }, .{ .x = 1, .y = 0 }, .{ .x = 1, .y = 1 } };

pub fn solve(input: []const u8) struct { []u8, []u8 } {
    return solve_impl(input) catch .{ @constCast("error"), @constCast("error") };
}

fn solve_impl(input: []const u8) !struct { []u8, []u8 } {
    var ans1: i64 = 0;
    var ans2: i64 = 0;
    const grid = try lib.grid(input);

    // std.debug.print("{}\n", .{grid});

    var it = grid.iterator();

    while (it.next()) |entry| {
        if (entry.value_ptr.* != '@') {
            continue;
        }
        var count: u8 = 0;
        for (adj) |offset| {
            const neigh: lib.Point = .{ .x = entry.key_ptr.x + offset.x, .y = entry.key_ptr.y + offset.y };
            if (grid.get(neigh) == '@') {
                count += 1;
            }
        }
        if (count < 4) {
            ans1 += 1;
            // std.debug.print("{}: {}\n", .{ entry.key_ptr.*, entry.value_ptr.* });
        }
    }

    var changed = true;
    while (changed) {
        changed = false;
        it = grid.iterator();
        while (it.next()) |entry| {
            if (entry.value_ptr.* != '@') {
                continue;
            }
            var count: u8 = 0;
            for (adj) |offset| {
                const neigh: lib.Point = .{ .x = entry.key_ptr.x + offset.x, .y = entry.key_ptr.y + offset.y };
                if (grid.get(neigh) == '@') {
                    count += 1;
                }
            }
            if (count < 4) {
                ans2 += 1;
                entry.value_ptr.* = '.';
                changed = true;
                // std.debug.print("{}: {}\n", .{ entry.key_ptr.*, entry.value_ptr.* });
            }
        }
    }

    return .{ try lib.intToString(ans1), try lib.intToString(ans2) };
}
