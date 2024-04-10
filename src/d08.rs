use std::fs;

const INPUT_PATH: &str = "src/inputs/d08.txt";

fn main() {
    // three methods of string escape
    // ['\\','\\'], single backslash
    // ['\\','"'], single double quotes
    // ['\\','x', ...] (two hexadecimal characters), single character
    let file = fs::read_to_string(INPUT_PATH).expect("file should exist");
    let lines: Vec<&str> = file.lines().collect();

    task1(lines);
    task2();
}

fn task1(lines: Vec<&str>) -> () {
    let (total, escaped, new) = calc_chars(lines);
    println!("new: {new}, total: {total}, escaped: {escaped}");
    println!("part 1: {:?}", total - escaped);
    println!("part 2: {:?}", new - total);
}

fn task2() -> () {}

fn calc_chars(lines: Vec<&str>) -> (usize, usize, usize) {
    let mut new = 0;
    let mut total = 0;
    let mut escaped = 0;
    
    for line in lines {
        println!("\n{line}");
        let chars: Vec<char> = line.chars().collect();
        println!("{chars:?}");

        total += line.chars().count();

        let length = chars.len() - 1;
        let mut index = 1;
        while index < length {
            escaped += 1;
            if chars[index] == '\\' {
                if chars[index+1] == 'x' {
                    index += 4;       
                } else {
                    index += 2;       
                }
            } else {
                index += 1;
            }
        }
        
        for c in &chars {
            new += 1;
            if c == &'"' || c == &'\\'{
                new += 1;
            }
        }
        new += 2;
    }

    println!("new: {new}, total: {total}, escaped: {escaped}");
    (total, escaped, new)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn calc_new_empty() {
        let lines = vec!["\"\""];
        let (total, escaped, new) = calc_chars(lines);

        assert_eq!(total, 2);
        assert_eq!(escaped, 0);
        assert_eq!(new, 6);
    }

    #[test]
    fn calc_escaped() {
        let lines = vec!["\"abc\""];
        let (total, escaped, new) = calc_chars(lines);

        assert_eq!(total, 5);
        assert_eq!(escaped, 3);
        assert_eq!(new, 9);
    }

    #[test]
    fn calc_hex() {
        let lines = vec!["\"\\x27\""];
        let (total, escaped, new) = calc_chars(lines);

        assert_eq!(total, 6);
        assert_eq!(escaped, 1);
        assert_eq!(new, 11);
    }

    #[test]
    fn calc_another() {
        let lines = vec!["\"aaa\\\"aaa\""];
        let (total, escaped, new) = calc_chars(lines);

        assert_eq!(total, 10);
        assert_eq!(escaped, 7);
        assert_eq!(new, 16);
    }
}
