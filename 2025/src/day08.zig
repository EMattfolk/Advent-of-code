const std = @import("std");
const lib = @import("lib.zig");

pub fn solve(input: []const u8) struct { []u8, []u8 } {
    return solve_impl(input) catch .{ @constCast("error"), @constCast("error") };
}

const Point = struct { x: i64, y: i64, z: i64 };
const Pair = struct { a: Point, b: Point };

fn dstsq(pair: Pair) i64 {
    const x = (pair.a.x - pair.b.x);
    const y = (pair.a.y - pair.b.y);
    const z = (pair.a.z - pair.b.z);
    return x * x + y * y + z * z;
}

fn lt(_: u8, lhs: Pair, rhs: Pair) bool {
    return dstsq(lhs) < dstsq(rhs);
}

fn solve_impl(input: []const u8) !struct { []u8, []u8 } {
    var ans1: i64 = 0;
    var ans2: i64 = 0;
    var values: std.ArrayList(Point) = .empty;
    {
        var it = lib.splitAny(input, "\n,");
        while (it.next()) |v1| {
            const v2 = it.next().?;
            const v3 = it.next().?;
            try values.append(lib.a, .{ .x = try std.fmt.parseInt(i64, v1, 10), .y = try std.fmt.parseInt(i64, v2, 10), .z = try std.fmt.parseInt(i64, v3, 10) });
        }
    }
    var pairs: std.ArrayList(Pair) = .empty;
    var circuits: std.hash_map.AutoHashMap(Point, usize) = .init(lib.a);
    var mapping: std.hash_map.AutoHashMap(usize, usize) = .init(lib.a);
    for (0..values.items.len) |i| {
        try circuits.put(values.items[i], i);
        for (i + 1..values.items.len) |j| {
            try pairs.append(lib.a, .{ .a = values.items[i], .b = values.items[j] });
        }
    }
    std.mem.sortUnstable(Pair, pairs.items, @as(u8, 0), lt);

    var connections: i64 = 0;

    for (pairs.items[0..1000]) |pair| {
        var a = circuits.get(pair.a).?;
        while (mapping.get(a)) |newA| {
            a = newA;
        }
        var b = circuits.get(pair.b).?;
        while (mapping.get(b)) |newB| {
            b = newB;
        }
        if (a == b) continue;

        try circuits.put(pair.b, a);
        try mapping.put(b, a);
        connections += 1;
    }

    var sizes: std.hash_map.AutoHashMap(usize, usize) = .init(lib.a);
    {
        var it = circuits.valueIterator();
        while (it.next()) |circuit| {
            var c = circuit.*;
            while (mapping.get(c)) |newC| {
                c = newC;
            }
            if (sizes.get(c)) |v| {
                // std.debug.print("{} {}\n", .{ c, v + 1 });
                try sizes.put(c, v + 1);
            } else {
                try sizes.put(c, 1);
            }
        }
    }
    var sizeValues: std.ArrayList(usize) = .empty;
    var it = sizes.valueIterator();
    while (it.next()) |size| {
        try sizeValues.append(lib.a, size.*);
    }

    std.mem.sortUnstable(usize, sizeValues.items, {}, std.sort.desc(usize));

    ans1 = @as(i64, @intCast(sizeValues.items[0] * sizeValues.items[1] * sizeValues.items[2]));

    for (pairs.items[1000..]) |pair| {
        var a = circuits.get(pair.a).?;
        while (mapping.get(a)) |newA| {
            a = newA;
        }
        var b = circuits.get(pair.b).?;
        while (mapping.get(b)) |newB| {
            b = newB;
        }
        if (a == b) continue;

        try circuits.put(pair.b, a);
        try mapping.put(b, a);
        connections += 1;

        if (connections == 999) {
            ans2 = pair.a.x * pair.b.x;
            break;
        }
    }

    return .{ try lib.intToString(ans1), try lib.intToString(ans2) };
}
