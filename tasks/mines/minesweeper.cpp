#include "minesweeper.h"
#include <iostream>
size_t Minesweeper::Coordinate(Cell my_cell) {
    return my_cell.x + my_cell.y * width_field_;
}
void Minesweeper::NewGame(size_t width, size_t height, size_t mines_count) {
    std::vector<size_t> mines_location;
    Cell default_cell;
    closed_cells_ = width * height - mines_count;
    width_field_ = width;
    height_field_ = height;
    game_field_.clear();
    event_status_ = GameStatus::NOT_STARTED;
    for (size_t j = 0; j < height * width; ++j) {
        default_cell.x = j % width;
        default_cell.y = j / width;
        game_field_.push_back(default_cell);
        mines_location.push_back(j);
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(mines_location.begin(), mines_location.end(), g);
    for (size_t j = 0; j < mines_count; ++j) {
        game_field_[mines_location[j]].is_mine = true;
    }
}
void Minesweeper::NewGame(size_t width, size_t height, const std::vector<Cell>& cells_with_mines) {
    Cell default_cell;
    width_field_ = width;
    game_field_.clear();
    height_field_ = height;
    closed_cells_ = width * height - cells_with_mines.size();
    event_status_ = GameStatus::NOT_STARTED;
    for (size_t j = 0; j < height * width; ++j) {
        default_cell.x = j % width;
        default_cell.y = j / width;
        game_field_.push_back(default_cell);
    }
    for (auto& cell : cells_with_mines) {
        game_field_[cell.x + width * (cell.y)].is_mine = true;
    }
}
Minesweeper::Minesweeper(size_t width, size_t height, const std::vector<Cell>& cells_with_mines) {
    NewGame(width, height, cells_with_mines);
}
Minesweeper::Minesweeper(size_t width, size_t height, size_t mines_count) {
    NewGame(width, height, mines_count);
}
Minesweeper::GameStatus Minesweeper::GetGameStatus() {
    size_t opened_cells = 0;
    if (event_status_ != GameStatus::DEFEAT) {
        for (size_t j = 0; j < game_field_.size(); ++j) {
            if (game_field_[j].is_opened) {
                opened_cells += 1;
            }
        }
        if (opened_cells == closed_cells_) {
            event_status_ = GameStatus::VICTORY;
        }
    }
    return event_status_;
}
time_t Minesweeper::GetGameTime() const {
    if (event_status_ == GameStatus::NOT_STARTED) {
        return 0;
    } else {
        return std::time(nullptr) - begin_;
    }
}
Minesweeper::RenderedField Minesweeper::RenderField() {
    std::string row;
    print_status_game_.clear();
    if (event_status_ != GameStatus::DEFEAT) {
        for (size_t j = 0; j < game_field_.size(); ++j) {
            if (j % width_field_ == 0 && j != 0) {
                print_status_game_.push_back(row);
                row.clear();
            }
            size_t counter_mines = 0;
            if (game_field_[j].is_flag) {
                row += '?';
            } else if (game_field_[j].is_closed) {
                row += '-';
            } else {
                if (j / width_field_ + 1 < height_field_) {
                    if (game_field_[j + width_field_].is_mine) {
                        counter_mines += 1;
                    }
                }
                if (j / width_field_ + 1 < height_field_ && j % width_field_ + 1 < width_field_) {
                    if (game_field_[j + width_field_ + 1].is_mine) {
                        counter_mines += 1;
                    }
                }
                if (j / width_field_ + 1 < height_field_ && j % width_field_ >= 1) {
                    if (game_field_[j + width_field_ - 1].is_mine) {
                        counter_mines += 1;
                    }
                }
                if (j % width_field_ >= 1) {
                    if (game_field_[j - 1].is_mine) {
                        counter_mines += 1;
                    }
                }
                if (j % width_field_ + 1 < width_field_) {
                    if (game_field_[j + 1].is_mine) {
                        counter_mines += 1;
                    }
                }
                if (j / width_field_ > 0) {
                    if (game_field_[j - width_field_].is_mine) {
                        counter_mines += 1;
                    }
                }
                if (j / width_field_ > 0 && j % width_field_ >= 1) {
                    if (game_field_[j - width_field_ - 1].is_mine) {
                        counter_mines += 1;
                    }
                }
                if (j / width_field_ > 0 && j % width_field_ + 1 < width_field_) {
                    if (game_field_[j - width_field_ + 1].is_mine) {
                        counter_mines += 1;
                    }
                }
                if (counter_mines == 0) {
                    row += '.';
                } else {
                    row += std::to_string(counter_mines);
                }
            }
            if (j + 1 == game_field_.size()) {
                print_status_game_.push_back(row);
                row.clear();
            }
        }
    } else {
        for (size_t j = 0; j < game_field_.size(); ++j) {
            if (j % width_field_ == 0 && j != 0) {
                print_status_game_.push_back(row);
                row.clear();
            }
            if (game_field_[j].is_mine) {
                row += '*';
            } else {
                row += '.';
            }
        }
    }
    return print_status_game_;
}
void Minesweeper::MarkCell(const Cell& cell) {
    if (event_status_ != GameStatus::VICTORY && event_status_ != GameStatus::DEFEAT) {
        if (event_status_ == GameStatus::NOT_STARTED) {
            begin_ = std::time(nullptr);
            event_status_ = GameStatus::IN_PROGRESS;
        }
        game_field_[Coordinate(cell)].is_flag = !game_field_[Coordinate(cell)].is_flag;
    }
}
void Minesweeper::OpenCell(const Cell& cell) {
    if (event_status_ != GameStatus::VICTORY && event_status_ != GameStatus::DEFEAT) {
        if (event_status_ == GameStatus::NOT_STARTED) {
            begin_ = std::time(nullptr);
            event_status_ = GameStatus::IN_PROGRESS;
        }
        if (!game_field_[Coordinate(cell)].is_flag && !game_field_[Coordinate(cell)].is_mine) {
            Open(game_field_[Coordinate(cell)]);
        } else {
            event_status_ = GameStatus::DEFEAT;
        }
    }
}
void Minesweeper::Open(const Cell& cell) {
    //нужно посмотреть на соседей
    size_t counter_mines = 0;
    std::vector<Cell> neighbors;
    size_t coordinate = Coordinate(cell);
    if (coordinate / width_field_ + 1 < height_field_) {
        if (game_field_[Coordinate(cell) + width_field_].is_mine) {
            counter_mines += 1;
            neighbors.push_back(game_field_[Coordinate(cell) + width_field_]);
        }
    }
    if (coordinate / width_field_ + 1 < height_field_ && cell.x + 1 < width_field_) {
        if (game_field_[Coordinate(cell) + width_field_ + 1].is_mine) {
            counter_mines += 1;
            neighbors.push_back(game_field_[Coordinate(cell) + width_field_ + 1]);
        }
    }
    if (coordinate / width_field_ + 1 < height_field_ && cell.x >= 1) {
        if (game_field_[Coordinate(cell) + width_field_ - 1].is_mine) {
            counter_mines += 1;
            neighbors.push_back(game_field_[Coordinate(cell) + width_field_ - 1]);
        }
    }
    if (cell.x >= 1) {
        if (game_field_[Coordinate(cell) - 1].is_mine) {
            counter_mines += 1;
        }
        neighbors.push_back(game_field_[Coordinate(cell) - 1]);
    }
    if (cell.x + 1 < width_field_) {
        if (game_field_[Coordinate(cell) + 1].is_mine) {
            counter_mines += 1;
        }
        neighbors.push_back(game_field_[Coordinate(cell) + 1]);
    }
    if (coordinate / width_field_ > 0) {
        if (game_field_[Coordinate(cell) - width_field_].is_mine) {
            counter_mines += 1;
        }
        neighbors.push_back(game_field_[Coordinate(cell) - width_field_]);
    }
    if (coordinate / width_field_ > 0 && cell.x >= 1) {
        if (game_field_[Coordinate(cell) - width_field_ - 1].is_mine) {
            counter_mines += 1;
        }
        neighbors.push_back(game_field_[Coordinate(cell) - width_field_ - 1]);
    }
    if (coordinate / width_field_ > 0 && cell.x + 1 < width_field_) {
        if (game_field_[Coordinate(cell) - width_field_ + 1].is_mine) {
            counter_mines += 1;
        }
        neighbors.push_back(game_field_[Coordinate(cell) - width_field_ + 1]);
    }
    if (counter_mines != 0) {
        game_field_[Coordinate(cell)].is_opened = true;
        game_field_[Coordinate(cell)].is_closed = false;
    } else {
        game_field_[Coordinate(cell)].is_opened = true;
        game_field_[Coordinate(cell)].is_closed = false;
        for (const auto& space : neighbors) {
            if (!space.is_opened && !space.is_flag) {
                Minesweeper::Open(space);
            }
        }
    }
}