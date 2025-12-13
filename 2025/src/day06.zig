const std = @import("std");
const lib = @import("lib.zig");

pub fn solve(input: []const u8) !struct { []u8, []u8 } {
    var ans1: i64 = 0;
    var ans2: i64 = 0;
    var lines: std.ArrayList([]const i64) = .empty;
    var ops: std.ArrayList([]const u8) = .empty;
    var intlines: [4][]const u8 = .{ "", "", "", "" };
    var opsline: []const u8 = "";
    var it = lib.lines(input);
    var j: usize = 0;
    while (it.next()) |l| {
        if (l[0] != '*' and l[0] != '+') {
            var it2 = lib.splitAny(l, " ");
            var chars: std.ArrayList([]const u8) = .empty;
            while (it2.next()) |c| {
                if (c.len == 0) continue;
                try chars.append(lib.a, c);
            }
            const ints = try lib.a.alloc(i64, chars.items.len);
            var i: usize = 0;
            for (chars.items) |item| {
                // std.debug.print("{s}\n", .{item});
                ints[i] = try std.fmt.parseInt(i64, item, 10);
                i += 1;
            }
            try lines.append(lib.a, ints);
            intlines[j] = l;
        } else {
            var it2 = lib.splitAny(l, " ");
            while (it2.next()) |c| {
                if (c.len == 0) continue;
                try ops.append(lib.a, c);
            }
            opsline = l;
        }
        j += 1;
    }

    var i: usize = 0;
    while (i < lines.items[0].len) : (i += 1) {
        var v: i64 = if (ops.items[i][0] == '*') 1 else 0;
        for (lines.items) |l| {
            if (ops.items[i][0] == '*') {
                v *= l[i];
            } else {
                v += l[i];
            }
        }
        ans1 += v;
    }

    i = 0;
    while (i < opsline.len) {
        var w: usize = 1;
        while (i + w == opsline.len or (i + w < opsline.len and opsline[i + w] == ' ')) : (w += 1) {}
        w -= 1;

        var v: i64 = if (opsline[i] == '*') 1 else 0;

        var buf: [4]u8 = .{ ' ', ' ', ' ', ' ' };
        j = 0;
        while (j < w) : (j += 1) {
            var k: usize = 0;
            var l: usize = 0;
            while (k < intlines.len) : (k += 1) {
                if (intlines[k][i + j] != ' ') {
                    buf[l] = intlines[k][i + j];
                    l += 1;
                }
            }
            if (opsline[i] == '*') {
                v *= try std.fmt.parseInt(i64, buf[0..l], 10);
            } else {
                v += try std.fmt.parseInt(i64, buf[0..l], 10);
            }
        }

        // std.debug.print("{}\n", .{w});
        ans2 += v;
        i += w + 1;
    }

    return .{ try lib.intToString(ans1), try lib.intToString(ans2) };
}
