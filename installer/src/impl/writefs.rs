//
//  [=>                 Myles Wilson 2024                   <=]
//                  https://github.com/Mellurboo

//
//  Making it easy to write files to the host system.
//

use std::fs::{self};

use colored::Colorize;

// write the required folders to the host system
pub fn ntget_write_folders() -> std::io::Result<()>{
    println!("{}", "Attempting to Write Folders".yellow());
    fs::create_dir_all("C:\\NTGET\\Logs")?;
    fs::create_dir_all("C:\\NTGET\\bin")?;
    Ok(())
}