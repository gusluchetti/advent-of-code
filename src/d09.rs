use std::{collections::HashMap, u32::MAX};

const INPUT_PATH: &str = "src/inputs/d09.txt";

fn main() {
    let input = std::fs::read_to_string(INPUT_PATH).expect("should have input");
    task1(&input);
    task2(&input);
}

fn task1(input: &String) {
    let lines: Vec<Vec<&str>> = input
        .lines()
        .map(|f| f.split_whitespace().collect())
        .collect();

    let nodes = get_nodes(lines);
    let is_longest = false;
    let shortest_path = get_distance(nodes, is_longest);
}

fn task2(input: &String) {}

fn get_nodes(lines: Vec<Vec<&str>>) -> HashMap<String, HashMap<String, u32>> {
    let mut nodes: HashMap<String, HashMap<String, u32>> = HashMap::new();
    for line in lines {
        let start = line[0].to_string();
        let end = line[2].to_string();
        let distance = line[4].parse::<u32>().expect("is always number");

        let mut saved: HashMap<String, u32> = HashMap::new();
        if nodes.contains_key(&start) {
            saved = nodes.get(&start).expect("should always exist").clone();
        }
        saved.insert(end.clone(), distance);
        nodes.insert(start.clone(), saved);

        saved = HashMap::new();
        if nodes.contains_key(&end) {
            saved = nodes.get(&end).expect("should always exist").clone();
        }
        saved.insert(start.clone(), distance);
        nodes.insert(end.clone(), saved);
    }

    nodes
}

fn get_distance(nodes:HashMap<String, HashMap<String, u32>>, is_longest: bool) -> u32 {
    let mut visited: HashMap<String, u32> = HashMap::new();
    let first = nodes.iter().next().expect("should have at least one");
    visited.insert(first.0.clone(), 0);

    let mut next_node: (&String, &HashMap<String, u32>) = first;
    let mut cur_node = next_node;
    println!("visited: {visited:?}");
    while visited.len() < nodes.len() {
        let mut shortest_path = MAX;
        for (place, distance) in cur_node.1 {
            if distance < &shortest_path {
                next_node = nodes.get_key_value(place).expect("should always exist");
                shortest_path = distance.clone();
            }
        }
        println!("best path: {} ={shortest_path}> {}", cur_node.0, next_node.0);
        visited.insert(next_node.0.clone(), shortest_path);
        cur_node = next_node;
        println!("visited: {visited:?}\n");
    }
 
    let mut sum = 0;
    for (_, value) in visited.iter() {
        sum += value;
    }
    println!("shortest path: {sum}");
    sum
}
