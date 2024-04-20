const INPUT_PATH: &str = "src/inputs/d01.txt";

fn counting_stairs(input: &String, basement_reached: Option<bool>) -> i32 {
    let mut counter = 0;
    for (i, inst) in input.chars().enumerate() {
        match inst {
            '(' => counter += 1,
            ')' => counter -= 1,
            _ => (),
        }

        if counter == -1 && basement_reached == Some(true) {
            return (i + 1).try_into().unwrap();
        }
    }
    counter
}

fn task1(input: &String) -> i32 {
    counting_stairs(input, Some(false))
}

fn task2(input: &String) -> i32 {
    counting_stairs(input, Some(true))
}

fn main() {
    let input = std::fs::read_to_string(INPUT_PATH).expect("should have input");
    let p1 = task1(&input);
    println!("{}", p1);

    let p2 = task2(&input);
    println!("{}", p2);
}
