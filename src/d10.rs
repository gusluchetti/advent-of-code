const INPUT_PATH: &str = "src/inputs/d10.txt";

fn main() {
    let input = std::fs::read_to_string(INPUT_PATH).expect("should have input");
    // let mut line: &str = input.lines().collect::<Vec<&str>>()[0];
    let mut line: &str = "1";

    let stop = 5;
    let mut count = 0;
    let mut prev: char = 'j';
    let mut new_line: String = "".to_string();

    for _ in 0..stop {
        println!("{:?}\n", line);
        for (i, c) in line.to_owned().chars().enumerate() {
            println!("cur: {c} w/ count ({count}), prev: {prev}");
            if i == 0 {
                prev = c;
            }

            if c != prev {
                println!("done w/ {prev}");
                new_line += &count.to_string();
                new_line.push(prev);

                count = 0;
                prev = c;
            }

            count += 1;
        }
        line = &new_line;
    }
}
