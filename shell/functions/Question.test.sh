#!/bin/sh

source Question.sh

FILENAME=core
QUESTION="Remove $FILENAME"
DEFAULT="yes"
HELPMSG="The file $FILENAME is going to be removed. Is that OK?"

Question "$QUESTION" "$DEFAULT" "$HELPMSG"

echo $ANSWER
