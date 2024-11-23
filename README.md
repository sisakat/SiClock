# Good Old Clock Widget

A small cross-platform executable that displays an analog clock.
It ships with various designs and can easily be tweaked by modifying a JSON configuration file.

![Display](./docs/display.png)

## Controls

| Button           | Action                 |
|------------------|------------------------|
| Left mouse down  | Moves the widget       |
| Right mouse down | Changes the clock face |
| Mouse wheel      | Scales the clock       |

## Todos

- Remove the application from the task bar and move it to the notification area.
- Save and load the state from configuration directories (currently working directory).

## Copyright and license

The source code of this project is licensed under Zlib.
The clock faces and graphics included in this project are licensed under CC BY 4.0.

This project uses raylib (Zlib) for rendering and nlohmann json (MIT) for reading and writing JSON files.
