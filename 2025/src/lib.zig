const std = @import("std");

pub const a = std.heap.page_allocator;

pub fn readFile(fileName: []const u8) ![]const u8 {
    const file = try std.fs.cwd().openFile(fileName, .{});
    const size = (try file.stat()).size;
    const buf = try file.readToEndAlloc(a, size);
    return std.mem.trim(u8, buf, "\n");
}

pub fn intToString(i: i64) ![]u8 {
    return try std.fmt.allocPrint(a, "{}", .{i});
}

pub fn lines(input: []const u8) std.mem.SplitIterator(u8, .sequence) {
    return std.mem.splitSequence(u8, input, "\n");
}

pub fn splitAny(input: []const u8, delims: []const u8) std.mem.SplitIterator(u8, .any) {
    return std.mem.splitAny(u8, std.mem.trim(u8, input, delims), delims);
}
