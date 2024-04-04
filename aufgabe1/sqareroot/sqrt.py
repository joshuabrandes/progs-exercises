# calculate the square root of a number using the Newton-Raphson method

def sqrt(x):
    """
    Calculate the square root of a number using the Newton-Raphson method.

    Args:
        x: The number for which the square root is to be calculated.

    Returns:
        The square root of x.
    """
    # Initial guess for the square root
    z = x / 2.0
    # Keep getting a better estimate for the square root
    while abs(x - (z * z)) > 0.0001:
        z -= (z * z - x) / (2 * z)
    return z


# main program
if __name__ == "__main__":
    while True:
        num = input("Enter a number (or 'exit' to quit): ")
        if num.lower() == 'exit':
            break
        else:
            try:
                num = float(num)
                print("Square root of", num, "is", sqrt(num))
            except ValueError:
                print("Invalid input. Please enter a number.")
