#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

std::string parseBeforeDot(std::string parsedStr) {
  std::string result;
  for (char c : parsedStr) {
    if (c == '.')
      break;
    result += c;
  }
  return result;
}

int main(int argc, char *argv[]) {
  // argv[1] = FILEPATH
  // argv[2] = iterations
  // argv[3] = "work.cpp"
  // argv[4] = "check.cpp"
  // argv[5] = "gen.cpp"
  // argv[6] = "work.txt"
  // argv[7] = "check.txt"
  // argv[8] = "test.txt"
  // argv[9] = create settings if exist

  size_t iterations;
  std::string FILEPATH;
  std::string settings = "settings.txt";
  std::string commandCompileWork, commandCompileCheck, commandCompileGen;
  std::string commandLaunchWork, commandLaunchCheck, commandLaunchGen;
  std::string commandRmWork, commandRmCheck, commandRmGen;
  std::string workName, checkName, genName;
  std::string argvWork, argvCheck, argvGen;
  std::string argvWorkT, argvCheckT, argvGenT;

  FILEPATH = std::string(argv[1]);
  iterations = atoi(argv[2]);
  if (std::filesystem::exists(FILEPATH + settings)) {
    std::ifstream input(FILEPATH + settings);
    input >> argvWork >> argvCheck >> argvGen;
    input >> argvWorkT >> argvCheckT >> argvGenT;
  } else {
    argvWork = std::string(argv[3]);
    argvCheck = std::string(argv[4]);
    argvGen = std::string(argv[5]);
    argvWorkT = std::string(argv[6]);
    argvCheckT = std::string(argv[7]);
    argvGenT = std::string(argv[8]);
    if (argc >= 9) {
      std::ofstream setSettings(FILEPATH + settings);
      setSettings << argvWork << "\n" << argvCheck << "\n" << argvGen << "\n";
      setSettings << argvWorkT << "\n" << argvCheckT << "\n" << argvGenT;
      std::cout << "Settings set\n";
    }
  }

  std::ifstream workOutput, checkOutput;
  workOutput.open(argvWorkT);
  checkOutput.open(argvCheckT);

  workName = parseBeforeDot(argvWork);
  checkName = parseBeforeDot(argvCheck);
  genName = parseBeforeDot(argvGen);

  commandCompileWork =
      "clang++ " + FILEPATH + argvWork + " -std=c++20 " + " -o " + FILEPATH + workName;
  commandCompileCheck =
      "clang++ " + FILEPATH + argvCheck + " -std=c++20 " + " -o " + FILEPATH + checkName;
  commandCompileGen =
      "clang++ " + FILEPATH + argvGen + " -std=c++20 " + " -o " + FILEPATH + genName;

  commandLaunchWork = FILEPATH + "./" + workName + " < " + FILEPATH + argvGenT +
                      " > " + FILEPATH + argvWorkT;
  commandLaunchCheck = FILEPATH + "./" + checkName + " < " + FILEPATH +
                       argvGenT + " > " + FILEPATH + argvCheckT;
  commandLaunchGen = FILEPATH + "./" + genName + " > " + FILEPATH + argvGenT;

  commandRmWork = "rm " + FILEPATH + workName;
  commandRmCheck = "rm " + FILEPATH + checkName;
  commandRmGen = "rm " + FILEPATH + genName;

  std::stringstream workR, checkR;

  std::system(commandCompileWork.c_str());
  std::system(commandCompileCheck.c_str());
  std::system(commandCompileGen.c_str());
  std::cout << "Compiled\n";

  for (int i = 0; i < iterations; i++) {
    std::system(commandLaunchGen.c_str());
    std::system(commandLaunchWork.c_str());
    std::system(commandLaunchCheck.c_str());
    workR << workOutput.rdbuf();
    checkR << checkOutput.rdbuf();
    while (workR.rdbuf()->in_avail() != 0 && checkR.rdbuf()->in_avail() != 0) {
      std::string readSomeWork, readSomeCheck;
      workR >> readSomeWork;
      checkR >> readSomeCheck;
      if (readSomeWork != readSomeCheck) {
        std::cout << "Test " << i + 1 << " wrong!\n";
        goto breakFlag;
      }
    }
    std::cout << "Test " << i + 1 << " passed\n";
  }

breakFlag:
  std::system(commandRmWork.c_str());
  std::system(commandRmCheck.c_str());
  std::system(commandRmGen.c_str());
  std::cout << "Removed\n";
  return 0;
}
