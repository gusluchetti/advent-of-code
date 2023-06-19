use advent_of_code_2015::utils::{Method, parse_input};

const INPUT_PATH: &str = "src/inputs/d02.txt";

struct Size {
    length: u8,
    width: u8,
    height: u8
}

fn main() {
    task1();
    task2();
}

fn task1() -> () {
    let input = parse_input(INPUT_PATH, Method::Other('x'));
    let input: Vec<String> = input.ok().unwrap();
}

fn task2() -> () {

}
