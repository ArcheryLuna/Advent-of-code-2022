#include <iostream>
#include <iomanip> // E.g., std::quoted
#include <string>
#include <sstream> // E.g., std::istringstream, std::ostringstream
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <deque>
#include <array>
#include <ranges> // E.g., std::subrange, std::view 
#include <utility> // E.g., std::pair,..
#include <algorithm> // E.g., std::find, std::all_of,...
#include <numeric> // E.g., std::accumulate
#include <limits> // E.g., std::numeric_limits

extern char const* pTest;
extern char const* pData;

using Result = std::string;
using Answers = std::vector<std::pair<std::string,Result>>;

using Stack = std::stack<char>;
using Stacks = std::map<std::size_t,Stack>;
using Move = std::array<int,3>;
using Moves = std::vector<Move>;

using Model = std::pair<Stacks,Moves>;

Stacks to_stacks(std::stack<std::string> layers) {
  Stacks result{};
  while (layers.size()>0) {
    // result.push_back({});
    std::cout << "\nto_stacks layer:" << std::quoted(layers.top());
    auto layer = layers.top(); layers.pop();
    auto iter = layer.begin(); 
    auto end = iter+4;
    while (iter != layer.end()) {
      std::string crate_s{iter,end};
      iter = end;
      end = (iter+4>layer.end())?layer.end():iter+4;
    }
  }
  return result;
}

std::vector<char> to_crates(std::size_t count,std::string const& layer) {
  std::vector<char> result{};
  auto iter = layer.begin(); 
  auto end = iter+4;
  for (int i=0;i<count;++i) {
    std::string crate_s{iter,end};
    result.push_back(crate_s[1]);
    iter = end;
    end = (iter+4>layer.end())?layer.end():iter+4;
  }
  return result;
}

std::vector<std::size_t> to_indices(std::string const& entry) {
  std::vector<std::size_t> result{};
  std::istringstream is{entry};
  int index;
  while (is >> index) {
    result.push_back(index);
  }
  return result;
}

Move to_move(std::string const& entry) {
  Move result{};
  std::istringstream is{entry};
  int count,from,to;
  std::string move_s,from_s,to_s;
  // move 6 from 2 to 1
  is >> move_s >> count >> from_s >> from >> to_s >> to;
  result[0] = count;
  result[1] = from;
  result[2] = to;
  return result;
}

Model parse(auto& in) {
    Model result{};
    std::string line{};
    int state{0};
    std::stack<std::string> stack_layers{};
    while (std::getline(in,line)) {
      switch (state) {
        case 0: {
          if (line.size()==0) {
            // 1. pop indeces line and parse it into a map from index to empty Stacks
            auto indices = to_indices(stack_layers.top());
            stack_layers.pop(); 
            for (auto index : indices) {
              result.first[index] = {};
            }
            // 2. for each crates entry
            while (stack_layers.size()>0) {
              //    2.1 turn it into crates
              auto crates = to_crates(indices.size(),stack_layers.top());
              stack_layers.pop();
              //    2.2 push crates onto stacks
              for (auto index : indices) {
                if (crates[index-1] != ' ') {
                  result.first[index].push(crates[index-1]);
                }
              }
            }
            state=1;
          } 
          else {
            // read stacks
            stack_layers.push(line);
          }
        } break;
        case 1: {
          // Process moves
          auto move = to_move(line);
          result.second.push_back(move);
        } break;
      }
    }
    return result;
}

namespace part1 {
  Result solve_for(char const* pData) {
      Result result{};
      std::stringstream in{ pData };
      auto data_model = parse(in);
      for (auto const& move : data_model.second) {
        // 0: count 1:from 2:to
        for (std::size_t i = 0;i<move[0];++i) {
          auto crate = data_model.first[move[1]].top();
          data_model.first[move[1]].pop();
          data_model.first[move[2]].push(crate);
        }
      }
      for (auto const& [index,stack] : data_model.first) {
        result += stack.top();
      }
      return result;
  }
}

