use advent_of_code_2015::utils::{parse_input, Method};
use std::collections::HashMap;

const INPUT_PATH: &str = "src/inputs/d05.txt";

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn test_task1_helpers() {
        assert_eq!(twice_row_char("lajkdkdabb"), true);
        assert_eq!(twice_row_char("aba"), false);

        assert_eq!(three_vowel_count("understand"), true);
        assert_eq!(three_vowel_count("bbb"), false);
    }

    #[test]
    fn test_full_task1() {
        assert_eq!(is_nice_string("ugknbfddgicrmopn"), true);
        assert_eq!(is_nice_string("aaa"), true);

        assert_eq!(is_nice_string("jchzalrnumimnmhp"), false);
        assert_eq!(is_nice_string("dvszwmarrgswjxmb"), false);
    }

    #[test]
    fn test_task2_helpers() {
        assert_eq!(two_pairs("aabcdefgaa"), true);
        assert_eq!(two_pairs("aaa"), false);

        assert_eq!(repeat_with_between("abcdefeghi"), true);
        assert_eq!(repeat_with_between("xxaabbcc"), false);
    }

    #[test]
    fn test_full_task2() {
        assert_eq!(is_nicest_string("qjhvhtzxzqqjkmpb"), true);
        assert_eq!(is_nicest_string("xxyxx"), true);
        assert_eq!(is_nicest_string("hubpbvxknepammep"), true);

        assert_eq!(is_nicest_string("uurcxstgmygtbstg"), false);
        assert_eq!(is_nicest_string("ieodomkazucvgmuy"), false);
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
}

///

fn two_pairs(string: &str) -> bool {
    let chars: Vec<char> = string.chars().collect();
    for i in 0..chars.len() - 1 {
        for j in 2..chars.len() - 1 {
            let first = &chars[i..=i + 1];
            let second = &chars[j..=j + 1];
            if j > i + 1 && first == second {
                println!("{:?},{:?} -- i:{i}, j:{j}", first, second);
                println!("{string} has two two-letter pairs!");
                return true;
            }
        }
    }

    return false;
}

fn repeat_with_between(string: &str) -> bool {
    let chars: Vec<char> = string.chars().collect();
    for i in 0..chars.len() - 2 {
        let j = i + 2;
        if chars[i] == chars[j] {
            println!("{:?} at {i} and {j}", &chars[i..=i + 2]);
            println!("{string} consecutive chars with one in between");
            return true;
        }
    }
    return false;
}

fn is_nicest_string(string: &str) -> bool {
    if two_pairs(string) && repeat_with_between(string) {
        return true;
    } else {
        return false;
    }
}

fn task2() -> () {
    let input = parse_input(INPUT_PATH, Method::NewLine);
    let mut counter = 1;
    let mut nice_strings: u32 = 0;

    for line in input {
        if is_nicest_string(line.as_str()) {
            println!("{line} is nice!");
            nice_strings = nice_strings + 1;
        } else {
            println!("word {counter} is bad! {line}");
        }
        counter = counter + 1;
    }
    println!("number of nice strings: {nice_strings}");
}
