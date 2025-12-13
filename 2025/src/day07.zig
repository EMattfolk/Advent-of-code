const std = @import("std");
const lib = @import("lib.zig");

// low 5224

pub fn solve(input: []const u8) !struct { []u8, []u8 } {
    var ans1: i64 = 0;
    var ans2: i64 = 0;
    var lines: std.ArrayList([]const u8) = .empty;
    var counts: std.ArrayList([]i64) = .empty;
    var it = lib.lines(input);
    while (it.next()) |line| {
        try lines.append(lib.a, line);
        try counts.append(lib.a, try lib.a.alloc(i64, line.len));
        var i: usize = 0;
        for (line) |c| {
            if (c == 'S') {
                counts.items[counts.items.len - 1][i] = 1;
            } else {
                counts.items[counts.items.len - 1][i] = 0;
            }
            i += 1;
        }
    }
    var y: usize = 0;
    for (lines.items) |l| {
        if (y == 0) {
            y += 1;
            continue;
        }
        var x: usize = 0;
        for (l) |c| {
            if (c == '.') {
                // std.debug.print("{}\n", .{counts.items[y][x]});
                // std.debug.print("{}\n", .{counts.items[y - 1][x]});
                counts.items[y][x] += counts.items[y - 1][x];
            } else if (c == '^') {
                if (counts.items[y - 1][x] > 0) {
                    ans1 += 1;
                    counts.items[y][x - 1] += counts.items[y - 1][x];
                    counts.items[y][x + 1] += counts.items[y - 1][x];
                }
            }
            x += 1;
        }
        y += 1;
    }

    for (counts.items[counts.items.len - 1]) |c| {
        ans2 += c;
    }

    return .{ try lib.intToString(ans1), try lib.intToString(ans2) };
}
