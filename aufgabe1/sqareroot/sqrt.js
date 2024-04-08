// calculate square root of a number using Newton's method

function newton_sqrt(number) {
    // initial guess
    let guess = number / 2;
    let newGuess = (guess + number / guess) / 2;
    while (Math.abs(newGuess - guess) > 0.0001) {
        guess = newGuess;
        newGuess = (guess + number / guess) / 2;
    }
    return newGuess;
}

// run the function reading input from the command line
let args = process.argv.slice(2);
let numbers = args.map(Number);

numbers.forEach(number => {
    console.log(`Square root of ${number} is ${newton_sqrt(number)}`);
});