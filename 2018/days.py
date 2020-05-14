for i in range(1, 26):
    print("Day {:>2}".format(i))
    try:
        day = __import__("day{:02}".format(i))

        if "both" in dir(day):
            day.both()
        else:
            day.first()
            day.second()
        print(flush=True)
    except Exception as e:
        print("Failed to run day {}!".format(i))