namespace part2 {
  Result solve_for(char const* pData) {
      Result result{};
      std::stringstream in{ pData };
      auto data_model = parse(in);
      for (auto const& move : data_model.second) {
        // 0: count 1:from 2:to
        Stack to_move{};
        for (std::size_t i = 0;i<move[0];++i) {
          auto crate = data_model.first[move[1]].top();
          data_model.first[move[1]].pop();
          to_move.push(crate);
        }
        while (to_move.size()) {
          data_model.first[move[2]].push(to_move.top());
          to_move.pop();
        }
      }
      for (auto const& [index,stack] : data_model.first) {
        result += stack.top();
      }
      return result;
  }
}

int main(int argc, char *argv[])
{
  Answers answers{};
  answers.push_back({"Part 1",part1::solve_for(pData)});
  answers.push_back({"Part 2",part2::solve_for(pData)});
  for (auto const& answer : answers) {
    std::cout << "\nanswer[" << answer.first << "] " << answer.second;
  }
  // std::cout << "\nPress <enter>...";
  // std::cin.get();
  std::cout << "\n";
  return 0;
}

char const* pTest = R"(    [D]    
[N] [C]    
[Z] [M] [P]
 1   2   3 
move 1 from 2 to 1
move 3 from 1 to 3
move 2 from 2 to 1
move 1 from 1 to 2)";
char const* pData = R"([V]     [B]                     [C]
[C]     [N] [G]         [W]     [P]
[W]     [C] [Q] [S]     [C]     [M]
[L]     [W] [B] [Z]     [F] [S] [V]
[R]     [G] [H] [F] [P] [V] [M] [T]
[M] [L] [R] [D] [L] [N] [P] [D] [W]
[F] [Q] [S] [C] [G] [G] [Z] [P] [N]
[Q] [D] [P] [L] [V] [D] [D] [C] [Z]
 1   2   3   4   5   6   7   8   9 

