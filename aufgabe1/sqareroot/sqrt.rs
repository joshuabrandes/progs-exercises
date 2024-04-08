fn main() {
    loop {
        println!("Please enter a number to find the square root of (exit to exit): ");
        let mut input = String::new();
        std::io::stdin().read_line(&mut input).unwrap();
        let input = input.trim();
        if input == "exit" {
            return;
        }
        let input: f64 = match input.parse() {
            Ok(num) => num,
            Err(_) => {
                println!("Invalid input");
                continue;
            }
        };

        newton_sqrt(input);
    }
}

fn newton_sqrt(num: f64) {
    let mut guess = num / 2.0;
    let mut prev_guess = 0.0;
    let mut i = 0;
    while guess != prev_guess {
        prev_guess = guess;
        guess = (guess + num / guess) / 2.0;
        i += 1;
    }
    println!("The square root of {} is {} (found in {} iterations)", num, guess, i);
}