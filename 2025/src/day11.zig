const std = @import("std");
const lib = @import("lib.zig");

pub fn solve(input: []const u8) struct { []u8, []u8 } {
    return solve_impl(input) catch .{ @constCast("error"), @constCast("error") };
}

fn all_paths(paths: *std.hash_map.AutoHashMap([3]u8, [][3]u8), node: [3]u8) i64 {
    if (std.mem.eql(u8, &node, @constCast("out"))) {
        return 1;
    }
    var res: i64 = 0;
    for (paths.get(node).?) |child| {
        res += all_paths(paths, child);
    }
    return res;
}

const State = struct { count: i64, dac: bool, fft: bool };

fn combine(a: State, b: State) State {
    if (a.dac == b.dac and a.fft == b.fft) {
        return .{ .count = a.count + b.count, .dac = a.dac, .fft = a.fft };
    } else {
        const sa: u8 = if (a.dac and a.fft) 2 else if (a.dac or a.fft) 1 else 0;
        const sb: u8 = if (b.dac and b.fft) 2 else if (b.dac or b.fft) 1 else 0;
        if (sa > sb) {
            return a;
        } else {
            return b;
        }
    }
}

fn solve_impl(input: []const u8) !struct { []u8, []u8 } {
    var ans1: i64 = 0;
    var ans2: i64 = 0;
    var it = lib.lines(input);
    var paths: std.hash_map.AutoHashMap([3]u8, [][3]u8) = .init(lib.a);
    while (it.next()) |line| {
        var it2 = lib.splitAny(line, ": ");
        var children: std.ArrayList([3]u8) = .empty;
        const parent: []const u8 = it2.next().?;
        _ = it2.next();
        while (it2.next()) |child| {
            try children.append(lib.a, child[0..3].*);
        }
        try paths.put(parent[0..3].*, children.items);
    }

    ans1 = all_paths(&paths, @constCast("you").*);

    var visited = std.AutoHashMap([3]u8, State).init(lib.a);
    try visited.put(@constCast("svr").*, .{ .count = 1, .dac = false, .fft = false });
    defer visited.deinit();
    var toVisit: std.ArrayList([3]u8) = .empty;
    defer toVisit.deinit(lib.a);
    var newToVisit: std.ArrayList([3]u8) = .empty;
    defer newToVisit.deinit(lib.a);
    try toVisit.append(lib.a, @constCast("svr").*);
    var steps: i64 = 0;
    while (toVisit.items.len > 0) : (steps += 1) {
        for (toVisit.items) |node| {
            if (std.mem.eql(u8, &node, @constCast("out"))) {
                continue;
            }
            if (std.mem.eql(u8, &node, @constCast("fft"))) {
                var old = visited.get(node).?;
                old.fft = true;
                try visited.put(node, old);
            }
            if (std.mem.eql(u8, &node, @constCast("dac"))) {
                var old = visited.get(node).?;
                old.dac = true;
                try visited.put(node, old);
            }

            for (paths.get(node).?) |child| {
                if (!visited.contains(child)) {
                    try visited.put(child, visited.get(node).?);
                    try newToVisit.append(lib.a, child);
                } else {
                    const a = visited.get(node).?;
                    const b = visited.get(child).?;
                    try visited.put(child, combine(a, b));

                    var shouldInsert = true;
                    for (newToVisit.items) |new| {
                        if (std.mem.eql(u8, &child, &new)) {
                            shouldInsert = false;
                            break;
                        }
                    }
                    if (shouldInsert) {
                        try newToVisit.append(lib.a, child);
                    }
                }
            }
        }
        std.mem.swap(std.ArrayList([3]u8), &toVisit, &newToVisit);
        newToVisit.shrinkRetainingCapacity(0);
    }

    ans2 = visited.get(@constCast("out").*).?.count;

    // 46366925751047616 high

    std.debug.print("{}\n", .{visited.get(@constCast("out").*).?});

    return .{ try lib.intToString(ans1), try lib.intToString(ans2) };
}
