#pragma once

#include <string>
#include <vector>
#include <ctime>
#include <random>
class Minesweeper {
public:
    struct Cell {
        size_t x = 0;
        size_t y = 0;
        bool is_flag = false;
        bool is_mine = false;
        bool is_opened = false;
        bool is_closed = true;
    };

    enum class GameStatus {
        NOT_STARTED,
        IN_PROGRESS,
        VICTORY,
        DEFEAT,
    };

    using RenderedField = std::vector<std::string>;

    Minesweeper(size_t width, size_t height, size_t mines_count);
    Minesweeper(size_t width, size_t height, const std::vector<Cell>& cells_with_mines);

    void NewGame(size_t width, size_t height, size_t mines_count);
    void NewGame(size_t width, size_t height, const std::vector<Cell>& cells_with_mines);

    void OpenCell(const Cell& cell);
    void MarkCell(const Cell& cell);

    GameStatus GetGameStatus();
    time_t GetGameTime() const;

    RenderedField RenderField();
    size_t Coordinate(Cell my_cell);

private:
    std::vector<Cell> game_field_;
    GameStatus event_status_ = GameStatus::NOT_STARTED;
    time_t begin_;
    RenderedField print_status_game_;
    size_t width_field_;
    size_t height_field_;
    size_t closed_cells_ = 0;
    void Open(const Cell& cell);
};
