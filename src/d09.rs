use std::collections::HashMap;

use itertools::Itertools;

const INPUT_PATH: &str = "src/inputs/d09.txt";

fn main() {
    let input = std::fs::read_to_string(INPUT_PATH).expect("should have input");
    let lines = input.lines().collect::<Vec<&str>>();

    let mut distances: HashMap<String, HashMap<String, i32>> = HashMap::new();

    for line in &lines {
        let inst: Vec<&str> = line.split(" ").collect();
        let connection = vec![inst[0], inst[2]];
        let distance = str::parse(inst[4]).unwrap();
        println!("{:?},{distance}", connection);

        for (i, c) in connection.iter().enumerate() {
            let other;
            if i == 1 {
                other = connection[0];
            } else {
                other = connection[1];
            }

            if distances.get(c.to_owned()) == None {
                distances.insert(c.to_string(), HashMap::new());
            }
            let city = distances.get_mut(c.to_owned()).unwrap();
            city.insert(other.to_string(), distance);
        }
    }

    println!("{:?}", distances);
    let mut total_distances: Vec<i32> = vec![];
    for perm in distances
        .clone()
        .into_keys()
        .collect::<Vec<String>>()
        .iter()
        .permutations(distances.keys().len())
        .unique()
    {
        // println!("{:?}", perm);
        let mut total: i32 = 0;
        for n in 0..perm.len() - 1 {
            let distance = distances.get(perm[n]).unwrap().get(perm[n + 1]).unwrap();
            total += distance;
        }
        total_distances.push(total);
    }

    println!(
        "shortest distance: {:?}",
        total_distances.iter().min().unwrap()
    );
    println!(
        "longest distance: {:?}",
        total_distances.iter().max().unwrap()
    );
}
