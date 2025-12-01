const std = @import("std");

const day1 = @embedFile("main.zig");

pub fn main() !void {
    std.debug.print("{s}\n", .{day1});
}
