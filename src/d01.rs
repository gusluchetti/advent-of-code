const INPUT_PATH: &str = "src/inputs/d01.txt";

fn main() {
    let input = std::fs::read_to_string(INPUT_PATH).expect("should have input");
    task1(&input);
    task2(&input);
}

fn task1(input: &String) {
    let mut counter = 0;
    for inst in input.chars() {
        match inst {
            '(' => counter += 1,
            ')' => counter -= 1,
            _ => (),
        }
    }
    println!("final floor: {}", counter);
}

fn task2(input: &String) {
    let mut counter = 0;
    for (i, inst) in input.chars().enumerate() {
        match inst {
            '(' => counter += 1,
            ')' => counter -= 1,
            _ => (),
        }

        if counter == -1 {
            println!("got in basement at {} instruction", i + 1);
            break;
        }
    }
}
