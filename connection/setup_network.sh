#!/bin/bash

if [[ $EUID -ne 0 ]]; then
   echo "Этот скрипт должен быть запущен с правами суперпользователя." 
   exit 1
fi

echo "Изменяем /etc/NetworkManager/NetworkManager.conf..."
cp /etc/NetworkManager/NetworkManager.conf /etc/NetworkManager/NetworkManager.conf.bak
echo -e "[main]\nplugins=\n\n[ifupdown]\nmanaged=true\n" > /etc/NetworkManager/NetworkManager.conf

echo "Перезапускаем NetworkManager..."
systemctl restart NetworkManager

echo "Перезагружаем систему..."
reboot
