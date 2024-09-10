//
//  [=>                 Myles Wilson 2024                   <=]
//                  https://github.com/Mellurboo

//
//  Limine 
//      "In Limine" is a Latin term meaning "at the threashold". ~ www.law.cornell.edu
//
//  The Beginning of a new era for opening the Windows Users mind to the Terminal Interface steamlining
//  package installation on Windows machines and opening a door for backwards compatability between Shell Script and Windows Batch file
//
use colored::Colorize;
use helper::pause::wait;

mod r#helper{
    pub mod pause;
}

fn splash(){
    print!("\x1B[2J\x1B[1;1H");         // send escape codes to clear the screen when run.
    println!("{}\n\t{}\n\t{}\n",
        "Install NTGET - Version vBETA (RUST)".yellow(),
        "Creating Folders, Pulling Files, Installing NTGET and Setting up the Windows Environment".green().bold(),
        "Myles 'Mellurboo' Wilson 2024".green()
    );
}

fn main() {
    splash();
    wait();
}