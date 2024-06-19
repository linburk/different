package stress

import (
	"flag"
	"fmt"
	"os"
	"os/exec"
	"strconv"
	"time"
)

func genCmds(compileCmds, rmCmds, execCmds []string, cfg config) {
	compileCmds = compileCmdsList(cfg)
	rmCmds = append(rmCmds, rmCmdsList(cfg.filenPaths)...)
	if cfg.removetxt {
		rmCmds = append(rmCmds, rmCmdsList(cfg.outFilenPath)...)
	}
	execCmds = execCmdsList(cfg.filenPathsExec, cfg.outFilenPath)
}

func launchCmds(cmdsList ...string) {
	for _, cmd := range cmdsList {
		exec.Command(cmd)
	}
}

func compareSolves() {
	// TODO
}

func main() {

	var cfgMain config
	var execCmds []string
	var rmCmds []string
	var compileCmds []string

	args := flag.Args()
	iters, err := strconv.Atoi(args[0])
	if err != nil {
		fmt.Fprint(os.Stderr, "Wrong arguments!\n")
		return
	}
	cfgMain, err = readConfig(cfgFilename)
	if err != nil {
		return
	}
	genCmds(compileCmds, rmCmds, execCmds, cfgMain)
	launchCmds(compileCmds...)
	for i := 0; i < iters; i++ {
		launchCmds(execCmds[len(execCmds)-1])
		fmt.Printf("Test %d generated\n", i+1)
		for j, execSolveCmd := range cfgMain.filenPathsExec[:cfgMain.fileNum-1] {
			start := time.Now()
			launchCmds(execSolveCmd)
			fmt.Printf("Time %s : %s\n", cfgMain.files[j], time.Since(start))
		}
		if cfgMain.compare {
			compareSolves()
		}
	}
	launchCmds(rmCmds...)
}
