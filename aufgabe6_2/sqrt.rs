#![allow(non_snake_case)]

use std::io;
use std::io::Write;

enum  Opt {
    Result { result: f64 },
    Error { error: String }
}

fn sqrt_newton(x: f64) -> Opt {
    if x < 0.0 {
        return Opt::Error { error: "Die Wurzel aus einer negativen Zahl ist nicht definiert!".to_string() };
    }

    let mut y = 1.0;
    while (y * y - x).abs() > 0.0000001 {
        y = 0.5 * (y + x / y);
    }

    Opt::Result { result: y }
}

fn main() {
    let mut xStr = String::new();

    print!("Bitte geben Sie eine Zahl ein: ");
    io::stdout().flush().unwrap();
    io::stdin().read_line(&mut xStr).expect("Fehler beim lesen der Eingabe!");

    let x = xStr.trim().parse::<f64>().expect("Ich kann die Eingabe nicht zu einer Zahl konvertieren!");

    let result = sqrt_newton(x);

    match result {
        Opt::Result { result } => println!("Die Wurzel aus {} ist etwa {}", x, result),
        Opt::Error { error } => println!("{}", error)
    }
}
