const INPUT_PATH: &str = "src/inputs/d11.txt";

fn main() {
    let input = std::fs::read_to_string(INPUT_PATH).expect("should have input");
    task1(&input);
    task2(&input);
}

fn task1(input: &String) {
    println!("{}", input);
    let mut temp = 1;
}

fn task2(input: &String) {
    let mut temp = 1;
}
