use advent_of_code_2015::utils::{parse_input, Method};

const INPUT_PATH: &str = "src/inputs/d08.txt";

fn main() {
    // three methods of string escape
    // \\, single backslash
    // \", single double quotes
    // \x27 (two hexadecimal characters), single character
    let lines = parse_input(INPUT_PATH, Method::NewLine);
    for line in lines {
        let chars: Vec<char> = line.chars().collect();
        let len = chars.len();
        let literal = chars[1..len-1].into_iter().collect::<String>();
        let str = literal.as_str();

        println!("\n{str}");
        println!("{chars:?}");
    }

    task1();
    task2();
}

fn task1() -> () {}

fn task2() -> () {}
