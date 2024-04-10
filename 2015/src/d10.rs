const INPUT_PATH: &str = "src/inputs/d10.txt";

fn main() {
    let _input = std::fs::read_to_string(INPUT_PATH).expect("should have input");
    let mut line: String = _input.lines().collect::<Vec<&str>>()[0].to_string();
    // let mut line = String::from("1");
    let mut new_line: String;

    let stop = 50;
    for n in 0..stop {
        new_line = String::from("");
        let length = line.len();
        let mut count = 1;
        let mut prev: char = 'x';

        for (i, c) in line.chars().enumerate() {
            // println!("cur: {c} w/ count ({count}), prev: {prev}");

            if i != 0 && c != prev {
                // println!("adding prev -> {count}{prev}");
                new_line.push_str(&count.to_string());
                new_line.push(prev);
                count = 1;
            }

            if c == prev {
                count += 1;
            }

            if i == length - 1 {
                // println!("adding cur -> {count}{c}");
                new_line.push_str(&count.to_string());
                new_line.push(c);
            }

            prev = c;
        }

        line = new_line.clone();
        println!("pass {:?} length: {:?}", n + 1, line.len());
    }
}
