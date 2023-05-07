#!/bin/sh

set -e

MYSQL_ROOT_PASSWORD=${MYSQL_ROOT_PASSWORD:-docker}
MYSQL_DATABASE=${MYSQL_DATABASE:-}
MYSQL_USER=${MYSQL_USER:-}
MYSQL_PASSWORD=${MYSQL_PASSWORD:-}
MYSQLD_ARGS=${MYSQLD_ARGS:-}

chown -R mysql:mysql /var/lib/mysql

# make sure that the run directory exists & has the right permissions
if [ ! -d "/run/mysqld" ]
then
  mkdir /run/mysqld
  chown mysql:mysql /run/mysqld
fi

# only bootstrap if /var/lib/mysql is empty
if [ ! "$(ls -A /var/lib/mysql)" ];
then
  echo "==================================="
  echo "Bootstrapping system database...";echo

  # shellcheck disable=SC2086
  /usr/bin/mysql_install_db ${MYSQLD_ARGS} --user=mysql --datadir=/var/lib/mysql

  echo "Bootstrap of system db complete!"
  echo "===================================";echo

  echo "==================================="
  echo "Bootstrapping new database...";echo

  # create a sql file to bootstrap db
# create a sql file used to bootstrap the environment
  TEMP_FILE="$(mktemp)"
  if [ ! -f "${TEMP_FILE}" ];
  then
    echo "error: unable to create temp file; exiting"
    exit 1
  fi

  cat << EOF > "${TEMP_FILE}"
# drop test database
DROP DATABASE IF EXISTS test;

# update user access to allow root login from all hosts and set a password for root
CREATE DATABASE IF NOT EXISTS mysql;
USE mysql;
FLUSH PRIVILEGES;
CREATE OR REPLACE USER 'root'@'%' IDENTIFIED BY "${MYSQL_ROOT_PASSWORD}";
GRANT ALL PRIVILEGES ON *.* TO 'root'@'%' WITH GRANT OPTION;
EOF

  # only create db if db name provided
  if [ -n "${MYSQL_DATABASE}" ];
  then
    echo "CREATE DATABASE IF NOT EXISTS \`${MYSQL_DATABASE}\` CHARACTER SET utf8 COLLATE utf8_general_ci;" >> "${TEMP_FILE}"

    # only create a non-root user if user name provided
    if [ -n "${MYSQL_USER}" ];
    then
      echo "GRANT ALL ON \`${MYSQL_DATABASE}\`.* to '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';" >> "${TEMP_FILE}"
      echo "GRANT ALL ON \`${MYSQL_DATABASE}\`.* to '${MYSQL_USER}'@'localhost' IDENTIFIED BY '${MYSQL_PASSWORD}';" >> "${TEMP_FILE}"
    fi
  fi

  # shellcheck disable=SC2086
  /usr/bin/mysqld --user=mysql --bootstrap --verbose=0 ${MYSQLD_ARGS} < "${TEMP_FILE}"
  rm -f "${TEMP_FILE}"

  echo;echo "Bootstrap of MariaDB complete"
  echo "===================================";echo
else
  echo "Bootstrapping MariaDB not neccessary; skipping.";echo
fi

echo "==================================="
echo "Launching MariaDB...";echo
# shellcheck disable=SC2086
exec /usr/bin/mysqld --user=mysql ${MYSQLD_ARGS}
