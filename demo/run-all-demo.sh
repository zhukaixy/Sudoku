#! /usr/bin/env bash

exitWhileError() {
	if test $? -ne 0; then
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

AllCommonDemos=(
	"for-c"
	"for-cs"
)

MacDemos=(
	"for-go"
	"for-java"
)

LinuxDemos=(
	"for-go"
	"for-java"
)

ARCH=$(uname -s)

for demo in ${AllCommonDemos[@]}; do
	cd ${ScriptRootDir}/${demo} && make clean && make && make run
	exitWhileError "run ${demo} failed"
done

if [ Y"${ARCH}" == Y"Darwin" ]; then
	for demo in ${MacDemos[@]}; do
		cd ${ScriptRootDir}/${demo} && make clean && make && make run
		exitWhileError "run ${demo} failed"
	done
fi

if [ Y"${ARCH}" == Y"Linux" ]; then
	for demo in ${LinuxDemos[@]}; do
		cd ${ScriptRootDir}/${demo} && make clean && make && make run
		exitWhileError "run ${demo} failed"
	done
fi
