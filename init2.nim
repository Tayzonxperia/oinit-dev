import os, osproc, strformat

let star = "\e[36m*\e[0m"

echo fmt"{star} Stage 2: services"

for i in walkFiles("/init/services/*"):
    echo fmt"{star} Init service: {i}"
    discard execShellCmd(fmt"sh {i}")

echo fmt"{star} Done."

discard execShellCmd("/sbin/oinit-finale")

quit()
