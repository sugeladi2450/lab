#include <iostream>
#include <string>
#include <utility>

#include "board.h"
#include "queue.h"


void generate_hanoi_moves(
    const int k,
    const int from_rod,
    const int to_rod,
    const int aux_rod,
    Queue<std::pair<int, int>> &solution_moves) {
    if (k == 0) {
        return;
    }
    generate_hanoi_moves(k - 1, from_rod, aux_rod, to_rod, solution_moves);
    solution_moves.push({from_rod + 1, to_rod + 1});
    generate_hanoi_moves(k - 1, aux_rod, to_rod, from_rod, solution_moves);
}


Board::Board(const int num_disk_val) :
    num_disk(num_disk_val),
    rods{Rod(num_disk_val, 0), Rod(num_disk_val, 1), Rod(num_disk_val, 2)},
    disks(nullptr),
    history(),
    optimal_states() {

    this->disks = new Disk[this->num_disk];
    for (int i = 0; i < this->num_disk; ++i) {
        this->disks[i] = Disk(i, 3 + 2 * i);
    }

    for (int i = this->num_disk - 1; i >= 0; --i) {
        rods[0].push(this->disks[i]);
    }

    Rod sim_rods[] = {Rod(this->num_disk, 0), Rod(this->num_disk, 1), Rod(this->num_disk, 2)};
    Disk* sim_disks_temp = new Disk[this->num_disk];

    for (int i = 0; i < this->num_disk; ++i) {
        sim_disks_temp[i] = Disk(i, 3 + 2 * i);
    }
    for (int i = this->num_disk - 1; i >= 0; --i) {
        sim_rods[0].push(sim_disks_temp[i]);
    }

    auto board_state_to_string_fn = [&](Rod r_arr[]) {
        std::string str_state;
        for (int i = 0; i < ROD_SIZE; ++i) {
            str_state += r_arr[i].toString();
        }
        return str_state;
    };

    this->optimal_states.insert(board_state_to_string_fn(sim_rods));

    Queue<std::pair<int, int>> q_optimal_moves;
    generate_hanoi_moves(this->num_disk, 0, 1, 2, q_optimal_moves);

    while(!q_optimal_moves.empty()){
        std::pair<int, int> m = q_optimal_moves.front();
        q_optimal_moves.pop();

        int from_idx = m.first - 1;
        int to_idx = m.second - 1;

        if (!sim_rods[from_idx].empty()) {
             Disk d_sim = sim_rods[from_idx].top();
             if (sim_rods[to_idx].push(d_sim)) {
                 sim_rods[from_idx].pop();
             }
        }
        this->optimal_states.insert(board_state_to_string_fn(sim_rods));
    }
    delete[] sim_disks_temp;
}

Board::~Board() {
    delete[] disks;
    disks = nullptr;
}

void Board::draw() {
    Canvas canvas {};
    canvas.reset();

    for (int j = 0; j < Canvas::WIDTH; ++j) {
        canvas.buffer[Canvas::HEIGHT - 1][j] = '-';
    }

    for (int i = 0; i < ROD_SIZE; ++i) {
        rods[i].draw(canvas);
    }

    canvas.draw();
}

void Board::move(int from_rod_idx, int to_rod_idx, const bool log_move) {
    if (from_rod_idx < 0 || from_rod_idx >= ROD_SIZE ||
        to_rod_idx < 0 || to_rod_idx >= ROD_SIZE ||
        from_rod_idx == to_rod_idx) {
        return;
    }

    if (rods[from_rod_idx].empty()) {
        return;
    }

    const Disk& disk_to_move = rods[from_rod_idx].top();

    if (rods[to_rod_idx].push(disk_to_move)) {
        rods[from_rod_idx].pop();
        if (log_move) {
            history.push({from_rod_idx + 1, to_rod_idx + 1});
        }
    } else {
    }
}

bool Board::win() const {
    return rods[1].size() == static_cast<size_t>(num_disk);
}


void Board::autoplay() {
    while (!history.empty()) {
        std::pair<int, int> last_user_move = history.top();
        history.pop();

        int revert_from_rod = last_user_move.second;
        int revert_to_rod = last_user_move.first;

        std::cout << "Auto moving:" << revert_from_rod << "->" << revert_to_rod << std::endl;
        move(revert_from_rod - 1, revert_to_rod - 1, false);
        draw();
    }

    Queue<std::pair<int, int>> solution_moves;
    generate_hanoi_moves(num_disk, 0, 1, 2, solution_moves);

    while (!solution_moves.empty()) {
        std::pair<int, int> current_move = solution_moves.front();
        solution_moves.pop();

        std::cout << "Auto moving:" << current_move.first << "->" << current_move.second << std::endl;
        move(current_move.first - 1, current_move.second - 1, false);
        draw();
    }
}

void Board::hint() {
    std::string current_board_state_str = this->toString();
    if (optimal_states.count(current_board_state_str)) {
        std::cout << "You are on the optimal path!" << std::endl;
    } else {
        std::cout << "Sorry. You are not on the optimal path." << std::endl;
    }
}

std::string Board::toString() {
    std::string state;
    for (int i = 0; i < ROD_SIZE; ++i) {
        state += rods[i].toString();
    }
    return state;
}