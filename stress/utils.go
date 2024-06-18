package stress

import (
	"fmt"
	"os"
	"path/filepath"
)

const cfgPath string = "~/stress_cfg/"
const cfgFilename string = "config.txt"

type config struct {
	codePath     string
	removetxt    bool
	fileNum      int
	files        []string
	languages    []string
	compilators  []string
	compileFlags []string
	// TODO compare      bool

}

func eraseExt(filename string) string {
	filename = filename[:len(filename)-len(filepath.Ext(filename))]
	return filename
}

func createCompilationCommands(cfg config) (compilationCommands []string) {
	for i := 0; i < cfg.fileNum; i++ {
		if cfg.languages[i] == "Python" {
			continue
		}
		compileCommand := cfg.compilators[i] + " " + cfg.compileFlags[i] + " " + cfg.codePath + cfg.files[i] + " -o " + cfg.codePath + eraseExt(cfg.files[i])
		compilationCommands = append(compilationCommands, compileCommand)
	}
	return
}
func createExecCommands(cfg config) (execCommands []string) {
	for i := 0; i < cfg.fileNum; i++ {
		var execCommand string
		if cfg.languages[i] == "Python" {
			execCommand = cfg.compilators[i] + " " + cfg.codePath + cfg.files[i]
		} else {
			execCommand = cfg.codePath + "./ " + eraseExt(cfg.files[i])
		}
		execCommands = append(execCommands, execCommand)
	}
	return
}
func createRemoveCommands(cfg config) (removeCommands []string) {
	for i := 0; i < cfg.fileNum; i++ {
		if cfg.languages[i] == "Python" {
			continue
		}
		removeCommand := "rm " + cfg.codePath + eraseExt(cfg.files[i])
		removeCommands = append(removeCommands, removeCommand)
	}
	return
}
func createTextFiles(cfg config) {
	// TODO
}

func readConfig(fileName string) (cfg config, err error) {
	cfgFile, err := os.Open(cfgPath + fileName)
	if os.IsNotExist(err) {
		cfgFile, err = newFileConfig(cfgPath + fileName)
		if err != nil {
			return
		}
		writeConfig(cfgFile)
	} else {
		fmt.Fprint(os.Stderr, "File open error\n")
		return
	}
	fmt.Fscan(cfgFile, &cfg)
	return
}
func newFileConfig(cfgName string) (cfgFile *os.File, err error) {
	cfgFile, err = os.Create(cfgPath + cfgName)
	if err != nil {
		fmt.Print(os.Stderr, "File create error\n")
		return
	}
	return
}
func writeConfig(cfgFile *os.File) {
	var cfg config
	fmt.Print("Enter path to your code...\n")
	fmt.Scan(&cfg.codePath)
	fmt.Print("Enter number of files, last file must be generator...\n")
	fmt.Scan(&cfg.fileNum)
	// TODO
	// if cfg.fileNum > 2 {
	// 	fmt.Print("Check comparison? Y/n \n")
	// 	var comparisonFlag string
	// 	fmt.Scan(&comparisonFlag)
	// 	if comparisonFlag == "Y" || comparisonFlag == "y" {
	// 		cfg.compare = true
	// 	}
	// }
	fmt.Printf("Remove .txt files? Y/n\n")
	var rmtxt string
	fmt.Scan(&rmtxt)
	if rmtxt == "Y" || rmtxt == "y" {
		cfg.removetxt = true
	}
	for i := 0; i < cfg.fileNum; i++ {
		fmt.Printf("Enter %d filename\n")
		var filename string
		fmt.Scan(&filename)
		cfg.files = append(cfg.files, filename)
	}
	for i := 0; i < cfg.fileNum; i++ {
		fmt.Printf("Enter %d file language (Python / C++ / C)\n", i+1)
		var lang string
		fmt.Scan(&lang)
		cfg.languages = append(cfg.languages, lang)
	}
	for i := 0; i < cfg.fileNum; i++ {
		fmt.Printf("Enter %d compilator (g++, python3, etc.) \n", i+1)
		var compilator string
		fmt.Scan(&compilator)
		cfg.compilators = append(cfg.compilators, compilator)
	}
	for i := 0; i < cfg.fileNum; i++ {
		fmt.Printf("Enter %d compile flags or 0 if not\n", i+1)
		var compileFlag string
		fmt.Scan(&compileFlag)
		cfg.compileFlags = append(cfg.compileFlags, compileFlag)
	}
	fmt.Fprint(cfgFile, cfg)
}
