use std::fs;

const INPUT_PATH: &str = "src/inputs/d08.txt";

fn main() {
    // three methods of string escape
    // \\, single backslash
    // \", single double quotes
    // \x27 (two hexadecimal characters), single character
    let file = fs::read_to_string(INPUT_PATH).expect("file should exist");
    let lines: Vec<&str> = file.lines().collect();

    for line in lines {
        let chars: Vec<char> = line.chars().collect();
        let len = chars.len();
        let literal = chars[1..len-1].into_iter().collect::<String>();
        let str = literal.as_bytes();
        let test = "qludrkkvljljd\\xvdeum\x4e".as_bytes();
        
        println!("\n{str:?} | {test:?}");
        println!("{chars:?}");
        println!("char length: {len}");
    }

    task1();
    task2();
}

fn task1() -> () {}

fn task2() -> () {}
