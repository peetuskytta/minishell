#!/bin/bash
#Purpose: Show the difference of quoting in shell
#Version: 1.0
#Created: Fri Jul 15 2022
#Author: pskytta
#START#

VAR1=020202
TEST_USER=Spelodon

# Double Quotes
echo "Execute double quotes $VAR1 $TEST_USER"

# Single Quotes
echo 'Execute double quotes $VAR1 $TEST_USER'

# Reverse quotes
echo "This Hostname is: `hostname`"

#END#
