#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "logs.h"

bool is_number(const std::string &s) {
  std::string::const_iterator it = s.begin();
  while (it != s.end() && std::isdigit(*it)) ++it;
  return !s.empty() && it == s.end();
}

int main(int argc, char **argv) {
  logger::Logger logger = logger::Logger();
  if (argc < 2) {
    logger.ERROR("usage: montador <file>");
  }

  std::string inputFile = std::string(argv[1]);
  std::ifstream t = std::ifstream(inputFile);
  if (!t.good()) {
    logger.ERROR(std::string("invalid file name: ") + inputFile);
  }
  std::stringstream buffer;
  buffer << t.rdbuf();

  int fp = 0;
  std::string op = "";
  std::map<std::string, int> registers = {
      {"R0", 0},
      {"R1", 1},
      {"R2", 2},
      {"R3", 3},
  };
  std::map<std::string, std::pair<int, std::vector<std::string>>> operations = {
      {"HALT", {0, {}}},          {"LOAD", {1, {"R", "M"}}},
      {"STORE", {2, {"R", "M"}}}, {"READ", {3, {"R"}}},
      {"WRITE", {4, {"R"}}},      {"COPY", {5, {"R", "R"}}},
      {"PUSH", {6, {"R"}}},       {"POP", {7, {"R"}}},
      {"ADD", {8, {"R", "R"}}},   {"SUB", {9, {"R", "R"}}},
      {"MUL", {10, {"R", "R"}}},  {"DIV", {11, {"R", "R"}}},
      {"MOD", {12, {"R", "R"}}},  {"AND", {13, {"R", "R"}}},
      {"OR", {14, {"R", "R"}}},   {"NOT", {15, {"M"}}},
      {"JUMP", {16, {"M"}}},      {"JZ", {17, {"M"}}},
      {"JN", {18, {"M"}}},        {"CALL", {19, {"M"}}},
      {"RET", {20, {}}},          {"WORD", {21, {"M"}}},
  };
  std::vector<std::string> first_pass = std::vector<std::string>();
  logger.INFO("initiating first pass");
  for (std::string line; getline(buffer, line);) {
    if (line.find_first_not_of(" \t\n") == line.npos) {
      continue;
    }
    logger.DEBUG("line:", line);
    std::stringstream buf;
    buf.str(line);
    buf >> op;
    if (op[0] == ';') {
      logger.DEBUG("interpreting line as comment");
      continue;
    }

    if (op == "END") break;
    if (op.back() == ':') {
      registers[op.substr(0, op.size() - 1)] = fp;
      logger.DEBUG("label:", op.substr(0, op.size() - 1));
      buf >> op;
    }
    logger.DEBUG("operation:", op);
    first_pass.push_back(op);
    for (int i = 0; i < operations[op].second.size(); ++i) {
      std::string r;
      buf >> r;
      logger.DEBUG("parameter:", r);
      first_pass.push_back(r);
    }
    fp += operations[op].second.size() + (op != "WORD");
  }

  logger.INFO("initiating second pass");
  std::stringstream compiled;
  int i = 0;
  int fp2 = 0;
  for (; i < first_pass.size(); ++i) {
    std::string op = first_pass[i];
    if (op != "WORD") fp2++;

    logger.DEBUG("operation:", op);
    logger.DEBUG("translating operation", operations[op].first);
    compiled << operations[op].first
             << ((i + 1 != first_pass.size()) ? " " : "");
    for (std::string &reg : operations[op].second) {
      i++;
      fp2++;
      std::string e = i == first_pass.size() - 1 ? "" : " ";
      if (reg == "R") {
        logger.DEBUG("treating input as register:", first_pass[i]);
        compiled << first_pass[i] << e;
      } else if (reg == "M") {
        logger.DEBUG("printing input directly:", first_pass[i]);
        compiled << first_pass[i] << e;
      }
    }
  }

  logger.INFO("compilation complete, outputing to stdout");

  std::cout << fp << std::endl;
  int k = 0;
  for (auto it = registers.begin(); it != registers.end(); it++) {
    auto p = *it;
    if (p.first != "R0" && p.first != "R1" && p.first != "R2" &&
        p.first != "R3") {
      if (k++ != 0) std::cout << " ";
      std::cout << p.first << " " << p.second;
    }
  }
  std::cout << std::endl;

  logger.DEBUG("printing compiled program");
  std::cout << compiled.rdbuf() << std::endl;
}
