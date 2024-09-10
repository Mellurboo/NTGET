//
//  [=>                 Myles Wilson 2024                   <=]
//                  https://github.com/Mellurboo

//  this goes in another file simply because im a clean freak
//  anyway it could go in main but i dont care xoxo

use std::io;
use colored::Colorize;
use std::io::prelude::*;

// calls for the CLI to pause until a key is pressed
pub fn wait() {
    let mut stdin = io::stdin();
    let mut stdout = io::stdout();

    println!("{}", "[=> Press Any Key to Continue <=]".red().bold());       // its not any key lol its only enter, ill fix that later
    stdout.flush().unwrap();

    let _ = stdin.read(&mut [0u8]).unwrap();
}