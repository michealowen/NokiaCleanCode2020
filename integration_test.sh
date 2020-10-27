#!/usr/bin/env bash
# Uncomment below line for debug
# set -x
EXECUTABLE=$1
USE_VALGRIND=0
shift

if [ $# -ge 1 ]; then
    TC_DIR=$1/testcases/
    shift

    VALGRIND=$1
    VALGRIND_OPTS=""
    while [ $# -ne 0 ]; do
        VALGRIND_OPTS="${VALGRIND_OPTS} $1"
        shift
    done

    if [ ! -z "${VALGRIND_OPTS}" ]; then
        USE_VALGRIND=1
    fi
else
    TC_DIR=./testcases/
fi

errors=0
passed=0
inputs=$(ls ${TC_DIR}/case-*-input.txt)
for input in ${inputs}; do
    caseId=$(echo "$(basename ${input})" | cut -d "-" -f2)
    expected="${TC_DIR}/case-${caseId}-output.txt"
    actual="actual-${caseId}-output.txt"

    if [ ${USE_VALGRIND} -eq 1 ];then 
        valgrind_log=./Testing/Temporary/MemoryChecker-it-${caseId}.log
        ${VALGRIND} ${VALGRIND_OPTS} --log-file=${valgrind_log} $EXECUTABLE $input  > ${actual}
        if bash check_valgrind.sh "${valgrind_log}" ; then 
            echo "Valgrind report contains no error..."
        else
            echo -e "Valgrind contains failure for ${input}... Collecting errors..."
            errors=$((errors + 1))
        fi 
    else
        $EXECUTABLE $input > ${actual}
    fi

    if [ ! -f ${actual} ]; then
        echo -e "Case ${caseId} is failing due to no output generated!"
        errors=$((errors + 1))
    elif diff ${actual} ${expected} > /dev/null ; then
        echo "Case ${caseId} passed now..."
        passed=$((passed + 1))
    else
        echo -e "Case ${caseId} generated wrong outputs! See also diff as below"
        diff ${actual} ${expected}
        errors=$((errors + 1))
    fi
done

echo "Totally ${passed} passed, ${errors} failed..."
exit ${errors}