package Main

import (
	"fmt"
	"os"
	"path/filepath"
)

const cfgPath string = "~/stress_cfg/"
const cfgFilename string = "config.txt"

type config struct {
	filePath     string
	compare      bool
	removetxt    bool
	fileNum      int
	files        []string
	languages    []string
	compilators  []string
	compileFlags []string

	filenPaths     []string
	filenPathsExec []string
	outFilenPath   []string
}

func writeFilenPaths(filePath string, files []string, mode int, cfg config) (filenPaths []string) {
	for i, file := range files {
		var filenPath string
		if mode == 1 { // exec compilated
			if filepath.Ext(file) == ".py" {
				filenPath = cfg.compilators[i] + " " + filenPath + file
			} else {
				filenPath = filePath + "./" + eraseExt(file)
			}
		}
		if mode == 2 { // compilated
			if filepath.Ext(file) == ".py" {
				continue
			} else {
				filenPath = filePath + eraseExt(file)
			}
		}
		if mode == 3 { // don't change
			filenPath = filePath + file
		}
		filenPaths = append(filenPaths, filenPath)
	}
	return
}

func eraseExt(filename string) string {
	filename = filename[:len(filename)-len(filepath.Ext(filename))]
	return filename
}

func outputFilesList(cfg config) (outFiles []string) {
	for i := 0; i < cfg.fileNum; i++ {
		outFile := cfg.files[i] + ".txt"
		outFiles = append(outFiles, outFile)
	}
	return
}

func readConfig(fileName string) (cfg config, err error) {
	cfgFile, err := os.Open(cfgPath + fileName)
	defer cfgFile.Close()
	if os.IsNotExist(err) {
		cfgFile, err = newFileConfig(cfgPath + fileName)
		if err != nil {
			return
		}
		inputConfig(cfgFile)
	} else {
		fmt.Fprint(os.Stderr, "File open error\n")
		return
	}
	fmt.Fscan(cfgFile, &cfg)
	return
}
func newFileConfig(cfgName string) (cfgFile *os.File, err error) {
	cfgFile, err = os.Create(cfgPath + cfgName)
	defer cfgFile.Close()
	if err != nil {
		fmt.Print(os.Stderr, "File create error\n")
		return
	}
	return
}

func inputConfig(cfgFile *os.File) {
	var cfg config
	fmt.Print("Enter path to your code...\n")
	fmt.Scan(&cfg.filePath)
	fmt.Print("Enter number of files, last file must be generator...\n")
	fmt.Scan(&cfg.fileNum)
	if cfg.fileNum == 3 {
		fmt.Print("Check comparison? Y/n \n")
		var comparisonFlag string
		fmt.Scan(&comparisonFlag)
		if comparisonFlag == "Y" || comparisonFlag == "y" {
			cfg.compare = true
		}
	}
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
	outFiles := outputFilesList(cfg)
	cfg.outFilenPath = writeFilenPaths(cfg.filePath, outFiles, 3, cfg)
	cfg.filenPaths = writeFilenPaths(cfg.filePath, cfg.files, 2, cfg)
	cfg.filenPathsExec = writeFilenPaths(cfg.filePath, cfg.files, 1, cfg)
	fmt.Fprint(cfgFile, cfg)
}
