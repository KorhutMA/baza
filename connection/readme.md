## Описание проекта

Этот проект включает в себя несколько компонентов, предназначенных для настройки и управления сетевыми подключениями Wi-Fi на устройстве с операционной системой Linux. Он состоит из четырех основных файлов:

1. **connector.cpp** - программа для сохранения учетных данных сети (SSID и пароль) в файл и их передачи на удаленный сервер.
2. **wificon.cpp** - программа для подключения к Wi-Fi сети, используя сохраненные учетные данные.
3. **setup_network.sh** - скрипт для настройки менеджера сетей и запуска программы подключения к сети.
4. **reset_network.c** - программа для восстановления конфигурации менеджера сетей с помощью пароля.

## Список файлов

### 1. connector.cpp

- **Основная функция**: Запрашивает у пользователя имя сети (SSID) и пароль, сохраняет эти данные в файл, читает их и отправляет на удалённый сервер.
- **Функции**:
  - `saveNetworkCredentials`: Сохраняет учетные данные сети в файл.
  - `readNetworkCredentials`: Читает учетные данные сети из файла.
- **Зависимости**: Библиотеки `<iostream>`, `<fstream>`, `<string>`, `<cstdlib>`.

### 2. wificon.cpp

- **Основная функция**: Читает учетные данные сети из файла и выполняет команду подключения к Wi-Fi сети с использованием `nmcli`.
- **Функции**:
  - `readNetworkCredentials`: Читает учетные данные сети из файла.
- **Зависимости**: Библиотека `<iostream>`.

### 3. setup_network.sh

- **Основная функция**: Настраивает менеджер сетей на устройстве и запускает программу `wificon`.
- **Шаги выполнения**:
  1. Проверяет, запущен ли скрипт от имени суперпользователя.
  2. Резервирует текущую конфигурацию `/etc/NetworkManager/NetworkManager.conf`.
  3. Меняет конфигурацию менеджера сетей.
  4. Перезапускает менеджер сетей.
  5. Запускает программу `wificon`.
  6. Перезагружает систему.
  
### 4. reset_network.c

- **Основная функция**: Восстанавливает исходную конфигурацию менеджера сетей после проверки пароля.
- **Функции**:
  - `execute_command`: Выполняет переданную команду в системе.
- **Шаги выполнения**:
  1. Запрашивает у пользователя пароль.
  2. Если пароль правильный, выполняет команды для восстановления конфигурации менеджера сетей.

## Установка

1. Убедитесь, что на вашем устройстве установлены необходимые библиотеки и инструменты для компиляции C++ (например, `g++`).
2. Скомпилируйте файлы:
   ```bash
   g++ connector.cpp -o connector
   g++ wificon.cpp -o wificon
   gcc reset_network.c -o reset_network
   ```
3. Сделайте скрипт `setup_network.sh` исполняемым:
   ```bash
   chmod +x setup_network.sh
   ```

## Запуск

1. Запустите скрипт настройки с правами суперпользователя:
   ```bash
   sudo ./setup_network.sh
   ```
2. Если вы хотите восстановить прежние настройки, запустите программу с проверкой пароля:
   ```bash
   ./reset_network
   ```

## Замечания

- Убедитесь, что у вас есть доступ к удаленному серверу, указанному в `connector.cpp`.
- Не забудьте изменить путь к файлам конфигурации и сетевым данным в коде, если это необходимо для вашего окружения.
- Для запуска `wificon` необходимо, чтобы `NetworkManager` был установлен и запущен на вашем устройстве.

## Лицензия

Этот проект распространяется под лицензией MIT. Используйте и изменяйте его на ваше усмотрение.