move 1 from 9 to 2
move 4 from 6 to 1
move 4 from 2 to 6
move 5 from 8 to 7
move 4 from 9 to 2
move 1 from 5 to 8
move 1 from 3 to 1
move 2 from 3 to 1
move 1 from 4 to 2
move 11 from 7 to 2
move 5 from 5 to 1
move 1 from 6 to 8
move 1 from 7 to 6
move 3 from 6 to 7
move 1 from 3 to 2
move 1 from 6 to 8
move 11 from 2 to 1
move 1 from 9 to 8
move 1 from 3 to 7
move 4 from 7 to 9
move 3 from 3 to 7
move 4 from 8 to 2
move 3 from 7 to 6
move 2 from 6 to 3
move 5 from 4 to 1
move 1 from 6 to 5
move 26 from 1 to 7
move 1 from 4 to 6
move 22 from 7 to 5
move 4 from 9 to 1
move 3 from 7 to 3
move 1 from 6 to 3
move 6 from 1 to 7
move 2 from 7 to 5
move 8 from 1 to 9
move 4 from 3 to 4
move 10 from 2 to 7
move 6 from 7 to 4
move 2 from 9 to 5
move 1 from 5 to 1
move 8 from 4 to 1
move 2 from 5 to 9
move 1 from 3 to 6
move 1 from 9 to 1
move 1 from 3 to 6
move 2 from 5 to 2
move 1 from 4 to 2
move 1 from 2 to 3
move 7 from 1 to 4
move 9 from 7 to 4
move 1 from 3 to 4
move 2 from 2 to 4
move 5 from 9 to 6
move 1 from 4 to 5
move 2 from 9 to 3
move 1 from 1 to 6
move 2 from 6 to 1
move 2 from 6 to 5
move 2 from 9 to 7
move 1 from 3 to 9
move 1 from 9 to 5
move 2 from 7 to 3
move 1 from 1 to 7
move 7 from 4 to 5
move 2 from 1 to 2
move 3 from 3 to 8
move 3 from 8 to 9
move 31 from 5 to 8
move 1 from 7 to 1
move 1 from 2 to 1
move 1 from 1 to 5
move 1 from 5 to 6
move 2 from 5 to 7
move 10 from 4 to 9
move 5 from 6 to 2
move 3 from 2 to 6
move 2 from 7 to 8
move 1 from 6 to 3
move 1 from 4 to 1
move 1 from 3 to 6
move 1 from 4 to 2
move 2 from 1 to 2
move 1 from 8 to 7
move 10 from 8 to 2
move 13 from 2 to 9
move 1 from 1 to 5
move 18 from 8 to 2
move 21 from 9 to 6
move 1 from 7 to 8
move 2 from 9 to 7
move 1 from 2 to 3
move 1 from 7 to 8
move 9 from 2 to 4
move 1 from 7 to 8
move 3 from 9 to 1
move 1 from 8 to 1
move 6 from 2 to 3
move 5 from 4 to 7
move 1 from 5 to 8
move 2 from 4 to 3
move 5 from 7 to 3
move 2 from 2 to 7
move 15 from 6 to 1
move 12 from 1 to 2
move 6 from 2 to 9
move 4 from 9 to 5
move 4 from 5 to 6
move 14 from 3 to 9
move 1 from 6 to 7
move 1 from 7 to 2
move 1 from 7 to 8
move 9 from 2 to 6
move 1 from 1 to 6
move 2 from 9 to 8
move 4 from 9 to 7
move 1 from 1 to 5
move 8 from 8 to 3
move 1 from 5 to 4
move 2 from 1 to 2
move 3 from 1 to 4
move 9 from 6 to 2
move 1 from 7 to 4
move 1 from 8 to 2
move 1 from 6 to 4
move 4 from 7 to 8
move 12 from 6 to 8
move 3 from 2 to 1
move 6 from 8 to 7
move 5 from 3 to 6
move 3 from 3 to 6
move 3 from 1 to 3
move 8 from 2 to 9
move 2 from 4 to 5
move 2 from 7 to 2
move 10 from 8 to 5
move 3 from 3 to 2
move 10 from 5 to 3
move 1 from 4 to 3
move 1 from 2 to 1
move 1 from 1 to 7
move 14 from 9 to 6
move 5 from 2 to 4
move 15 from 6 to 5
move 3 from 9 to 3
move 1 from 8 to 6
move 1 from 3 to 8
move 7 from 3 to 8
move 16 from 5 to 1
move 2 from 7 to 1
move 1 from 5 to 9
move 2 from 9 to 3
move 15 from 1 to 5
move 3 from 8 to 2
move 3 from 3 to 1
move 3 from 7 to 3
move 8 from 4 to 6
move 5 from 1 to 6
move 9 from 5 to 7
move 2 from 8 to 3
move 2 from 2 to 7
move 1 from 1 to 4
move 2 from 5 to 8
move 4 from 3 to 1
move 4 from 8 to 1
move 1 from 8 to 6
move 9 from 7 to 6
move 2 from 7 to 5
move 3 from 1 to 8
move 1 from 4 to 8
move 1 from 2 to 4
move 12 from 6 to 2
move 3 from 8 to 6
move 1 from 4 to 7
move 2 from 6 to 8
move 5 from 5 to 9
move 13 from 2 to 9
move 2 from 4 to 7
move 13 from 9 to 5
move 2 from 6 to 5
move 1 from 3 to 9
move 6 from 9 to 4
move 5 from 1 to 3
move 1 from 7 to 9
move 15 from 5 to 8
move 2 from 4 to 7
move 2 from 4 to 6
move 1 from 4 to 6
move 1 from 5 to 7
move 18 from 6 to 2
move 2 from 7 to 3
move 3 from 6 to 7
move 3 from 2 to 8
move 5 from 7 to 3
move 1 from 9 to 6
move 2 from 3 to 8
move 11 from 3 to 2
move 2 from 2 to 9
move 1 from 6 to 2
move 1 from 7 to 5
move 1 from 5 to 9
move 9 from 8 to 4
move 1 from 4 to 6
move 2 from 3 to 1
move 2 from 1 to 5
move 12 from 8 to 3
move 1 from 8 to 2
move 14 from 3 to 4
move 1 from 6 to 4
move 1 from 5 to 4
move 20 from 2 to 7
move 2 from 9 to 5
move 1 from 5 to 3
move 1 from 9 to 2
move 1 from 2 to 8
move 2 from 2 to 3
move 5 from 4 to 5
move 6 from 5 to 7
move 2 from 8 to 2
move 3 from 3 to 9
move 5 from 4 to 5
move 2 from 9 to 7
move 2 from 2 to 3
move 1 from 9 to 3
move 22 from 7 to 3
move 4 from 7 to 4
move 24 from 3 to 6
move 4 from 2 to 6
move 18 from 6 to 9
move 15 from 4 to 6
move 8 from 6 to 3
move 6 from 6 to 1
move 7 from 9 to 6
move 2 from 7 to 4
move 8 from 3 to 9
move 14 from 6 to 3
move 2 from 3 to 9
move 1 from 9 to 6
move 13 from 9 to 1
move 3 from 4 to 5
move 1 from 9 to 6
move 5 from 1 to 8
move 3 from 3 to 9
move 2 from 1 to 5
move 8 from 5 to 8
move 10 from 3 to 5
move 3 from 4 to 6
move 6 from 1 to 9
move 4 from 5 to 3
move 5 from 8 to 2
move 6 from 6 to 3
move 7 from 3 to 6
move 1 from 3 to 4
move 5 from 8 to 7
move 5 from 2 to 6
move 2 from 7 to 3
move 3 from 7 to 3
move 1 from 4 to 9
move 9 from 6 to 9
move 2 from 6 to 2
move 1 from 8 to 2
move 2 from 8 to 7
move 5 from 1 to 5
move 1 from 1 to 4
move 13 from 5 to 7
move 5 from 3 to 7
move 1 from 5 to 6
move 1 from 4 to 6
move 3 from 2 to 8
move 1 from 3 to 5
move 1 from 3 to 8
move 14 from 7 to 4
move 1 from 5 to 6
move 7 from 6 to 9
move 6 from 7 to 9
move 2 from 8 to 9
move 2 from 8 to 1
move 31 from 9 to 1
move 13 from 4 to 2
move 1 from 4 to 3
move 10 from 2 to 7
move 1 from 3 to 4
move 1 from 2 to 7
move 3 from 7 to 8
move 1 from 4 to 1
move 3 from 8 to 5
move 32 from 1 to 5
move 3 from 9 to 7
move 4 from 9 to 6
move 2 from 2 to 7
move 2 from 1 to 7
move 1 from 6 to 1
move 1 from 9 to 4
move 3 from 6 to 4
move 1 from 1 to 8
move 15 from 5 to 1
move 1 from 8 to 4
move 9 from 5 to 7
move 1 from 9 to 8
move 1 from 8 to 1
move 10 from 1 to 9
move 1 from 4 to 2
move 2 from 9 to 5
move 4 from 9 to 6
move 1 from 2 to 7
move 3 from 4 to 2
move 1 from 1 to 5
move 5 from 1 to 5
move 1 from 4 to 9
move 3 from 6 to 7
move 23 from 7 to 6
move 1 from 2 to 4
move 1 from 2 to 5
move 9 from 5 to 4
move 1 from 2 to 5
move 9 from 5 to 6
move 1 from 9 to 7
move 1 from 9 to 3
move 3 from 9 to 4
move 14 from 6 to 3
move 5 from 7 to 4
move 1 from 7 to 5
move 1 from 5 to 9
move 2 from 5 to 6
move 16 from 6 to 2
move 2 from 6 to 1
move 7 from 4 to 8
move 2 from 1 to 2
move 4 from 3 to 5
move 5 from 4 to 7
move 2 from 6 to 7
move 4 from 4 to 1
move 4 from 8 to 9
move 1 from 4 to 5
move 1 from 6 to 8
move 1 from 4 to 9
move 4 from 1 to 7
move 1 from 9 to 4
move 2 from 2 to 7
move 7 from 3 to 9
move 15 from 2 to 3
move 4 from 8 to 6
move 1 from 4 to 7
move 2 from 9 to 7
move 1 from 6 to 8
move 2 from 7 to 2
move 5 from 7 to 2
move 1 from 5 to 2
move 6 from 2 to 9
move 3 from 7 to 1
move 3 from 1 to 2
move 3 from 7 to 1
move 2 from 2 to 9
move 2 from 6 to 9
move 1 from 8 to 3
move 19 from 3 to 9
move 1 from 6 to 3
move 3 from 7 to 4
move 1 from 2 to 5
move 2 from 1 to 9
move 2 from 2 to 3
move 33 from 9 to 7
move 1 from 1 to 7
move 3 from 3 to 7
move 1 from 3 to 2
move 1 from 5 to 8
move 4 from 9 to 7
move 1 from 5 to 2
move 2 from 4 to 9
move 4 from 9 to 7
move 3 from 2 to 1
move 1 from 4 to 3
move 1 from 9 to 7
move 1 from 8 to 3
move 7 from 7 to 3
move 3 from 1 to 9
move 4 from 9 to 7
move 4 from 5 to 8
move 3 from 3 to 4
move 3 from 4 to 5
move 3 from 3 to 6
move 2 from 6 to 5
move 38 from 7 to 5
move 40 from 5 to 3
move 4 from 8 to 9
move 1 from 6 to 9
move 1 from 5 to 1
move 3 from 7 to 6
move 1 from 7 to 5
move 38 from 3 to 8
move 1 from 1 to 9
move 3 from 9 to 6
move 5 from 3 to 9
move 4 from 8 to 6
move 1 from 7 to 1
move 3 from 5 to 9
move 1 from 1 to 2
move 10 from 8 to 3
move 5 from 8 to 1
move 3 from 1 to 2
move 9 from 6 to 7
move 9 from 3 to 5
move 1 from 7 to 6
move 1 from 3 to 8
move 1 from 7 to 9
move 1 from 1 to 5
move 1 from 1 to 3
move 1 from 9 to 2
move 4 from 2 to 3
move 1 from 2 to 4
move 9 from 8 to 1
move 2 from 9 to 5
move 2 from 1 to 2
move 2 from 3 to 4
move 6 from 8 to 6
move 10 from 5 to 3
move 7 from 3 to 2
move 2 from 1 to 2
move 5 from 1 to 7
move 7 from 9 to 6
move 7 from 6 to 5
move 1 from 4 to 3
move 7 from 7 to 4
move 5 from 3 to 9
move 7 from 2 to 6
move 4 from 7 to 8
move 5 from 8 to 9
move 1 from 2 to 6
move 1 from 3 to 5
move 2 from 2 to 8
move 8 from 4 to 6
move 7 from 9 to 7
move 4 from 7 to 9
move 7 from 9 to 3
move 8 from 3 to 1
move 6 from 5 to 9
move 8 from 1 to 8
move 13 from 8 to 4
move 3 from 9 to 6
move 1 from 8 to 6
move 1 from 7 to 3
move 2 from 4 to 1
move 5 from 9 to 1
move 1 from 3 to 7
move 15 from 6 to 1
move 1 from 7 to 9
move 10 from 4 to 7
move 11 from 7 to 5
move 17 from 1 to 6
move 1 from 9 to 3
move 6 from 6 to 1
move 3 from 5 to 3
move 2 from 4 to 5
move 2 from 7 to 8
move 12 from 5 to 3
move 13 from 6 to 9
move 2 from 8 to 2
move 2 from 5 to 1
move 16 from 3 to 8
move 3 from 2 to 3
move 2 from 3 to 7
move 2 from 7 to 9
move 1 from 3 to 7
move 4 from 8 to 4
move 2 from 4 to 8
move 5 from 1 to 5
move 2 from 4 to 7
move 6 from 6 to 8
move 2 from 8 to 5
move 2 from 1 to 4
move 5 from 8 to 7
move 5 from 6 to 3
move 6 from 9 to 8
move 2 from 9 to 2
move 1 from 1 to 7
move 4 from 5 to 3
move 2 from 2 to 3
move 1 from 4 to 9
move 10 from 3 to 6
move 1 from 3 to 7
move 10 from 7 to 2
move 2 from 5 to 3
move 1 from 4 to 2
move 2 from 6 to 8
move 3 from 6 to 5
move 1 from 6 to 1
move 7 from 2 to 3
move 6 from 8 to 7
move 4 from 6 to 3
move 14 from 8 to 6
move 11 from 6 to 8
move 1 from 1 to 4
move 6 from 7 to 2
move 3 from 5 to 8
move 4 from 1 to 7
move 1 from 2 to 8
move 1 from 2 to 6
move 1 from 3 to 4
move 1 from 5 to 6
move 7 from 8 to 6
move 9 from 3 to 2
move 1 from 8 to 5)";