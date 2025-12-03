const std = @import("std");
const lib = @import("lib.zig");

pub fn solve(input: []const u8) !struct { []u8, []u8 } {
    var it = lib.lines(input);
    var dial1: i32 = 50;
    var pass1: i32 = 0;
    var dial2: i32 = 50;
    var pass2: i32 = 0;
    while (it.next()) |line| {
        const dir: i32 = if (line[0] == 'R') 1 else -1;
        const v: i32 = try std.fmt.parseInt(i32, line[1..], 10);
        dial1 += dir * v;
        if (@mod(dial1, 100) == 0) {
            pass1 += 1;
        }

        for (0..@intCast(v)) |_| {
            dial2 += dir;
            if (@mod(dial2, 100) == 0) {
                pass2 += 1;
            }
        }
    }
    return .{ try lib.intToString(pass1), try lib.intToString(pass2) };
}
