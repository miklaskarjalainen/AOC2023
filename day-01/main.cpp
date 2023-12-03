#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

#include <cstdio>

// Do part1 or part2
#if !defined(AOC_PART1) && !defined(AOC_PART2) 
    #error #define AOC_PART1 or AOC_PART2
#endif

// the example given on the AOC website
#define AOC_EXAMPLE_PART1 "1abc2\npqr3stu8vwx\na1b2c3d4e5f\ntreb7uchet\n"
#define AOC_EXAMPLE_PART2 "two1nine\neightwothree\nabcone2threexyz\nxtwone3four\n4nineeightseven2\nzoneight234\n7pqrstsixteen\n"

#define AOC_TEST \
"12\n" \
"34\n" \
"56\n" \
"78\n" \
"91\n" \
"23\n" \
"45\n" \
"67\n" \
"89\n" \
"onetwo\n" \
"threefour\n" \
"fivesix\n" \
"seveneight\n" \
"nineone\n" \
"twothree\n" \
"fourfive\n" \
"sixseven\n" \
"eightnine\n" \
"twonethree\n" \
"threetwone\n" \
"fivertwonineight\n" 

#define STR_ERROR "\033[1;31m"
#define STR_RESET "\033[0m"

#define ASSERT_EQ(cmp, error_msg, ...) \
    if (!(cmp)) { \
        printf(__FILE__ ":%d: " STR_ERROR "Error: " STR_RESET error_msg "\n", __LINE__, __VA_ARGS__); \
        exit(-1); \
    }

#define ASSERT_NE(cmp, error_msg, ...) ASSERT_EQ(!(cmp), error_msg, __VA_ARGS__)

inline std::string read_file_contents(const std::string& filepath) {
    std::ifstream file(filepath);
    ASSERT_EQ(file.is_open(), "no input file found at '%s' :-(", filepath.c_str());
    std::string contents;
    
    std::string line;
    while(std::getline(file, line)) {
        contents += line;
        contents.push_back('\n');
    }

    return contents;
}

inline std::vector<std::string> split_string(const std::string& str, char delimetter) {
    std::vector<std::string> splitted = {};

    std::string current = "";
    for (auto ch : str) {
        if (ch == delimetter) {
            if (!current.empty()) {
                splitted.emplace_back(current);
                current.clear();
            }
            continue;
        }
        current.push_back(ch);
    }

    if (!current.empty()) {
        splitted.emplace_back(current);
    }

    return splitted;
}

class Calibrator {
public:
    Calibrator(const std::string& adjustments)
        : mAdjustments(adjustments) {}
    ~Calibrator() {}

    int get_calibration();
private:
    int get_last_from_line(const std::string& Line, const char* ToFind, size_t From);
    int mCalibration = 0;
    std::string mAdjustments;
};

int Calibrator::get_last_from_line(const std::string& Line, const char* ToFind, size_t From) {
    const int Pos = (int)Line.find(ToFind, From);
    if (Pos != std::string::npos) {
        const auto Next = get_last_from_line(Line, ToFind, Pos+1);
        if (Next != std::string::npos) {
            return Next;
        }
    }
    return Pos;
}

int Calibrator::get_calibration() {
    const static std::unordered_map<const char*, int> WrittenNumbers = {
        {"1", 1},
        {"2", 2},
        {"3", 3},
        {"4", 4},
        {"5", 5},
        {"6", 6},
        {"7", 7},
        {"8", 8},
        {"9", 9},

#ifdef AOC_PART2
        {"one", 1},
        {"two", 2},
        {"three", 3},
        {"four", 4},
        {"five", 5},
        {"six", 6},
        {"seven", 7},
        {"eight", 8},
        {"nine", 9},
#endif
    };    

    const auto Splitted = split_string(mAdjustments, '\n');
    int line = 1;
    for (const std::string& Line : Splitted) {
        // Find the calibration
        int first_num = -1;
        int first_pos = 9999;
        int last_num = -1;
        int last_pos = -1;

        for (const auto[num_str, num] : WrittenNumbers) {
            const int Pos = (int)Line.find(num_str);
            if ( Pos != std::string::npos) {
                if (Pos < first_pos) {
                    first_pos = Pos;
                    first_num = num;
                }

                // The line might contain the same number multiple times like "3343"
                const int Last = get_last_from_line(Line, num_str, 0);
                if (Last > last_pos) {
                    last_pos = Last;
                    last_num = num;
                }
            }
        }

        // Calibrate
        const int Adjustment = (first_num * 10) + last_num;
        mCalibration += Adjustment;
        printf("%i: %i | %i -> %i. New Calibration %i\n", line++, first_num, last_num, Adjustment, mCalibration);
    }

    return mCalibration;
}

int main(int argc, char** argv) {
    ASSERT_EQ(argc > 1, "pass a filepath to the input file as the only argument './calibrator.o <path>'");

    const std::string Input = read_file_contents(argv[1]);
    Calibrator calibrator(Input);
    printf("Result: %i\n", calibrator.get_calibration());

    return 0;
}
