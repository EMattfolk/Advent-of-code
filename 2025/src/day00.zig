const std = @import("std");
const lib = @import("lib.zig");

pub fn solve(input: []const u8) struct { []u8, []u8 } {
    return solve_impl(input) catch .{ @constCast("error"), @constCast("error") };
}

fn solve_impl(input: []const u8) !struct { []u8, []u8 } {
    var ans1: i64 = 0;
    var ans2: i64 = 0;
    return .{ try lib.intToString(ans1), try lib.intToString(ans2) };
}
