const INPUT_PATH: &str = "src/inputs/d09.txt";

fn main() {
    let input = std::fs::read_to_string(INPUT_PATH).expect("should have input");
    let lines = input.lines().collect::<Vec<&str>>();
    for line in &lines {
        println!("{line}");
    }

    task1(&input);
    task2(&input);
}

fn task1(input: &String) {}

fn task2(input: &String) {}
