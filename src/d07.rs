const INPUT_PATH: &str = "src/inputs/d07.txt";

#[cfg(test)]
mod tests {
    use super::*;
    const INPUT_TEST: &str = "src/inputs/test_d07.txt";

    #[test]
    fn test_sample_circuit() {
        
    }
}


fn main() {
    let lines = std::fs::read_to_string(INPUT_PATH)
        .expect("cargo should be run from root")
        .lines()
        .map(String::from)
        .collect();

    task1(lines);
    task2();
}

fn task1(lines: Vec<String>) -> () {
    println!("{:?}", lines);
}

fn task2() -> () {}
