use ::day_02::gamerecord::*;

fn main() {
    // Load file
    let args: Vec<String> = std::env::args().collect();
    let contents: String;
    if args.len() == 1 {
        contents = std::fs::read_to_string("./input.txt").expect("couldn't open file");
    }
    else {
        contents = std::fs::read_to_string(&args[1]).expect("couldn't open file");
    }
    
    let records = GameRecord::parse_multiple(&contents);

    // fewest balls needed per game
    let filtered: Vec<GameSet> = records.into_iter().map(|record| {
        record.get_fewest_balls_needed()
    }).collect();
    
    let mut answer = 0;
    for game in &filtered {
        let power = (game.red_cubes as usize) * (game.green_cubes as usize) * (game.blue_cubes as usize);
        answer += power;
    }
    println!("final answer: {}", answer);
}


