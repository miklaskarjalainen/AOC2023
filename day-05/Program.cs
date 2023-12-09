using System;
using System.Collections.Generic;
using System.Globalization;
using IntegerMap = System.Collections.Generic.Dictionary<ulong,ulong>;

public class Mapper {
    private List<IntegerMap> m_Maps = new();
    private List<ulong> m_Seeds = new();

    public void ParseText(string text) {
        List<string> lines = text.Split('\n').ToList();

        // parse: 'seeds: 79 14 55 13'
        m_Seeds = lines[0]
            .Remove(0, 7)
            .Split(' ')
            .ToList()
            .ConvertAll(num => ulong.Parse(num));
        Console.Write("seeds: ");
        m_Seeds.ForEach(n => Console.Write($"{n} "));
        Console.Write('\n');        

        // remove first 2 lines
        lines.RemoveAt(0);
        lines.RemoveAt(0);
        
        
        foreach (string _line in lines) {
            string line = _line.Replace("\r", "");
            if (line == "") { continue; }

            if (line.Contains(':')) {
                m_Maps.Add(new IntegerMap());
                Console.WriteLine("--------------");
                continue;
            }

            // parse: '49 53 8\r'
            List<ulong> nums = line
                .Split(' ')
                .ToList()
                .ConvertAll<ulong>(num => ulong.Parse(num));
            
            // create maps
            //! line like "1760603826 3853766926 127009556" crates stupidly huge maps and consumes way too much ram
            ulong range_length = nums[2];
            for (ulong i = 0; i < range_length; i++) {
                m_Maps.Last().Add(nums[1] + i, nums[0] + i);
            }

            nums.ForEach(n => Console.Write($"{n} "));
            Console.Write('\n');
        }
        
    }

    public List<ulong> GetSeedLocations() {
        List<ulong> mapped = new();
        
        foreach (ulong seed in m_Seeds) {
            ulong currentMap = seed;
            foreach(IntegerMap map in m_Maps) {
                if (map.ContainsKey(currentMap)) {
                    currentMap = map[currentMap];
                }
            }
            mapped.Add(currentMap);
        }

        return mapped;
    }

    public static Mapper ParseFile(string filePath) {
        Mapper mapper = new();
        string text = File.ReadAllText(filePath);
        mapper.ParseText(text);
        return mapper;
    }    

}

public static class Program {
    
    public static void Main() {
        var map = Mapper.ParseFile("./input.txt");
        
        var mapped = map.GetSeedLocations();
        mapped.Sort();

        Console.WriteLine("--------------");
        Console.WriteLine($"Answer {mapped.First()}");
    }

}

