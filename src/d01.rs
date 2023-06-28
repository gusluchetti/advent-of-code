const INPUT_PATH: &str = "src/inputs/d01.txt";

fn main() {
    let input = std::fs::read_to_string(INPUT_PATH).expect("should have input");
    task1(&input);
    task2(&input);
}

fn task1(input: &String) {
    let mut counter = 0;
    for inst in input.chars() {
        if inst == '(' {
            counter = counter + 1;
        } else if inst == ')' {
            counter = counter - 1;
        }
    }
    println!("final floor: {}", counter);
}

fn task2(input: &String) {
    let mut counter = 0;
    for (i, inst) in input.chars().enumerate() {
        if inst == '(' {
            counter = counter + 1;
        } else if inst == ')' {
            counter = counter - 1;
        }

        if counter == -1 {
            println!("got in basement at {} instruction", i + 1);
            break;
        }
    }
}
