const std = @import("std");
const lib = @import("lib.zig");

pub fn solve(input: []const u8) struct { []u8, []u8 } {
    return solve_impl(input) catch .{ @constCast("error"), @constCast("error") };
}

fn solve_impl(input: []const u8) !struct { []u8, []u8 } {
    // std.debug.print("{s}", .{input});
    var ans1: i64 = 0;
    var ans2: i64 = 0;
    var sec = lib.sections(input);
    const rangesInput = sec.next().?;
    const valuesInput = sec.next().?;
    var rangesIt = lib.splitAny(rangesInput, "\n-");
    var ranges: std.ArrayList(struct { start: u64, end: u64 }) = .empty;
    while (rangesIt.next()) |start| {
        const end = rangesIt.next().?;
        try ranges.append(lib.a, .{ .start = try std.fmt.parseInt(u64, start, 10), .end = try std.fmt.parseInt(u64, end, 10) });
    }

    var values = lib.lines(valuesInput);
    while (values.next()) |v| {
        const value = try std.fmt.parseInt(u64, v, 10);
        var fresh = false;
        for (ranges.items) |r| {
            if (r.start <= value and value <= r.end) {
                fresh = true;
                break;
            }
        }
        if (fresh) {
            ans1 += 1;
        }
    }

    var i: usize = 0;
    while (i < ranges.items.len) : (i += 1) {
        var j: usize = i + 1;
        while (j < ranges.items.len) : (j += 1) {
            const m = ranges.items[i];
            const n = ranges.items[j];
            const a = @min(m.start, n.start);
            const b = @min(m.end, n.end);
            const c = @max(m.start, n.start);
            const d = @max(m.end, n.end);
            if (b >= c) {
                ranges.items[i] = .{ .start = a, .end = c };
                ranges.items[j] = .{ .start = c + 1, .end = d };
            } else {
                ranges.items[i] = .{ .start = a, .end = b };
                ranges.items[j] = .{ .start = c, .end = d };
            }
        }
    }

    for (ranges.items) |r| {
        ans2 += @as(i64, @intCast(r.end)) - @as(i64, @intCast(r.start)) + 1;
    }

    return .{ try lib.intToString(ans1), try lib.intToString(ans2) };
}
