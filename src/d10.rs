const INPUT_PATH: &str = "src/inputs/d10.txt";

fn main() {
    // let input = std::fs::read_to_string(INPUT_PATH).expect("should have input");
    // let mut line: &str = input.lines().collect::<Vec<&str>>()[0];
    let mut line: String = String::from("1");
    let mut new_line: String;

    let stop = 5;
    for n in 0..stop {
        new_line = "".to_string();
        let length = line.len();
        let mut count = 1;
        let mut prev: char = 'x';

        for (i, c) in line.chars().enumerate() {
            println!("cur: {c} w/ count ({count}), prev: {prev}");

            if i == 0 && length == 1 {
                prev = c;
            }

            if c != prev || (i == length - 1) {
                println!("adding to newline: {count}, {prev}");
                new_line.push_str(&count.to_string());
                new_line.push(prev);

                count = 0;
                prev = c;
            }

            count += 1;
        }

        line = new_line.clone();
        println!("\npass {:x}: {:?}", n + 1, line);
    }
}
