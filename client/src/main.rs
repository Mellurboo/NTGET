use std::env;


fn main() {
    let args: Vec<String> = env::args().collect();
    
    if args.len() < 3 {
        println!("Usage: ntget <process> <package>");
        return;
    }

    let process = &args[1];
    let package = &args[2];

    match process.to_lowercase().as_str() {
        "download" => println!("Downloads does not install the msi package for you."),
        "extract" => println!("Extracts and installs the msi package but will not download it from the internet"),
        "install" => println!("Download, extracts and installs the package for you fully"),
        _ => println!("Invalid NTGET process, {} is empty or not a valid action", process),
    }

    println!("Package {} added to install queue", package);
}
