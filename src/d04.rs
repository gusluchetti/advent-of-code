use advent_of_code_2015::utils::{Method, parse_input};

const INPUT_PATH: &str = "src/inputs/d04.txt";

#[cfg(test)]
mod tests {
    #[test]
    fn first_md5_hash() {
        let secret = "abcdef";
        let answer = 609043;
        let result = 0;

        assert_eq![result, answer];
    }

    #[test]
    fn second_md5_hash() {
        let secret = "pqrstuv";
        let answer = 1048970;
        let result = 0;

        assert_eq![result, answer];
    }
}

fn main() {
    task1();
    task2();
}

fn task1() {
    let input = parse_input(INPUT_PATH, Method::OneString);
    let secret: &str = input[0].trim();
    println!("{:?}", secret);
}

fn task2() {
    let input = parse_input(INPUT_PATH, Method::OneString);
    let secret: &str = input[0].trim();
    println!("{:?}", secret);
}
