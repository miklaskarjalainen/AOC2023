using System;
using System.Collections.Generic;
using System.Globalization;
using IntegerMap = System.Collections.Generic.Dictionary<(ulong, ulong),ulong>;

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
            m_Maps.Last().Add((nums[1], nums[2]), nums[0]);

            nums.ForEach(n => Console.Write($"{n} "));
            Console.Write('\n');
        }
        
    }

    public List<ulong> GetSeedLocations() {
        List<ulong> mapped = new();
        
        foreach (ulong seed in m_Seeds) {
            ulong currentMap = seed;
            
            Console.Write($"seed {seed} -> ");
            foreach(IntegerMap map in m_Maps) {
                foreach ((ulong start, ulong range) in map.Keys) {
                    if (currentMap >= start && currentMap < (start + range)) {
                        ulong difference = currentMap - start;
                        ulong dest = map[(start, range)];
                        currentMap = dest + difference;
                        break;
                    }
                }
                Console.Write($"{currentMap} -> ");
            }
            Console.Write('\n');
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

