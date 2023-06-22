use advent_of_code_2015::utils::{parse_input, Method};
use std::vec;

const INPUT_PATH: &str = "src/inputs/d06.txt";

fn main() {
    let lines: Vec<String> = parse_input(INPUT_PATH, Method::NewLine);
    let instructions = parse_instructions(lines);

    task1(&instructions);
    task2(&instructions);
}

#[derive(Debug)]
enum Action {
    TurnOn,
    TurnOff,
    Toggle,
}

#[derive(Debug)]
struct Instructions {
    action: Action,
    x_path: (u32, u32),
    y_path: (u32, u32),
}

impl Instructions {
    fn new(action: Action, x_path: (u32, u32), y_path: (u32, u32)) -> Self {
        Self {
            action,
            x_path,
            y_path,
        }
    }
}

fn parse_instructions(lines: Vec<String>) -> Vec<Instructions> {
    let mut instructions: Vec<Instructions> = Vec::new();
    for line in lines {
        let split: Vec<&str> = line.split_terminator(" ").collect();
        let mut action = Action::TurnOn;
        let mut x_path = (0, 0);
        let mut y_path = (0, 0);

        let first_set: Vec<&str>;
        let second_set: Vec<&str> = split.last().unwrap().split(",").collect();
        x_path.1 = second_set[0].parse().unwrap();
        y_path.1 = second_set[1].parse().unwrap();

        if split[0] == "toggle" {
            action = Action::Toggle;
            first_set = split[1].split(",").collect();
        } else {
            if split[1] == "off" {
                action = Action::TurnOff;
            }
            first_set = split[2].split(",").collect();
        }
        x_path.0 = first_set[0].parse().unwrap();
        y_path.0 = first_set[1].parse().unwrap();
        instructions.push(Instructions::new(action, x_path, y_path));
    }
    instructions
}

fn turn_lights_on(new_pattern: bool, instructions: &Vec<Instructions>, lights: &mut Vec<Vec<u32>>) -> (u32, u32) {
    for i in instructions {
        for y in i.y_path.0..=i.y_path.1 {
            for x in i.x_path.0..=i.x_path.1 {
                let y = y as usize;
                let x = x as usize;

                if new_pattern {
                    match i.action {
                        Action::TurnOn => {
                            lights[y][x] = lights[y][x] + 1;
                        }
                        Action::TurnOff => {
                            if lights[y][x] > 0 {
                                lights[y][x] = lights[y][x] - 1;
                            }
                        }
                        Action::Toggle => {
                            lights[y][x] = lights[y][x] + 2;
                        }
                    }
                } else {
                    match i.action {
                        Action::TurnOn => {
                            lights[y][x] = 1;
                        }
                        Action::TurnOff => {
                            lights[y][x] = 0;
                        }
                        Action::Toggle => {
                            if lights[y][x] == 0 {
                                lights[y][x] = 1;
                            } else {
                                lights[y][x] = 0;
                            }
                        }
                    }
                }
            }
        }
    }

    let mut counter = 0;
    let mut b_c = 0;
    for y in 0..=999 {
        for x in 0..=999 {
            let y = y as usize;
            let x = x as usize;
            b_c = b_c + lights[y][x];
            if lights[y][x] >= 1 {
                counter = counter + 1;
            }
        }
    }

    (counter, b_c)
}

fn task1(instructions: &Vec<Instructions>) -> () {
    let mut lights: Vec<Vec<u32>> = vec![vec![0; 1000]; 1000];
    let (counter, _) = turn_lights_on(false, instructions, &mut lights);
    println!("number of lights turned on: {counter}");
}

fn task2(instructions: &Vec<Instructions>) -> () {
    let mut lights: Vec<Vec<u32>> = vec![vec![0; 1000]; 1000];
    let (_, b_c) = turn_lights_on(true, instructions, &mut lights);
    println!("all lights' brightness combined equals: {b_c}");
}
