#[derive(Debug)]
pub struct GameSet {
    pub red_cubes: u16,
    pub green_cubes: u16,
    pub blue_cubes: u16,
}

impl GameSet {
    fn new() -> Self {
        Self {
            red_cubes: 0,
            green_cubes: 0,
            blue_cubes: 0,
        }
    }

    pub fn is_valid(&self, rules: &GameSet) -> bool {
        if rules.red_cubes < self.red_cubes {
            return false
        }
        if rules.green_cubes < self.green_cubes {
            return false
        }
        if rules.blue_cubes < self.blue_cubes {
            return false
        }
        true
    }

    // "5 blue, 5 green, 1 red\r"
    fn parse(contents: &str) -> GameSet{
        let mut set = GameSet::new();

        let turns: Vec<&str> = contents.split(", ").collect();
        for turn in turns {
            // "15 red" "5 blue" "1 green"
            let args: Vec<&str> = turn.split(" ").collect();
            let count = args[0].parse::<u16>().unwrap();

            match args[1].trim_end() /* lines end with '\r' */ {
                "red"   => { set.red_cubes = count; }
                "blue"  => { set.blue_cubes = count; }
                "green" => { set.green_cubes = count; }

                _ => { panic!("invalid color '{}'", args[1]); }
            }
        }
        set
    }
}

#[derive(Debug)]
pub struct GameRecord {
    id: usize,
    sets: Vec<GameSet>,
}

impl GameRecord {
    pub const fn get_id(&self) -> usize {
        self.id
    }

    pub fn is_valid(&self, rules: &GameSet) -> bool {
        for set in &self.sets {
            if !set.is_valid(rules) {
                return false;
            }
        }
        true
    }

    //   <id>:         <set>;                  <set>;   <set>
    // Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
    pub fn parse(record_contents: &str) -> GameRecord {
        assert_eq!(record_contents.starts_with("Game "), true, "line doesn't start with 'Game ' :-(");

        let no_prefix = record_contents.strip_prefix("Game ").unwrap();
        let colon_pos = no_prefix.find(':').unwrap();

        // id
        let game_id = (&no_prefix[..colon_pos]).parse::<usize>().unwrap();

        // sets
        let mut sets = vec![];
        let sets_string: Vec<&str> = (&no_prefix[(colon_pos+2)..]).split("; ").collect();
        for set_str in sets_string {
            let set = GameSet::parse(set_str);
            sets.push(set);
        }


        GameRecord { id: game_id, sets: sets }
    }

    pub fn parse_multiple(file_contents: &String) -> Vec<GameRecord> {
        let mut records: Vec<GameRecord> = vec![];
        for line in file_contents.split('\n') {
            if line.is_empty() {
                continue;
            }
            let record = GameRecord::parse(line);
            records.push(record);
        }
        records
    }

    pub fn get_fewest_balls_needed(&self) -> GameSet {
        let mut current_lowest = GameSet::new();

        for set in &self.sets {
            current_lowest.red_cubes   = current_lowest.red_cubes.max(set.red_cubes);
            current_lowest.green_cubes = current_lowest.green_cubes.max(set.green_cubes);
            current_lowest.blue_cubes  = current_lowest.blue_cubes.max(set.blue_cubes);
        }

        current_lowest
    }
}
