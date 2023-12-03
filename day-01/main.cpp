#include <fstream>
#include <string>
#include <optional>
#include <cstdio>

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

// the example given on the AOC website
#define AOC_EXAMPLE_PART1 "1abc2\npqr3stu8vwx\na1b2c3d4e5f\ntreb7uchet\n"
#define AOC_EXAMPLE_PART2 "two1nine\neightwothree\nabcone2threexyz\nxtwone3four\n4nineeightseven2\nzoneight234\n7pqrstsixteen\n"

class Calibrator {
public:
    Calibrator(const std::string& adjustments)
        : mAdjustments(adjustments) {}
    ~Calibrator() {}

    int get_calibration();
private:

    int mCalibration = 0;
    std::string mAdjustments;
};

int Calibrator::get_calibration() {
    int first_num = -1;
    int last_num = -1;
    mCalibration = 0;

    auto flush = [&]() {
        [[unlikely]] if (first_num == -1) { return; } 
        ASSERT_NE(last_num == -1, "last_num is -1 :(");

        const int Adjustment = (first_num * 10) + last_num;
        mCalibration += Adjustment;
        printf("%i | %i -> %i. New Calibration %i\n", first_num, last_num, Adjustment, mCalibration);

        first_num = -1;
        last_num = -1;
    };
    
    for (const char ch : mAdjustments) {
        // Begin next number
        if (ch == '\n') {
            flush();
            continue;
        }
        else if (!std::isdigit(ch)) { continue; }

        // first number not set
        if (first_num == -1) {
            first_num = (ch - '0');
        }
        last_num = (ch - '0');
    }

    flush();
    return mCalibration;
}

int main(int argc, char** argv) {
    const std::string Input = read_file_contents("./part1-input.txt");
    printf("%s\n", Input.c_str());
    Calibrator calibrator(Input);

    printf("result: %i\n", calibrator.get_calibration());

    return 0;
}