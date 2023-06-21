use advent_of_code_2015::utils::{parse_input, Method};
use std::collections::HashMap;

const INPUT_PATH: &str = "src/inputs/d05.txt";

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn test_twice_row_char() {
        assert_eq!(twice_row_char("aa"), true);
        assert_eq!(twice_row_char("ab"), false);
        assert_eq!(twice_row_char("aba"), false);
        assert_eq!(twice_row_char("lajkdkdabb"), true);
    }
    #[test]
    fn test_three_vowels() {
        assert_eq!(three_vowel_count("aaa"), true);
        assert_eq!(three_vowel_count("understand"), true);
        assert_eq!(three_vowel_count("bbb"), false);
    }

    #[test]
    fn test_nice_strings() {
        assert_eq!(is_nice_string("ugknbfddgicrmopn"), true);
        assert_eq!(is_nice_string("aaa"), true);
    }
    #[test]
    fn test_naughty_strings() {
        assert_eq!(is_nice_string("jchzalrnumimnmhp"), false);
        assert_eq!(is_nice_string("haegwjzuvuyypxyu"), false);
        assert_eq!(is_nice_string("dvszwmarrgswjxmb"), false);
    }
}

fn main() {
    task1();
    task2();
}

///

fn twice_row_char(string: &str) -> bool {
    let mut characters = string.chars();
    let mut last_c = characters.next().unwrap();
    for c in characters {
        if c == last_c {
            return true;
        } else {
            last_c = c;
        }
    }

    false
}

fn three_vowel_count(string: &str) -> bool {
    let mut char_count: HashMap<char, _> = HashMap::new();
    for c in string.chars() {
        char_count.entry(c).and_modify(|c| *c += 1).or_insert(1);
    }

    let to_find = ['a', 'o', 'e', 'i', 'u'];
    let mut vowel_count = 0;
    for &char in &to_find {
        match char_count.get(&char) {
            Some(number) => vowel_count = vowel_count + number,
            None => {}
        }
    }

    if vowel_count >= 3 {
        true
    } else {
        false
    }
}

fn is_nice_string(string: &str) -> bool {
    let bad_combos = vec!["ab", "cd", "pq", "xy"];
    for b in bad_combos {
        if string.find(b) != None {
            return false;
        }
    }

    if three_vowel_count(string) && twice_row_char(string) {
        return true;
    } else {
        return false;
    }
}

fn task1() -> () {
    let input = parse_input(INPUT_PATH, Method::NewLine);
    let mut nice_strings: u32 = 0;

    for line in input {
        if is_nice_string(line.as_str()) {
            nice_strings = nice_strings + 1;
        }
    }
    println!("number of nice strings: {nice_strings}");
}

///

fn pair_two_letters(string: &str) -> bool {
    let chars: Vec<char> = string.chars().collect();
    false
}

fn repeat_with_between(string: &str) -> bool {
    let chars: Vec<char> = string.chars().collect();
    for i in 0..chars.len() {

    }
    false
}

fn is_nicest_string(string: &str) -> bool {
    if pair_two_letters(string) && repeat_with_between(string) {
        return true;
    } else {
        return false;
    }
}

fn task2() -> () {
    let input = parse_input(INPUT_PATH, Method::NewLine);
    let mut nice_strings: u32 = 0;

    for line in input {
        if is_nicest_string(line.as_str()) {
            nice_strings = nice_strings + 1;
        }
    }
    println!("number of nice strings: {nice_strings}");
}
