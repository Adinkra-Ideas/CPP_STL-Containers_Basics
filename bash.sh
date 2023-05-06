#!/bin/sh

# set default env vars
MAX_SIZE=${MAX_SIZE:-8}
MAX_CHILDREN=${MAX_CHILDREN:-5}
MEMORY_LIMIT=${MEMORY_LIMIT:-128}
LISTEN=${LISTEN:-socket}

# make sure /run/php exists
if [ ! -d /run/php ]
then
  mkdir /run/php
fi

# check to see which version of php8.x we have
if [ -d /etc/php8 ]
then
  # php8
  PHP_VER="php8"
  SOCKFILE="php-fpm8.sock"
elif [ -d /etc/php81 ]
then
  # php81
  PHP_VER="php81"
  SOCKFILE="php-fpm81.sock"
else
  echo "ERROR: unknown php version!"
  exit 1
fi

# only configure once
if [ ! -f /tmp/configured ]
then
  if [ ! "${MAX_SIZE}" = "8" ]
  then
    echo "Setting 'post_max_size' and 'upload_max_filesize' to '${MAX_SIZE}'"
    sed -i "s/post_max_size = 8M/post_max_size = ${MAX_SIZE}M/g" "/etc/${PHP_VER}/php.ini"
    sed -i "s/upload_max_filesize = 8M/upload_max_filesize = ${MAX_SIZE}M/g" "/etc/${PHP_VER}/php.ini"
  else
    echo "Using default value '${MAX_SIZE}' for 'post_max_size' and 'upload_max_filesize'"
  fi

  if [ ! "${MAX_CHILDREN}" = "5" ]
  then
    echo "Setting 'max_children' to '${MAX_CHILDREN}'"
    sed -i "s/pm.max_children = 5/pm.max_children = ${MAX_CHILDREN}/g" "/etc/${PHP_VER}/php-fpm.d/www.conf"
  else
    echo "Using default value '${MAX_CHILDREN}' for 'pm.max_children'"
  fi

  if [ "${LISTEN}" = "port" ]
  then
    echo "Disabling UNIX socket; enabling listening on TCP port 9000"
    sed -i "s#listen = /var/run/php/${SOCKFILE}#listen = 9000#g" "/etc/${PHP_VER}/php-fpm.d/www.conf"
  else
    echo "Using default value 'listen = /var/run/php/${SOCKFILE}' for 'listen'"
  fi

  if [ ! "${MEMORY_LIMIT}" = "128" ]
  then
    echo "Setting 'memory_limit' to '${MEMORY_LIMIT}'"
    sed -i "s/memory_limit = 128M/memory_limit = ${MEMORY_LIMIT}M/g" "/etc/${PHP_VER}/php.ini"
  else
    echo "Using default value '${MEMORY_LIMIT}' for 'memory_limit'"
  fi

  touch /tmp/configured
  echo "Configuration complete."
fi

exec "$@"
