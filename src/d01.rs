use advent_of_code_2015::utils::{parse_input, Method};

const INPUT_PATH: &str = "src/inputs/d01.txt";

fn main() {
    task1();
    task2();
}

fn task1() -> () {
    let input = parse_input(INPUT_PATH, Method::OneString);

    let mut counter = 0;
    for inst in input[0].chars() {
        if inst == '(' {
            counter = counter + 1;
        } else if inst == ')' {
            counter = counter - 1;
        }
    }
    println!("final floor: {}", counter);
}

fn task2() -> () {
    let input = parse_input(INPUT_PATH, Method::OneString);

    let mut counter = 0;
    for (i, inst) in input[0].chars().enumerate() {
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
