#!/usr/bin/env bash
report=$1
if [ ! -f "$report" ]; then
    echo -e "Invalid report file = ${report}"
    exit 1
else
    errors=$(cat ${report} | sed -n "s/.*ERROR SUMMARY: \([0-9]\+\) errors.*/\1/gp")
    if [ -z "${errors}" ]; then 
        echo "No error found in ${report}"
        exit 0
    else
        echo -e "Totally ${errors} errors found in $report"
        if [ $errors -ne 0 ]; then
            cat $report
        fi
        exit ${errors}
    fi
fi