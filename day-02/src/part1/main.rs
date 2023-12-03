use ::day_02::gamerecord::*;

const MAX_CUBES: GameSet = GameSet{
    red_cubes: 12,
    green_cubes: 13,
    blue_cubes: 14,
};

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
    // only 12 red cubes, 13 green cubes, and 14 blue cubes
    let filtered: Vec<GameRecord> = records.into_iter().filter(|record| {
        if record.is_valid(&MAX_CUBES) {
            return true;
        }
        return false;
    }).collect();
    
    let mut ids_added = 0;
    for game in &filtered {
        ids_added += game.get_id();
    }
    println!("final answer: {}", ids_added);
}


