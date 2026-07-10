#include <iostream>
#include <string>
#include <stdexcept>
#include <cctype>
#include <sstream>

#include "board.h"

using namespace std;

int main() {
    while (true) {
        cout << "How many disks do you want? (1 ~ 5)" << endl;
        string num_disks_input_str;
        getline(cin, num_disks_input_str);

        if (num_disks_input_str.length() == 1 && toupper(num_disks_input_str[0]) == 'Q') {
            break;
        }

        int num_disks_val;
        try {
            bool is_numeric = true;
            if (num_disks_input_str.empty()) {
                is_numeric = false;
            } else {
                for (char c : num_disks_input_str) {
                    if (!isdigit(c)) {
                        is_numeric = false;
                        break;
                    }
                }
            }

            if (!is_numeric) {
                continue;
            }

            num_disks_val = std::stoi(num_disks_input_str);
            if (num_disks_val < 1 || num_disks_val > 5) {
                continue;
            }
        } catch (const std::invalid_argument& ia) {
            continue;
        } catch (const std::out_of_range& oor) {
            continue;
        }

        Board game_board(num_disks_val);
        game_board.draw();

        while (true) {
            if (game_board.win()) {
                cout << "Congratulations! You win!" << endl;
                break;
            }

            cout << "Move a disk. Format: x y (or 'H' for a hint)" << endl;
            string move_input_str;
            getline(cin, move_input_str);

            move_input_str.erase(0, move_input_str.find_first_not_of(" \t\n\r\f\v"));
            move_input_str.erase(move_input_str.find_last_not_of(" \t\n\r\f\v") + 1);

            if (move_input_str.length() == 1 && toupper(move_input_str[0]) == 'H') {
                game_board.hint();
                game_board.draw();
            } else if (move_input_str == "0 0") {
                game_board.autoplay();
            } else {
                stringstream ss(move_input_str);
                int from_rod_val = 0, to_rod_val = 0;
                char extra_char_check = 0;
                bool valid_parse = false;

                if (ss >> from_rod_val && ss >> to_rod_val) {
                    if (!(ss >> extra_char_check)) {
                        valid_parse = true;
                    }
                }

                if (valid_parse &&
                    from_rod_val >= 1 && from_rod_val <= ROD_SIZE &&
                    to_rod_val >= 1 && to_rod_val <= ROD_SIZE) {
                    game_board.move(from_rod_val - 1, to_rod_val - 1, true);
                }

                game_board.draw();
            }
        }
    }
    return 0;
}