class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __add__(self, other):
        return Point(self.x + other.x, self.y + other.y)

    def __sub__(self, other):
        return self + (-other)

    def __neg__(self):
        return Point(-self.x, -self.y)

    def __str__(self):
        return str((self.x, self.y))

    def __iter__(self):
        yield self.x
        yield self.y

    def __eq__(self, other):
        return self.x == other.x and self.y == other.y

    def __hash__(self):
        return hash((self.x, self.y))

    def scale(self, by):
        return Point(self.x * by, self.y * by)

    def lengthsq(self):
        return self.x * self.x + self.y * self.y


if __name__ == "__main__":
    print(Point(0, 0))
    print(tuple(Point(0, 0)))
    print(-Point(1, 1))
    print(Point(2, 3) - Point(1, 1))
    print(Point(2, 3).scale(10))
    a = Point(1, 1)
    a += Point(5, 4)
    print(a)
    print(Point(3, 4).lengthsq())
    print(Point(1, 1).lengthsq())
