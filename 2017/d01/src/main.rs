use std::fs;

fn main() {
    let input: String = fs::read_to_string("input.txt").expect("input should exist");

    for c in input.chars() {
        println!("{c}");
    }
}
