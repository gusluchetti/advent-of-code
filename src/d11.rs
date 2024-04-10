use std::str;
const INPUT_PATH: &str = "src/inputs/d11.txt";

fn main() {
    let input = std::fs::read_to_string(INPUT_PATH).expect("should have input");
    let line = input.trim();

    let prohibited = "iol";
    let p_bytes = prohibited.as_bytes();
    println!("{:?}", p_bytes);

    task1(line);
    task2(line);
}

fn task1(input: &str) {
    let bytes: &[u8] = input.as_bytes();
    println!("{:?} == {:?}", input, bytes);

    // NOTE: work mostly with bytes if possible
    // one abc, cbd, xyz necessary (101, 102, 103...)
    fn has_triple_consecutive() {}

    // 105 (i), 108(l), 111(o) are prohibited;
    fn has_valid_letters() {}

    // needs to have 2 non-overlapping pairs of letters
    fn has_two_unique_pairs() {}

    for b in bytes {
        let c = b + 1;
        let test: &[u8] = &[*b, c];
        let values = str::from_utf8(&test).unwrap();
        println!("{:?}, {:?}", b, c);
        println!("{:?}, {:?}", test, values);
    }
}

fn task2(input: &str) {
    let temp = 1;
}
