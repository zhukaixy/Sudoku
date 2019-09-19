#! /usr/bin/env bash

exitWhileError(){
    if test $? -ne 0 ; then
        echo "
        Error Message: $1
        Please Check The Error And Test Again! Exit Now.
        " 1>&2
        exit
    fi
}

ScriptExe=$0
while [ -h ${ScriptExe} ]; do
    ScriptRootDir=$(cd -P $(dirname ${ScriptExe}) && pwd)
    ScriptExe=$(readlink ${ScriptExe})
    [[ ${ScriptExe} != /* ]] && ScriptExe=${ScriptRootDir}/${ScriptExe}
done
ScriptRootDir=$(cd -P $(dirname ${ScriptExe}) && pwd)

AllDemos=(
	"for-c"
	"for-cs"
	"for-go"
	"for-java"
);

for demo in ${AllDemos[@]}; do
	cd ${ScriptRootDir}/${demo} && make && make run
	exitWhileError "run ${demo} failed"
done
