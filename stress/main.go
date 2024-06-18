package stress

import (
	"flag"
	"fmt"
	"os"
	"strconv"
)

func main() {
	args := flag.Args()
	iters, err := strconv.Atoi(args[0])
	if err != nil {
		fmt.Fprint(os.Stderr, "Wrong arguments!\n")
		return
	}
	cfg, err := readConfig(cfgFilename)
	if err != nil {
		return
	}
	for i := 0; i < iters; i++ {
		//TODO
	}
}
