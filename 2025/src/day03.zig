const std = @import("std");
const lib = @import("lib.zig");

fn joltage(line: []const u8, res: u64, toGo: usize) u64 {
    if (toGo == 0) {
        return res;
    }
    var i: usize = 0;
    var maxc = line[0];
    var maxi: usize = 0;
    for (line[0 .. line.len - toGo + 1]) |c| {
        if (c > maxc) {
            maxc = c;
            maxi = i;
        }
        i += 1;
    }
    return joltage(line[maxi + 1 ..], res * 10 + @as(u64, maxc - '0'), toGo - 1);
}

pub fn solve(input: []const u8) struct { []u8, []u8 } {
    return solve_impl(input) catch .{ @constCast("error"), @constCast("error") };
}

fn solve_impl(input: []const u8) !struct { []u8, []u8 } {
    var ans1: u64 = 0;
    var ans2: u64 = 0;
    var parsed = lib.lines(input);
    while (parsed.next()) |line| {
        ans1 += joltage(line, 0, 2);
        ans2 += joltage(line, 0, 12);
    }
    return .{ try lib.intToString(@intCast(ans1)), try lib.intToString(@intCast(ans2)) };
}
