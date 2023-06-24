use std::collections::HashMap;

const INPUT_PATH: &str = "src/inputs/d07.txt";

#[cfg(test)]
mod tests {
    use super::*;

    const INPUT_TEST: &str = "src/inputs/test_d07.txt";

    #[test]
    fn test_sample_circuit() {
        let lines: Vec<String> = std::fs::read_to_string(INPUT_TEST)
            .expect("cargo should be run from root")
            .lines()
            .map(String::from)
            .collect();

        let res = read_circuit(lines);

        assert_eq!(res["d"], 72);
        assert_eq!(res["e"], 507);
        assert_eq!(res["f"], 492);
        assert_eq!(res["g"], 114);
        assert_eq!(res["h"], 65412);
        assert_eq!(res["i"], 65079);
        assert_eq!(res["x"], 123);
        assert_eq!(res["y"], 456);
    }
}

fn main() {
    let lines: Vec<String> = std::fs::read_to_string(INPUT_PATH)
        .expect("cargo should be run from root")
        .lines()
        .map(String::from)
        .collect();

    task1(lines);
    task2();
}

fn get_value_or_current(circuit: &HashMap<String, u16>, s: &str) -> u16 {
    let cur: u16;
    let value = s.parse::<u16>();
    println!("{:?}", circuit);
    if value.is_err() {
        cur = circuit[&String::from(s)];
    } else {
        cur = value.ok().unwrap();
    }

    return cur;
}

fn read_circuit(lines: Vec<String>) -> HashMap<String, u16> {
    let mut circuit: HashMap<String, u16> = HashMap::new();

    for line in lines {
        let mut split: Vec<&str> = line.split_whitespace().collect();
        let receiver = split.pop().expect("should always have receiver");
        split.pop().unwrap(); // disconsider '->'
        let sender = &split[..];

        let mut msg: u16 = 0;
        println!("{:?} -> {:?}", sender, receiver);
        match sender.len() {
            3 => {
                let first = get_value_or_current(&circuit, sender[0]);
                let second = get_value_or_current(&circuit, sender[2]);

                msg = match sender[1] {
                    "AND" => first & second,
                    "OR" => first | second,
                    "RSHIFT" => first >> second,
                    "LSHIFT" => first << second,
                    _ => 0 as u16,
                }
            }
            2 => {
                msg = !get_value_or_current(&circuit, sender[1]);
            }
            // just a value assignment
            1 => {
                msg = get_value_or_current(&circuit, sender[0]);
            }
            _ => {}
        }

        circuit.entry(receiver.to_string()).or_insert(msg);
        println!("{:?}\n", circuit);
    }

    circuit
}

fn task1(lines: Vec<String>) -> () {
    let res = read_circuit(lines);
    println!("{:?}", res);
}

fn task2() -> () {}
