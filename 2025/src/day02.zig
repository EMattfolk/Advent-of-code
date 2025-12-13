const std = @import("std");
const lib = @import("lib.zig");

pub fn solve(input: []const u8) struct { []u8, []u8 } {
    return solve_impl(input) catch .{ @constCast("error"), @constCast("error") };
}

fn solve_impl(input: []const u8) !struct { []u8, []u8 } {
    var ans1: i64 = 0;
    var ans2: i64 = 0;
    var l: std.ArrayList([]const u8) = .empty;
    defer l.deinit(lib.a);
    var it = lib.splitAny(input, ",-");
    while (it.next()) |v| {
        try l.append(lib.a, v);
    }
    for (0..l.items.len / 2) |i| {
        const start: usize = try std.fmt.parseInt(usize, l.items[i * 2], 10);
        const end: usize = try std.fmt.parseInt(usize, l.items[i * 2 + 1], 10);
        for (start..(end + 1)) |j| {
            var buf: [16]u8 = undefined;
            const s = try std.fmt.bufPrint(&buf, "{}", .{j});

            for (1..s.len / 2 + 1) |k| {
                if (s.len % k != 0) {
                    continue;
                }
                var invalid = true;
                for (1..s.len / k) |m| {
                    if (!std.mem.eql(u8, s[0..k], s[k * m .. k * (m + 1)])) {
                        invalid = false;
                        break;
                    }
                }
                if (invalid) {
                    ans2 += @intCast(j);
                    break;
                }
            }

            if (s.len % 2 == 1) {
                continue;
            }
            const invalid = std.mem.eql(u8, s[0 .. s.len / 2], s[s.len / 2 .. s.len]);
            ans1 += if (invalid) @intCast(j) else 0;

            // std.debug.print("{s}\n", .{l.items[i * 2]});
        }
    }
    return .{ try lib.intToString(ans1), try lib.intToString(ans2) };
}
