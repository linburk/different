#include <cstdlib>
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
  // argv[1] = iterations
  // argv[2] = "work.cpp"
  // argv[3] = "check.cpp"
  // argv[4] = "gen.cpp"
  // argv[5] = "work.txt"
  // argv[6] = "check.txt"
  // argv[7] = "test.txt"
  std::string commandCompileWork, commandCompileCheck, commandCompileGen;
  std::string commandLaunchWork, commandLaunchCheck, commandLaunchGen;
  std::string commandRmWork, commandRmCheck, commandRmGen;
  std::string workName, checkName, genName;
  std::string argvWork, argvCheck, argvGen;
  std::string argvWorkT, argvCheckT, argvGenT;

  int iterations = atoi(argv[1]);
  argvWork = std::string(argv[2]);
  argvCheck = std::string(argv[3]);
  argvGen = std::string(argv[4]);
  argvWorkT = std::string(argv[5]);
  argvCheckT = std::string(argv[6]);
  argvGenT = std::string(argv[7]);

  std::ifstream workOutput, checkOutput;
  workOutput.open(argvWorkT);
  checkOutput.open(argvCheckT);

  workName = parseBeforeDot(argvWork);
  checkName = parseBeforeDot(argvCheck);
  genName = parseBeforeDot(argvCheck);

  commandCompileWork = "clang++ " + argvWork + " -o " + workName;
  commandCompileCheck = "clang++ " + argvCheck + " -o " + checkName;
  commandCompileGen = "clang++ " + argvGen + " -o " + genName;

  commandLaunchWork = "./" + workName + " < " + argvGenT + " > " + argvWorkT;
  commandLaunchCheck = "./" + checkName + " < " + argvGenT + " > " + argvCheckT;
  commandLaunchGen = "./" + genName + " > " + argvGenT;

  commandRmWork = "rm " + workName;
  commandRmCheck = "rm " + checkName;
  commandRmGen = "rm " + genName;

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
    while (workR.tellp() != std::streampos(0) &&
           checkR.tellp() != std::streampos(0)) {
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
}
