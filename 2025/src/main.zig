const std = @import("std");

pub fn main() !void {
    const file = try std.fs.cwd().openFile("input/day01.txt", .{});
    const size = (try file.stat()).size;
    const buf = try file.readToEndAlloc(std.heap.page_allocator, size);
    var it = std.mem.splitScalar(u8, std.mem.trim(u8, buf, "\n"), '\n');
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
    std.debug.print("{}, {}\n", .{ pass1, pass2 });
}
