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

bool is_number(const std::string& s) {
  std::string::const_iterator it = s.begin();
  while (it != s.end() && std::isdigit(*it)) ++it;
  return !s.empty() && it == s.end();
}

int main(int argc, char** argv) {
  logger::Logger logger = logger::Logger();
  if (argc < 2) {
    logger.ERROR("usage: montador <file>");
  }
  std::ifstream t = std::ifstream(argv[1]);
  if (!t.good()) {
    logger.ERROR(std::string("invalid file name: ") + std::string(argv[1]));
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
      {"RET", {20, {}}},          {"WORD", {0, {"M"}}},
  };
  std::vector<std::string> first_pass = std::vector<std::string>();
  logger.INFO("initiating first pass");
  for (std::string line; getline(buffer, line);) {
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
    fp += operations[op].second.size() + 1;
  }

  logger.INFO("initiating second pass");
  std::stringstream compiled;
  int i = 0;
  for (; i < first_pass.size(); ++i) {
    std::string op = first_pass[i];
    if (op == "WORD") {
      logger.DEBUG("WORD:",
                   "treating as word, printing value: " + first_pass[i + 1]);
      compiled << first_pass[++i] << " ";
      continue;
    }

    logger.DEBUG("operation:", op);
    logger.DEBUG("translating opeartion", operations[op].first);
    compiled << operations[op].first << " ";
    for (std::string& reg : operations[op].second) {
      i++;
      std::string e = i == first_pass.size() - 1 ? "" : " ";
      if (reg == "R") {
        logger.DEBUG("treating input as register:", first_pass[i]);
        logger.DEBUG("translating input to: ", registers[first_pass[i]]);
        if (registers.find(first_pass[i]) == registers.end())
          logger.ERROR("unable to find identifier", first_pass[i]);
        compiled << registers[first_pass[i]] << e;
      } else if (reg == "M") {
        logger.DEBUG("treating input as number");
        if (registers.find(first_pass[i]) == registers.end()) {
          if (!is_number(first_pass[i]))
            logger.ERROR("unknown identifier:", first_pass[i]);
          logger.DEBUG("printing input directly:", first_pass[i]);
          compiled << first_pass[i] << e;
        } else {
          logger.DEBUG("identifier", first_pass[i], "found, printing",
                       registers[first_pass[i]]);
          compiled << (registers[first_pass[i]] - i - 1) << e;
        }
      }
    }
  }
  logger.INFO("compilation complete, outputing to stdout");
  logger.DEBUG("printing header");
  std::cout << "MV-EXE" << std::endl;
  logger.DEBUG("printing program information.", "size:", i - 1);
  std::cout << (i - 1) << " 100 999 100" << std::endl;
  logger.DEBUG("printing compiled program");
  std::cout << compiled.rdbuf() << std::endl;
}
