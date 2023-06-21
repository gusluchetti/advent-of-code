use advent_of_code_2015::utils::{Method, parse_input};
use std::collections::HashMap;

const INPUT_PATH: &str = "src/inputs/d03.txt";

fn main() {
    task1();
    task2();
}

// state: cartesian coordinate system
// whats the best way to save it?
fn task1() {
    let input = parse_input(INPUT_PATH, Method::OneString);
    let directions: String = String::from(&input[0]);
    let mut known: HashMap<String, u32> = HashMap::from([
        ("0,0".to_string(), 1)
    ]);

    let mut x = 0;
    let mut y = 0;
    for dir in directions.chars() {
        match dir {
            '<' => {x = x-1;},
            '>' => {x = x+1;},
            '^' => {y = y+1;},
            'v' => {y = y-1;},
            _ => {}
        }
        let coords: String = format!["{x},{y}"];
        println!("{:?}", coords);
        known.entry(coords)
            .and_modify(|counter| { *counter += 1 })
            .or_insert(1); 
    }
    println!("houses that got >= 1 gift: {:?}", known.len());
}

fn task2() {
    let input = parse_input(INPUT_PATH, Method::OneString);
    let directions: String = String::from(&input[0]);
    let mut known: HashMap<String, u32> = HashMap::from([
        ("0,0".to_string(), 2)
    ]);

    let mut x1 = 0;
    let mut y1 = 0;

    let mut x2 = 0;
    let mut y2 = 0;

    let mut turn = 0;

    fn get_new_coords(x: i32, y: i32) {
        match dir {
            '<' => {x = x-1;},
            '>' => {x = x+1;},
            '^' => {y = y+1;},
            'v' => {y = y-1;},
            _ => {}
        }
    }
    
    for dir in directions.chars() {
        if turn % 2 == 0 {
            get_new_coords(x1, y1)
        }
        let coords: String = format!["{x},{y}"];
        println!("{:?}", coords);
        known.entry(coords)
            .and_modify(|counter| { *counter += 1 })
            .or_insert(1); 
    }
}
