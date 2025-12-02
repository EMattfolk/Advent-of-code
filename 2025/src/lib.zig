const std = @import("std");

pub fn readFile(fileName: []const u8) ![]u8 {
    const file = try std.fs.cwd().openFile(fileName, .{});
    const size = (try file.stat()).size;
    const buf = try file.readToEndAlloc(std.heap.page_allocator, size);
    return buf;
}

pub fn intToString(i: i64) ![]u8 {
    return try std.fmt.allocPrint(std.heap.page_allocator, "{}", .{i});
}
