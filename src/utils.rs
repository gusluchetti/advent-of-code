use std::{io, io::prelude::*};
use std::fs::File;
use std::str;

pub enum Method {
    NewLine,
    OneString,
    Other(char)
}

// parse puzzle input in a couple ways:
// default - no method (whole input as ONE string)
// new line method (array of lines)
// other method (any other character or word)
pub fn parse_input(path: &str, method: Method) -> io::Result<Vec<String>> {
    let mut file = File::open(path)?;
    let mut lines: Vec<String> = Vec::new();

    let mut input = Vec::new();
    file.read_to_end(&mut input)?;
    let text: &str = str::from_utf8(&input).unwrap();

    let lines = match method {
        Method::OneString => {
            lines.push(String::from(text));
            lines
        },
        Method::NewLine => {
            for line in text.lines() {
                lines.push(String::from(line));
            }
            lines
        },
        Method::Other(char) => {
            let splitter = char.to_string();
            let text = text.replace("\n", &splitter);
            let text = text.replace("\r", &splitter);

            let v: Vec<&str> = text.split_terminator(&splitter).collect();
            for item in v {
                lines.push(String::from(item));
            }
            println!("{:?}", lines);
            lines
        }
    };

    return Ok(lines);
}
