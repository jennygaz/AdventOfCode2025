#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <tuple>
#include <functional>
#include <cstdlib>
#include <vector>
#include <cmath>

constexpr int MOD = 100;
constexpr int START_VALUE = 50;

int
rotate_first(int start_point, int amount, bool left) {
  if( left )
    return (start_point - amount + MOD) % MOD;
  else
    return (start_point + amount) % MOD;
}

std::tuple<int, int>
rotate_second(int start_point, int amount, bool left) {
  const int new_amount = std::abs(amount) % MOD;
  const int next_point = (left ? start_point - new_amount : start_point + new_amount);
  const int zero_crossed_times = std::abs(amount) / MOD + (start_point != 0 and (next_point <= 0 or next_point >= 100));
  return { (next_point + MOD) % MOD, zero_crossed_times };
}

std::tuple<int, bool>
extract_direction(std::string str) {
  return {
    stoi(str.substr(1, std::string::npos)),
    str[0] == 'L'
  };
}

int
solve_first(std::vector<std::string>& strings) {
  int current_point = START_VALUE;
  int zeroes {};
  for( auto& str : strings ) {
    // std::cerr << "Started at: " << current_point << '\n'
    // 	      << "Next is >" << str << "<\n";
    auto vals = extract_direction(str);
    const int amount = std::get<0>(vals);
    const bool left = std::get<1>(vals);
    // std::cerr << "Values: (" << amount << ", " << (left ? "LEFT" : "RIGHT") << ")\n";
    current_point = rotate_first(current_point, amount, left);
    // std::cerr << "New position is " << current_point << "\n";
    if( current_point == 0 ) ++ zeroes;
  }
  return zeroes;
}

int solve_second(std::vector<std::string>& strings) {
  int current_point = START_VALUE;
  int zeroes {};
  for( auto& str : strings ) {
    // std::cerr << "Started at: " << current_point << '\n'
    // 	      << "Next is >" << str << "<\n";
    auto vals = extract_direction(str);
    const int amount = std::get<0>(vals);
    const bool left = std::get<1>(vals);
    // std::cerr << "Values: (" << amount << ", " << (left ? "LEFT" : "RIGHT") << ")\n";
    auto result = rotate_second(current_point, amount, left);
    current_point = std::get<0>(result);
    // std::cerr << "New position is " << current_point << "\n";
    // std::cerr << "Crossed zero " << std::get<1>(result) << " times\n";
    zeroes += std::get<1>(result);
  }
  return zeroes;
}

int main() {
  std::ifstream file("advent1-1.in");
  std::string line;
  std::vector<std::string> strs {};
  while( std::getline(file, line) ) {
    strs.emplace_back(line);
  }
  const int solution = solve_second(strs);
  std::cout << solution << '\n';
  return 0;
}
