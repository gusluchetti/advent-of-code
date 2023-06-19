use advent_of_code_2015::utils::{Method, parse_input};

const INPUT_PATH: &str = "src/inputs/d02.txt";

struct Size {
    length: u8,
    width: u8,
    height: u8
}

impl Size {
    fn total_area(&self) -> u32 {
        (self.length * self.height * self.height) as u32
    }
}

fn main() {
    task1();
    task2();
}

fn task1() -> () {
    let mut total_paper = 0;
    let input = parse_input(INPUT_PATH, Method::NewLine);
    let input: Vec<String> = input.ok().unwrap();
    println!("{:?}", input);

    for n in input {
        let split: Vec<&str> = n.split_terminator('x').collect();
        if split.len() == 3 {
            let length: u8 = split[0].parse().unwrap();
            let width: u8 = split[1].parse().unwrap();
            let height: u8 = split[2].parse().unwrap();

            let box_size = Size {
                length,
                width,
                height
            };

            let total_paper = total_paper + box_size.total_area();
        }
    }
}

fn task2() -> () {

}
