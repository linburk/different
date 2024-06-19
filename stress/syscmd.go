package stress

func compileCmdsList(cfg config) (compilationCmds []string) {
	for i := 0; i < cfg.fileNum; i++ {
		if cfg.languages[i] == "Python" {
			continue
		}
		compileCmd := cfg.compilators[i] + " " + cfg.compileFlags[i] + " " + cfg.filenPaths[i] + " -o " + eraseExt(cfg.filenPaths[i])
		compilationCmds = append(compilationCmds, compileCmd)
	}
	return
}
func execCmdsList(execFilenPaths, outFilenPaths []string) (execCmds []string) {
	for i, txtFile := range outFilenPaths[:len(outFilenPaths)-1] {
		execCmd := execFilenPaths[i] + " < " + outFilenPaths[len(outFilenPaths)-1] + " > " + txtFile
		execCmds = append(execCmds, execCmd)
	}
	execCmdGen := execFilenPaths[len(execFilenPaths)-1] + " > " + outFilenPaths[len(outFilenPaths)-1]
	execCmds = append(execCmds, execCmdGen)
	return
}
func rmCmdsList(filenPaths []string) (removeCmds []string) {
	for _, filenPath := range filenPaths {
		removeCmd := "rm " + filenPath
		removeCmds = append(removeCmds, removeCmd)
	}
	return
}
