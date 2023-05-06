# ft_containers
School 42 Project. My implementation of C++ 98 STL Containers

  sed -i "s#listen = 127.0.0.1:9000#listen = /var/run/php/php-fpm8.sock#g" /etc/php8/php-fpm.d/www.conf &&\
  sed -i "s#^user = nobody#user = www-data#g" /etc/php8/php-fpm.d/www.conf &&\
  sed -i "s#^group = nobody#group = www-data#g" /etc/php8/php-fpm.d/www.conf &&\
  sed -i "s#^;listen.owner = nobody#listen.owner = www-data#g" /etc/php8/php-fpm.d/www.conf &&\
  sed -i "s#^;listen.group = nobody#listen.group = www-data#g" /etc/php8/php-fpm.d/www.conf &&\
  sed -i "s#^;listen.mode = 0660#listen.mode = 0660#g" /etc/php8/php-fpm.d/www.conf &&\
  sed -i "s#^;env#env#g" /etc/php8/php-fpm.d/www.conf &&\
  sed -i "s#upload_max_filesize = 2M#upload_max_filesize = 8M#g" /etc/php8/php.ini &&\
  sed -i "s#^;opcache.enable=1#opcache.enable=1#g" /etc/php8/php.ini &&\
  sed -i "s#^;opcache.interned_strings_buffer=8#opcache.interned_strings_buffer=32#g" /etc/php8/php.ini &&\
  sed -i "s#^;opcache.max_accelerated_files=10000#opcache.max_accelerated_files=25000#g" /etc/php8/php.ini &&\
  sed -i "s#^;opcache.memory_consumption=128#opcache.memory_consumption=256#g" /etc/php8/php.ini &&\
  sed -i "s#^;opcache.save_comments=1#opcache.save_comments=1#g" /etc/php8/php.ini &&\
  sed -i "s#^;opcache.revalidate_freq=2#opcache.revalidate_freq=30#g" /etc/php8/php.ini &&\
  echo 'apc.enable_cli=1' >> /etc/php8/conf.d/apcu.ini &&\
  deluser "$(grep ':33:' /etc/passwd | awk -F ':' '{print $1}')" || true &&\
  delgroup "$(grep '^www-data:' /etc/group | awk -F ':' '{print $1}')" || true &&\
  mkdir /var/www &&\
  addgroup -g 33 www-data &&\
  adduser -D -u 33 -G www-data -s /sbin/nologin -H -h /var/www www-data &&\
  chown -R www-data:www-data /var/www
