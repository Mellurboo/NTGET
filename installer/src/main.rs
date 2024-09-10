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
use r#impl::writefs::ntget_write_folders;

mod r#helper{
    pub mod pause;
    pub mod elevation;
}

mod r#impl{
    pub mod writefs;
}

extern "C" {
    fn ntpath() -> i32;
}

fn splash(){
    print!("\x1B[2J\x1B[1;1H");         // send escape codes to clear the screen when run. (I found this on the internet, amen to stack overflow)
    println!("{}\n\t{}\n\t{}\n",
        "Install NTGET - Version vBETA (RUSTC)".yellow(),
        "Creating Folders, Pulling Files, Installing NTGET and Setting up the Windows Environment".green().bold(),
        "Myles 'Mellurboo' Wilson 2024".green()
    );
}

fn main() {
    splash();           // display the splash, lol

    match ntget_write_folders(){
        Ok(()) => println!("{} {}", "Wrote folders Successfully!".green(), " ---> C:\\NTGET".green().bold()),
        Err(e) => eprintln!("{}", format!("Failed to write folders: {}", e).red().bold()),
    }
    
    unsafe {
        let result = ntpath();
        println!("{}", "Attempting to write to System PATH variable".yellow());
        match result {
             0 => println!("{}", "Wrote to System PATH Successfully!".green().bold()),
             1 => println!("{}", "There was an error getting the system PATH".red().bold()),
            -1 => println!("{}", "The path is already in the system PATH, moving on".green().bold()),
            -2 => println!("{}", "The path length exceeds buffer size, sorry!".red().bold()),
            -3 => println!("{}", "Failed to open the required registry key".red().bold()),
            -4 => println!("{}", "Failed to edit PATH in registry".red().bold()),
            -5 => println!("{}", "Failed to get updated PATH to confirm the updated path".red().bold()),
            _ => println!("{}\n\treturned: {}", ":/ got a bad code in return , no status can be provided, check PATH manually!".red().bold(), result),
        }
    }
    
    // downloading the NTGET client to C:\NTGET\bin

    wait();
}