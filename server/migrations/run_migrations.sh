#!/bin/sh

DATABASE_NAME="link-share"
OPTION="up"

if [[ -n $1 ]]; then
  DATABASE_NAME=$1
fi

echo ${DATABASE_NAME}

if [[ $(psql -l | grep ${DATABASE_NAME} | wc -l) -eq 1 ]]; then
  echo "<${DATABASE_NAME}> Database exists!"
else
  echo "<${DATABASE_NAME}> not found!. Creating..."
  createdb ${DATABASE_NAME}
fi

echo "Applying migrations..."

if [[ -n $2 && (($2 == "down") || ($2 == "up")) ]]; then
  OPTION=$2
else
  echo "Using default option(up migration)..."
fi

if [[ ${OPTION} == "up" ]]; then
  psql -d ${DATABASE_NAME} -f up.sql
elif [[ ${OPTION} == "down" ]]; then
  psql -d ${DATABASE_NAME} -f down.sql
else
  echo "Unknown option!"
fi
