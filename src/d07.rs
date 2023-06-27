use std::{collections::HashMap, fs};

const INPUT_PATH: &str = "src/inputs/d07.txt";

#[derive(Debug)]
struct Output {
    wires: Vec<String>,
    operation: String,
}

#[cfg(test)]
mod tests {
    use std::{collections::HashMap, fs};

    use crate::{get_circuit, get_lines, solve_full};
    const INPUT_TEST: &str = "src/inputs/test_d07.txt";

    #[test]
    fn test_sample_circuit() {
        let file: String = fs::read_to_string(INPUT_TEST).unwrap();
        let lines = get_lines(&file);
        let circuit = get_circuit(lines);
        let mut res: HashMap<String, u16> = HashMap::new();
        for (key, output) in &circuit {
            let signal = solve_full(&circuit, &mut res, key, output);
            res.entry(key.to_string()).or_insert(signal);
        }

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

fn get_lines(file: &String) -> Vec<Vec<&str>> {
    let mut lines: Vec<Vec<&str>> = file
        .lines()
        .map(|f| f.split_whitespace().collect())
        .collect();

    lines.sort_by(|a, b| (a.len()).cmp(&b.len()));
    lines
}

fn get_circuit(lines: Vec<Vec<&str>>) -> HashMap<String, Output> {
    let mut circuit: HashMap<String, Output> = HashMap::new();
    for line in &lines {
        let mut wires: Vec<String> = Vec::new();
        let mut key: String = String::from("");
        let mut value: Output = Output {
            wires,
            operation: String::from(""),
        };

        match line.len() {
            // complex operation
            5 => {
                wires = vec![line[0].to_string(), line[2].to_string()];
                key = line[4].to_string();
                value = Output {
                    wires,
                    operation: String::from(line[1]),
                };
            }
            // NOT operation
            4 => {
                wires = vec![line[1].to_string()];
                key = line[3].to_string();
                value = Output {
                    wires,
                    operation: String::from(line[0]),
                };
            }
            // "assignment"
            3 => {
                wires = vec![line[0].to_string()];
                key = line[2].to_string();
                value = Output {
                    wires,
                    operation: String::from("ASSIGN"),
                };
            }
            _ => {}
        }

        circuit.insert(key, value);
    }

    circuit
}

fn solve_full(
    cir: &HashMap<String, Output>,
    res: &mut HashMap<String, u16>,
    key: &String,
    output: &Output,
) -> u16 {
    println!("{key}, {:?}", output);
    let fast_track = res.get(key);
    if fast_track.is_some() {
        println!("fastracked {key}");
        return fast_track.unwrap().clone();
    }
    let operation = &output.operation;
    let first: u16;
    let mut second: u16 = 0;

    first = solve_single(cir, res, key, &output.wires[0], operation);
    if output.wires.len() == 2 {
        second = solve_single(cir, res, key, &output.wires[1], operation);
    }
    // have to solve twice and match with operation
    let number = match operation.as_str() {
        "AND" => first & second,
        "OR" => first | second,
        "LSHIFT" => first << second,
        "RSHIFT" => first >> second,
        "NOT" => !first,
        "ASSIGN" => first,
        _ => 0u16,
    };

    println!("solved! {key}={number} using {operation}, on {first} and {second}");
    res.entry(key.to_string()).or_insert(number);
    return number;
}

fn solve_single(
    cir: &HashMap<String, Output>,
    res: &mut HashMap<String, u16>,
    key: &String,
    single: &String,
    operation: &String,
) -> u16 {
    let fast_track = res.get(single);
    if fast_track.is_some() {
        println!("fastracked {single}");
        return fast_track.unwrap().clone();
    }
    let solve = single.parse::<u16>();
    if solve.is_ok() {
        let number = solve.unwrap();
        return number;
    } else {
        let (key, output) = cir.get_key_value(single).unwrap();
        return solve_full(cir, res, key, output);
    }
}

fn main() {
    task1();
    task2();
}

fn task1() -> () {
    let file: String = fs::read_to_string(INPUT_PATH).unwrap();
    let mut lines = get_lines(&file);
    lines.sort_by(|a, b| (a.len()).cmp(&b.len()));

    let circuit = get_circuit(lines);
    let mut res: HashMap<String, u16> = HashMap::new();
    for (key, output) in &circuit {
        let signal = solve_full(&circuit, &mut res, key, output);
        res.entry(key.to_string()).or_insert(signal);
    }
    println!("\n{:?}", res.get("a").unwrap());
}

fn task2() -> () {
    let file: String = fs::read_to_string(INPUT_PATH).unwrap();
    let mut lines = get_lines(&file);
    lines.sort_by(|a, b| (a.len()).cmp(&b.len()));

    let mut circuit = get_circuit(lines);
    let overwrite = Output {
        wires: vec![46065u16.to_string()],
        operation: "ASSIGN".to_string()
    };

    circuit.insert("b".to_string(), overwrite);

    let mut res: HashMap<String, u16> = HashMap::new();
    for (key, output) in &circuit {
        let signal = solve_full(&circuit, &mut res, key, output);
        res.entry(key.to_string()).or_insert(signal);
    }
    println!("\n{:?}", res.get("a").unwrap());
}
