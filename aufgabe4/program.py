def exercise1():
    arr = []

    for i in range(10):
        j = 0

        def func():
            nonlocal j
            j += 1
            print(j)

        arr.append(func)
        
    for a in arr:
        a()


# main function
if __name__ == "__main__":
    exercise1()
